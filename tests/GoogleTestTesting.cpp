/**
 * This file verifies that GoogleTest is correctly configured and functional.
 */

#include <gtest/gtest.h>

#include <filesystem>

namespace Z::Zirsakht::Tests {

    class GoogleTestTesting : public ::testing::Test {
      protected:
        GoogleTestTesting()           = default;
        ~GoogleTestTesting() override = default;

        void SetUp() override {
            // Fixture setup.
        }

        void TearDown() override {
            // Fixture teardown.
        }
    };

    TEST(GoogleTest, BasicAssertion) {
        EXPECT_EQ(1 + 1, 2);
    }

    TEST_F(GoogleTestTesting, FixtureWorks) {
        EXPECT_TRUE(true);
    }

    TEST(GoogleTest, StringAssertion) {
        const std::string value = "GoogleTest";

        EXPECT_EQ(value, "GoogleTest");
    }

    TEST(ZIRSAKHT, CheckLibZirsakhtExist) {
#if defined(_WIN32)
        const std::filesystem::path dynamic_path("../zirsakht.dll");
        const std::filesystem::path static_path("../zirsakht.lib");

        EXPECT_TRUE(std::filesystem::exists(dynamic_path) ||
                    std::filesystem::exists(dynamic_path));
#endif
    }
} // namespace Z::Zirsakht::Tests

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
