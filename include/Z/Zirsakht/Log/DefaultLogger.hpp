#pragma once

#include <Z/Zirsakht/Log/DefaultFormatter.hpp>
#include <Z/Zirsakht/Log/Formatter.hpp>
#include <Z/Zirsakht/Log/ILogger.hpp>
#include <iostream>

namespace Z::Zirsakht::Log {
    class DefaultLogger final : public ILogger {
      private:
      public:
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
