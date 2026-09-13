#pragma once

#include <string_view>

namespace Z::Zirsakht::Log {
    enum class Level : int {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off,
    };

    static constexpr std::string_view level_to_name(Level level) {
        switch (level) {
            case Level::Trace:
                return "trace";
            case Level::Debug:
                return "debug";
            case Level::Info:
                return "info";
            case Level::Warn:
                return "warning";
            case Level::Error:
                return "error";
            case Level::Critical:
                return "critical";
            case Level::Off:
            default:
                return "unknown";
        }
    }
} // namespace Z::Zirsakht::Log
