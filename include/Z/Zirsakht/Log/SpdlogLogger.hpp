#pragma once

#include <Z/Zirsakht/Config.hpp>

#if ZIRSAKHT_HAS_SPDLOG

#include <Z/Zirsakht/Log/ILogger.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <format>
#include <memory>

namespace Z::Zirsakht::Log {
    class SpdlogLogger final : public ILogger {
        std::shared_ptr<spdlog::logger> logger;

      public:
        explicit SpdlogLogger() {
            auto console_sink =
                std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

            this->logger =
                std::make_shared<spdlog::logger>("spdlog", console_sink);

            this->logger->set_level(spdlog::level::info);
            this->logger->log(spdlog::level::info, "Logger created.");
        };

        void log(Level level, std::string_view message) override;

        template<typename... Args>
        void log(Level level, fmt::format_string<Args...> format,
                 Args &&...args);
    };
} // namespace Z::Zirsakht::Log

#endif
