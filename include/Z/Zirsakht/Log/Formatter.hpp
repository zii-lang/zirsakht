#pragma once

#include <Z/Zirsakht/Log/LogMessage.hpp>
#include <Z/Zirsakht/Memory/MemoryBuffer.hpp>

namespace Z::Zirsakht::Log {
    using DestenationBufferType = Memory::MemoryBuffer;
    class Formatter {
      public:
        virtual ~Formatter()                                    = default;
        virtual static void format(const LogMessage      &message,
                                   DestenationBufferType &dest) = 0;
    };
} // namespace Z::Zirsakht::Log
