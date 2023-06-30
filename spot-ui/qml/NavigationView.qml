import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  radius: 5
  color: Style.colorSpotifyDarkGray

  Rectangle {
    anchors.left: parent.left
    anchors.top: parent.top
    width: parent.width
    height: parent.height / 2
    color: "transparent"

    Image {
      id: homeIcon
      anchors.left: parent.left
      anchors.leftMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 15
      width: 30
      height: 30
      source: homeIconMouseArea.isFocused ? 
        Utils.ImagePath("HomeFocus.svg") : homeIconMouseArea.containsMouse ? 
        Utils.ImagePath("HomeWhite.svg") : Utils.ImagePath("HomeGray.svg")
    }
    Text {
      anchors.left: homeIcon.right
      anchors.leftMargin: 15
      anchors.verticalCenter: homeIcon.verticalCenter 
      text: "Home"
      font.pixelSize: 15
      font.bold: true
      color: homeIconMouseArea.isFocused ?
        Style.colorSpotifyWhite : homeIconMouseArea.containsMouse ?
        Style.colorSpotifyWhite : Style.colorSpotifyLightGray
    }
    MouseArea {
      property bool isFocused: false
      id: homeIconMouseArea
      anchors.fill: parent
      hoverEnabled: true
      onClicked: { isFocused = !isFocused }
      cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
    }
  }

  Rectangle {
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    width: parent.width
    height: parent.height / 2
    color: "transparent"

    Image {
      id: searchIcon
      anchors.left: parent.left
      anchors.leftMargin: 10
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 15
      width: 30
      height: 30
      source: searchIconMouseArea.isFocused ? 
        Utils.ImagePath("SearchFocus.svg") : searchIconMouseArea.containsMouse ? 
        Utils.ImagePath("SearchWhite.svg") : Utils.ImagePath("SearchGray.svg")
    }
    Text {
      id: searchIconText
      anchors.left: searchIcon.right
      anchors.leftMargin: 15
      anchors.verticalCenter: searchIcon.verticalCenter 
      text: "Search"
      font.pixelSize: 15
      font.bold: true
      color: searchIconMouseArea.isFocused ?
        Style.colorSpotifyWhite : searchIconMouseArea.containsMouse ?
        Style.colorSpotifyWhite : Style.colorSpotifyLightGray
    }
    MouseArea {
      property bool isFocused: false
      id: searchIconMouseArea
      anchors.fill: parent
      hoverEnabled: true
      onClicked: { isFocused = !isFocused }
      cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
    }
  }
}