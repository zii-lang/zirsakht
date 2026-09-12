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

        Log::Message m(level, message);
        m.logger_name = this->_name;
        Memory::MemoryBuffer buffer;
        DefaultFormatter::instance().format(m, buffer);
        std::cout << std::string_view(buffer.data(), buffer.size());
    }

    template<typename... Args>
    void DefaultLogger::log(Level level, std::format_string<Args...> format,
                            Args &&...args) {
        bool should_log = this->should_log(level);
        if (!should_log) {
            return;
        }

        Log::Message message(
            level, std::vformat(format, std::make_format_args(args...)));
        message.logger_name = this->_name;
        Memory::MemoryBuffer buffer;
        DefaultFormatter::instance().format(message, buffer);
        std::cout << std::string_view(buffer.data(), buffer.size());
    }
} // namespace Z::Zirsakht::Log
