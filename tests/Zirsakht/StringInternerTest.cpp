#include <Z/Zirsakht/Memory/StringInterner.hpp>

#include <gtest/gtest.h>

#include <gtest/gtest_prod.h>
#include <string>
#include <vector>

namespace Z::Zirsakht::Memory::Tests {
    TEST(StringInterner, InternEmptyString) {
        StringInterner<> interner;

        const auto *value = interner.intern("");

        ASSERT_NE(value, nullptr);
        EXPECT_TRUE(value->empty());
    }

    TEST(StringInterner, InternString) {
        StringInterner<> interner;

        const auto *value = interner.intern("hello");

        ASSERT_NE(value, nullptr);
        EXPECT_EQ(*value, "hello");
    }

    TEST(StringInterner, InternMultipleStrings) {
        StringInterner<> interner;

        const auto *first  = interner.intern("hello");
        const auto *second = interner.intern("world");
        const auto *third  = interner.intern("zirsakht");

        EXPECT_EQ(*first, "hello");
        EXPECT_EQ(*second, "world");
        EXPECT_EQ(*third, "zirsakht");
    }

    TEST(StringInterner, InternDuplicateString) {
        StringInterner<> interner;

        const auto *first  = interner.intern("hello");
        const auto *second = interner.intern("hello");

        EXPECT_EQ(first, second);
    }

    TEST(StringInterner, InternDifferentStrings) {
        StringInterner<> interner;

        const auto *first  = interner.intern("hello");
        const auto *second = interner.intern("world");

        EXPECT_NE(first, second);
    }

    TEST(StringInterner, InternCaseSensitiveStrings) {
        StringInterner<> interner;

        const auto *lowercase = interner.intern("hello");
        const auto *uppercase = interner.intern("Hello");

        EXPECT_NE(lowercase, uppercase);
        EXPECT_EQ(*lowercase, "hello");
        EXPECT_EQ(*uppercase, "Hello");
    }

    TEST(StringInterner, InternUnicodeStrings) {
        StringInterner<> interner;

        const auto *japanese = interner.intern("こんにちは");
        const auto *farsi    = interner.intern("سلامم");
        const auto *emoji    = interner.intern("Hello 🌍");

        EXPECT_EQ(*japanese, "こんにちは");
        EXPECT_EQ(*farsi, "سلامم");
        EXPECT_EQ(*emoji, "Hello 🌍");
    }

    TEST(StringInterner, InternEmbeddedNullCharacters) {
        StringInterner<> interner;

        const std::string original("hello\0world", 11);

        const auto *value = interner.intern(original);

        ASSERT_NE(value, nullptr);
        EXPECT_EQ(*value, original);
        EXPECT_EQ(value->size(), 11);

        const auto *duplicate = interner.intern(original);

        EXPECT_EQ(value, duplicate);
    }

    TEST(StringInterner, InternLongStrings) {
        StringInterner<> interner;

        const std::string original(100000, 'a');

        const auto *value = interner.intern(original);

        ASSERT_NE(value, nullptr);
        EXPECT_EQ(*value, original);
        EXPECT_EQ(value->size(), 100000);
    }

    TEST(StringInterner, ReferenceStability) {
        StringInterner<> interner;

        const auto *original = interner.intern("original");

        for (int i = 0; i < 10000; ++i) {
            interner.intern("string_" + std::to_string(i));
        }

        ASSERT_NE(original, nullptr);
        EXPECT_EQ(*original, "original");

        const auto *duplicate = interner.intern("original");

        EXPECT_EQ(original, duplicate);
    }

    TEST(StringInterner, StorageGrowth) {
        StringInterner<> interner;

        std::vector<const std::string *> values;

        for (int i = 0; i < 10000; ++i) {
            values.push_back(interner.intern("string_" + std::to_string(i)));
        }

        ASSERT_EQ(values.size(), 10000);

        for (int i = 0; i < 10000; ++i) {
            ASSERT_NE(values[i], nullptr);
            EXPECT_EQ(*values[i], "string_" + std::to_string(i));
        }
    }

    TEST(StringInterner, RepeatedInsertion) {
        StringInterner<> interner;

        const auto *original = interner.intern("repeated");

        for (int i = 0; i < 10000; ++i) {
            const auto *value = interner.intern("repeated");

            EXPECT_EQ(value, original);
        }
    }

    TEST(StringInterner, HashCollision) {
        struct ConstantHasher {
            std::size_t operator()(const std::string &) const {
                return 0;
            }
        };

        StringInterner<ConstantHasher> interner;

        const auto *first  = interner.intern("hello");
        const auto *second = interner.intern("world");
        const auto *third  = interner.intern("zirsakht");

        // Different strings must remain distinct despite identical hashes.
        EXPECT_NE(first, second);
        EXPECT_NE(first, third);
        EXPECT_NE(second, third);

        EXPECT_EQ(*first, "hello");
        EXPECT_EQ(*second, "world");
        EXPECT_EQ(*third, "zirsakht");

        // Identical strings must still resolve to the same interned instance.
        EXPECT_EQ(first, interner.intern("hello"));
        EXPECT_EQ(second, interner.intern("world"));
        EXPECT_EQ(third, interner.intern("zirsakht"));
    }

    TEST(StringInterner, LargeNumberOfStrings) {
        StringInterner<> interner;

        constexpr std::size_t count = 100000;

        std::vector<const std::string *> values;
        values.reserve(count);

        for (std::size_t i = 0; i < count; ++i) {
            values.push_back(
                interner.intern("identifier_" + std::to_string(i)));
        }

        ASSERT_EQ(values.size(), count);

        for (std::size_t i = 0; i < count; ++i) {
            EXPECT_EQ(*values[i], "identifier_" + std::to_string(i));
        }
    }
} // namespace Z::Zirsakht::Memory::Tests
