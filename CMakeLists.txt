# Minimal example of how to avoid installing OpenCV on Windows but instead have CMake fetch
# an OpenCV release from GitHub and use it to build an executable.
cmake_minimum_required(VERSION 3.24)
project(my_project)
set(CMAKE_CXX_STANDARD 17)

# Fetch and unpack a prebuilt OpenCV 7zip file (disguised as an .exe but CMake knows what to do)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
        opencv
        URL https://github.com/opencv/opencv/releases/download/4.8.0/opencv-4.8.0-windows.exe
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_Populate(opencv)

# Tell CMake where to find the OpenCV headers and libraries, namely the ones we just downloaded
set(CMAKE_PREFIX_PATH "${opencv_SOURCE_DIR}/build/x64/vc16/lib/")
find_package(OpenCV)

# Add an executable that uses the OpenCV libraries
# This will build just fine, but to run or debug it, on Windows you need to add
# "${opencv_SOURCE_DIR}/build/x64/vc16/bin" to your PATH environment variable.
# This is precisely because we didn't install OpenCV, we just downloaded it.
# VS Code: For an example how to do this in VS Code, see provided .vscode/settings.json.
#          Note that with the VS Code CMake extension, for some reason you need to press
#          Ctrl+F5 (not F5 as you'd expect) to debug the executable.
add_executable(my_target main.cpp)
target_link_libraries(my_target opencv_core opencv_highgui)
