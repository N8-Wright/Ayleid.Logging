#pragma once
#include "Ayleid/Logging/LogLevel.hpp"
#include <string>
namespace Ayleid::Logging
{
    class CLogger
    {
    protected:
        ELogLevel m_logLevel;

    public:
        virtual ~CLogger() = default;
        explicit CLogger(ELogLevel logLevel);
        [[nodiscard]] bool IsConfiguredToLog(ELogLevel logLevel) const;
        [[nodiscard]] ELogLevel GetLogLevel() const;
        virtual void Log(ELogLevel logLevel, std::string&& message) = 0;
    };
}