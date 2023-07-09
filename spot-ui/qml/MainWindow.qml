import QtQuick.Window
import QtQuick.Controls
import Views 1.0
import Images 1.0
import Styles 1.0

Window {
  visible: true
  width: 1200
  height: 700
  title: qsTr("Spotify-QML")

  Rectangle {
    id: background
    anchors.fill: parent
    color: Style.colorSpotifyBlack
  }

  NavigationView {
    id: navigation
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.leftMargin: 10
    anchors.topMargin: 10
    anchors.rightMargin: 10
    anchors.bottomMargin: 10
    width: parent.width / 5
    height: 100
  }

  MasterPage {
    anchors.left: playerLists.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: player.top
    anchors.leftMargin: 10
    anchors.topMargin: 10
    anchors.rightMargin: 10
    anchors.bottomMargin: 10
  }

  LibraryView {
    id: playerLists
    anchors.left: parent.left
    anchors.top: navigation.bottom
    anchors.bottom: player.top
    anchors.leftMargin: 10
    anchors.topMargin: 10
    anchors.rightMargin: 10
    anchors.bottomMargin: 10
    width: parent.width / 5
  }

  Player {
    id: player
    width: parent.width
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    height: 85
  }
}



