cmake_minimum_required(VERSION 3.8)
project(silver-umbrella)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Gui Widgets REQUIRED)
find_package(Git)

set(${PROJECT_NAME}_SOURCES
    Entry.cpp
    MainWindow.cpp
    MainWindow.ui

    controllers/MidiMessage.cpp
    controllers/Controller.cpp
    controllers/InputController.cpp
    controllers/OutputController.cpp
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE controllers)

file(TOUCH "${PROJECT_BINARY_DIR}/GIT_REVISION_HASH")
if(${GIT_FOUND})
    add_custom_target(git-revision-hash)
    set(HASH_COMMAND "\"\"${GIT_EXECUTABLE}\" log -n 1 --decorate=full --pretty='%H' > \"${PROJECT_BINARY_DIR}/GIT_REVISION_HASH\"\"")
    add_custom_command(TARGET git-revision-hash PRE_BUILD COMMAND ${HASH_COMMAND} DEPENDS ${PROJECT_NAME} COMMENT "Evaluating ${HASH_COMMAND}")
    add_dependencies(${PROJECT_NAME} git-revision-hash)
    file(READ "${PROJECT_BINARY_DIR}/GIT_REVISION_HASH" GIT_REVISION_HASH)
    message("Git revision hash: ${GIT_REVISION_HASH}")
endif()

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} Winmm)
    
    get_filename_component(_qt_bin_dir "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt.exe HINTS "${_qt_bin_dir}")
    message("Found windeployqt executable: ${WINDEPLOYQT_EXECUTABLE}")
    message("Binary is in: $<TARGET_FILE_DIR:${PROJECT_NAME}>")
    add_custom_command(TARGET ${PROJECT_NAME} COMMAND ${WINDEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${PROJECT_NAME}>")
endif()

add_executable(${PROJECT_NAME}-OLD main.c)

set_target_properties(${PROJECT_NAME}-OLD PROPERTIES LINK_FLAGS "/ENTRY:demo /SUBSYSTEM:Windows /OPT:REF /OPT:ICF=10 /VERBOSE /NODEFAULTLIB")
target_compile_options(${PROJECT_NAME}-OLD PRIVATE /Gy /O1 /fp:fast /GR- /GS- /MT )
target_link_libraries(${PROJECT_NAME}-OLD Winmm.lib  User32.lib Winmm.lib ucrt.lib msvcrt.lib)