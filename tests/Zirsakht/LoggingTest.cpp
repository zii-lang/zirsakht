#include <gtest/gtest.h>

#include <Z/Zirsakht/Log/DefaultLogger.hpp>

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
        DefaultLogger logger{};
        testing::internal::CaptureStdout();

        auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(
            std::chrono::system_clock::now());

        logger.log(Log::Level::Info, "Hello World");
        const std::string output = testing::internal::GetCapturedStdout();

        std::cout << output << "\n";
        // TODO: fix, the time reported is not actualy timezoned.
        EXPECT_EQ(
            output,
            std::format("[{:%Y-%m-%d %H:%M:%S}] [INFO] Hello World", seconds));
    }

} // namespace Z::Zirsakht::Log::Tests
