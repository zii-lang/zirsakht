#pragma once

#include <Z/Zirsakht/Log/LogLevel.hpp>

#include <chrono>
#include <string_view>

namespace Z::Zirsakht::Log {
    using Timepoint  = std::chrono::system_clock::time_point;
    using Stringview = std::string_view;

    struct LogMessage {
        LogMessage()                                   = default;
        LogMessage(const LogMessage &other)            = default;
        LogMessage &operator=(const LogMessage &other) = default;

        LogMessage(Stringview message) : payload(message) {};
        LogMessage(Stringview message, Timepoint log_time) :
            payload(message), timestamp(log_time) {};
        LogMessage(Level level, Stringview message) :
            level(level), payload(message) {};
        LogMessage(Level level, Stringview message, Timepoint log_time) :
            level(level), payload(message), timestamp(log_time) {};
        LogMessage(Timepoint log_time, Stringview logger_name, Level level,
                   Stringview message) :
            logger_name(logger_name), level(level), timestamp(log_time),
            payload(message) {};

        Stringview logger_name{};
        Level      level{Level::Off};
        Timepoint  timestamp{std::chrono::system_clock::now()};
        Stringview payload;
    };

}; // namespace Z::Zirsakht::Log
