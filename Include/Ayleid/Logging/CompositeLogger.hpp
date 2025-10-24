#pragma once
#include "Logger.hpp"
#include <vector>
#include <memory>
namespace Ayleid::Logging
{
	class CCompositeLogger final : public CLogger
	{
        std::vector<std::shared_ptr<CLogger>> m_loggers;

    public:
        CCompositeLogger();
        void RegisterLogger(std::shared_ptr<CLogger> logger);
        virtual void Log(ELogLevel logLevel, std::string&& message) override;
	};
}