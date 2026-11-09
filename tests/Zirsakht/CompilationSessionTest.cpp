#include <Z/Zirsakht/Compiler/CompilationSession.hpp>

#include <gtest/gtest.h>

#include <string>

namespace Z::Zirsakht::Compiler {

    TEST(CompilationSession, CreateLexeme) {
        CompilationSession<> session;

        auto *lexeme = session.create_lexeme("hello");

        ASSERT_NE(lexeme, nullptr);
        ASSERT_NE(*lexeme, nullptr);
        EXPECT_EQ(**lexeme, "hello");
    }

    TEST(CompilationSession, CreateSameLexeme) {
        CompilationSession<> session;

        auto *first  = session.create_lexeme("hello");
        auto *second = session.create_lexeme("hello");

        EXPECT_EQ(first, second);
    }

    TEST(CompilationSession, CreateDifferentLexemes) {
        CompilationSession<> session;

        auto *first  = session.create_lexeme("hello");
        auto *second = session.create_lexeme("world");

        EXPECT_NE(first, second);
        EXPECT_NE(*first, *second);
    }

    TEST(CompilationSession, PreserveLexemeValue) {
        CompilationSession<> session;

        auto *first  = session.create_lexeme("hello");
        auto *second = session.create_lexeme("world");

        EXPECT_EQ(**first, "hello");
        EXPECT_EQ(**second, "world");
    }

    TEST(CompilationSession, CreateLexemeFromLValue) {
        CompilationSession<> session;

        std::string value  = "hello";
        auto       *lexeme = session.create_lexeme(value);

        ASSERT_NE(lexeme, nullptr);
        EXPECT_EQ(**lexeme, value);
    }

    TEST(CompilationSession, CreateLexemeFromRValue) {
        CompilationSession<> session;

        auto *lexeme = session.create_lexeme(std::string{"hello"});

        ASSERT_NE(lexeme, nullptr);
        EXPECT_EQ(**lexeme, "hello");
    }

    TEST(CompilationSession, IndependentSessions) {
        CompilationSession<> first_session;
        CompilationSession<> second_session;

        auto *first  = first_session.create_lexeme("hello");
        auto *second = second_session.create_lexeme("hello");

        EXPECT_NE(first, second);
        EXPECT_NE(*first, *second);

        EXPECT_EQ(**first, **second);
    }

} // namespace Z::Zirsakht::Compiler
