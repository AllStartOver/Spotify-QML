import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  property var track
  color: Style.colorSpotifyDarkGray

  Text {
    id: trackIndex
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.verticalCenter: parent.verticalCenter
    font.pixelSize: 14
    clip: true
    text: index + 1
    color: Style.colorSpotifyLightGray
  }

  Text {
    id: trackName
    anchors.left: trackIndex.right
    anchors.leftMargin: 20
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -7
    font.pixelSize: 12
    text: track.name
    color: "white"
  }

  Text {
    id: artists
    anchors.left: trackIndex.right
    anchors.leftMargin: 20
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 7
    font.pixelSize: 10
    text: "Mock Aritst"
    color: Style.colorSpotifyLightGray
  }

  MouseArea {
    anchors.fill: parent
    x: 1
    hoverEnabled: true
    onDoubleClicked: {
      console.log("double clicked" + track.name)
      var album = albumAPI.getCurrentAlbum()
      playerAPI.startPlayback(album.uri, index)
    }
  }
}