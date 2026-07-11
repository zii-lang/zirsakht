#include <Z/IO/SourceFile.hpp>

namespace Z::IO {
    SourceFile::SourceFile(const std::filesystem::path &path) : path(path) {
    }

    void SourceFile::open_file() {
#ifdef _WIN32
        if (INVALID_HANDLE_VALUE != this->file)
            return;

        this->file =
            CreateFileW(this->get_path().c_str(), GENERIC_READ, FILE_SHARE_READ,
                        nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

        if (INVALID_HANDLE_VALUE == this->file) {
            throw std::system_error(GetLastError(), std::system_category());
        }

        LARGE_INTEGER size;

        if (!GetFileSizeEx(this->file, &size)) {
            this->close_file();
            throw std::system_error(GetLastError(), std::system_category());
        }

        this->size = static_cast<std::size_t>(size.QuadPart);
#endif
    }

    void SourceFile::close_file() noexcept {
#ifdef _WIN32
        if (INVALID_HANDLE_VALUE != this->file) {
            CloseHandle(this->file);
            this->file = INVALID_HANDLE_VALUE;
        }

        this->size = 0;
#endif
    }

    void SourceFile::map() {
        if (this->data) {
            return;
        }

#if _WIN32
        if (INVALID_HANDLE_VALUE == this->file) {
            this->open_file();
        }
#endif

        if (0 == this->size) {
            return;
        }

#if _WIN32
        this->mapping = CreateFileMappingW(this->file, nullptr, PAGE_READONLY,
                                           0, 0, nullptr);

        if (!this->mapping) {
            throw std::system_error(GetLastError(), std::system_category());
        }

        this->data = static_cast<const char *>(
            MapViewOfFile(this->mapping, FILE_MAP_READ, 0, 0, 0));

        if (!this->data) {
            CloseHandle(this->mapping);
            this->mapping = nullptr;

            throw std::system_error(GetLastError(), std::system_category());
        }
#endif
    }

    void SourceFile::unmap() {
#if _WIN32
        if (this->data) {
            UnmapViewOfFile(this->data);
            this->data = nullptr;
        }

        if (this->mapping) {
            CloseHandle(this->mapping);
            this->mapping = nullptr;
        }
#endif
    }
} // namespace Z::IO
