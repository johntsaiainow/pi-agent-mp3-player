import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Window {
    id: root
    visible: true
    title: qsTr("Pi Agent MP3 Station - Hi-Fi Studio")
    color: "#121212"

    // Auto-adapt to display resolution while maintaining 800x480 ratio fallback
    width: Screen.width > 0 ? Screen.width : 800
    height: Screen.height > 0 ? Screen.height : 480
    visibility: Window.FullScreen

    // File Dialog for Selecting MP3/Audio
    FileDialog {
        id: fileDialog
        title: "Select MP3 File"
        currentFolder: "file:///home/john/Music"
        nameFilters: ["Audio Files (*.mp3 *.flac *.wav *.m4a)"]
        fileMode: FileDialog.OpenFiles
        onAccepted: {
            player.addFilesToPlaylist(fileDialog.selectedFiles)
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 20

        // ==================== Left Column: Album Art & Controls ====================
        ColumnLayout {
            Layout.preferredWidth: parent.width * 0.45
            Layout.fillHeight: true
            spacing: 12

            // 1. Album Art (Rotating Disk Effect)
            Rectangle {
                Layout.alignment: Qt.AlignHCenter
                implicitWidth: Math.min(parent.width * 0.5, 180)
                implicitHeight: implicitWidth
                color: "#1E1E1E"
                radius: 12
                border.color: "#333333"
                border.width: 1

                Image {
                    id: coverImage
                    anchors.fill: parent
                    anchors.margins: 6
                    source: player.coverArtUrl
                    fillMode: Image.PreserveAspectFit
                    mipmap: true

                    RotationAnimation on rotation {
                        running: player.isPlaying
                        from: 0
                        to: 360
                        loops: Animation.Infinite
                        duration: 10000
                    }
                }
            }

            // 2. Track Title & Artist Info
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4

                Text {
                    Layout.fillWidth: true
                    text: player.currentTrackTitle !== "" ? player.currentTrackTitle : "No Track Selected"
                    color: "#FFFFFF"
                    font.pixelSize: 18
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                }

                Text {
                    Layout.fillWidth: true
                    text: player.currentArtist !== "" ? player.currentArtist : "Unknown Artist"
                    color: "#1DB954"
                    font.pixelSize: 13
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                }
            }

            // 3. Playback Position Slider
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 2

                Slider {
                    Layout.fillWidth: true
                    from: 0
                    to: player.duration > 0 ? player.duration : 1
                    value: player.position
                    onMoved: player.setPosition(value)
                }

                RowLayout {
                    Layout.fillWidth: true
                    Text {
                        text: formatTime(player.position)
                        color: "#888888"
                        font.pixelSize: 11
                    }
                    Item { Layout.fillWidth: true }
                    Text {
                        text: formatTime(player.duration)
                        color: "#888888"
                        font.pixelSize: 11
                    }
                }
            }

            // 4. Transport Controls (Prev / Play / Next)
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 15

                Button {
                    text: "⏮"
                    font.pixelSize: 20
                    onClicked: player.previousTrack()
                }

                Button {
                    implicitWidth: 56
                    implicitHeight: 56
                    text: player.isPlaying ? "⏸" : "▶"
                    font.pixelSize: 24
                    onClicked: player.playPause()
                    background: Rectangle {
                        color: parent.down ? "#1AA34A" : "#1DB954"
                        radius: 28
                    }
                }

                Button {
                    text: "⏭"
                    font.pixelSize: 20
                    onClicked: player.nextTrack()
                }
            }

            // 5. Volume Slider
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 8
                Text { text: "🔊"; color: "#AAAAAA"; font.pixelSize: 15 }
                Slider {
                    implicitWidth: 130
                    from: 0.0
                    to: 1.0
                    value: player.volume
                    onValueChanged: player.setVolume(value)
                }
            }
        }

        // ==================== Right Column: Playlist ====================
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: "Playlist"
                    color: "#FFFFFF"
                    font.pixelSize: 18
                    font.bold: true
                }
                Item { Layout.fillWidth: true }

                Button {
                    text: "+ Add Music"
                    onClicked: fileDialog.open()
                }
            }

            // Playlist ListView Container
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#181818"
                radius: 8
                border.color: "#282828"

                ListView {
                    id: playlistView
                    anchors.fill: parent
                    anchors.margins: 5
                    clip: true
                    model: player.playlist

                    delegate: Rectangle {
                        width: playlistView.width
                        height: 45
                        color: index === player.currentIndex ? "#282828" : (mouseArea.containsMouse ? "#202020" : "transparent")
                        radius: 4

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 10
                            anchors.rightMargin: 10
                            spacing: 10

                            Text {
                                text: (index + 1).toString()
                                color: index === player.currentIndex ? "#1DB954" : "#666666"
                                font.pixelSize: 12
                                Layout.preferredWidth: 20
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                Text {
                                    text: modelData.title
                                    color: index === player.currentIndex ? "#1DB954" : "#FFFFFF"
                                    font.pixelSize: 13
                                    font.bold: index === player.currentIndex
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Text {
                                    text: modelData.artist
                                    color: "#888888"
                                    font.pixelSize: 11
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                            }
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: player.playAtIndex(index)
                        }
                    }
                }
            }
        }
    }

    // Helper Function: Format milliseconds to mm:ss
    function formatTime(ms) {
        if (!ms || ms <= 0) return "00:00"
        var totalSeconds = Math.floor(ms / 1000)
        var minutes = Math.floor(totalSeconds / 60)
        var seconds = totalSeconds % 60
        return (minutes < 10 ? "0" + minutes : minutes) + ":" + (seconds < 10 ? "0" + seconds : seconds)
    }
}
