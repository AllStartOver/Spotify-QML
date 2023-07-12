import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  property var album: modelData
  property var isPlaying: album.uri === playerState.uri
  color: albumMouseArea.containsMouse ? Style.colorSpotifyLightGray: Style.colorSpotifyDarkGray

  Image {
    id: albumCover
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    width: 53
    height: width
    Connections {
      target: album 
      function onSignalAlbumRequestCoverFinished() {
        albumCover.source = "file:///" + executablePath + "/" + album.imgFileName
      }
    }
  }

  Text {
    id: albumName
    font.pixelSize: 14
    anchors.left: albumCover.right
    anchors.leftMargin: 10
    anchors.right: parent.right
    anchors.rightMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -13
    text: album.name
    elide: Text.ElideRight
    color: isPlaying ? Style.colorSpotifyGreen : Style.colorSpotifyWhite
  }

  Text {
    id: albumArtist
    anchors.left: albumCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 13
    text: album.artists[0].name
    font.pixelSize: 12
    color: Style.colorSpotifyLightWhite
  }

  MouseArea {
    id: albumMouseArea
    anchors.fill: parent
    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
    onClicked: {
      viewController.signalChangeAlbumSource(Utils.QMLPath("AlbumPage.qml"), album.id)
      albumAPI.requestAlbumByID(album.id)
    }
  }
  Component.onCompleted: {
    album.signalAlbumRequestCover(album.imgUrl, album.id)
  }
}