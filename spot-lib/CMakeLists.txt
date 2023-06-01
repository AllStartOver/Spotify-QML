cmake_minimum_required(VERSION 3.15)
project(spotify-qml)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/msvc2019_64/lib/cmake" "C:/libs/lib/cmake")
    find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network)
    find_package(fmt REQUIRED) 
endif()

include_directories(
    .
    controllers
    network
)

aux_source_directory(controllers CONTROLLERS_SOURCE)
aux_source_directory(network NETWORK_SOURCE)

add_library(spotify-qml STATIC
    ${CONTROLLERS_SOURCE}
    ${NETWORK_SOURCE}
    libSpotify_global.h
)

target_link_libraries(spotify-qml 
    Qt6::Core
    Qt6::Network
)

target_compile_definitions(spotify-qml PRIVATE LIBSPOTIFY_LIBRARY)

if(WIN32)
    target_compile_definitions(spotify-qml PRIVATE WINDOWS)
endif()