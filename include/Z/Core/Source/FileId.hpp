#pragma once

#include <concepts>
#include <cstdint>
#include <limits>
#include <type_traits>

#include <cstdint>
#include <limits>

namespace Z::Core::Source {
    template<std::unsigned_integral ValueT = std::size_t>
    class BasicFileId final {
      public:
        using ValueType = ValueT;

        static_assert(std::numeric_limits<ValueType>::is_specialized,
                      "ValueType must support std::numeric_limits");

        constexpr BasicFileId() noexcept = default;

        [[nodiscard]]
        constexpr bool is_valid() const noexcept {
            return this->value != invalid_value();
        }

        [[nodiscard]]
        constexpr explicit operator bool() const noexcept {
            return is_valid();
        }

        [[nodiscard]]
        constexpr ValueType get_value() const noexcept {
            return this->value;
        }

        friend constexpr bool operator==(BasicFileId,
                                         BasicFileId) noexcept = default;

      private:
        template<typename>
        friend class BasicSourceManager;

        [[nodiscard]]
        static constexpr ValueType invalid_value() noexcept {
            return std::numeric_limits<ValueType>::max();
        }

        explicit constexpr BasicFileId(ValueType value) noexcept :
            value(value) {
        }

        ValueType value = invalid_value();
    };

    using FileId = BasicFileId<std::size_t>;
} // namespace Z::Core::Source
