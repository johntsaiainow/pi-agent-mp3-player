import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    width: 800
    height: 480
    visible: true
    title: qsTr("Pi Agent MP3 Station")
    color: "#121212"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // 曲目名稱顯示
        Text {
            Layout.alignment: Qt.AlignHCenter
            text: player.currentTrackTitle
            color: "#FFFFFF"
            font.pixelSize: 24
            font.bold: true
            elide: Text.ElideRight
        }

        // 播放進度條
        Slider {
            Layout.fillWidth: true
            from: 0
            to: player.duration > 0 ? player.duration : 1
            value: player.position
            onMoved: player.setPosition(value)
        }

        // 播放 / 暫停按鈕
        Button {
            Layout.alignment: Qt.AlignHCenter
            implicitWidth: 80
            implicitHeight: 80
            text: player.isPlaying ? "⏸" : "▶"
            font.pixelSize: 32
            onClicked: player.playPause()
            background: Rectangle {
                color: parent.down ? "#1DB954" : "#282828"
                radius: 40
            }
        }

        // 音量控制條
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10
            Text { 
                text: "🔊"
                color: "#AAAAAA"
                font.pixelSize: 18 
            }
            Slider {
                from: 0.0
                to: 1.0
                value: player.volume
                onValueChanged: player.setVolume(value)
            }
        }
    }
}
