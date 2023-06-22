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
    id: navigation
    anchors.left: parent.left
    anchors.top: parent.top
    width: parent.width / 5
    height: (parent.height - player.height) * 0.44
    color: Style.colorSpotifyBlack
  }

  PlayListPage {
    anchors.left: navigation.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: player.top
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
      anchors.topMargin: 10
      anchors.fill: parent
      model: playListsAPI.playLists

      delegate: Text {
        anchors.left: parent.left
        anchors.right: parent.right
        leftPadding: 40
        text: modelData.name
        color: "gray"
        font.pixelSize: 14
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        width: parent.width
        height: 30

        MouseArea {
          anchors.fill: parent
          hoverEnabled: true
          onEntered: {
            parent.color = "white"
          }
          onExited: {
            parent.color = "gray"
          }
          onClicked: {
            console.log("Clicked on " + modelData.name)
            playListsAPI.getPlayListTracks(modelData.id)
          }
        }
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



