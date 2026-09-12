#pragma once

#include <Z/Zirsakht/Log/Formatter.hpp>
#include <Z/Zirsakht/Log/ILogger.hpp>

namespace Z::Zirsakht::Log {
    class DefaultLogger final : public ILogger {
      private:
      public:
        void log(Level level, std::string_view message) override;

        template<typename... args>
        void log(Level level, std::string_view format, args... arguments);
    };
} // namespace Z::Zirsakht::Log
