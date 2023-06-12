import QtQuick
import QtQuick.Controls

Rectangle {
  property color boundaryColor: "black"

  gradient: Gradient {
    orientation: Gradient.Horizontal
    GradientStop { 
      position: 0.0 
      color: boundaryColor
    }
    GradientStop {
      position: 0.02
      color: "transparent"
    }
    GradientStop {
      position: 0.98
      color: "transparent"
    }
    GradientStop {
      position: 1.0
      color: boundaryColor
    }
  }
}