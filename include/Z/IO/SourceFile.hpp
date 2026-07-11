#pragma once

#ifndef Z_IO_SOURCEFILE_H
#define Z_IO_SOURCEFILE_H

#include <Z/ZCoreConfig.hpp>

#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>

namespace Z::IO {
    struct SourceFile {
      public:
        explicit SourceFile(const std::filesystem::path &path);
        ~SourceFile();

        SourceFile(const SourceFile &)            = delete;
        SourceFile &operator=(const SourceFile &) = delete;

        SourceFile(SourceFile &&) noexcept;
        SourceFile &operator=(SourceFile &&) noexcept;

        std::string_view view() const noexcept {
            return nullptr;
        }

        const std::filesystem::path &path() const noexcept {
            return path_;
        }

      private:
        std::filesystem::path path_;

#ifdef _WIN32
        HANDLE file_    = INVALID_HANDLE_VALUE;
        HANDLE mapping_ = nullptr;
#else
        int file_ = -1;
#endif
    };
} // namespace Z::IO

#endif
