import QtQuick.Window
import QtQuick.Controls
import Views 1.0
import Images 1.0
import Styles 1.0

Window {
  visible: true
  width: Style.defaultWindowWidth
  height: Style.defaultWindowHeight
  title: qsTr("Spotify-QML")



  Rectangle {
    id: navigation
    anchors.left: parent.left
    anchors.top: parent.top
    width: parent.width / 5
    height: (parent.height - player.height) * 0.44
    color: Style.colorSpotifyBlack
  }

  Rectangle {
    id: playerLists
    anchors.left: parent.left
    anchors.top: navigation.bottom
    anchors.bottom: player.top
    width: parent.width / 5
    color: Style.colorSpotifyBlack

    ListView {
      id: playListsListView
      anchors.fill: parent
      model: playListsAPI.playLists

      delegate: Text {
        text: modelData.name
        color: "white"
        font.pixelSize: 12
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: parent.width
        height: 30
      }
      Connections {
        target: playListsAPI
        function onSignalGetCurrentUserPlaylistsFinished() {
          playListsListView.model = playListsAPI.playLists
        }
      }
    }
  }

  Rectangle {
    width: parent.width / 5
    height: 1
    anchors.left: parent.left
    anchors.top: navigation.bottom
    gradient: Gradient {
      orientation: Qt.Horizontal
      GradientStop {
        position: 0.0
        color: "transparent"
      }
      GradientStop {
        position: 0.2
        color: "gray"
      }
      GradientStop {
        position: 0.8
        color: "gray"
      }
      GradientStop {
        position: 1.0
        color: "transparent"
      }
    }
  }
  Player {
    id: player
  }
}



