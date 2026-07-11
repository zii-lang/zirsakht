#pragma once

#ifndef Z_IO_SOURCEMANAGER_H
#define Z_IO_SOURCEMANAGER_H

#include <Z/IO/SourceFile.hpp>

#include <string>
#include <unordered_map>

namespace Z::IO {
    struct SourceManager {
      private:
        std::unordered_map<std::string, SourceFile> sources;

      public:
        SourceManager() = default;

        void add_file(const std::string &path);
        bool has_source(const std::string &file_id) const;
        };
} // namespace Z::IO

#endif
