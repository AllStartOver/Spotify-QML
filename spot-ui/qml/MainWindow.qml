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

  Rectangle {
    id: navigation
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.leftMargin: 10
    anchors.topMargin: 10
    anchors.rightMargin: 10
    anchors.bottomMargin: 10
    radius: 5
    width: parent.width / 5
    height: 100
    color: Style.colorSpotifyDarkGray
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
    anchors.leftMargin: 10
    anchors.topMargin: 10
    anchors.rightMargin: 10
    anchors.bottomMargin: 10
    radius: 5
    width: parent.width / 5
    color: Style.colorSpotifyDarkGray

    ListView {
      id: playListsListView
      anchors.topMargin: 10
      anchors.fill: parent
      model: playListsAPI.playLists

      delegate: PlayListDelegate {
        id: playListItem
        width: parent.width
        height: 70
        playListNameText: modelData.name
        playListOwnerText: modelData.owner

        Component.onCompleted: {
          modelData.signalPlayListRequestCover(modelData.img_url, modelData.id)
        }   
        Connections {
          target: modelData
          function onSignalPlayListRequestCoverFinished() {
            playListCoverSource = "file:///" + executablePath + "/" + modelData.imgFileName;
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

  Player {
    id: player
  }
}



