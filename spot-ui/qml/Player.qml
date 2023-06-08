import QtQuick.Controls
import QtQuick
import Styles 1.0

Rectangle {
  width: parent.width
  height: 150
  anchors.bottom: parent.bottom
  anchors.left: parent.left
  color: Style.colorPlayerBG

  RoundButton {
    id: button_play_pause
    radius: 75
    anchors.centerIn: parent

    contentItem: Image {
      id: button_play_pause_image
      anchors.fill: parent
      source: "qrc:/spotify-qml/imports/Images/play.svg"
    }
  }  
}