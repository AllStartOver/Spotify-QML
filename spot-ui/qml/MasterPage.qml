import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Item {
  property var stackPages: []
  property int currentIndex: 0

  Rectangle {
    anchors.fill: parent
    color: Style.colorSpotifyDarkGray
  }
  Image {
    z: 3
    id: backwardButton
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.top: parent.top
    anchors.topMargin: 10
    width: 30
    height: 30
    opacity: currentIndex === 0 ? 0.5 : 1
    source: Utils.ImagePath("Back.svg")

    MouseArea {
      anchors.fill: parent
      hoverEnabled: currentIndex !== 0
      cursorShape: containsMouse && currentIndex !== 0 ? Qt.PointingHandCursor : Qt.ArrowCursor
      onClicked: {
        if (currentIndex == 0)
          return
        currentIndex--
        var page = stackPages[currentIndex]
        if (page.source == Utils.QMLPath("PlayListPage.qml"))
        {
          pageLoader.source = page.source
          playListsAPI.getPlayListByID(page.id).signalPlayListRequestTracks(page.id)
        }
        else if (page.source == Utils.QMLPath("HomePage.qml"))
        {
          pageLoader.source = page.source
        }
        else if (page.source == Utils.QMLPath("AlbumPage.qml"))
        {
          pageLoader.source = page.source
          albumAPI.requestAlbumByID(page.id)
        }
        else if (page.source == Utils.QMLPath("ArtistPage.qml"))
        {
          pageLoader.source = page.source
          artistAPI.requestArtistByID(page.id)
        }
      }
    }
  }

  Image {
    z : 3
    id: forwardButton
    anchors.left: backwardButton.right
    anchors.leftMargin: 10
    anchors.top: parent.top
    anchors.topMargin: 10
    width: 30
    height: 30
    opacity: currentIndex === stackPages.length - 1 ? 0.5 : 1
    source: Utils.ImagePath("Forward.svg")

    MouseArea {
      anchors.fill: parent
      hoverEnabled: currentIndex !== stackPages.length - 1
      cursorShape: containsMouse && currentIndex !== stackPages.length - 1 ? Qt.PointingHandCursor : Qt.ArrowCursor
      onClicked: {
        if (currentIndex == stackPages.length - 1)
          return
        currentIndex++
        var page = stackPages[currentIndex]
        if (page.source == Utils.QMLPath("PlayListPage.qml"))
        {
          pageLoader.source = page.source
          playListsAPI.getPlayListByID(page.id).signalPlayListRequestTracks(page.id)
        }
        else if (page.source == Utils.QMLPath("HomePage.qml"))
        {
          pageLoader.source = page.source
        }
        else if (page.source == Utils.QMLPath("AlbumPage.qml"))
        {
          pageLoader.source = page.source
          albumAPI.requestAlbumByID(page.id)
        }
        else if (page.source == Utils.QMLPath("ArtistPage.qml"))
        {
          pageLoader.source = page.source
          artistAPI.requestArtistByID(page.id)
        }
      }
    }
  }

  Loader {
    id: pageLoader
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    z: 1

    Connections {
      target: viewController
      function onSignalChangePlayListSource(source, id)
      {
        pageLoader.source = source
        stackPages.push({id: id, source: source})
        currentIndex++
      }
      function onSignalChangeAlbumSource(source, id)
      {
        pageLoader.source = source
        stackPages.push({id: id, source: source})
        currentIndex++
      }
      function onSignalChangeArtistSource(source, id)
      {
        pageLoader.source = source
        stackPages.push({id: id, source: source})
        currentIndex++
      }
    }
  }

  Component.onCompleted: {
    pageLoader.source = Utils.QMLPath("HomePage.qml")
    stackPages.push({id: 0, source: Utils.QMLPath("HomePage.qml")})
  }
}