add_library(Ayleid.Logging
    Logger.cpp
    ThreadedLogger.cpp
    ConsoleLogger.cpp
    FileLogger.cpp
    CompositeLogger.cpp
)
add_library(Ayleid::Logging ALIAS Ayleid.Logging)
target_sources(Ayleid.Logging
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
install(TARGETS Ayleid.Logging
    EXPORT
)
find_package(fmt CONFIG REQUIRED)
find_package(ayleid-install-library REQUIRED)
ayleid_install_library(Ayleid.Logging)
target_link_libraries(Ayleid.Logging PUBLIC fmt::fmt)