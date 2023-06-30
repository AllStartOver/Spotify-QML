import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Views 1.0
import Styles 1.0

Rectangle {
  property var centerText: "HomePage"
  anchors.fill: parent
  color: "pink"
  radius: 5

  Text {
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    text: centerText
    font.pixelSize: 20
  }
}