#include "Ayleid/Logging/CompositeLogger.hpp"
#include <algorithm>
namespace Ayleid::Logging
{
    CCompositeLogger::CCompositeLogger() :
        CLogger(ELogLevel::Critial)
    {
    }

    void CCompositeLogger::RegisterLogger(std::shared_ptr<CLogger> logger)
    {
        m_logLevel = std::max(logger->GetLogLevel(), m_logLevel);
        m_loggers.push_back(std::move(logger));
    }

    void CCompositeLogger::Log(ELogLevel logLevel, std::string&& message)
    {
        const auto owningMessage = std::move(message);
        for (const auto& logger : m_loggers)
        {
            if (logger->IsConfiguredToLog(logLevel))
            {
                auto copy = owningMessage;
                logger->Log(logLevel, std::move(copy));
            }
        }
    }
}