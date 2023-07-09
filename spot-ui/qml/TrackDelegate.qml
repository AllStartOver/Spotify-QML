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
    width: parent.width * 0.05
    color: "transparent"
    Text {
      anchors.centerIn: parent
      font.pixelSize: 14
      clip: true
      text: index + 1
      color: "white"
      visible: isPlaying? false : bgContainsMouse? false : true
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

  Image {
    id: trackCover
    anchors.left: trackIndex.right
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.04
    height: width
  }

  Text {
    id: trackName
    anchors.left: trackCover.right
    anchors.leftMargin: 10
    anchors.top: trackCover.top
    anchors.topMargin: 5
    width: parent.width * 0.3
    text: track.name
    font.weight: Font.DemiBold
    font.pixelSize: 12
    color: isPlaying? Style.colorSpotifyGreen : Style.colorSpotifyWhite
    elide: Text.ElideRight
  }

  ListView {
    id: trackArtists
    visible: true
    anchors.left: trackCover.right
    anchors.leftMargin: 10
    anchors.bottom: trackCover.bottom
    anchors.bottomMargin: 5
    width: parent.width * 0.35
    height: 10
    orientation: ListView.Horizontal
    model: track.artists
    delegate: Row {
      Text {
        font.pixelSize: 12
        text: modelData.name
        color: bgContainsMouse ? Style.colorSpotifyWhite : Style.colorSpotifyLightWhite
      }
      Text {
        font.pixelSize: 12
        text: index < trackArtists.count - 1 ? ", " : ""
        color: bgContainsMouse ? Style.colorSpotifyWhite : Style.colorSpotifyLightWhite
      }
    }
  }

  Text {
    id: albumName
    z: 2
    anchors.left: trackName.right
    anchors.leftMargin: 30
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.25
    text: track.album
    font.bold: Font.DemiBold
    font.pixelSize: 12
    font.underline: albumMouseArea.containsMouse
    elide: Text.ElideRight
    color: bgContainsMouse ? Style.colorSpotifyWhite : Style.colorSpotifyLightWhite

    MouseArea {
      id: albumMouseArea
      anchors.fill: albumName
      hoverEnabled: true
      cursorShape: Qt.PointingHandCursor
      onClicked: {
        albumAPI.requestAlbumByID(track.album_id)
        viewController.signalChangeAlbumSource(Utils.QMLPath("AlbumPage.qml"), track.album_id)
      }
    }
  }

  Text {
    id: duration
    anchors.right: parent.right
    anchors.rightMargin: 30
    anchors.verticalCenter: parent.verticalCenter
    text: Utils.formatTime(track.duration_ms % 1000)
    font.pixelSize: 12
    color: Style.colorSpotifyLightWhite
  }

  MouseArea {
    id: trackMouseArea
    anchors.fill: parent
    hoverEnabled: true
    onDoubleClicked: {
      playerAPI.startPlayback(track.context_uri, index)
    }
    onEntered: {
      bgContainsMouse = true
    }
    onExited: {
      if (albumMouseArea.containsMouse) { return }
      bgContainsMouse = false
    }
  }

  Connections {
    target: track
    function onSignalTrackRequestCoverFinished() {
      trackCover.source = "file:///" + executablePath + "/" + track.imgFileName
    }
  }
  Connections {
    target: playerState
    function onSignalContextChanged() {
      isPlaying = playerState.uri === track.context_uri && playerState.trackID === track.id
    }
  }
}