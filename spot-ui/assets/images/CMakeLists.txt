qt_add_library(ImagesLib STATIC)

set_target_properties(ImagesLib PROPERTIES
  AUTOMOC ON
  AUTORCC ON
  AUTOUIC ON
)

target_link_libraries(ImagesLib PRIVATE Qt6::Quick)

set(images 
  "pause.svg"
  "pause2.svg"
  "play.svg"
  "play2.svg"
  "trackNext.svg"
  "trackNextHover.svg"
  "trackPrev.svg"
  "trackPrevHover.svg"
  "volumnHigh.svg"
  "volumnLow.svg"
  "volumnMuted.svg"
  "devices.svg"
  "loop.svg"
  "loopEnabled.svg"
  "singleLoop.svg"
  "queue.svg"
  "queueOpened.svg"
  "shuffle.svg"
  "shuffleEnabled.svg"
  "heartGray.svg"
  "heartGreen.svg"
)

qt_add_qml_module(ImagesLib
  URI Images
  VERSION 1.0
  RESOURCE_PREFIX /spotify-qml/imports
  RESOURCES ${images}
)