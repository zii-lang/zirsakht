#pragma once

#include <string_view>

namespace Z::Zirsakht::Log {
    enum class Level {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
    };

    class Logger {
      public:
        virtual ~Logger() = default;

        virtual void log(Level level, std::string_view message) = 0;

        virtual void trace(std::string_view message)    = 0;
        virtual void debug(std::string_view message)    = 0;
        virtual void info(std::string_view message)     = 0;
        virtual void warn(std::string_view message)     = 0;
        virtual void error(std::string_view message)    = 0;
        virtual void critical(std::string_view message) = 0;
    };
} // namespace Z::Zirsakht::Log
