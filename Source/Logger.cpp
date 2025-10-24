#include "Ayleid/Logging/Logger.hpp"
namespace Ayleid::Logging
{
    CLogger::CLogger(const ELogLevel logLevel) :
        m_logLevel(logLevel)
    {
    }

    bool CLogger::IsConfiguredToLog(ELogLevel logLevel) const
    {
        return m_logLevel >= logLevel;
    }

    ELogLevel CLogger::GetLogLevel() const
    {
        return m_logLevel;
    }
}