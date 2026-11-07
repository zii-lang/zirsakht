#pragma once

#include <string>
#include <unordered_set>

namespace Z::Zirsakht::Memory {
    /**
     * @brief Stores unique strings and provides canonical references to them.
     *
     * Repeatedly interning the same string returns the same pointer.
     *
     * @tparam Hasher Hash function used by the underlying unordered_set.
     *
     * @note Returned pointers remain valid for the lifetime of the interner.
     */
    template<typename Hasher = std::hash<std::string>>
    class StringInterner {
      public:
        /**
         * @brief Interns a string.
         *
         * @param value String to intern.
         * @return Pointer to the canonical interned string.
         */
        const std::string *intern(const std::string &value) {
            return &*m_strings.emplace(value).first;
        }

      private:
        std::unordered_set<std::string, Hasher> m_strings;
    };
} // namespace Z::Zirsakht::Memory
