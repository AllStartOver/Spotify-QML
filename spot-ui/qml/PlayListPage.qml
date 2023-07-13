import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

ListView {
  property var playList
  property var backgroundColor : Style.colorSpotifyBlack
  id: playListTracksView
  anchors.fill: parent 
  interactive: true
  clip: true

  header: Rectangle {
    width: parent.width
    height: 400

    Image {
      id: cover
      anchors.left: parent.left
      anchors.leftMargin: 30
      anchors.top: parent.top
      anchors.topMargin: 60
      height: 240
      width: 240
      source: playList !== null ? "file:///" + executablePath + "/" + playList.imgFileName : ""
    } 

    gradient: Gradient {
      orientation: Gradient.Vertical
      GradientStop { 
        position: 0.0 
        color: backgroundColor
      }
      GradientStop {
        position: 1.0
        color: Style.colorSpotifyDarkGray
      }
    }

    Text {
      id: playListOwner
      anchors.left: cover.right
      anchors.leftMargin: 30
      anchors.bottom: cover.bottom
      font.pixelSize: 15
      font.bold: true
      color: Style.colorSpotifyWhite
      text: playList !== null ? playList.owner : ""
    }

    Text {
      id: playListName
      anchors.left: playListOwner.left
      anchors.bottom: playListOwner.top
      font.pixelSize: 100
      font.bold: true
      color: Style.colorSpotifyWhite
      text: playList !== null ? playList.name : ""
    }

    Text {
      anchors.left: playListOwner.left
      anchors.bottom: playListName.top
      font.pixelSize: 15
      font.bold: true
      color: Style.colorSpotifyWhite
      text: playList !== null ? "Playlist" : ""
    }

    Image {
      id: playButton
      anchors.left: cover.left
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 30
      height: playButtonMouseArea.containsMouse ? 53 : 50 
      width: playButtonMouseArea.containsMouse ? 53 : 50
      source: Utils.ImagePath("PlayGreen.svg")

      MouseArea {
        id: playButtonMouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
        onClicked: {
          playerAPI.startPlayback(playList.uri, 0)
        }
      }
    }
  }

  model: playList !== null ? playList.tracks : []

  delegate: TrackDelegate {
    id: trackDelegate
    width: parent.width
    height: 50
    track: modelData
  }

  Connections {
    target: playListsAPI
    function onSignalGetPlayListTracksFinished(id) {
      playList = playListsAPI.getPlayListByID(id)
      playList.calculateAverageCoverColor()
      backgroundColor = playList.averageCoverColor
    }
  }
  Component.onCompleted: {
    var id = playListsAPI.currentPlayListID
    playList = playListsAPI.getPlayListByID(id)
    backgroundColor = playList.averageCoverColor
  }
}

