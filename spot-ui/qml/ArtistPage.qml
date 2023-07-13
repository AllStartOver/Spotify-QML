import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Flickable {
  property var artist
  id: root
  anchors.fill: parent
  contentHeight: 400 + topTracksList.contentHeight + discographyList.contentHeight
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
          artist.calculateAverageCoverColor()
          backgroundGradient.color = artist.averageCoverColor
          console.log(artist.averageCoverColor)
        }
      }
    }
  }

  Rectangle {
    id: backgroundGradient
    anchors.top: topTracksList.top
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    gradient: Gradient {
      orientation: Gradient.Vertical
      GradientStop { position: 0.0; color: backgroundGradient.color }
      GradientStop { position: 0.2; color: Style.colorSpotifyDarkGray }
      GradientStop { position: 1.0; color: Style.colorSpotifyDarkGray }
    }
  }

  ListView {
    id: topTracksList
    anchors.top: parent.top
    anchors.topMargin: 400
    anchors.left: parent.left
    anchors.right: parent.right
    height: contentHeight
    interactive: false

    header: Rectangle {
      width: parent.width
      height: 140
      color: "transparent"
      Image {
        id: playButton
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        height: playButtonMouseArea.containsMouse ? 53 : 50
        width: playButtonMouseArea.containsMouse ? 53 : 50
        source: Utils.ImagePath("PlayGreen.svg")

        MouseArea {
          id: playButtonMouseArea
          anchors.fill: parent
          hoverEnabled: true
          cursorShape: Qt.PointingHandCursor
          onClicked: {
            console.log("playButton clicked")
          }
        } 
      }
      Rectangle {
        id: followButton
        anchors.left: playButton.right
        anchors.leftMargin: 30
        anchors.verticalCenter: playButton.verticalCenter
        height: 30
        width: 100
        border.width: 1
        border.color: followButtonMouseArea.containsMouse ? Style.colorSpotifyWhite : Style.colorSpotifyLightWhite
        radius: 3
        color: "transparent"

        Text {
          anchors.centerIn: parent
          text: "FOLLOW"
          font.pixelSize: 12
          font.bold: true
          color: Style.colorSpotifyWhite
        }
        MouseArea {
          id: followButtonMouseArea
          anchors.fill: parent
          hoverEnabled: true
          onClicked: {
            console.log("followButton clicked")
          }
        }
      }

      Text {
        anchors.left: playButton.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        text: "Popular"
        font.pixelSize: 20
        font.bold: true
        color: Style.colorSpotifyWhite
      }
    }

    delegate: ArtistTrackDelegate {
      track: modelData
    }
    Connections {
      target: artist
      enabled: artist !== null
      function onSignalArtistPageRequestTopTracksFinished() {
        console.log("onSignalRequestArtistTopTracksFinished")
        topTracksList.model = artistAPI.getCurrentArtistPage().topTracks
      }
    }
  }

  ListView {
    id: discographyList
    anchors.top: topTracksList.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    height: contentHeight

    header: Rectangle {
      width: parent.width
      height: 110
      color: "transparent"
      Text {
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "Discography"
        font.pixelSize: 20
        font.bold: true
        color: Style.colorSpotifyWhite
      }
      Row {
        id: discographyButtons 
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        spacing: 10
        Rectangle {
          id: albumsButton
          width: albumsButtonText.width + 20
          height: 30
          color: Style.colorSpotifyLightGray
          radius: 10
          Text {
            id: albumsButtonText
            anchors.centerIn: parent
            text: "Albums"
            font.pixelSize: 12
            color: Style.colorSpotifyWhite
          }
        }

        Rectangle {
          id: singlesButton
          width: singlesButtonText.width + 20
          height: 30
          color: Style.colorSpotifyLightGray
          radius: 10
          Text {
            id: singlesButtonText
            anchors.centerIn: parent
            text: "Singles"
            font.pixelSize: 12
            color: Style.colorSpotifyWhite
          }
        }

        Rectangle {
          id: compilationsButton
          width: compilationsButtonText.width + 20
          height: 30
          color: Style.colorSpotifyLightGray
          radius: 10
          Text {
            id: compilationsButtonText
            anchors.centerIn: parent
            text: "Compilations"
            font.pixelSize: 12
            color: Style.colorSpotifyWhite
          }
        }
      }
    }
  }
  Connections {
    target: artistAPI
    function onSignalRequestArtistByIDFinished() {
      console.log("onSignalRequestArtistByIDFinished")
      artist = artistAPI.getCurrentArtistPage()
      artistAPI.requestArtistTopTracks(artist.id)
      artist.signalArtistPageRequestCover(artist.imgUrl, artist.id)
    }
  }
}