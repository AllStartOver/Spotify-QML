import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

ScrollView {
  anchors.leftMargin: 10
  anchors.rightMargin: 10
  anchors.topMargin: 10
  anchors.bottomMargin: 10

  clip: true

  ScrollBar.vertical.policy: ScrollBar.AlwaysOn
  ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

  Rectangle {
    anchors.fill: parent
    color: Style.colorSpotifyDarkGray
    radius: 5
  }

  Text {
    id: symbolHeader
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.leftMargin: 20
    width: parent.width * 0.03
    font.pixelSize: 14
    clip: true
    text: "#"
    color: "gray"
  }

  Text {
    id: trackNameHeader
    anchors.top: parent.top
    anchors.left: symbolHeader.right
    width: parent.width * 0.45
    font.pixelSize: 14
    clip: true
    text: "标题"
    color: "gray"
  }

  Text {
    id: trackAlbumHeader
    anchors.left: trackNameHeader.right
    anchors.verticalCenter: trackNameHeader.verticalCenter
    width: parent.width * 0.25
    font.pixelSize: 14
    clip: true
    text: "专辑"
    color: "gray"
  }

  Text {
    id: addDateHeader
    anchors.left: trackAlbumHeader.right
    anchors.verticalCenter: trackNameHeader.verticalCenter
    width: parent.width * 0.15
    font.pixelSize: 14
    clip: true
    text: "添加日期"
    color: "gray"
  }

  Text {
    id: durationHeader
    anchors.left: addDateHeader.right
    anchors.verticalCenter: trackNameHeader.verticalCenter
    width: parent.width * 0.15
    font.pixelSize: 14
    clip: true
    text: "时长"
    color: Style.colorSpotifyDarkGray
  }

  Rectangle {
    id: headerLine
    anchors.top: trackNameHeader.bottom
    anchors.topMargin: 10
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.right: parent.right
    anchors.rightMargin: 20
    height: 1
    color: "gray"
  }

  ListView {
    id: playListTracksView
    anchors.top: headerLine.bottom
    anchors.topMargin: 10
    anchors.bottom: parent.bottom
    width: parent.width
    clip: true

    delegate: TrackDelegate {
      id: trackDelegate
      width: parent.width
      height: 50
      track: modelData
    }

    Connections {
      target: playListsAPI
      function onSignalGetPlayListTracksFinished(id){
        playListTracksView.model = playListsAPI.getPlayListTracksByID(id)
      }
    }
  }  
}