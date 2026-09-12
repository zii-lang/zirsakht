#include <gtest/gtest.h>

#include <chrono>
#include <string_view>

#include <Z/Zirsakht/Log/DefaultFormatter.hpp>
#include <Z/Zirsakht/Log/Message.hpp>
#include <Z/Zirsakht/Memory/MemoryBuffer.hpp>

namespace Z::Zirsakht::Log::Tests {

    class LogFormatTest : public ::testing::Test {
      protected:
        using Buffer = Memory::MemoryBuffer;

        static std::string_view view(const Buffer &buffer) {
            return {buffer.data(), buffer.size()};
        }
    };

    TEST_F(LogFormatTest, FormatsCompleteMessage) {
        using namespace std::chrono;

        const auto timestamp =
            system_clock::time_point{seconds{1757244642} + milliseconds{123}};

        const Message message{timestamp, "Lexer", Level::Info,
                              "Starting lexing"};

        Buffer buffer;

        DefaultFormatter::instance().format(message, buffer);

        EXPECT_EQ(view(buffer),
                  "[2025-09-07 11:30:42] [Lexer] [INFO] Starting lexing");
    }

    TEST_F(LogFormatTest, FormatsEmptyLoggerName) {
        using namespace std::chrono;

        const auto timestamp = system_clock::time_point{seconds{1757244642}};

        const Message message{timestamp, "", Level::Error,
                              "Something went wrong"};

        Buffer buffer;

        DefaultFormatter::instance().format(message, buffer);

        EXPECT_EQ(view(buffer),
                  "[2025-09-07 11:30:42] [ERROR] Something went wrong");
    }

    TEST_F(LogFormatTest, FormatsEmptyMessage) {
        using namespace std::chrono;

        const auto timestamp = system_clock::time_point{seconds{1757244642}};

        const Message message{timestamp, "Parser", Level::Debug, ""};

        Buffer buffer;

        DefaultFormatter::instance().format(message, buffer);

        EXPECT_EQ(view(buffer), "[2025-09-07 11:30:42] [Parser] [DEBUG] ");
    }

    TEST_F(LogFormatTest, FormatsDifferentLevels) {
        using namespace std::chrono;

        const auto timestamp = system_clock::time_point{seconds{1757244642}};

        struct TestCase {
            Level            level;
            std::string_view expected;
        };

        const TestCase cases[] = {
            {Level::Trace, "TRACE"}, {Level::Debug, "DEBUG"},
            {Level::Info, "INFO"},   {Level::Warn, "WARN"},
            {Level::Error, "ERROR"}, {Level::Critical, "CRITICAL"},
            {Level::Off, "OFF"},
        };

        for (const auto &test: cases) {
            Message message{timestamp, "Test", test.level, "message"};

            Buffer buffer;

            DefaultFormatter::instance().format(message, buffer);

            EXPECT_NE(view(buffer).find(test.expected), std::string_view::npos);
        }
    }

    TEST_F(LogFormatTest, DoesNotModifyEmptyBufferBeforeFormatting) {
        Message message{"hello"};

        Buffer buffer;

        ASSERT_TRUE(buffer.empty());

        DefaultFormatter::instance().format(message, buffer);

        EXPECT_FALSE(buffer.empty());
    }

} // namespace Z::Zirsakht::Log::Tests
