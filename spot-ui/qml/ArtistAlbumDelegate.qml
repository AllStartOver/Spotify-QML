import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  id: root 
  property var album
  height: 250
  width: 180
  color: albumMouseArea.containsMouse ? Style.colorSpotifyLighterGray : Style.colorSpotifyLightGray
  radius: 5

  Image {
    id: albumCover
    anchors.top: parent.top
    anchors.topMargin: 20
    anchors.horizontalCenter: parent.horizontalCenter
    width: 150
    height: 150
    Connections {
      target: album 
      function onSignalAlbumRequestCoverFinished() {
        albumCover.source = "file:///" + executablePath + "/" + album.imgFileName
      }
    }
  }
  Text {
    id: albumName
    anchors.top: albumCover.bottom
    anchors.topMargin: 20
    anchors.left: albumCover.left
    width: albumCover.width
    text: album.name
    font.pixelSize: 17
    font.bold: true
    elide: Text.ElideRight
    color: Style.colorSpotifyWhite
  }

  Text {
    id: albumInfo
    anchors.top: albumName.bottom
    anchors.topMargin: 15
    anchors.left: albumCover.left
    width: albumCover.width
    text: album.release_date.slice(0, 4) + " • " + album.albumType
    font.pixelSize: 14
    elide: Text.ElideRight
    color: Style.colorSpotifyWhite
  }

  MouseArea {
    id: albumMouseArea
    anchors.fill: parent
    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
    onClicked: {
    }
  }

  Component.onCompleted: {
    album.requestAlbumCover()
  }
}