#pragma once

#include <Z/Zirsakht/Log/LogMessage.hpp>

namespace Z::Zirsakht::Log {
    using DestenationBufferType = void *;
    class Formatter {
      public:
        virtual ~Formatter()                             = default;
        virtual void format(const LogMessage      &message,
                            DestenationBufferType &dest) = 0;
    };
} // namespace Z::Zirsakht::Log
