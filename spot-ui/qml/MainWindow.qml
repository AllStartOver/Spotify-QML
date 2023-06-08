import QtQuick.Window
import QtQuick.Controls
import Views 1.0
import Images 1.0
import Styles 1.0

Window {
  visible: true
  width: Style.defaultWindowWidth
  height: Style.defaultWindowHeight
  title: qsTr("Spotify-QML")

  Player {
  }
}