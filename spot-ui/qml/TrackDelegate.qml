import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  color: Style.colorSpotifyDarkGray
  property var track

  Text {
    id: trackIndex
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.03
    font.pixelSize: 14
    clip: true
    text: index + 1
    color: "white"
  }

  Rectangle {
    id: trackCover
    anchors.left: trackIndex.right
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.04
    height: width
    color: "white"
  }

  Text {
    id: trackName
    font.pixelSize: 12
    anchors.left: trackCover.right
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -5
    width: parent.width * 0.41
    text: track.name
    leftPadding: 10
    color: "white"
  }

  ListView {
    id: trackArtists
    anchors.left: trackCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 5
    width: parent.width * 0.35
    orientation: ListView.Horizontal
    model: track.artists
    delegate: Row {
      Text {
        text: modelData.name
        color: "gray"
        font.pixelSize: 12
        MouseArea {
          anchors.fill: parent
          onClicked: {
            console.log("Clicked on artist: " + modelData.name)
          }
        }
      }
      Text {
        text: index < trackArtists.count - 1 ? ", " : ""
        color: "gray"
        font.pixelSize: 12
      }
    }
  }

  Text {
    id: albumName
    font.pixelSize: 14
    anchors.left: trackName.right
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.25
    text: track.album
    color: "gray"
  }

  Text {
    id: addDate
    anchors.left: albumName.right
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.15
    text: "Mock Add Date"
    font.pixelSize: 12
    color: "gray"
  }

  Text {
    id: duration
    anchors.left: addDate.right
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.15
    text: "Mock Duration"
    font.pixelSize: 12
    color: "gray"
  }
}