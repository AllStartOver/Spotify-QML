cmake_minimum_required(VERSION 3.15)
project(spotify-qml)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/msvc2019_64/lib/cmake" "C:/libs/lib/cmake")
    find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network Qml Gui)
elseif(APPLE)
    find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network Qml Gui)
endif()

include_directories(
    .
    src/include
)

# collect sources
aux_source_directory(src/network NETWORK_SOURCES)
aux_source_directory(src/controllers CONTROLLERS_SOURCES)
aux_source_directory(src/setting SETTING_SOURCES)
aux_source_directory(src/network/spotify-api SPOTIFY_SOURCES)
aux_source_directory(src/data DATA_SOURCES)

# collect headers
file(GLOB NETWORK_HEADERS src/include/network/*.h)
file(GLOB SPOTIFY_HEADERS src/include/network/spotify-api/*.h)
file(GLOB CONTROLLERS_HEADERS src/include/controllers/*.h)
file(GLOB SETTING_HEADERS src/include/setting/*.h)
file(GLOB DATA_HEADERS src/include/data/*.h)

add_library(spotify-qml STATIC
    ${NETWORK_SOURCES}
    ${CONTROLLERS_SOURCES}
    ${SETTING_SOURCES}
    ${SPOTIFY_SOURCES}
    ${DATA_SOURCES}

    ${NETWORK_HEADERS}
    ${SPOTIFY_HEADERS}
    ${CONTROLLERS_HEADERS}
    ${SETTING_HEADERS}
    ${DATA_HEADERS}
    libSpotify_global.h
)

target_link_libraries(spotify-qml 
    Qt6::Core
    Qt6::Network
    Qt6::Qml
    Qt6::Gui
)

target_compile_definitions(spotify-qml PRIVATE LIBSPOTIFY_LIBRARY)

if(WIN32)
    target_compile_definitions(spotify-qml PRIVATE WINDOWS)
elseif(APPLE)
    target_compile_definitions(spotify-qml PRIVATE MACOS)
endif()