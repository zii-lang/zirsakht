#pragma once

#include <Z/Zirsakht/Log/Formatter.hpp>
#include <Z/Zirsakht/Log/ILogger.hpp>

namespace Z::Zirsakht::Log {
    class DefaultLogger final : public ILogger {
      private:
      public:
        void log(Level level, std::string_view message) override;

        template<typename... Args>
        void log(Level level, std::format_string<Args...> format,
                 Args &&...args);
    };
} // namespace Z::Zirsakht::Log
