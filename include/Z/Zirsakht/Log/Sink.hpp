#pragma once

#include <Z/Zirsakht/Log/Message.hpp>

namespace Z::Zirsakht::Log {
    class Sink {
      public:
        virtual ~Sink() = default;

        virtual void write(const Message &message) = 0;
    };

} // namespace Z::Zirsakht::Log
