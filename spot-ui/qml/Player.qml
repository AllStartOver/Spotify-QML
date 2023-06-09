import QtQuick.Controls
import QtQuick
import Styles 1.0

Rectangle {
  width: parent.width
  height: 150
  anchors.bottom: parent.bottom
  anchors.left: parent.left
  color: Style.colorSpotifyBlack

  Image {
    id: button_play_pause
    height: 50
    width: height
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenterOffset: -25

    source: "qrc:/spotify-qml/imports/Images/play2.svg"

    MouseArea {
      id: button_play_pause_mouse_area
      anchors.fill: parent
      hoverEnabled: true
      onClicked: { 
        console.log("button_play_pause clicked");
        playerAPI.pausePlayback();
      }

    }
  }

  Image {
    id: trackPrev
    width: 30
    height: width

    anchors.right: button_play_pause.left
    anchors.rightMargin: 30
    anchors.verticalCenter: button_play_pause.verticalCenter

    source: trackPrevMouseArea.containsMouse ? "qrc:/spotify-qml/imports/Images/trackPrevHover.svg" : "qrc:/spotify-qml/imports/Images/trackPrev.svg"

    MouseArea {
      id: trackPrevMouseArea
      anchors.fill: parent
      hoverEnabled: true
      onClicked: { 
        console.log("trackPrev clicked");
        playerAPI.prevTrack();
      }
    }
  }

  Image {
    id: trackNext
    width: 30
    height: width

    anchors.left: button_play_pause.right
    anchors.leftMargin: 30
    anchors.verticalCenter: button_play_pause.verticalCenter

    source: trackNextMouseArea.containsMouse ? "qrc:/spotify-qml/imports/Images/trackNextHover.svg" : "qrc:/spotify-qml/imports/Images/trackNext.svg"
    MouseArea {
      id: trackNextMouseArea
      anchors.fill: parent
      hoverEnabled: true
      onClicked: { 
        console.log("trackNext clicked");
        playerAPI.nextTrack();
      }
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
    value: 0
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

    Timer {
      id: progressBarTimer
      interval: 1000
      repeat: true
      running: false
      onTriggered: {
        audioProgressIndicator.width += 1000 / playerState.durationMs * parent.width
        if (audioProgressIndicator.width >= audioProgress.width) {
          audioProgressIndicator.width = 0
          progressBarTimer.stop()
        }
      }
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
      onEntered: { audioProgressIndicator.color = Style.colorSpotifyGreen }
      onExited: { audioProgressIndicator.color = "white" }
      onClicked: { 
        console.log("audioProgress clicked");
        var progressTo = Math.round(audioProgressMouseArea.mouseX / audioProgress.width * playerState.durationMs)
        playerAPI.seekTrack(progressTo)
        audioProgressIndicator.width = audioProgressMouseArea.mouseX
      }
    }

    Connections {
      target: playerState
      onProgressMsChanged: {
        audioProgressIndicator.width = playerState.progressMs / playerState.durationMs * audioProgress.width
        progressBarTimer.start()
      }
      onDurationMsChanged: {
      }
    }
  }
}