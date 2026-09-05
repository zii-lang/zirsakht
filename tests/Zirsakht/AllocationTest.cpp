#include <gtest/gtest.h>

#include <Z/Zirsakht/Memory/AllocatorBase.hpp>

namespace Z::Zirsakht::Tests {
    TEST(ConstructAllocatorTest, ConstructAllocator) {
        ConstructAllocator allocator;

        void *ptr = allocator.allocate(1024, 16);
        EXPECT_NE(ptr, nullptr);

        allocator.deallocate(ptr, 1024, 16);
    }

    TEST(MallocAllocatorTest, MallocAllocator) {
        MallocAllocator allocator;

        void *ptr = allocator.allocate(1024, 16);
        EXPECT_NE(ptr, nullptr);

        allocator.deallocate(ptr, 1024, 16);
    }

    TEST(MallocAllocatorTest, AllocatedMemoryIsAligned) {
        MallocAllocator allocator;

        void *ptr = allocator.allocate(1024, 64);
        ASSERT_NE(ptr, nullptr);

        EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr) % 64, 0);

        allocator.deallocate(ptr, 1024, 64);

        ptr = allocator.allocate(1024, 32);
        ASSERT_NE(ptr, nullptr);

        EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr) % 32, 0);

        allocator.deallocate(ptr, 1024, 32);
    }

    TEST(MallocAllocatorTest, AllocateTypedArray) {
        MallocAllocator       allocator;
        constexpr std::size_t count = 10;

        int *ptr = allocator.allocate<int>(count);

        ASSERT_NE(ptr, nullptr);

        // Verify alignment.
        auto address = reinterpret_cast<std::uintptr_t>(ptr);

        EXPECT_EQ(address % alignof(int), 0);

        // The memory should be usable for count ints.
        for (std::size_t i = 0; i < count; ++i) {
            ptr[i] = static_cast<int>(i);
        }

        for (std::size_t i = 0; i < count; ++i) {
            EXPECT_EQ(ptr[i], static_cast<int>(i));
        }

        allocator.deallocate<int>(ptr, count);
    }

    TEST(ConstructAllocatorTest, AllocateTypedArray) {
        ConstructAllocator    allocator;
        constexpr std::size_t count = 10;

        int *ptr = allocator.allocate<int>(count);

        ASSERT_NE(ptr, nullptr);

        // Verify alignment.
        auto address = reinterpret_cast<std::uintptr_t>(ptr);

        EXPECT_EQ(address % alignof(int), 0);

        // The memory should be usable for count ints.
        for (std::size_t i = 0; i < count; ++i) {
            ptr[i] = static_cast<int>(i);
        }

        for (std::size_t i = 0; i < count; ++i) {
            EXPECT_EQ(ptr[i], static_cast<int>(i));
        }

        allocator.deallocate<int>(ptr, count);
    }
} // namespace Z::Zirsakht::Tests
