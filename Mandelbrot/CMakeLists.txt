cmake_minimum_required(VERSION 3.16)
project(Mandelbrot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(Mandelbrot MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    imagerender.cpp
    myclassscene.cpp
    complex.cpp
    mainwindow.ui
    label.qrc
)

target_link_libraries(Mandelbrot PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
