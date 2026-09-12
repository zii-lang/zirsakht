#include <Z/Zirsakht/Log/SpdlogLogger.hpp>
#include <iostream>

#if ZIRSAKHT_HAS_SPDLOG

namespace Z::Zirsakht::Log {

    static spdlog::level::level_enum to_spdlog_level(Level level) {
        switch (level) {
            case Level::Trace:
                return spdlog::level::trace;
            case Level::Debug:
                return spdlog::level::debug;
            case Level::Info:
                return spdlog::level::info;
            case Level::Warn:
                return spdlog::level::warn;
            case Level::Error:
                return spdlog::level::err;
            case Level::Critical:
                return spdlog::level::critical;
            case Level::Off:
                return spdlog::level::off;
        }

        return spdlog::level::off;
    }

    void SpdlogLogger::log(Level level, std::string_view message) {
        logger->log(to_spdlog_level(level), "{}", message);
    }

    template<typename... Args>
    void SpdlogLogger::log(Level level, fmt::format_string<Args...> format,
                           Args &&...args) {
        bool should_log = this->should_log(level);
        if (!should_log) {
            return;
        }
        logger->log(to_spdlog_level(level), format,
                    std::forward<Args>(args)...);
    }
} // namespace Z::Zirsakht::Log

#endif
