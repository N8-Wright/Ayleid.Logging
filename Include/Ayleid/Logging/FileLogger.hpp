#pragma once
#include "Ayleid/Logging/ThreadedLogger.hpp"
#include <cstdio>
#include <filesystem>
namespace Ayleid::Logging
{
    class CFileLogger : public CThreadedLogger
    {
        FILE* m_file;

    public:
        CFileLogger(ELogLevel logLevel, const std::filesystem::path& path);
        virtual ~CFileLogger() override;

    protected:
        virtual void LogInternal(ELogLevel logLevel, std::chrono::time_point<std::chrono::system_clock> timestamp, std::string_view message) override;
    };
}