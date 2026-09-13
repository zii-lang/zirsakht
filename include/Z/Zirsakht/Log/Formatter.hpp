#pragma once

#include <Z/Zirsakht/Log/Message.hpp>
#include <Z/Zirsakht/Memory/MemoryBuffer.hpp>

namespace Z::Zirsakht::Log {
    using DestenationBufferType = Memory::MemoryBuffer;
    class Formatter {
      public:
        virtual ~Formatter()                             = default;
        virtual void format(const Message         &message,
                            DestenationBufferType &dest) = 0;
    };
} // namespace Z::Zirsakht::Log
