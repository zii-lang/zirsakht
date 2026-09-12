#pragma once

#include <Z/Zirsakht/Log/ILogger.hpp>

#if ZIRSAKHT_HAS_SPDLOG
#include <spdlog/spdlog.h>
#endif

#include <memory>

namespace Z::Zirsakht::Log {
    class SpdlogLogger final : public ILogger {
#if ZIRSAKHT_HAS_SPDLOG
        std::shared_ptr<spdlog::logger> logger;
#endif

        void log(Level level, std::string_view message) override;
    };
} // namespace Z::Zirsakht::Log
