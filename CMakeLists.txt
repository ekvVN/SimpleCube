cmake_minimum_required(VERSION 3.8)
project(QtGuiExample)

set(CMAKE_CXX_STANDARD 11)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# и ui compiler
set(CMAKE_AUTOUIC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_CXX_FLAGS "-O2")
#SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
#SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

set(SOURCE_FILES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        geometry.cpp
        geometry.h
        model.cpp
        model.h
        MyPainter.cpp
        MyPainter.h
        Matrix3x3.h
        PrimitivePainter.cpp
        PrimitivePainter.h
        Image.h
        ViewMatrix.cpp
        ViewMatrix.h
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

qt5_use_modules(${PROJECT_NAME} Widgets)