#include <gtest/gtest.h>

#include <Z/Zirsakht/Log/DefaultLogger.hpp>
#include <Z/Zirsakht/Log/SpdlogLogger.hpp>

namespace Z::Zirsakht::Log::Tests {

    // Basic test no logger.
    TEST(LoggerTest, WritesToStdout) {
        testing::internal::CaptureStdout();

        // Code that writes to stdout
        std::cout << "hello";

        const std::string output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "hello");
    }

    TEST(LoggerTest, DefaultLoggerWritesMessage) {
        DefaultLogger logger;
        testing::internal::CaptureStdout();

        auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(
            std::chrono::system_clock::now());

        logger.log(Log::Level::Info, "Hello World");
        const std::string output = testing::internal::GetCapturedStdout();

        // TODO: fix, the time reported is not actualy timezoned.
        EXPECT_EQ(
            output,
            std::format("[{:%Y-%m-%d %H:%M:%S}] [INFO] Hello World", seconds));
    }

    TEST(LoggerTest, DefaultLoggerFormatMessage) {
        DefaultLogger logger;

        testing::internal::CaptureStdout();
        logger.log(Log::Level::Info, "Hello {} and {}.", "multiple format", 12);
        const std::string output1 = testing::internal::GetCapturedStdout();

        EXPECT_NE(output1.find("Hello multiple format and 12."),
                  std::string::npos);

        testing::internal::CaptureStdout();

        logger.log(Log::Level::Info, "Hello {}", "testing.");
        const std::string output2 = testing::internal::GetCapturedStdout();

        EXPECT_NE(output2.find("Hello testing."), std::string::npos);
    }

    TEST(LoggerTest, SpdLoggerWritesMessage) {
        testing::internal::CaptureStdout();

        SpdlogLogger logger;

        logger.log(Log::Level::Info, "Hello World");

        const std::string output = testing::internal::GetCapturedStdout();

        EXPECT_NE(output.find("Hello World"), std::string::npos);
    }
} // namespace Z::Zirsakht::Log::Tests
