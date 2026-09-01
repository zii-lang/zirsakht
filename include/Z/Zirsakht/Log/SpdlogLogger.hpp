#pragma once

#include <Z/Zirsakht/Log/Logger.hpp>

namespace Z::Zirsakht::Log {
    class SpdlogLogger final : public Logger {
        void log(Level level, std::string_view message) override;
    };
} // namespace Z::Zirsakht::Log
