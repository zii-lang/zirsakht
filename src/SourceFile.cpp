#include <Z/IO/SourceFile.hpp>

namespace Z::IO {
    SourceFile::SourceFile(const std::filesystem::path &path) : path_(path) {

#ifdef _WIN32

#else

#endif
    }
} // namespace Z::IO
