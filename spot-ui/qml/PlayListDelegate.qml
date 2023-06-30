import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  property alias playListCoverSource: playListCover.source;
  property var playList;
  color: Style.colorSpotifyDarkGray

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
    font.pixelSize: 12
    anchors.left: playListCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -10
    text: playList.name
    color: "white"
  }

  Text {
    id: playListOwner
    font.pixelSize: 12
    anchors.left: playListCover.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 10
    text: playList.owner
    color: "gray"
  }

  MouseArea {
    anchors.fill: parent
    onClicked: {
      viewController.signalChangePlayListSource(Utils.QMLPath("PlayListPage.qml"), playList.id)
      playList.signalPlayListRequestTracks(playList.id)
    }
  }

  Component.onCompleted: {
    playList.signalPlayListRequestCover(playList.img_url, playList.id)
  }   
  Connections {
    target: modelData
    function onSignalPlayListRequestCoverFinished() {
      playListCoverSource = "file:///" + executablePath + "/" + playList.imgFileName;
    }
  }
}