cmake_minimum_required(VERSION 3.22)
project(pi_agent_mp3_ui VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Multimedia)

add_executable(pi_agent_mp3_ui
    main.cpp
    playercontroller.h
    playercontroller.cpp
    resources.qrc
)

target_link_libraries(pi_agent_mp3_ui PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Multimedia
)
