import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Window {
    id: root
    width: 800
    height: 480
    visible: true
    title: qsTr("Pi Agent MP3 Station - Hi-Fi Studio")
    color: "#121212"

    // 檔案選擇器器 (專門挑選 MP3/Audio)
    FileDialog {
        id: fileDialog
        title: "選擇 MP3 檔案"
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

        // ==================== 左側：唱片封面與控制面板 ====================
        ColumnLayout {
            Layout.preferredWidth: 380
            Layout.fillHeight: true
            spacing: 15

            // 1. 唱片封面 (帶旋轉效果)
            Rectangle {
                Layout.alignment: Qt.AlignHCenter
                implicitWidth: 180
                implicitHeight: 180
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

                    // 當播放時旋轉封面
                    RotationAnimation on rotation {
                        running: player.isPlaying
                        from: 0
                        to: 360
                        loops: Animation.Infinite
                        duration: 10000
                    }
                }
            }

            // 2. 歌名與歌手資訊
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4

                Text {
                    Layout.fillWidth: true
                    text: player.currentTrackTitle
                    color: "#FFFFFF"
                    font.pixelSize: 20
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                }

                Text {
                    Layout.fillWidth: true
                    text: player.currentArtist
                    color: "#1DB954"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                }
            }

            // 3. 播放進度條
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

            // 4. 播放控制按鈕區 (Prev / Play / Next)
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 15

                Button {
                    text: "⏮"
                    font.pixelSize: 20
                    onClicked: player.previousTrack()
                }

                Button {
                    implicitWidth: 60
                    implicitHeight: 60
                    text: player.isPlaying ? "⏸" : "▶"
                    font.pixelSize: 26
                    onClicked: player.playPause()
                    background: Rectangle {
                        color: parent.down ? "#1AA34A" : "#1DB954"
                        radius: 30
                    }
                }

                Button {
                    text: "⏭"
                    font.pixelSize: 20
                    onClicked: player.nextTrack()
                }
            }

            // 5. 音量控制區
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 8
                Text { text: "🔊"; color: "#AAAAAA"; font.pixelSize: 16 }
                Slider {
                    implicitWidth: 140
                    from: 0.0
                    to: 1.0
                    value: player.volume
                    onValueChanged: player.setVolume(value)
                }
            }
        }

        // ==================== 右側：播放清單 (Playlist) ====================
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: "播放清單"
                    color: "#FFFFFF"
                    font.pixelSize: 18
                    font.bold: true
                }
                Item { Layout.fillWidth: true }

                // 開啟檔案選單按鈕
                Button {
                    text: "➕ 新增音樂"
                    onClicked: fileDialog.open()
                }
            }

            // 播放清單列表
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

    // 時間毫秒轉 mm:ss 輔助函式
    function formatTime(ms) {
        if (!ms || ms <= 0) return "00:00"
        var totalSeconds = Math.floor(ms / 1000)
        var minutes = Math.floor(totalSeconds / 60)
        var seconds = totalSeconds % 60
        return (minutes < 10 ? "0" + minutes : minutes) + ":" + (seconds < 10 ? "0" + seconds : seconds)
    }
}
