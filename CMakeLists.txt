cmake_minimum_required(VERSION 3.25)
project(AyleidLogging LANGUAGES CXX VERSION 1.0.1)
include(FetchContent)
FetchContent_Declare(
    AyleidInfrastructure
    GIT_REPOSITORY https://github.com/N8-Wright/Ayleid.Infrastructure
    GIT_TAG main
)
FetchContent_MakeAvailable(AyleidInfrastructure)
list(APPEND CMAKE_PREFIX_PATH "${ayleidinfrastructure_SOURCE_DIR}/CMake")
add_subdirectory(Source)