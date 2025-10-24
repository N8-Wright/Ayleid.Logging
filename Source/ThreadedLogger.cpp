#include "Ayleid/Logging/ThreadedLogger.hpp"
#include <iostream>
namespace Ayleid::Logging
{
    CThreadedLogger::LogMessage::LogMessage(ELogLevel logLevel, std::string&& message, std::chrono::time_point<std::chrono::system_clock> timestamp) :
        LogLevel(logLevel), Message(std::move(message)), Timestamp(timestamp)
    {
    }

    CThreadedLogger::CThreadedLogger(const ELogLevel logLevel) :
        CLogger(logLevel)
    {
        m_logThread = std::jthread([this](const std::stop_token& token) {
            ProcessToLog(token);
        });
    }

    void CThreadedLogger::Log(const ELogLevel logLevel, std::string&& message)
    {
        std::unique_lock lock(m_logMutex);
        m_toLog.emplace_back(logLevel, std::move(message), std::chrono::system_clock::now());
        m_notifyLogThread.notify_one();
    }

    void CThreadedLogger::ShutdownLogging()
    {
        m_logThread.request_stop();
        m_notifyLogThread.notify_all();
        m_logThread.join();
    }

    void CThreadedLogger::ProcessToLog(const std::stop_token& token)
    {
        while (true)
        {
            try
            {
                std::vector<LogMessage> batch;
                {
                    std::unique_lock lock(m_logMutex);
                    m_notifyLogThread.wait(lock, [this, &token] {
                        return token.stop_requested() || !m_toLog.empty();
                    });

                    if (token.stop_requested() && m_toLog.empty())
                    {
                        break;
                    }

                    std::swap(batch, m_toLog);
                }

                for (const auto& entry : batch)
                {
                    LogInternal(entry.LogLevel, entry.Timestamp, entry.Message);
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << "\n";
            }
            catch (...)
            {
                std::cerr << "Unknown exception\n";
            }
        }
    }
}