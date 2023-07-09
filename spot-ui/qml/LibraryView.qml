import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  id: root
  radius: 5
  color: Style.colorSpotifyDarkGray

  ListView {
    id: libraryListView
    anchors.topMargin: 20
    anchors.fill: parent

    header: Item {
      width: parent.width
      height: 130
      Image {
        id: libraryImage
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        width: 30
        height: width
        source: Utils.ImagePath("LibraryWhite.svg")
      }

      Text {
        anchors.left: libraryImage.right
        anchors.leftMargin: 15
        anchors.verticalCenter: libraryImage.verticalCenter
        text: "Your Library"
        font.pixelSize: 15
        font.bold: true
        color: Style.colorSpotifyLightWhite
      }

      FilterView {
        id: filterFlickable
        height: 30
        anchors.top: libraryImage.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        clip: true
        interactive: true
      }

      Rectangle {
        id: filterBackGradient
        anchors.left: filterBack.left
        anchors.top: filterBack.top
        anchors.bottom: filterBack.bottom
        width: filterBack.width + 30
        visible: filterFlickable.contentX > 0 

        gradient: Gradient {
          orientation: Gradient.Horizontal
          GradientStop {
            position: 0
            color: Style.colorSpotifyDarkGray
          }
          GradientStop {
            position: 1
            color: "transparent"
          }
        }
      }
      Image {
        id: filterBack
        anchors.left: filterFlickable.left
        anchors.verticalCenter: filterFlickable.verticalCenter
        width: 35
        height: width
        source: Utils.ImagePath("FilterBack.svg")
        visible: filterFlickable.contentX > 0
        MouseArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
          onClicked: {
            filterBackAnimation.start()
          }
        }
        PropertyAnimation {
          id: filterBackAnimation
          target: filterFlickable
          property: "contentX"
          duration: 500
          to: 0
        }
      }

      Rectangle {
        id: filterForwardGradient
        anchors.right: filterForward.right
        anchors.top: filterForward.top
        anchors.bottom: filterForward.bottom
        width: filterForward.width + 30
        visible: filterFlickable.contentX < filterFlickable.contentWidth - filterFlickable.width

        gradient: Gradient {
          orientation: Gradient.Horizontal
          GradientStop {
            position: 0
            color: "transparent"
          }
          GradientStop {
            position: 1
            color: Style.colorSpotifyDarkGray
          }
        }
      }

      Image {
        id: filterForward
        anchors.right: filterFlickable.right
        anchors.verticalCenter: filterFlickable.verticalCenter
        width: 35
        height: width
        source: Utils.ImagePath("FilterForward.svg")
        visible: filterFlickable.contentX < filterFlickable.contentWidth - filterFlickable.width
        MouseArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
          onClicked: {
            filterForwardAnimation.start()
          }
        }
        PropertyAnimation {
          id: filterForwardAnimation
          target: filterFlickable
          property: "contentX"
          duration: 500
          to: filterFlickable.contentWidth - filterFlickable.width
        }
      }
      Image {
        id: searhButton
        anchors.left: filterFlickable.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: 20
        height: width
        source: Utils.ImagePath("SearchGray.svg")
      }
    }
    delegate: PlayListDelegate {
      width: parent.width
      height: 70
      playList: modelData
    }
    Connections {
      target: playListsAPI
      function onSignalGetCurrentUserPlaylistsFinished() {
        libraryListView.model = playListsAPI.playLists
      }
    }
    Component.onCompleted: {
      playListsAPI.getCurrentUserPlaylists()
    }
  }
}