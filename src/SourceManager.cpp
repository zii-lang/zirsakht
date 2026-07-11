#include <Z/IO/SourceManager.hpp>

#include <filesystem>

namespace Z::IO {

    void SourceManager::add_file(const std::string &path) {
        auto absolute = std::filesystem::absolute(path);

        this->sources.emplace(absolute.string(), SourceFile{absolute});
    }

} // namespace Z::IO
