#pragma once
#include "Ayleid/Logging/Logger.hpp"
#include "Ayleid/Logging/LogLevel.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
namespace Ayleid::Logging
{
    class CThreadedLogger : public CLogger
    {
        struct LogMessage
        {
            ELogLevel LogLevel;
            std::string Message;
            std::chrono::time_point<std::chrono::system_clock> Timestamp;
            LogMessage(ELogLevel logLevel, std::string&& message, std::chrono::time_point<std::chrono::system_clock> timestamp);
        };

        std::vector<LogMessage> m_toLog;
        std::mutex m_logMutex;
        std::jthread m_logThread;
        std::condition_variable m_notifyLogThread;

    public:
        explicit CThreadedLogger(ELogLevel logLevel);
        virtual void Log(ELogLevel logLevel, std::string&& message) override;

    protected:
        virtual void LogInternal(ELogLevel logLevel, std::chrono::time_point<std::chrono::system_clock> timestamp, std::string_view message) = 0;
        void ShutdownLogging();

    private:
        void ProcessToLog(const std::stop_token& token);
    };
}