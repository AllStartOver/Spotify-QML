import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {

  color: Style.colorSpotifyDarkGray

  Rectangle {
    id: playListCover
    width: 60
    height: width
    anchors.verticalCenter: parent.verticalCenter
    anchors.left: parent.left
    anchors.leftMargin: 10
    radius: 30
    color: "white"
  }

  Text {
    id: playListName
    font.pixelSize: 12
    anchors.left: playListCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -10
    text: "MockName"
    color: "white"
  }

  Text {
    id: playListOwner
    font.pixelSize: 12
    anchors.left: playListCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 10
    text: "MockOwner"
    color: "gray"
  }
}