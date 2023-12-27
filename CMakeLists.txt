cmake_minimum_required(VERSION 3.24)
project(ActionSudoku)
set(APPLICATION_LIBRARY SudokuLib)

set(CMAKE_CXX_STANDARD 17)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp
        SudokuApp.cpp
        SudokuApp.h
        pch.h
        ActionSudoku.rc
)

set(MACOSX_BUNDLE_EXECUTABLE_NAME ActionSudoku)
set (MACOSX_BUNDLE_ICON_FILE ActionSudoku.icns)
set(PROJECT_NAME_ICON Images/ActionSudoku.icns)
set(WIN32_ICON Images/ActionSudoku.ico)
set_source_files_properties(${PROJECT_NAME_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${PROJECT_NAME_ICON} ${WIN32_ICON} ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)
#TEST
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Levels/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Audio/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Audio/)

add_subdirectory(Tests)