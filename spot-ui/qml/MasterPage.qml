import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Item {
  property var stackPages: []
  property int currentIndex: 0
  Button {
    id: backwardButton
    text: "<"
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.top: parent.top
    anchors.topMargin: 10
    width: 50
    height: 50

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
        albumAPI.requestAlbumByID(page.id)
        pageLoader.source = page.source
      }
    }
  }

  Button {
    id: forwardButton
    text: ">"
    anchors.left: backwardButton.right
    anchors.leftMargin: 10
    anchors.top: parent.top
    anchors.topMargin: 10
    width: 50
    height: 50

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
        albumAPI.requestAlbumByID(page.id)
        pageLoader.source = page.source
      }
    }
  }

  Loader {
    id: pageLoader
    anchors.top: forwardButton.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom

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
    }
  }

  Component.onCompleted: {
    pageLoader.source = Utils.QMLPath("HomePage.qml")
    stackPages.push({id: 0, source: Utils.QMLPath("HomePage.qml")})
  }
}