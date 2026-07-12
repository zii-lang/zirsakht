#pragma once

#include <Z/Core/Source/SourceLocation.hpp>

namespace Z::Core::Source {
    class SourceRange final {
      public:
        constexpr SourceRange() noexcept = default;

        [[nodiscard]]
        constexpr bool is_valid() const noexcept {
            return begin_.is_valid() && end_.is_valid() &&
                   begin_.get_file_id() == end_.get_file_id() &&
                   begin_.get_offset() <= end_.get_offset();
        }

        [[nodiscard]]
        constexpr explicit operator bool() const noexcept {
            return is_valid();
        }

        [[nodiscard]]
        constexpr SourceLocation begin() const noexcept {
            return begin_;
        }

        [[nodiscard]]
        constexpr SourceLocation end() const noexcept {
            return end_;
        }

        [[nodiscard]]
        constexpr bool is_empty() const noexcept {
            return is_valid() && begin_.get_offset() == end_.get_offset();
        }

        [[nodiscard]]
        constexpr std::uint32_t length() const noexcept {
            return is_valid() ? end_.get_offset() - begin_.get_offset() : 0;
        }

        friend constexpr bool operator==(SourceRange,
                                         SourceRange) noexcept = default;

      private:
        friend class SourceManager;

        constexpr SourceRange(SourceLocation begin, SourceLocation end) noexcept
            : begin_(begin), end_(end) {
        }

        SourceLocation begin_;
        SourceLocation end_;
    };
} // namespace Z::Core::Source
