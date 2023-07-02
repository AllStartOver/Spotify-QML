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
    width: parent.width * 0.03
    font.pixelSize: 14
    clip: true
    text: index + 1
    color: "white"
  }

  Image {
    id: trackCover
    anchors.left: trackIndex.right
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.04
    height: width
  }

  Text {
    id: trackName
    font.pixelSize: 12
    anchors.left: trackCover.right
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -7
    width: parent.width * 0.41
    text: track.name
    leftPadding: 10
    color: "white"
  }

  ListView {
    id: trackArtists
    visible: true
    anchors.left: trackCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 7
    width: parent.width * 0.35
    height: 10
    orientation: ListView.Horizontal
    model: track.artists
    delegate: Row {
      Text {
        font.pixelSize: 12
        text: modelData.name
        color: "gray"
      }
      Text {
        font.pixelSize: 12
        text: index < trackArtists.count - 1 ? ", " : ""
        color: "gray"
      }
    }
  }

  Text {
    id: albumName
    font.pixelSize: 14
    anchors.left: trackName.right
    anchors.verticalCenter: parent.verticalCenter
    z: 2
    width: parent.width * 0.25
    text: track.album
    font.bold: true
    color: "white"
    opacity: albumMouseArea.containsMouse ? 1 : 0.5

    MouseArea {
      id: albumMouseArea
      anchors.fill: albumName
      hoverEnabled: true
      preventStealing: true
      onClicked: {
        albumAPI.requestAlbumByID(track.album_id)
        viewController.signalChangeAlbumSource(Utils.QMLPath("AlbumPage.qml"), track.album_id)
      }
    }
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
    text: track.duration_ms
    font.pixelSize: 12
    color: "gray"
  }

  MouseArea {
    anchors.fill: parent
    z: 1
    hoverEnabled: true
    onDoubleClicked: {
      playerAPI.startPlayback(track.context_uri, index)
    }
    onEntered: {
    }
    onExited: {
      parent.color = Style.colorSpotifyDarkGray
    }
  }

  Connections {
    target: track
    function onSignalTrackRequestCoverFinished() {
      trackCover.source = "file:///" + executablePath + "/" + track.imgFileName
    }
  }
}