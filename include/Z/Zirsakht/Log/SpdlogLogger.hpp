#pragma once

#include <Z/Zirsakht/Config.hpp>

#if ZIRSAKHT_HAS_SPDLOG

#include <Z/Zirsakht/Log/ILogger.hpp>
#include <spdlog/spdlog.h>

#include <format>
#include <memory>

namespace Z::Zirsakht::Log {
    class SpdlogLogger final : public ILogger {
#if ZIRSAKHT_HAS_SPDLOG
        std::shared_ptr<spdlog::logger> logger;
#endif

        void log(Level level, std::string_view message) override;

        template<typename... Args>
        void log(Level level, fmt::format_string<Args...> format,
                 Args &&...args);
    };
} // namespace Z::Zirsakht::Log

#endif
