#include "Ayleid/Logging/ConsoleLogger.hpp"
#include <fmt/format.h>
#include <fmt/chrono.h>
namespace Ayleid::Logging
{
    CConsoleLogger::CConsoleLogger(const ELogLevel logLevel) :
        CThreadedLogger(logLevel)
    {
    }

    CConsoleLogger::~CConsoleLogger()
    {
    }

    void CConsoleLogger::LogInternal(const ELogLevel logLevel, const std::chrono::time_point<std::chrono::system_clock> timestamp, const std::string_view message)
    {
        fmt::print("{} [{}] - {}", timestamp.time_since_epoch(), logLevel, message);
    }
}