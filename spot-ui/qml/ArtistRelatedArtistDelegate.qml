
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  id: root 
  property var artist
  height: 250
  width: 180
  color: artistMouseArea.containsMouse ? Style.colorSpotifyLighterGray : Style.colorSpotifyLightGray
  radius: 5

  Item {
    id: artistImage
    anchors.top: parent.top
    anchors.topMargin: 10
    anchors.horizontalCenter: parent.horizontalCenter
    width: 150
    height: 150

    Image {
      id: img
      anchors.fill: parent
      visible: false
      Connections {
        target: artist
        function onSignalRequestArtistImageFinished() {
          img.source = "file:///" + executablePath + "/" + artist.imgFileName
        }
      }
    }
    Rectangle {
      id: mask
      anchors.fill: parent
      radius: width / 2
      visible: false
    }
    OpacityMask {
      anchors.fill: parent
      maskSource: mask
      source: img
    }
  }

  Text {
    id: artistName
    anchors.top: artistImage.bottom
    anchors.topMargin: 20
    anchors.left: artistImage.left
    width: artistImage.width
    text: artist.name
    font.pixelSize: 17 
    font.bold: true
    elide: Text.ElideRight
    color: Style.colorSpotifyWhite
  }

  Text {
    id: artistInfo
    anchors.top: artistName.bottom
    anchors.topMargin: 15
    anchors.left: artistImage.left
    width: artistImage.width
    text: "Artist"
    font.pixelSize: 14
    elide: Text.ElideRight
    color: Style.colorSpotifyWhite
  }

  MouseArea {
    id: artistMouseArea
    anchors.fill: parent
    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
    onClicked: {
      viewController.signalChangeArtistSource(Utils.QMLPath("ArtistPage.qml"), artist.id)
      artistAPI.requestArtistByID(artist.id)
    }
  }
  Component.onCompleted: {
    artist.requestArtistImage()
    contentY = 0
  }
}