#pragma once

#include <Z/Zirsakht/Log/Formatter.hpp>

namespace Z::Zirsakht::Log {
    class DefaultFormatter : public Formatter {
      public:
        void format(const Message &, DestenationBufferType &) override;

        static DefaultFormatter &instance() {
            static DefaultFormatter instance;
            return instance;
        }

      private:
        DefaultFormatter() = default;

        DefaultFormatter(const DefaultFormatter &)            = delete;
        DefaultFormatter &operator=(const DefaultFormatter &) = delete;
    };
} // namespace Z::Zirsakht::Log
