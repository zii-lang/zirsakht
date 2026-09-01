#pragma once

#include <Z/Zirsakht/Log/Logger.hpp>

namespace Z::Zirsakht::Log {
    class DefaultLogger final : public Logger {
        void log(Level level, std::string_view message) override;

        template<typename... args>
        void log(Level level, std::string_view format, args... arguments);

        template<typename... args>
        void trace(std::string_view format, args... arguments);
    };
} // namespace Z::Zirsakht::Log
