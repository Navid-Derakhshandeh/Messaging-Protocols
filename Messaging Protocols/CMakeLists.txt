cmake_minimum_required(VERSION 3.16)
project(Protocols)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

add_executable(Protocols
    main.cpp
    mainwindow.cpp
    mainwindow.ui

       peerconnection.cpp
       peerconnection.h
       server.cpp
       server.h

)

target_link_libraries(Protocols Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)
