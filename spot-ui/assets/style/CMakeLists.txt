qt_add_library(StyleLib STATIC)

set_target_properties(StyleLib PROPERTIES
  AUTOMOC ON
  AUTORCC ON
  AUTOUIC ON
)

target_link_libraries(StyleLib PRIVATE Qt6::Quick)

list(APPEND STYLE_FILES Style.qml)
set_source_files_properties(${STYLE_FILES} PROPERTIES
  QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(StyleLib
  URI Styles
  VERSION 1.0
  RESOURCE_PREFIX /spotify-qml/imports
  QML_FILES 
    ${STYLE_FILES}
)