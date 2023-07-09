import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Flickable {
  contentWidth: playlistsFilter.width + artistsFilter.width + albumsFilter.width + podcastsFilter.width + 40
  Row {
    spacing: 10
    height: parent.height
    width: parent.width
    Rectangle {
      id: playlistsFilter
      height: parent.height
      width: playlistsFilterText.width + 20
      radius: 15
      color: Style.colorSpotifyLightGray
      enabled: false
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
          console.log("playlistsFilter clicked")
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
          console.log("artistsFilter clicked")
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
          console.log("albumsFilter clicked")
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
          console.log("podcastsFilter clicked")
        }
      }
    }
  }
}