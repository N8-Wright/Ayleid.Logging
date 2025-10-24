#pragma once
#include "Ayleid/Logging/ThreadedLogger.hpp"
namespace Ayleid::Logging
{
    class CConsoleLogger : public CThreadedLogger
    {
    public:
        CConsoleLogger(ELogLevel logLevel);
        virtual ~CConsoleLogger() override;
    protected:
        virtual void LogInternal(ELogLevel logLevel, std::chrono::time_point<std::chrono::system_clock> timestamp, std::string_view message) override;
    };
}