#pragma once

#include "Ayleid/Logging/Logger.hpp"

#include <functional>
#include <memory>

namespace Ayleid::Logging
{
    template<typename T>
    concept DerivedFromLogger = std::is_base_of_v<CLogger, T>;

    // Helper to extract function signature from a lambda
    template<typename T>
    struct CLambdaTraits;

    template<typename R, typename... Args>
    struct CLambdaTraits<R (*)(Args...)>
    {
        using ReturnType = R;
        using ArgsTuple = std::tuple<Args...>;
    };

    template<typename R, typename... Args>
    struct CLambdaTraits<std::function<R(Args...)>>
    {
        using ReturnType = R;
        using ArgsTuple = std::tuple<Args...>;
    };

    // NOTE: The unary + operator on a lambda converts it to a function pointer if possible.
    // See: https://stackoverflow.com/questions/70505162/why-would-one-want-to-put-a-unary-plus-operator-in-front-of-a-c-lambda
    template<typename TLambda>
    struct CLambdaTraits : CLambdaTraits<decltype(+std::declval<TLambda>())>
    {
    };

    template<typename TGeneratedLog, typename TLogLambda, typename... TGenArgs>
    class CLoggerDelegate
    {
    public:
        CLoggerDelegate(const ELogLevel logLevel, TLogLambda&& logGenerator) :
            m_logLevel(logLevel), m_logGenerator(std::move(logGenerator))
        {
        }

        template<DerivedFromLogger TLogger, typename... TArgs>
        inline void operator()(TLogger& logger, TArgs&&... args) const
        {
            if (logger.ConfiguredToLog(m_logLevel))
            {
                logger.Log(m_logLevel, m_logGenerator(std::forward<TArgs>(args)...));
            }
        }

        template<DerivedFromLogger TLogger, typename... TArgs>
        inline void operator()(TLogger* logger, TArgs&&... args) const
        {
            if (logger != nullptr)
            {
                operator()(*logger, std::forward<TArgs>(args)...);
            }
            else
            {
                throw std::runtime_error("Logger was null");
            }
        }

        template<DerivedFromLogger TLogger, typename... Args>
        inline void operator()(std::shared_ptr<TLogger>& logger, Args&&... args) const
        {
            operator()(*logger, std::forward<Args>(args)...);
        }

        template<DerivedFromLogger TLogger, typename... Args>
        inline void operator()(std::unique_ptr<TLogger>& logger, Args&&... args) const
        {
            operator()(*logger, std::forward<Args>(args)...);
        }

    private:
        ELogLevel m_logLevel;
        TLogLambda m_logGenerator;
    };

    template<typename Lambda>
    auto MakeLoggerDelegate(ELogLevel level, Lambda&& lambda)
    {
        using Traits = CLambdaTraits<std::decay_t<Lambda>>;
        using ReturnType = typename Traits::ReturnType;
        using ArgsTuple = typename Traits::ArgsTuple;

        return [&]<std::size_t... I>(std::index_sequence<I...>) {
            using DecayedLambda = std::decay_t<Lambda>;
            return CLoggerDelegate<
                ReturnType,
                DecayedLambda,
                std::tuple_element_t<I, ArgsTuple>...>(
                level,
                std::forward<Lambda>(lambda));
        }(std::make_index_sequence<std::tuple_size_v<ArgsTuple>>{});
    }
}