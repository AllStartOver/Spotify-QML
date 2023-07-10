import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Item {
  id: root
  property string selectedText: ""
  Loader {
    id: loader
    anchors.fill: parent
    active: true
    sourceComponent: flickable
  }

  Component  {
    id: selected
    Item {
      anchors.fill: parent
      Image {
        id: deSelected
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: 45
        height: width
        source: Utils.ImagePath("FilterCross.svg")
        MouseArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
          onClicked: {
            loader.sourceComponent = flickable
          }
        }
      }
      Rectangle {
        id: selected
        anchors.left: deSelected.right
        anchors.top: parent.top
        width: text.contentWidth + 20
        height: parent.height
        color: Style.colorSpotifyWhite
        radius: 15
        Text {
          id: text
          anchors.centerIn: parent
          text: selectedText
          font.pixelSize: 14
          font.weight: Font.DemiBold
          color: Style.colorSpotifyBlack
        }
      }
    }
  }

  Component {
    id: flickable
    Item {
      anchors.fill: parent
      Flickable {
        id: filterFlickable
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        contentWidth: playlistsFilter.width + artistsFilter.width + albumsFilter.width + podcastsFilter.width + 40
        interactive: true 
        clip: true
        Row {
          id: filterRow 
          spacing: 10
          height: parent.height
          width: parent.width
          Rectangle {
            id: playlistsFilter
            height: parent.height
            width: playlistsFilterText.width + 20
            radius: 15
            color: Style.colorSpotifyLightGray
            Text {
              id: playlistsFilterText
              anchors.centerIn: parent
              text: "Playlists"
              font.pixelSize: 14
              font.weight: Font.DemiBold
              color: Style.colorSpotifyWhite
            }
            MouseArea {
              anchors.fill: parent
              cursorShape: Qt.PointingHandCursor
              onClicked: {
                selectedText = playlistsFilterText.text
                loader.sourceComponent = selected
                viewController.signalChangeLibrary("Playlists")
              }
            }
          }
          Rectangle {
            id: artistsFilter
            height: parent.height
            width: artistsFilterText.width + 20
            radius: 15
            color: Style.colorSpotifyLightGray
            Text {
              id: artistsFilterText
              anchors.centerIn: parent
              text: "Artists"
              font.pixelSize: 14
              font.weight: Font.DemiBold
              color: Style.colorSpotifyWhite
            }
            MouseArea {
              anchors.fill: parent
              cursorShape: Qt.PointingHandCursor
              onClicked: {
                selectedText = artistsFilterText.text
                loader.sourceComponent = selected
                viewController.signalChangeLibrary("Artists")
              }
            }
          }
          Rectangle {
            id: albumsFilter
            height: parent.height
            width: albumsFilterText.width + 20
            radius: 15
            color: Style.colorSpotifyLightGray
            Text {
              id: albumsFilterText
              anchors.centerIn: parent
              text: "Albums"
              font.pixelSize: 14
              font.weight: Font.DemiBold
              color: Style.colorSpotifyWhite
            }
            MouseArea {
              anchors.fill: parent
              cursorShape: Qt.PointingHandCursor
              onClicked: {
                selectedText = albumsFilterText.text
                loader.sourceComponent = selected
              }
            }
          }
          Rectangle {
            id: podcastsFilter
            height: parent.height
            width: podcastsFilterText.width + 20
            radius: 15
            color: Style.colorSpotifyLightGray
            Text {
              id: podcastsFilterText
              anchors.centerIn: parent
              text: "Podcasts"
              font.pixelSize: 14
              font.weight: Font.DemiBold
              color: Style.colorSpotifyWhite
            }
            MouseArea {
              anchors.fill: parent
              cursorShape: Qt.PointingHandCursor
              onClicked: {
                selectedText = podcastsFilterText.text
                loader.sourceComponent = selected
              }
            }
          }
        }
      }
      Rectangle {
        id: filterBackGradient
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        width: filterBack.width + 30
        visible: filterFlickable.contentX > 0

        gradient: Gradient {
          orientation: Gradient.Horizontal
          GradientStop { position: 0.0; color: Style.colorSpotifyDarkGray }
          GradientStop { position: 1.0; color: "transparent" }
        }
      }
      Image {
        id: filterBack
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: 40
        height: width
        source: Utils.ImagePath("FilterBack.svg")
        visible: filterFlickable.contentX > 0
        MouseArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
          onClicked:  {
            filterBackAnimation.start()
          }
        }
        PropertyAnimation {
          id: filterBackAnimation
          target: filterFlickable
          property: "contentX"
          duration: 250
          to: 0
        }
      }

      Rectangle {
        id: filterForwardGradient
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        width: filterForward.width + 30
        visible: filterFlickable.contentX < filterFlickable.contentWidth - filterFlickable.width

        gradient: Gradient {
          orientation: Gradient.Horizontal
          GradientStop { position: 0.0; color: "transparent" }
          GradientStop { position: 1.0; color: Style.colorSpotifyDarkGray }
        }
      }

      Image {
        id: filterForward
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: 40
        height: width
        source: Utils.ImagePath("FilterForward.svg")
        visible: filterFlickable.contentX < filterFlickable.contentWidth - filterFlickable.width
        MouseArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
          onClicked:  {
            filterForwardAnimation.start()
          }
        }
        PropertyAnimation {
          id: filterForwardAnimation
          target: filterFlickable
          property: "contentX"
          duration: 250
          to: filterFlickable.contentWidth - filterFlickable.width
        }
      }
    }
  }
}