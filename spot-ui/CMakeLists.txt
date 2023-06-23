cmake_minimum_required(VERSION 3.16)

project(spot-ui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/libs/lib/cmake" "C:/Qt/6.5.0/msvc2019_64/lib/cmake")
    find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick)
elseif(APPLE)
    find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick)
endif()

include_directories(../spot-lib/src/include 
    ../spot-lib/
)

if(WIN32)
    file(GLOB SPOT_LIB "../spot-lib/build/Debug/*.lib")
elseif(APPLE)
    file(GLOB SPOT_LIB "../spot-lib/build/*.a")
endif()

message(${SPOT_LIB})

qt_standard_project_setup()

qt_add_executable(spot-ui
    main.cpp
)

set(qml_files 
    "qml/MainWindow.qml"
    "qml/Player.qml"
    "qml/BoundFadeEffect.qml"
    "qml/PlayListPage.qml"
    "qml/PlayListDelegate.qml"
    "qml/TrackDelegate.qml"
    "qml/Utils.js"
)

# add qml files to target
qt_add_qml_module(spot-ui
    URI Views
    VERSION 1.0
    RESOURCE_PREFIX /spotify-qml/imports
    QML_FILES 
        ${qml_files}
)

add_subdirectory(assets/images)
add_subdirectory(assets/style)

# qt_add_qml_module(spot-ui 
#     URI Images
#     VERSION 1.0
#     RESOURCE_PREFIX /spotify-qml/imports
#     RESOURCES
#         ${img_files}
# )

target_link_libraries(spot-ui
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    PRIVATE ${SPOT_LIB}
    PRIVATE ImagesLibplugin
    PRIVATE StyleLibplugin
)

if (WIN32)
    target_compile_definitions(spot-ui PRIVATE WINDOWS)
endif()
if (APPLE)
    target_compile_definitions(spot-ui PRIVATE MACOS)
endif()