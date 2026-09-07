#pragma once

#include <Z/Zirsakht/Log/Formatter.hpp>

namespace Z::Zirsakht::Log {
    class DefaultFormatter : public Formatter {
        static void format(const LogMessage &,
                           DestenationBufferType &) override;
    };
} // namespace Z::Zirsakht::Log
