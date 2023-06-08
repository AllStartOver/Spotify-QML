qt_add_library(ImagesLib STATIC)

set_target_properties(ImagesLib PROPERTIES
  AUTOMOC ON
  AUTORCC ON
  AUTOUIC ON
)

target_link_libraries(ImagesLib PRIVATE Qt6::Quick)

set(images 
  "pause.svg"
  "play.svg"
  "trackNext.svg"
  "trackPrev.svg"
  "volumnHigh.svg"
  "volumnLow.svg"
  "volumnMuted.svg"
)

qt_add_qml_module(ImagesLib
  URI Images
  VERSION 1.0
  RESOURCE_PREFIX /spotify-qml/imports
  RESOURCES ${images}
)