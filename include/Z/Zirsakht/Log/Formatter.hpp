#pragma once

namespace Z::Zirsakht::Log {
    class Formatter {
      public:
        virtual ~Formatter()  = default;
        virtual void format() = 0;
    };
} // namespace Z::Zirsakht::Log
