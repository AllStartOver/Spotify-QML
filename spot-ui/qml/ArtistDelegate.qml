import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  property var artist: modelData
  color: artistMouseArea.containsMouse ? Style.colorSpotifyLightGray : Style.colorSpotifyDarkGray
  Item {
    id: artistImage
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    width: 53
    height: width
    Image {
      id: img
      anchors.fill: parent
      smooth: true
      visible: false
      Connections {
        target: artist
        function onSignalArtistPageRequestCoverFinished() {
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
    anchors.left: artistImage.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -13
    text: artist.name
    font.pixelSize: 14
    color: Style.colorSpotifyWhite
  }

  Text {
    anchors.left: artistImage.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 13
    text: "Artist"
    font.pixelSize: 12
    color: Style.colorSpotifyLightWhite
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
    artist.signalArtistPageRequestCover(artist.imgUrl, artist.id)
  }
}