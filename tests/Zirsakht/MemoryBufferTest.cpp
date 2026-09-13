#include <gtest/gtest.h>

#include <Z/Zirsakht/Memory/MemoryBuffer.hpp>

#include <cstring>
#include <string_view>

namespace Z::Zirsakht::Memory::Tests {

    TEST(MemoryBufferTest, StartsWithInlineStorage) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        EXPECT_TRUE(buffer.empty());
        EXPECT_EQ(buffer.size(), 0);
        EXPECT_EQ(buffer.capacity(), 256);
        EXPECT_TRUE(buffer.using_inline_storage());
    }

    TEST(MemoryBufferTest, PushBack) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        buffer.push_back('a');
        buffer.push_back('b');
        buffer.push_back('c');

        EXPECT_EQ(buffer.size(), 3);
        EXPECT_EQ(buffer[0], 'a');
        EXPECT_EQ(buffer[1], 'b');
        EXPECT_EQ(buffer[2], 'c');
    }

    TEST(MemoryBufferTest, GrowsWhenInlineStorageIsExhausted) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        ASSERT_TRUE(buffer.using_inline_storage());

        const std::size_t old_capacity = buffer.capacity();

        buffer.resize(old_capacity + 1);

        EXPECT_EQ(buffer.size(), old_capacity + 1);
        EXPECT_GT(buffer.capacity(), old_capacity);
        EXPECT_FALSE(buffer.using_inline_storage());
    }

    TEST(MemoryBufferTest, PreservesDataAfterGrowth) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        for (std::size_t i = 0; i < 256; ++i)
            buffer.push_back(static_cast<char>(i));

        ASSERT_TRUE(buffer.using_inline_storage());

        buffer.push_back('x');

        ASSERT_FALSE(buffer.using_inline_storage());
        ASSERT_EQ(buffer.size(), 257);

        for (std::size_t i = 0; i < 256; ++i)
            EXPECT_EQ(buffer[i], static_cast<char>(i));

        EXPECT_EQ(buffer[256], 'x');
    }

    TEST(MemoryBufferTest, ReserveGrowsCapacity) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        ASSERT_TRUE(buffer.using_inline_storage());

        buffer.reserve(1024);

        EXPECT_GE(buffer.capacity(), 1024);
        EXPECT_EQ(buffer.size(), 0);
        EXPECT_FALSE(buffer.using_inline_storage());
    }

    TEST(MemoryBufferTest, ReserveDoesNotShrink) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        buffer.reserve(1024);

        const std::size_t capacity = buffer.capacity();

        buffer.reserve(128);

        EXPECT_EQ(buffer.capacity(), capacity);
    }

    TEST(MemoryBufferTest, ResizeLarger) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        buffer.resize(100);

        EXPECT_EQ(buffer.size(), 100);
        EXPECT_GE(buffer.capacity(), 100);

        for (std::size_t i = 0; i < 100; ++i)
            EXPECT_EQ(buffer[i], '\0');
    }

    TEST(MemoryBufferTest, ResizeSmaller) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        for (std::size_t i = 0; i < 100; ++i)
            buffer.push_back(static_cast<char>(i));

        buffer.resize(50);

        EXPECT_EQ(buffer.size(), 50);

        for (std::size_t i = 0; i < 50; ++i)
            EXPECT_EQ(buffer[i], static_cast<char>(i));
    }

    TEST(MemoryBufferTest, ResizeToZero) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        buffer.resize(100);

        EXPECT_FALSE(buffer.empty());

        buffer.resize(0);

        EXPECT_TRUE(buffer.empty());
        EXPECT_EQ(buffer.size(), 0);
    }

    TEST(MemoryBufferTest, Clear) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        buffer.resize(100);

        const std::size_t capacity = buffer.capacity();

        buffer.clear();

        EXPECT_TRUE(buffer.empty());
        EXPECT_EQ(buffer.size(), 0);
        EXPECT_EQ(buffer.capacity(), capacity);
    }

    TEST(MemoryBufferTest, DataIsContiguous) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        buffer.resize(10);

        for (std::size_t i = 0; i < 10; ++i)
            buffer[i] = static_cast<char>(i);

        const char *data = buffer.data();

        for (std::size_t i = 0; i < 10; ++i)
            EXPECT_EQ(data[i], static_cast<char>(i));
    }

    TEST(MemoryBufferTest, Back) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        buffer.push_back('a');
        buffer.push_back('b');
        buffer.push_back('c');

        EXPECT_EQ(buffer.back(), 'c');
    }

    TEST(MemoryBufferTest, MoveFromInlineStorage) {
        Memory::BasicMemoryBuffer<char, 256> source;

        source.push_back('h');
        source.push_back('e');
        source.push_back('l');
        source.push_back('l');
        source.push_back('o');

        ASSERT_TRUE(source.using_inline_storage());

        Memory::BasicMemoryBuffer<char, 256> destination(std::move(source));

        EXPECT_EQ(destination.size(), 5);
        EXPECT_TRUE(destination.using_inline_storage());

        EXPECT_EQ(destination[0], 'h');
        EXPECT_EQ(destination[1], 'e');
        EXPECT_EQ(destination[2], 'l');
        EXPECT_EQ(destination[3], 'l');
        EXPECT_EQ(destination[4], 'o');

        EXPECT_TRUE(source.empty());
    }

    TEST(MemoryBufferTest, MoveFromHeapStorage) {
        Memory::BasicMemoryBuffer<char, 256> source;

        source.resize(1024);

        std::memset(source.data(), 'x', source.size());

        ASSERT_FALSE(source.using_inline_storage());

        char *original_data = source.data();

        Memory::BasicMemoryBuffer<char, 256> destination(std::move(source));

        EXPECT_EQ(destination.size(), 1024);
        EXPECT_FALSE(destination.using_inline_storage());

        // Heap storage should be transferred rather than copied.
        EXPECT_EQ(destination.data(), original_data);

        for (std::size_t i = 0; i < destination.size(); ++i)
            EXPECT_EQ(destination[i], 'x');

        EXPECT_TRUE(source.empty());
    }

    TEST(MemoryBufferTest, MoveAssignmentFromInlineStorage) {
        Memory::BasicMemoryBuffer<char, 256> source;

        source.push_back('h');
        source.push_back('i');

        Memory::BasicMemoryBuffer<char, 256> destination;

        destination = std::move(source);

        EXPECT_EQ(destination.size(), 2);
        EXPECT_EQ(destination[0], 'h');
        EXPECT_EQ(destination[1], 'i');

        EXPECT_TRUE(destination.using_inline_storage());
        EXPECT_TRUE(source.empty());
    }

    TEST(MemoryBufferTest, MoveAssignmentFromHeapStorage) {
        Memory::BasicMemoryBuffer<char, 256> source;

        source.resize(1024);
        std::memset(source.data(), 'x', source.size());

        char *original_data = source.data();

        Memory::BasicMemoryBuffer<char, 256> destination;

        destination = std::move(source);

        EXPECT_EQ(destination.size(), 1024);
        EXPECT_FALSE(destination.using_inline_storage());

        EXPECT_EQ(destination.data(), original_data);

        for (std::size_t i = 0; i < destination.size(); ++i)
            EXPECT_EQ(destination[i], 'x');

        EXPECT_TRUE(source.empty());
    }

    TEST(MemoryBufferTest, MultipleGrowthOperations) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        std::size_t previous_capacity = buffer.capacity();

        for (std::size_t size = 1; size <= 4096; ++size) {
            buffer.resize(size);

            EXPECT_EQ(buffer.size(), size);
            EXPECT_GE(buffer.capacity(), size);

            if (size > previous_capacity) {
                EXPECT_GT(buffer.capacity(), previous_capacity);
                previous_capacity = buffer.capacity();
            }
        }

        EXPECT_EQ(buffer.size(), 4096);
        EXPECT_FALSE(buffer.using_inline_storage());
    }

    TEST(MemoryBufferTest, GrowthPreservesExistingData) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        for (std::size_t i = 0; i < 1000; ++i)
            buffer.push_back(static_cast<char>(i % 256));

        ASSERT_EQ(buffer.size(), 1000);

        for (std::size_t i = 0; i < 1000; ++i)
            EXPECT_EQ(buffer[i], static_cast<char>(i % 256));
    }

    TEST(MemoryBufferTest, CapacityIsAtLeastSize) {
        Memory::BasicMemoryBuffer<char, 256> buffer;

        for (std::size_t size = 0; size < 2048; ++size) {
            buffer.resize(size);

            EXPECT_GE(buffer.capacity(), buffer.size());
        }
    }

} // namespace Z::Zirsakht::Memory::Tests
