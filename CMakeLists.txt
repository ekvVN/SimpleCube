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

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(SOURCE_FILES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES})