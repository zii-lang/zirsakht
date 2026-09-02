#include <Z/IO/SourceFile.hpp>

#include <stdexcept>

#if ZIRSAKHT_POSIX
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace Z::IO {
    SourceFile::SourceFile(const std::filesystem::path &path) : path(path) {
    }

    SourceFile::~SourceFile() {
        this->unmap();
        this->close_file();
    }

    SourceFile::SourceFile(SourceFile &&other) noexcept :
        path(std::move(other.path)), data(other.data), size(other.size),
        line_offsets(std::move(other.line_offsets)),
        file_changed(other.file_changed)
#if ZIRSAKHT_OS_WINDOWS
        ,
        file(other.file), mapping(other.mapping)
#elif ZIRSAKHT_POSIX
        ,
        file(other.file)
#endif
    {
        other.data         = nullptr;
        other.size         = 0;
        other.file_changed = true;
        other.line_offsets.clear();

#if ZIRSAKHT_OS_WINDOWS
        other.file    = INVALID_HANDLE_VALUE;
        other.mapping = nullptr;
#elif ZIRSAKHT_POSIX
        other.file = -1;
#endif
    }

    SourceFile &SourceFile::operator=(SourceFile &&other) noexcept {
        if (this == &other)
            return *this;

        this->unmap();
        this->close_file();

        this->path         = std::move(other.path);
        this->data         = other.data;
        this->size         = other.size;
        this->line_offsets = std::move(other.line_offsets);
        this->file_changed = other.file_changed;

#if ZIRSAKHT_OS_WINDOWS
        this->file    = other.file;
        this->mapping = other.mapping;

        other.file    = INVALID_HANDLE_VALUE;
        other.mapping = nullptr;
#elif ZIRSAKHT_POSIX
        this->file = other.file;

        other.file = -1;
#endif

        other.data         = nullptr;
        other.size         = 0;
        other.file_changed = true;
        other.line_offsets.clear();

        return *this;
    }

    void SourceFile::open_file() {
#if ZIRSAKHT_OS_WINDOWS
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
#elif ZIRSAKHT_POSIX
        if (-1 != this->file) {
            return;
        }

        this->file = open(this->get_path().c_str(), O_RDONLY);

        if (-1 == this->file) {
            throw std::system_error(errno, std::generic_category());
        }

        struct stat st{};
        if (-1 == fstat(this->file, &st)) {
            this->close_file();
            throw std::system_error(errno, std::generic_category());
        }

        this->size = static_cast<std::size_t>(st.st_size);
#else
        throw std::logic_error(
            "SourceFile::open_file() is not implemented for this system.");
#endif
    }

    void SourceFile::close_file() noexcept {
#if ZIRSAKHT_OS_WINDOWS
        if (INVALID_HANDLE_VALUE != this->file) {
            CloseHandle(this->file);
            this->file = INVALID_HANDLE_VALUE;
        }

        this->size = 0;
#elif ZIRSAKHT_POSIX
        if (-1 != this->file) {
            close(this->file);
            this->file = -1;
        }

        this->size = 0;
#endif
    }

    void SourceFile::map() {
        if (this->data) {
            return;
        }

#if ZIRSAKHT_OS_WINDOWS
        if (INVALID_HANDLE_VALUE == this->file) {
            this->open_file();
        }
#elif ZIRSAKHT_POSIX
        if (-1 == this->file) {
            this->open_file();
        }
#else
        throw std::logic_error(
            "SourceFile::open_file() is not implemented for this system.");
#endif

        if (0 == this->size) {
            return;
        }

#if ZIRSAKHT_OS_WINDOWS
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
#elif ZIRSAKHT_POSIX
        this->data = static_cast<const char *>(
            mmap(nullptr, this->size, PROT_READ, MAP_PRIVATE, this->file, 0));
        if (MAP_FAILED == this->data) {
            this->data = nullptr;
            throw std::system_error(errno, std::generic_category());
        }
#endif
    }

    void SourceFile::unmap() noexcept {
#if ZIRSAKHT_OS_WINDOWS
        if (this->data) {
            UnmapViewOfFile(this->data);
            this->data = nullptr;
        }

        if (this->mapping) {
            CloseHandle(this->mapping);
            this->mapping = nullptr;
        }
#elif ZIRSAKHT_POSIX
        if (this->data) {
            munmap(const_cast<char *>(this->data), this->size);
            this->data = nullptr;
        }
#endif
    }

    std::string_view SourceFile::view() {
        if (!this->data)
            this->map();

        return {this->data, this->size};
    }

    void SourceFile::build_line_table() {
        if (!line_offsets.empty())
            return;

        auto source = view();

        // Always have line 0
        line_offsets.push_back(0);

        for (std::size_t i = 0; i < source.size(); i++) {
            if (source[i] == '\n') {
                line_offsets.push_back(i + 1);
            }
        }
    }

    std::string_view SourceFile::view_line(std::size_t index) {
        this->build_line_table();

        if (index >= this->line_offsets.size())
            return {};

        auto start = line_offsets[index];

        auto end = (index + 1 < line_offsets.size()) ? line_offsets[index + 1]
                                                     : this->size;

        return {this->data + start, end - start};
    }
} // namespace Z::IO
