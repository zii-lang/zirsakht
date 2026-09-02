#include <gtest/gtest.h>

#include <Z/Zirsakht/Memory/AllocatorBase.hpp>

namespace Z::Zirsakht::Tests {

    class AllocationTest : public ::testing::Test {
      protected:
        AllocationTest()           = default;
        ~AllocationTest() override = default;

        void SetUp() override {
            // Fixture setup.
        }

        void TearDown() override {
            // Fixture teardown.
        }
    };

    TEST_F(AllocationTest, ConstructAllocator) {
        ConstructAllocator allocator;

        void *ptr = allocator.allocate(1024, 16);
        EXPECT_NE(ptr, nullptr);

        allocator.deallocate(ptr, 1024, 16);
    }

    TEST_F(AllocationTest, MallocAllocator) {
        MallocAllocator allocator;

        void *ptr = allocator.allocate(1024, 16);
        EXPECT_NE(ptr, nullptr);

        allocator.deallocate(ptr, 1024, 16);
    }

    TEST_F(AllocationTest, AllocatedMemoryIsAligned) {
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
} // namespace Z::Zirsakht::Tests
