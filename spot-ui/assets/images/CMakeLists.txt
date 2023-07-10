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
  "loopOff.svg"
  "loopContext.svg"
  "loopTrack.svg"
  "queue.svg"
  "queueOpened.svg"
  "shuffle.svg"
  "shuffleEnabled.svg"
  "heartGray.svg"
  "heartGreen.svg"
  "image_test.jpeg"
  "HomeGray.svg"
  "HomeWhite.svg"
  "HomeFocus.svg"
  "SearchGray.svg"
  "SearchWhite.svg"
  "SearchFocus.svg"
  "Back.svg"
  "Forward.svg"
  "PlayGreen.svg"
  "PauseGreen.svg"
  "TrackPlay.svg"
  "TrackPlayGreen.svg"
  "TrackPause.svg"
  "AudioWave.svg"
  "VolumnMuteWhite.svg"
  "PlaylistPlayGreen.svg"
  "PlaylistPauseWhite.svg"
  "LibraryWhite.svg"
  "FilterBack.svg"
  "FilterForward.svg"
  "FilterCross.svg"
)

qt_add_qml_module(ImagesLib
  URI Images
  VERSION 1.0
  RESOURCE_PREFIX /spotify-qml/imports
  RESOURCES ${images}
)