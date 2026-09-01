#include <Z/Zirsakht/Log/DefaultLogger.hpp>

#include <chrono>
#include <format>
#include <iostream>

namespace Z::Zirsakht::Log {
    void DefaultLogger::log(Level level, std::string_view message) {
        switch (level) {
            case Level::Trace:
                this->trace(message);
                break;
            case Level::Info:
                this->info(message);
                break;
            case Level::Debug:
                this->debug(message);
                break;
            case Level::Warn:
                this->warn(message);
                break;
            case Level::Error:
                this->error(message);
                break;
            case Level::Critical:
                this->critical(message);
                break;
            default:
                std::cerr << "[Critical] log level not implemented.";
        }
    }

    template<typename... args>
    void DefaultLogger::log(Level level, std::string_view format,
                            args... arguments) {
        bool should_log = this->should_log(level);
    }

    template<typename... args>
    void DefaultLogger::trace(std::string_view format, args... arguments) {
        std::cout << "[Trace] "
                  << std::vformat(format, std::make_format_args(arguments...))
                  << std::endl;
    }
} // namespace Z::Zirsakht::Log
