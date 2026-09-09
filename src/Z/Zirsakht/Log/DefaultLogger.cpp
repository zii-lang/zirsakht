#include <Z/Zirsakht/Log/DefaultFormatter.hpp>
#include <Z/Zirsakht/Log/DefaultLogger.hpp>

#include <chrono>
#include <format>
#include <iostream>
#include <string_view>

namespace Z::Zirsakht::Log {
    void DefaultLogger::log(Level level, std::string_view message) {
        bool should_log = this->should_log(level);
        if (!should_log) {
            return;
        }

        LogMessage m(level, message);
        m.logger_name = this->_name;
        Memory::MemoryBuffer buffer;
        DefaultFormatter::instance().format(m, buffer);
        std::cout << std::string_view(buffer.data(), buffer.size());
    }

    void DefaultLogger::trace(std::string_view message) {
        this->log(Level::Trace, message);
    }

    void DefaultLogger::debug(std::string_view message) {
        this->log(Level::Debug, message);
    }

    void DefaultLogger::info(std::string_view message) {
        this->log(Level::Info, message);
    }

    void DefaultLogger::warn(std::string_view message) {
        this->log(Level::Warn, message);
    }

    void DefaultLogger::error(std::string_view message) {
        this->log(Level::Error, message);
    }

    void DefaultLogger::critical(std::string_view message) {
        this->log(Level::Critical, message);
    }

    template<typename... args>
    void DefaultLogger::log(Level level, std::string_view format,
                            args... arguments) {
        bool should_log = this->should_log(level);
        if (!should_log) {
            return;
        }

        LogMessage message(
            level, std::vformat(format, std::make_format_args(arguments...)));
        message.logger_name = this->_name;
        Memory::MemoryBuffer buffer;
        DefaultFormatter::instance().format(message, buffer);
        std::cout << std::string_view(buffer.data(), buffer.size());
    }
} // namespace Z::Zirsakht::Log
