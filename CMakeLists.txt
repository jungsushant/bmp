# CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(bitmap VERSION 1.0 LANGUAGES CXX)

# Specify C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Recursively collect all source files
file(GLOB_RECURSE SRCS src/*.cpp)

# Recursively collect all header directories under include/
file(GLOB_RECURSE HEADER_DIRS RELATIVE ${PROJECT_SOURCE_DIR} include/*)

# Find the GTKmm 4 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Add executable
add_executable(${PROJECT_NAME} ${SRCS})

# Link GTKmm libraries
target_link_libraries(bitmap PRIVATE ${GTKMM_LIBRARIES})

# Include GTKmm headers and all header directories under include/
target_include_directories(bitmap PRIVATE ${GTKMM_INCLUDE_DIRS})
target_include_directories(bitmap PRIVATE ${PROJECT_SOURCE_DIR}/include)
foreach(dir ${HEADER_DIRS})
    get_filename_component(absolute_dir ${PROJECT_SOURCE_DIR}/${dir} DIRECTORY)
    target_include_directories(bitmap PRIVATE ${absolute_dir})
endforeach()

# Set the compile options
target_compile_options(bitmap PRIVATE ${GTKMM_CFLAGS_OTHER})

# Install target
install(TARGETS bitmap DESTINATION bin)
