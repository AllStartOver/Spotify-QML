import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  width: parent.width
  height: 100
  anchors.bottom: parent.bottom
  anchors.left: parent.left
  color: Style.colorSpotifyDarkGray
  border.color: "gray"
  border.width: 0.5

  Image {
    property bool isPlaying: true
    id: button_play_pause
    height: 50
    width: height
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenterOffset: -15

    source: isPlaying ? "qrc:/spotify-qml/imports/Images/pause.svg" : "qrc:/spotify-qml/imports/Images/play.svg"

    MouseArea {
      id: button_play_pause_mouse_area
      anchors.fill: parent
      hoverEnabled: true
      onClicked: { 
        if (parent.isPlaying) {
          console.log("button_pause clicked");
          playerAPI.pausePlayback();
          progressBarTimer.stop();
          parent.isPlaying = false;
        } else {
          console.log("button_play clicked");
          playerAPI.resumePlayback();
          progressBarTimer.start();
          parent.isPlaying = true;
        }
      }
    }

    Connections {
      target: playerState
      function onSignalPlayerStateUpdated() {
        // Update the Play/Pause Button;
        button_play_pause.isPlaying = playerState.isPlaying;
        if (playerState.isPlaying) progressBarTimer.start();
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

  Image {
    property bool isShuffle: false
    id: buttonShuffle
    width: 25
    height: width

    anchors.right: trackPrev.left
    anchors.rightMargin: 30
    anchors.verticalCenter: button_play_pause.verticalCenter

    source: isShuffle ? "qrc:/spotify-qml/imports/Images/shuffleEnabled.svg" : "qrc:/spotify-qml/imports/Images/shuffle.svg"

    MouseArea {
      id: buttonShuffleMouseArea
      anchors.fill: parent
      hoverEnabled: true
      onClicked: { 
        console.log("buttonShuffle clicked");
        playerAPI.toggleShuffle(!buttonShuffle.isShuffle);
        parent.isShuffle = !parent.isShuffle;
      }
    }

    Connections {
      target: playerState
      function onSignalPlayerStateUpdated() {
        buttonShuffle.isShuffle = playerState.isShuffling;
      }
    }
  }

  Image {
    property string loopMode: "off"
    id: buttonLoop
    width: 25
    height: width
    anchors.left: trackNext.right
    anchors.leftMargin: 30
    anchors.verticalCenter: button_play_pause.verticalCenter

    source: loopMode == "off" ? "qrc:/spotify-qml/imports/Images/loopOff.svg" : loopMode == "context" ? "qrc:/spotify-qml/imports/Images/loopContext.svg" : "qrc:/spotify-qml/imports/Images/loopTrack.svg"

    MouseArea {
      id: buttonLoopMouseArea
      anchors.fill: parent
      hoverEnabled: true
      onClicked: { 
        console.log("buttonLoop clicked");
        if (parent.loopMode == "off") {
          parent.loopMode = "context";
          playerAPI.setLoopMode("context");
        } else if (parent.loopMode == "context") {
          parent.loopMode = "track";
          playerAPI.setLoopMode("track");
        } else if (parent.loopMode == "track") {
          parent.loopMode = "off";
          playerAPI.setLoopMode("off");
        }
      }
    }

    Connections {
      target: playerState
      function onSignalPlayerStateUpdated() {
        buttonLoop.loopMode = playerState.loopMode;
      }
    }
  }

  ProgressBar {
    property int progressTime: 0
    id: audioProgress
    width: parent.width / 5 * 2
    height: 5
    value: 0
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 20

    background: Rectangle {
      radius: 2
      color: "gray"
    }
    contentItem: Rectangle {
      id: audioProgressIndicator
      width: 0
      radius: 2
    }

    Timer {
      id: progressBarTimer
      interval: 1000
      repeat: true
      running: false
      onTriggered: {
        audioProgressIndicator.width += 1000 / playerState.durationMs * parent.width;
        audioProgress.progressTime += 1;
        // Update the PlayerState;
        if (audioProgressIndicator.width > audioProgress.width) {
          audioProgressIndicator.width = 0;
          progressBarTimer.stop();
          buttonLoop.loopMode === "track" ? playerAPI.updatePlayerState(false) : playerAPI.updatePlayerState(true) 
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
        audioProgress.progressTime = Math.round(progressTo / 1000)
        playerAPI.seekTrack(progressTo)
        audioProgressIndicator.width = audioProgressMouseArea.mouseX
      }
    }

    Connections {
      target: playerState
      function onSignalPlayerStateUpdated() {
        // Update the Progress;
        audioProgress.progressTime = Math.round(playerState.progressMs / 1000) - 1
        audioProgressIndicator.width = playerState.progressMs / playerState.durationMs * audioProgress.width
        // Update the Duration;
        audioDurationText.text = Utils.formatTime(Math.round(playerState.durationMs / 1000))
      }
    }

    Text {
      id: audioProgressText
      anchors.right: parent.left
      anchors.verticalCenter: parent.verticalCenter
      anchors.rightMargin: 10
      font.pixelSize: 12
      color: "lightgray"
      text: Utils.formatTime(parent.progressTime)
    }

    Text {
      id: audioDurationText
      anchors.left: parent.right
      anchors.verticalCenter: parent.verticalCenter
      anchors.leftMargin: 10
      font.pixelSize: 12
      color: "lightgray"
    }
  }

  Image {
    id: albumCover
    width: 70
    height: width
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter 
    anchors.leftMargin: 15

    Connections {
      target: playerState
      function onSignalRequestImageFinished(path) {
        albumCover.source = "file:///" + executablePath + "/" + path;
      }
    }
  }

  Flickable {
    id: artistListFlick
    height: 15
    width: 200
    anchors.left: albumCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 10
    clip: true
    interactive: false
    contentWidth: artistList.contentWidth

    ListView {
      id: artistList
      height: parent.height
      width: parent.width
      orientation: ListView.Horizontal

      model: playerState.artists

      delegate: Row {
        Text {
          id: artistName
          text: modelData.name
          color: "lightgray"
          font.pixelSize: 12

          MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: { 
              parent.color = "white"
              artistName.font.underline = true
            }
            onExited: { 
              parent.color = "lightgray"
              artistName.font.underline = false
            }
            onClicked: { 
              console.log(modelData.name);
            }
          }
        }
        Text {
          text: index < artistList.count - 1 ? " • " : ""
          color: "lightgray"
          font.pixelSize: 12
        }
      }

      Connections {
        target: playerState
        function onSignalPlayerStateUpdated() {
          artistListAnimation.stop()
          artistList.model = playerState.artists
          if (artistList.contentWidth > artistListFlick.width) {
            artistListAnimation.start()
          }
        }
      } 
    }
    SequentialAnimation {
      id: artistListAnimation
      loops: Animation.Infinite

      PauseAnimation {
        duration: 1500
      }

      PropertyAnimation {
        target: artistListFlick
        property: "contentX"
        to: artistListFlick.contentWidth - artistListFlick.width
        duration: 5000
      }

      PauseAnimation {
        duration: 1500
      }

      PropertyAnimation {
        target: artistListFlick
        property: "contentX"
        to: 0
        duration: 5000
      }
    }
  }

  BoundFadeEffect {
    boundaryColor: Style.colorSpotifyDarkGray
    anchors.fill: artistListFlick
    visible: artistListFlick.contentWidth > artistListFlick.width
  }

  Flickable {
    id: trackNameFlick
    anchors.left: albumCover.right
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -10
    anchors.leftMargin: 10
    width: 200
    height: 15
    contentWidth: trackName.contentWidth
    clip: true
    interactive: false

    Text {
      id: trackName
      width: parent.width
      font.pixelSize: 12
      font.bold: true 
      color: "white"


      Connections {
        target: playerState
        function onSignalPlayerStateUpdated() {
          trackNameAnimation.stop()
          trackName.text = playerState.trackName
          if(trackName.contentWidth > trackNameFlick.width) {
            trackNameAnimation.start()
          }
        }
      }
    }

    SequentialAnimation {
      id: trackNameAnimation
      loops: Animation.Infinite

      PauseAnimation {
        duration: 1500
      }
      PropertyAnimation {
        target: trackNameFlick
        property: "contentX"
        to: trackNameFlick.contentWidth - trackNameFlick.width
        duration: 3000
      }
      PauseAnimation {
        duration: 1500
      } 
      PropertyAnimation {
        target: trackNameFlick
        property: "contentX"
        to: 0
        duration: 3000
      }
    }
  }

  BoundFadeEffect {
    boundaryColor: Style.colorSpotifyDarkGray
    anchors.fill: trackNameFlick
    visible: trackNameFlick.contentWidth > trackNameFlick.width
  }
}