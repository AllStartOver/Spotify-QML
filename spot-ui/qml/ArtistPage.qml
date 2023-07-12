import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Flickable {
  property var artist
  id: root
  anchors.fill: parent
  contentHeight: 300 + content.height
  contentWidth: parent.width
  interactive: true
  clip: true

  Rectangle {
    id: background
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    clip: true
    height: 600
    color: "transparent"
    Image {
      id: backgroundImage
      anchors.fill: parent
      fillMode: Image.Stretch
      opacity: 0.8
      Connections {
        target: artist
        enabled: artist !== null
        function onSignalArtistPageRequestCoverFinished() {
          backgroundImage.source = "file:///" + executablePath + "/" + artist.imgFileName
        }
      }
    }
  }

  Rectangle {
    id: content
    anchors.top: background.bottom
    anchors.topMargin: -300
    anchors.left: parent.left
    anchors.right: parent.right
    height: 1000
    color: "pink"

    gradient: Gradient {
      orientation: Gradient.Vertical
      GradientStop { position: 0.0; color: "pink" }
      GradientStop { position: 1.0; color: "black" }
    }
  }

  Connections {
    target: artistAPI
    function onSignalRequestArtistByIDFinished() {
      console.log("onSignalRequestArtistByIDFinished")
      artist = artistAPI.getCurrentArtistPage()
      artist.signalArtistPageRequestCover(artist.imgUrl, artist.id)
    }
  }
}