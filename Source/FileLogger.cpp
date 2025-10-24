#include "Ayleid/Logging/FileLogger.hpp"
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <cerrno>
#include <system_error>
namespace Ayleid::Logging
{
    CFileLogger::CFileLogger(const ELogLevel logLevel, const std::filesystem::path& path) :
        CThreadedLogger(logLevel)
    {
        #ifdef _WIN32
        m_file = _wfopen(path.c_str(), L"w");
        #else
        m_file = fopen(path.c_str(), "w");
        #endif

        if (m_file == nullptr)
        {
            throw std::system_error(errno, std::generic_category(), std::string("Failed to open file: ") + path.string());
        }
    }

    CFileLogger::~CFileLogger()
    {
        ShutdownLogging();
        fclose(m_file);
    }

    void CFileLogger::LogInternal(const ELogLevel logLevel, const std::chrono::time_point<std::chrono::system_clock> timestamp, const std::string_view message)
    {
        fmt::print(m_file, "{} [{}] - {}", timestamp.time_since_epoch(), logLevel, message);
    }
}