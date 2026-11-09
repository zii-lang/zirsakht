#pragma once

#include <Z/Zirsakht/Memory/StringInterner.hpp>

#include <concepts>
#include <memory>
#include <memory_resource>
#include <string>
#include <unordered_map>

namespace Z::Zirsakht::Compiler {
    template<typename Lexeme = const std::string *>
        requires std::constructible_from<Lexeme, const std::string *>
    class CompilationSession {
      private:
        std::pmr::monotonic_buffer_resource m_lexeme_arena;
        Memory::StringInterner<>            m_interner;

        std::pmr::unordered_map<const std::string *, Lexeme *> m_lexemes;

      public:
        CompilationSession() : m_lexemes{&m_lexeme_arena} {
        }

        Lexeme *create_lexeme(std::string value) {
            const auto *interned = m_interner.intern(value);

            if (auto it = m_lexemes.find(interned); it != m_lexemes.end()) {
                return it->second;
            }

            auto *ptr =
                m_lexeme_arena.allocate(sizeof(Lexeme), alignof(Lexeme));

            auto *lexeme =
                std::construct_at(static_cast<Lexeme *>(ptr), interned);

            m_lexemes.emplace(interned, lexeme);

            return lexeme;
        }
    };
} // namespace Z::Zirsakht::Compiler
