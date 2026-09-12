#pragma once

#include <Z/Zirsakht/Log/Level.hpp>

#include <chrono>
#include <string_view>

namespace Z::Zirsakht::Log {
    using Timepoint  = std::chrono::system_clock::time_point;
    using Stringview = std::string_view;

    struct Message {
        Message()                                = default;
        Message(const Message &other)            = default;
        Message &operator=(const Message &other) = default;

        Message(Stringview message) : payload(message) {};
        Message(Stringview message, Timepoint log_time) :
            payload(message), timestamp(log_time) {};
        Message(Level level, Stringview message) :
            level(level), payload(message) {};
        Message(Level level, Stringview message, Timepoint log_time) :
            level(level), payload(message), timestamp(log_time) {};
        Message(Timepoint log_time, Stringview logger_name, Level level,
                Stringview message) :
            logger_name(logger_name), level(level), timestamp(log_time),
            payload(message) {};

        Stringview logger_name{};
        Stringview tag{};
        Level      level{Level::Off};
        Timepoint  timestamp{std::chrono::zoned_time{
            std::chrono::current_zone(), std::chrono::system_clock::now()}};
        Stringview payload;
    };
}; // namespace Z::Zirsakht::Log
