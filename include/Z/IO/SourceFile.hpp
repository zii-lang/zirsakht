#pragma once

#ifndef Z_IO_SOURCEFILE_H
#define Z_IO_SOURCEFILE_H

#include <Z/ZCoreConfig.hpp>

#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace Z::IO {
    struct SourceFile {
      public:
        explicit SourceFile(const std::filesystem::path &path);
        ~SourceFile();

        SourceFile(const SourceFile &)            = delete;
        SourceFile &operator=(const SourceFile &) = delete;

        SourceFile(SourceFile &&) noexcept;
        SourceFile &operator=(SourceFile &&) noexcept;

        std::string_view view() const noexcept;

        const std::filesystem::path &get_path() const noexcept {
            return this->path;
        }

      private:
        std::filesystem::path path;
        const char           *data = nullptr;
        std::size_t           size = 0;

        std::vector<std::size_t> line_offsets;
        bool                     file_changed = true;

        // ==== Private Functions ====

        void build_line_table();

        void open_file();
        void close_file() noexcept;

        void map();
        void unmap() noexcept;

        // ==========================

#ifdef _WIN32
        HANDLE file    = INVALID_HANDLE_VALUE;
        HANDLE mapping = nullptr;
#else
        int file = -1;
#endif
    };
} // namespace Z::IO

#endif
