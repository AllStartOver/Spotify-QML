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
    width: 60
    height: 60
    anchors.verticalCenter: parent.verticalCenter
    anchors.left: parent.left
    anchors.leftMargin: 10
  }

  Text {
    id: albumName
    font.pixelSize: 14
    anchors.left: albumCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -13
    text: album.name
    color: isPlaying ? Style.colorSpotifyGreen : Style.colorSpotifyWhite
  }

  MouseArea {
    id: albumMouseArea
    anchors.fill: parent
    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
  }
}