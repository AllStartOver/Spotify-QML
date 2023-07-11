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
        id: filter
        height: 30
        anchors.top: libraryImage.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.right: parent.right
      }
      Image {
        id: searhButton
        anchors.left: filter.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: 20
        height: width
        source: Utils.ImagePath("SearchGray.svg")
      }
    }

    delegate: Loader {
      id: delegateLoader
      height: 70
      width: parent.width
      Connections {
        target: libraryListView
        function onModelChanged() {
          if (libraryListView.model) {
            if (libraryListView.model[0].type === "playlist") {
              delegateLoader.source = Utils.QMLPath("PlayListDelegate.qml")
            } else if (libraryListView.model[0].type === "artist") {
              delegateLoader.source = Utils.QMLPath("ArtistDelegate.qml")
            } else if (libraryListView.model[0].type === "album") {
              delegateLoader.source = Utils.QMLPath("AlbumDelegate.qml")
            }
          }
        }
      }
    }
    Connections {
      target: playListsAPI
      function onSignalGetCurrentUserPlaylistsFinished() {
        libraryListView.model = playListsAPI.playLists
      }
    }
    Connections {
      target: artistAPI
      function onSignalRequestUserFollowedArtistsFinished() {
        libraryListView.model = artistAPI.artistPages;
      }
    }
    Connections {
      target: albumAPI
      function onSignalRequestUserSavedAlbumsFinished() {
        libraryListView.model = albumAPI.userSavedAlbums
      }
    }
    Connections {
      target: viewController
      function onSignalChangeLibrary(lib) {
        if (lib === "Playlists") {
          playListsAPI.getCurrentUserPlaylists()
        } else if (lib === "Artists") {
          artistAPI.requestUserFollowedArtists()
        } else if (lib === "Albums") {
          albumAPI.requestUserSavedAlbums()
        } else if (lib === "Podcasts") {
          console.log("Podcasts")
        } else if (lib === "Local Files") {
          console.log("Local Files")
        }
      }
    }
  }
}