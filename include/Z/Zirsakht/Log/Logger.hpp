#pragma once

#include <Z/Zirsakht/Common.hpp>
#include <Z/Zirsakht/Log/Level.hpp>

#include <string>
#include <string_view>

namespace Z::Zirsakht::Log {
    class Logger {
      protected:
        std::string _name;
        Level       _level = Level::Info;

      public:
        explicit Logger(std::string name) : _name(std::move(name)) {};
        virtual ~Logger() = default;
        Logger(Logger &&other) Z_NOEXCEPT;
        Logger &operator=(Logger &&other) Z_NOEXCEPT;

        virtual void trace(std::string_view message)    = 0;
        virtual void debug(std::string_view message)    = 0;
        virtual void info(std::string_view message)     = 0;
        virtual void warn(std::string_view message)     = 0;
        virtual void error(std::string_view message)    = 0;
        virtual void critical(std::string_view message) = 0;

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
