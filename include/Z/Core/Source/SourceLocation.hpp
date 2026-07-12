#pragma once

#include <Z/Core/Source/FileId.hpp>

namespace Z::Core::Source {
    class SourceLocation final {
      public:
        using OffsetType = std::uint32_t;

        constexpr SourceLocation() noexcept = default;

        [[nodiscard]]
        constexpr bool is_valid() const noexcept {
            return this->file_id.is_valid();
        }

        [[nodiscard]]
        constexpr explicit operator bool() const noexcept {
            return this->is_valid();
        }

        [[nodiscard]]
        constexpr FileId get_file_id() const noexcept {
            return this->file_id;
        }

        [[nodiscard]]
        constexpr OffsetType get_offset() const noexcept {
            return offset;
        }

        friend constexpr bool operator==(SourceLocation lhs,
                                         SourceLocation rhs) noexcept = default;

      private:
        friend class SourceManager;

        constexpr SourceLocation(FileId file_id, OffsetType offset) noexcept :
            file_id(file_id), offset(offset) {
        }

        FileId     file_id;
        OffsetType offset = 0;
    };
} // namespace Z::Core::Source
