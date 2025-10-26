add_library(ayleid-logging
    Logger.cpp
    ThreadedLogger.cpp
    ConsoleLogger.cpp
    FileLogger.cpp
    CompositeLogger.cpp
)
add_library(ayleid::logging ALIAS ayleid-logging)
target_sources(ayleid-logging
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../Include"
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../Include/Ayleid/Logging/Logger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Include/Ayleid/Logging/ThreadedLogger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Include/Ayleid/Logging/ConsoleLogger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Include/Ayleid/Logging/FileLogger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Include/Ayleid/Logging/CompositeLogger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Include/Ayleid/Logging/LogLevel.hpp"
)
install(TARGETS ayleid-logging
    EXPORT
)
find_package(fmt CONFIG REQUIRED)
find_package(ayleid-install-library REQUIRED)
ayleid_install_library(ayleid-logging)
target_link_libraries(ayleid-logging PUBLIC fmt::fmt)
set_target_properties(ayleid-logging PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON)
target_compile_features(ayleid-logging PUBLIC cxx_std_20)