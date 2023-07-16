import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  id: root 
  height: 50
  width: parent.width
  anchors.left: parent.left
  anchors.leftMargin: 40
  anchors.right: parent.right
  anchors.rightMargin: 40
  property var track
  property bool bgContainsMouse: false
  property bool isPlaying : playerState.uri === track.context_uri && playerState.trackID === track.id
  property bool isPaused: false
  color: bgContainsMouse ? Style.colorSpotifyLightGray : "transparent"

  Rectangle {
    id: trackIndex
    z: 2
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter
    height: parent.width * 0.05
    width: height
    color: "transparent"
    Text {
      anchors.centerIn: parent
      font.pixelSize: 14
      clip: true
      text: index + 1
      color: Style.colorSpotifyLightWhite
      visible: isPlaying ? false : bgContainsMouse ? false : true
    }
    Image {
      anchors.centerIn: parent
      width: 12 
      height: width
      source: !isPlaying || isPaused ? Utils.ImagePath("TrackPlay.svg") : bgContainsMouse? Utils.ImagePath("PlaylistPauseWhite.svg") : Utils.ImagePath("PlaylistPlayGreen.svg")
      visible: isPlaying ? true : bgContainsMouse? true : false
    }
    MouseArea {
      anchors.fill: parent
      onClicked: {
        if (isPlaying) {
          if (isPaused) {
            playerAPI.resumePlayback()
            isPaused = false
            return 
          } else {
            playerAPI.pausePlayback()
            isPaused = true
            return 
          }
        }
        var context_uri = artistAPI.getCurrentArtistPage().uri
        playerAPI.startPlayback("", "", [track.uri])
      }
    }
  }

  Image {
    id: trackCover
    anchors.left: trackIndex.right
    anchors.verticalCenter: parent.verticalCenter  
    width: parent.width * 0.04
    height: width

    Connections {
      target: track
      function onSignalTrackRequestCoverFinished() {
        trackCover.source = "file:///" + executablePath + "/" + track.imgFileName
      }
    }
  }

  Text {
    id: trackName
    anchors.left: trackCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.4
    text: track.name
    font.weight: Font.DemiBold
    font.pixelSize: 14
    color: Style.colorSpotifyWhite
    elide: Text.ElideRight
  }

  Text {
    id: duration
    anchors.right: parent.right
    anchors.rightMargin: 30
    anchors.verticalCenter: parent.verticalCenter
    text: Utils.formatTime(Math.round(track.duration_ms / 1000))
    font.pixelSize: 12
    color: Style.colorSpotifyLightWhite
  }

  MouseArea {
    id: trackMouseArea
    anchors.fill: parent
    hoverEnabled: true
    onEntered: bgContainsMouse = true
    onExited: bgContainsMouse = false
  }

  Connections {
    target: playerState
    function onSignalContextChanged() {
      isPlaying = playerState.uri === track.context_uri && playerState.trackID === track.id
    }
  }

  Component.onCompleted: {
    track.signalTrackRequestCover(track.img_url)
  }
}