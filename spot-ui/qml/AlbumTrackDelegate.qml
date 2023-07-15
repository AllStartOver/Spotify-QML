import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  id: root
  property var track
  property bool bgContainsMouse: false
  property bool isPlaying : playerState.uri === track.context_uri && playerState.trackID === track.id
  property bool isPaused: false
  color: bgContainsMouse ? Style.colorSpotifyLightGray : Style.colorSpotifyDarkGray

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
      color: Style.colorSpotifyWhite
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
        playerAPI.startPlayback(track.context_uri, index)
      }
    }
  }

  Text {
    id: trackName
    anchors.left: trackIndex.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -7
    width: parent.width * 0.3
    text: track.name
    font.weight: Font.DemiBold
    font.pixelSize: 12
    color: isPlaying ? Style.colorSpotifyGreen : Style.colorSpotifyWhite
    elide: Text.ElideRight
  }

  ListView {
    id: trackArtists
    z: 2
    anchors.left: trackIndex.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 7
    width: parent.width * 0.3
    height: 10
    orientation: ListView.Horizontal
    model: track.artists
    delegate: Row {
      Text {
        font.pixelSize: 12
        text: modelData.name
        color: bgContainsMouse ? Style.colorSpotifyWhite : Style.colorSpotifyLightWhite
        font.underline: artistMouseArea.containsMouse
        MouseArea {
          id: artistMouseArea
          anchors.fill: parent
          hoverEnabled: true
          cursorShape: Qt.PointingHandCursor
          onClicked: {
            viewController.signalChangeArtistSource(Utils.QMLPath("ArtistPage.qml"), modelData.id)
            artistAPI.requestArtistByID(modelData.id)
          }
        }
      }
      Text {
        font.pixelSize: 12 
        text: index < track.artists.length - 1 ? ", " : ""
        color: bgContainsMouse ? Style.colorSpotifyWhite : Style.colorSpotifyLightWhite
      }
    }
  }

  Text {
    id: duration
    anchors.right: parent.right
    anchors.rightMargin: 30
    anchors.verticalCenter: parent.verticalCenter
    text: Utils.formatTime(Math.round(track.duration_ms / 1000))
    font.pixelSize: 12 
    color: Style.colorSpotifyWhite
  }


  MouseArea {
    id: trackMouseArea
    anchors.fill: parent
    hoverEnabled: true
    onDoubleClicked: {
      playerAPI.startPlayback(albumAPI.getCurrentAlbum().uri, index)
    }
    onEntered: {
      bgContainsMouse = true
    }
    onExited: {
      bgContainsMouse = false
    }
  }

  Connections {
    target: playerState
    function onSignalContextChanged() {
      isPlaying = playerState.uri === track.context_uri && playerState.trackID === track.id
    }
  }
}