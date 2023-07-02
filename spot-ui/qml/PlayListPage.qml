import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

ListView {
  property var context_uri
  id: playListTracksView
  anchors.fill: parent 
  interactive: true
  clip: true

  header: Rectangle {
    width: parent.width
    height: 400
    color: Style.colorSpotifyWhite

    Image {
      id: cover
      anchors.left: parent.left
      anchors.leftMargin: 30
      anchors.top: parent.top
      anchors.topMargin: 60
      height: 240
      width: 240
      source: Utils.ImagePath("image_test.jpeg")
    } 
  }

  delegate: TrackDelegate {
    id: trackDelegate
    width: parent.width
    height: 50
    track: modelData

    Component.onCompleted: {
      modelData.signalTrackRequestCover(modelData.img_url)
    }
  }

  Connections {
    target: playListsAPI
    function onSignalGetPlayListTracksFinished(id) {
      var playList = playListsAPI.getPlayListByID(id)
      playListTracksView.model = playList.tracks
    }
  }
  Component.onCompleted: {
    var id = playListsAPI.currentPlayListID
    playListTracksView.model = playListsAPI.getPlayListByID(id).tracks
  }
}

