#pragma once

#include <Z/Zirsakht/Log/DefaultFormatter.hpp>
#include <Z/Zirsakht/Log/Formatter.hpp>
#include <Z/Zirsakht/Log/ILogger.hpp>
#include <iostream>

namespace Z::Zirsakht::Log {
    class DefaultLogger final : public ILogger {
      private:
        static DefaultLogger _baseLogger;

      public:
        static void set_default_log_level(Level level) {
            _baseLogger.set_log_level(level);
        }

        static void out(Level level, std::string_view message) {
            _baseLogger.log(level, message);
        }

        template<typename... Args>
        static void out(Level level, std::format_string<Args...> format,
                        Args &&...args) {
            _baseLogger.log(level, format, std::forward<Args>(args)...);
        }

        void log(Level level, std::string_view message) override;

        template<typename... Args>
        void log(Level level, std::format_string<Args...> format,
                 Args &&...args) {
            if (!should_log(level)) {
                return;
            }

            auto formatted = std::format(format, std::forward<Args>(args)...);

            Log::Message message(level, formatted);
            message.logger_name = this->_name;

            Memory::MemoryBuffer buffer;
            DefaultFormatter::instance().format(message, buffer);

            std::cout.write(buffer.data(), buffer.size());
        }
    };
} // namespace Z::Zirsakht::Log
