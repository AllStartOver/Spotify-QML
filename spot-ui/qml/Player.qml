import QtQuick.Controls
import QtQuick
import Styles 1.0

Rectangle {
  width: parent.width
  height: 150
  anchors.bottom: parent.bottom
  anchors.left: parent.left
  color: Style.colorSpotifyBlack

  RoundButton {
    id: button_play_pause
    radius: 75
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenterOffset: -25

    background: Image {
      id: button_play_pause_image
      source: "qrc:/spotify-qml/imports/Images/play2.svg"
    }
  }

  Button {
    id: trackPrev
    width: 30
    height: width

    anchors.right: button_play_pause.left
    anchors.rightMargin: 30
    anchors.verticalCenter: button_play_pause.verticalCenter

    background: Image {
      id: trackPrevImage
      source: "qrc:/spotify-qml/imports/Images/trackPrev.svg"
    }
  }

  Button {
    id: trackNext
    width: 30
    height: width

    anchors.left: button_play_pause.right
    anchors.leftMargin: 30
    anchors.verticalCenter: button_play_pause.verticalCenter

    background: Image {
      id: trackNextImage
      source: "qrc:/spotify-qml/imports/Images/trackNext.svg"
    }
  }

  Button {
    id: buttonShuffle
    width: 30
    height: width

    anchors.right: trackPrev.left
    anchors.rightMargin: 30
    anchors.verticalCenter: button_play_pause.verticalCenter

    background: Image {
      id: buttonShuffleImage
      source: "qrc:/spotify-qml/imports/Images/shuffle.svg"
    }
  }

  Button {
    id: buttonLoop
    width: 30
    height: width
    anchors.left: trackNext.right
    anchors.leftMargin: 30
    anchors.verticalCenter: button_play_pause.verticalCenter

    background: Image {
      id: buttonLoopImage
      source: "qrc:/spotify-qml/imports/Images/loop.svg"
    }
  }

  ProgressBar {
    property real progress: 0.5
    id: audioProgress
    width: parent.width / 5 * 2
    height: 5
    value: 0.5
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 25

    background: Rectangle {
      radius: 2
      color: "gray"
    }
    contentItem: Rectangle {
      id: audioProgressIndicator
      width: audioProgress.width * audioProgress.progress
      radius: 2
    }

    MouseArea {
      id: audioProgressMouseArea
      width: parent.width
      height: parent.height + 15
      anchors {
        verticalCenter: parent.verticalCenter
        horizontalCenter: parent.horizontalCenter
      }
      hoverEnabled: true
      onEntered: { audioProgressIndicator.color = "green" }
      onExited: { audioProgressIndicator.color = "white" }
      onClicked: { console.log("clicked") }
    }
  }
}