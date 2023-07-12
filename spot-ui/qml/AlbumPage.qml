import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

ListView {
  id: root
  property var album
  property var backgroundColor : Style.colorSpotifyBlack
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

      Connections {
        target: album
        enabled: album !== null
        function onSignalAlbumRequestCoverFinished() {
          cover.source = "file:///" + executablePath + "/" + album.imgFileName
          album.calculateAverageCoverColor()
          backgroundColor = album.averageCoverColor
        }
      }
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

    ListView {
      id: albumArtists
      anchors.left: cover.right
      anchors.leftMargin: 30
      anchors.bottom: cover.bottom
      anchors.right: parent.right
      anchors.rightMargin: 30
      height: 30
      orientation: ListView.Horizontal
      delegate: Row {
        Text {
          text: modelData.name
          color: Style.colorSpotifyWhite
          font.pixelSize: 15
          font.bold: true
          font.underline: artistMouseArea.containsMouse ? true : false
          MouseArea {
            id: artistMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
          }
        }
        Text {
          text: " • "
          color: Style.colorSpotifyWhite
          font.pixelSize: 15
          font.bold: true
        }
      }
      footer: Text {
        text: album !== null ? album.release_date + " • " + album.tracks.length + " songs" : ""
        color: Style.colorSpotifyWhite
        font.pixelSize: 15
      }
      Connections {
        target: album
        enabled: album !== null
        function onSignalAlbumRequestCoverFinished() {
          albumArtists.model = album.artists
        }
      }
    }

    Text {
      id: albumName
      anchors.left: albumArtists.left
      anchors.bottom: albumArtists.top
      font.pixelSize: 70
      font.bold: true
      color: Style.colorSpotifyWhite
      text: album !== null ? album.name : ""
    }

    Text {
      anchors.left: albumArtists.left
      anchors.bottom: albumName.top
      font.pixelSize: 15
      font.bold: true
      color: Style.colorSpotifyWhite
      text: album !== null ? "Album" : ""
    }

    Image {
      id: playButton
      anchors.left: cover.left
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 30
      height: playButtonMouseArea.containsMouse ? 53 : 50
      width: height
      source: Utils.ImagePath("PlayGreen.svg")

      MouseArea {
        id: playButtonMouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
          playerAPI.startPlayback(album.uri, 0)
        }
      }
    }
  }

  model: album !== null ? album.tracks : []

  delegate: AlbumTrackDelegate {
    id: albumTrackDelegate
    width: parent.width
    height: 50
    track: modelData
  }

  Connections {
    target: albumAPI
    function onSignalRequestAlbumByIDFinished() {
      album = albumAPI.getCurrentAlbum()
      album.signalAlbumRequestCover(album.imgUrl, album.id)
    }
  }
}