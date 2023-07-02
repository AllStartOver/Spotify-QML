import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

ListView {
  id: albumTracksView
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

  delegate: AlbumTrackDelegate {
    id: albumTrackDelegate
    width: parent.width
    height: 50
    track: modelData
  }

  Connections {
    target: albumAPI
    function onSignalRequestAlbumByIDFinished() {
      console.log("onSignalRequestAlbumByIDFinished" + ", " + albumAPI.currentAlbumID)
      console.log(albumAPI.getCurrentAlbum().name)
      albumTracksView.model = albumAPI.getCurrentAlbum().tracks
    }
  }
}