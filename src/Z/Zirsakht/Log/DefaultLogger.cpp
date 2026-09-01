#include <Z/Zirsakht/Log/DefaultLogger.hpp>

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
} // namespace Z::Zirsakht::Log
