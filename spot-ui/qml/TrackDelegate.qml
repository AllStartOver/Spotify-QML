import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  color: Style.colorSpotifyDarkGray
  Rectangle {
    id: trackCover
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter
    anchors.leftMargin: 10
    width: 40
    height: width
    color: "white"
  }
}