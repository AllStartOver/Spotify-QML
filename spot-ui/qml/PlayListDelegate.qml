import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  property alias playListCoverSource: playListCover.source;
  property var playList: modelData
  property bool isPlaying : playList.uri === playerState.uri
  color: playListMouseArea.containsMouse ? Style.colorSpotifyLightGray : Style.colorSpotifyDarkGray

  Image {
    id: playListCover
    width: 60
    height: width
    anchors.verticalCenter: parent.verticalCenter
    anchors.left: parent.left
    anchors.leftMargin: 10
  }

  Text {
    id: playListName
    font.pixelSize: 14
    anchors.left: playListCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -13
    text: playList.name
    color: isPlaying ? Style.colorSpotifyGreen : Style.colorSpotifyWhite
  }

  Text {
    id: playListOwner
    font.pixelSize: 12
    anchors.left: playListCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 13
    text: playList.owner
    color: "gray"
  }

  Image {
    id: playListPlaying
    width: 16
    height: width
    anchors.right: parent.right
    anchors.rightMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    source: playListPlayingMouseArea.containsMouse ? Utils.ImagePath("PlaylistPauseWhite.svg") : Utils.ImagePath("PlaylistPlayGreen.svg") 
    visible: isPlaying

    MouseArea {
      id: playListPlayingMouseArea
      anchors.fill: parent
      hoverEnabled: true
    }
  }

  MouseArea {
    id: playListMouseArea
    anchors.fill: parent
    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
    onClicked: {
      viewController.signalChangePlayListSource(Utils.QMLPath("PlayListPage.qml"), playList.id)
      playList.signalPlayListRequestTracks(playList.id)
    }
  }

  Component.onCompleted: {
    playList.signalPlayListRequestCover(playList.img_url, playList.id)
  }   
  Connections {
    target: playList
    function onSignalPlayListRequestCoverFinished() {
      playListCoverSource = "file:///" + executablePath + "/" + playList.imgFileName;
    }
  }
  Connections {
    target: playerState
    function onSignalContextChanged() {
      isPlaying = playerState.uri == playList.uri
    }
  }
}