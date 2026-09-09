#pragma once

#include <Z/Zirsakht/Log/Formatter.hpp>
#include <Z/Zirsakht/Log/Logger.hpp>

namespace Z::Zirsakht::Log {
    class DefaultLogger final : public Logger {
      private:
      public:
        void log(Level level, std::string_view message) override;
        void trace(std::string_view message) override;
        void debug(std::string_view message) override;
        void info(std::string_view message) override;
        void warn(std::string_view message) override;
        void error(std::string_view message) override;
        void critical(std::string_view message) override;

        template<typename... args>
        void log(Level level, std::string_view format, args... arguments);
    };
} // namespace Z::Zirsakht::Log
