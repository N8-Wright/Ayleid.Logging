cmake_minimum_required(VERSION 3.25)
project(Ayleid.Logging LANGUAGES CXX VERSION 1.0.7)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Infrastructure/CMake")
add_subdirectory(Source)