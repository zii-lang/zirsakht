#include <Z/Zirsakht/Log/Formatter.hpp>
#include <chrono>
#include <format>

namespace Z::Zirsakht::Log {
    constexpr std::string_view level_name(Level level) noexcept {
        switch (level) {
            case Level::Trace:
                return "TRACE";
            case Level::Debug:
                return "DEBUG";
            case Level::Info:
                return "INFO";
            case Level::Warn:
                return "WARN";
            case Level::Error:
                return "ERROR";
            case Level::Critical:
                return "CRITICAL";
            case Level::Off:
                return "OFF";
        }

        return "UNKNOWN";
    }

    void format(const LogMessage &message, DestenationBufferType &dest) {
        const auto formatted = std::format(
            "[{:%Y-%m-%d %H:%M:%S}] [{}] [{}] {}", message.timestamp,
            level_name(message.level), message.logger_name, message.payload);

        dest.append(formatted);
    }
} // namespace Z::Zirsakht::Log
