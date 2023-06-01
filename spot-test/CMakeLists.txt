cmake_minimum_required(VERSION 3.15)

project(spot-test)

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/libs/lib/cmake" "C:/Qt/6.5.0/msvc2019_64/lib/cmake")
    find_package(GTest REQUIRED)
    find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network Gui Test)
endif()

include_directories(../spot-lib)
file(GLOB SPOT_LIB "../spot-lib/build/Debug/*.lib")
message(${SPOT_LIB})

include_directories(testsuite)
aux_source_directory(testsuite TESTSUITE_SRC)

add_executable(spot-test main.cpp ${TESTSUITE_SRC})

target_link_libraries(spot-test 
    PRIVATE GTest::GTest
    PRIVATE GTest::Main
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Test
    PRIVATE ${SPOT_LIB}
)