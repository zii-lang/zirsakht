#pragma once

#include <Z/Zirsakht/Log/Level.hpp>

#include <string_view>

namespace Z::Zirsakht::Log {
    class ILogger {
      protected:
        std::string_view _name;
        Level            _log_level = Level::Info;

      public:
        virtual ~ILogger()                                      = default;
        virtual void log(Level level, std::string_view message) = 0;

        bool should_log(Level level) {
            return level >= this->_log_level;
        }
    };
} // namespace Z::Zirsakht::Log
