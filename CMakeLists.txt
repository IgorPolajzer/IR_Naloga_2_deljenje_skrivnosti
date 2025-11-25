cmake_minimum_required(VERSION 4.0)
project(Naloga_2_deljenje_skrivnosti)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")
list(APPEND CMAKE_MODULE_PATH "C:/msys64/mingw64/lib/cmake/fltk")

# Find FLTK package
find_package(FLTK REQUIRED)

# Include FLTK directories
include_directories(${FLTK_INCLUDE_DIR})
include_directories("C:/Libraries/boost_1_89_0/boost_1_89_0")

# Add executable
add_executable(Naloga_2_deljenje_skrivnosti main.cpp
        lcg.h
        lcg.cpp)

# Link FLTK libraries
target_link_libraries(Naloga_2_deljenje_skrivnosti ${FLTK_LIBRARIES})
