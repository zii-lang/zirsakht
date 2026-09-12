#include <Z/Zirsakht/Log/DefaultFormatter.hpp>
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

    void DefaultFormatter::format(const Message         &message,
                                  DestenationBufferType &dest) {
        auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(
            message.timestamp);

        const auto logger_name =
            message.logger_name.empty()
                ? std::string{}
                : std::format("[{}] ", message.logger_name);

        const auto formatted = std::format(
            "[{:%Y-%m-%d %H:%M:%S}] {}[{}] {}", seconds, logger_name,
            level_name(message.level), message.payload);

        dest.append(formatted);
    }
} // namespace Z::Zirsakht::Log
