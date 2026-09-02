#pragma once

#include <Z/Zirsakht/Common.hpp>

#include <string>
#include <string_view>

namespace Z::Zirsakht::Log {
    enum class Level : int {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
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
            default:
                return "unknown";
        }
    }

    class Logger {
      protected:
        std::string _name;
        Level       _level = Level::Info;

      public:
        explicit Logger(std::string name) : _name(std::move(name)) {};
        virtual ~Logger() = default;
        Logger(const Logger &other);
        Logger(Logger &&other) ZIRSAKHT_NOEXCEPT;
        Logger &operator=(const Logger &other);
        Logger &operator=(Logger &&other) ZIRSAKHT_NOEXCEPT;

        virtual void log(Level level, std::string_view message) = 0;
        virtual void trace(std::string_view message)            = 0;
        virtual void debug(std::string_view message)            = 0;
        virtual void info(std::string_view message)             = 0;
        virtual void warn(std::string_view message)             = 0;
        virtual void error(std::string_view message)            = 0;
        virtual void critical(std::string_view message)         = 0;

        void set_level(Level level) {
            _level = level;
        }

        void set_level(int level) {
            _level = static_cast<Level>(level);
        }

        bool should_log(Level level) const {
            return static_cast<int>(level) >= static_cast<int>(_level);
        }
    };
} // namespace Z::Zirsakht::Log
