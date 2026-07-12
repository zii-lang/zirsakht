#pragma once

#include <Z/Core/Source/SourceFile.hpp>
#include <Z/Core/Source/SourceLocation.hpp>

#include <filesystem>
#include <string>
#include <unordered_map>

namespace Z::Core::Source {
    /**
     * @brief Describes the origin of a source file.
     *
     * This enumeration identifies where a source originates from, allowing
     * the compiler to distinguish between project files, library
     * dependencies, external sources, and in-memory generated code.
     */
    enum class SourceOrigin {
        /**
         * @brief Source file that belongs to the current project.
         */
        Project,

        /**
         * @brief Source file provided by a library or package dependency.
         */
        Library,

        /**
         * @brief Source file outside the project or managed libraries.
         *
         * Examples include system headers, SDK files, or arbitrary files
         * referenced by an absolute path.
         */
        External,

        /**
         * @brief Source that exists only in memory.
         *
         * Used for generated code, REPL input, editor buffers, or other sources
         * that do not have a corresponding file on disk.
         */
        Memory
    };

    struct ResolvedSourcePath final {
        std::filesystem::path      absolute_path;
        std::filesystem::path      logical_path;
        SourceOrigin               origin = SourceOrigin::External;
        std::optional<std::string> library_name;
    };

    class SourceManager {
      public:
        using OffsetType = SourceLocation::OffsetType;

        explicit SourceManager(std::filesystem::path project_root);
        SourceManager(const SourceManager &)            = delete;
        SourceManager &operator=(const SourceManager &) = delete;

        SourceManager(SourceManager &&) noexcept            = default;
        SourceManager &operator=(SourceManager &&) noexcept = default;

        [[nodiscard]]
        const std::filesystem::path &get_project_root() const noexcept;

        void add_library(std::string name, std::filesystem::path absolute_path);

        [[nodiscard]]
        bool has_library(std::string_view name) const noexcept;

        [[nodiscard]]
        const std::filesystem::path &library_root(std::string_view name) const;

        [[nodiscard]]
        ResolvedSourcePath
        resolve_project_path(const std::filesystem::path &relative_path) const;

        [[nodiscard]]
        ResolvedSourcePath
        resolve_library_path(std::string_view             library_name,
                             const std::filesystem::path &relative_path) const;

        [[nodiscard]]
        ResolvedSourcePath
        resolve_absolute_path(const std::filesystem::path &absolute_path) const;

        [[nodiscard]]
        FileId load_project_file(const std::filesystem::path &relative_path);

        [[nodiscard]]
        SourceLocation location(FileId                     file,
                                SourceLocation::OffsetType offset) const;

        [[nodiscard]]
        FileId load_library_file(std::string_view             libraryName,
                                 const std::filesystem::path &relativePath);

        [[nodiscard]]
        FileId load_absolute_file(const std::filesystem::path &absolute_path);

        // TODO: contents are required?
        [[nodiscard]]
        FileId add_memory_source(std::string display_name,
                                 std::string contents);

        [[nodiscard]]
        std::string_view get_file_data(FileId file) const;

        [[nodiscard]]
        SourceLocation get_location(FileId file, OffsetType offset) const;

      private:
        std::filesystem::path   projectRoot_;
        std::vector<SourceFile> files_;
    };
} // namespace Z::Core::Source
