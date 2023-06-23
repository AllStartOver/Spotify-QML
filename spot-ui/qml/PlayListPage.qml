import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  anchors.leftMargin: 10
  anchors.rightMargin: 10
  anchors.topMargin: 10
  anchors.bottomMargin: 10
  radius: 5
  color: Style.colorSpotifyDarkGray

  ListView {
    id: playListTracksView
    anchors.topMargin: 10
    anchors.fill: parent

    delegate: TrackDelegate {
      id: trackDelegate
      width: parent.width
      height: 50
    }

    Connections {
      target: playListsAPI
      function onSignalGetPlayListTracksFinished(id){
        playListTracksView.model = playListsAPI.getPlayListTracksByID(id)
      }
    }
  }  
}