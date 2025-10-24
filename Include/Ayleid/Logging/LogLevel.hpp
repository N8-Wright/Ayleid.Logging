#pragma once
#include <fmt/format.h>
namespace Ayleid::Logging
{
    enum class ELogLevel
    {
        Critial = 0,
        Error = 1,
        Warning = 2,
        Info = 3,
        Detail = 4,
        Trace = 5,
    };
}

template<>
struct fmt::formatter<Ayleid::Logging::ELogLevel>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    auto format(const Ayleid::Logging::ELogLevel& logLevel, format_context& ctx) const
    {
        using namespace Ayleid::Logging;
        switch (logLevel)
        {
        case ELogLevel::Critial:
            return fmt::format_to(ctx.out(), "{}", "Critial");
        case ELogLevel::Detail:
            return fmt::format_to(ctx.out(), "{}", "Detail");
        case ELogLevel::Error:
            return fmt::format_to(ctx.out(), "{}", "Error");
        case ELogLevel::Info:
            return fmt::format_to(ctx.out(), "{}", "Info");
        case ELogLevel::Trace:
            return fmt::format_to(ctx.out(), "{}", "Trace");
        case ELogLevel::Warning:
            return fmt::format_to(ctx.out(), "{}", "Warning");
        default:
            throw std::runtime_error("Invalid log level");
        }
    }
};