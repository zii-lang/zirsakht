#pragma once

#include <cstddef>

namespace Z::Zirsakht {
    template<typename DerivedT>
    class AllocatorBase {
      public:
        inline void *allocate(std::size_t size, std::size_t alignment) {
            return static_cast<DerivedT *>(this)->allocate(size, alignment);
        }

        inline void deallocate(const void *ptr, std::size_t size,
                               std::size_t alignment) {
            static_cast<DerivedT *>(this)->deallocate(ptr, size, alignment);
        }

        template<typename T>
        T *allocate(std::size_t count = 1) {
            return static_cast<T *>(allocate(count * sizeof(T), alignof(T)));
        }

        template<typename T>
        void deallocate(const T *ptr, std::size_t count = 1) {
            deallocate(ptr, count * sizeof(T), alignof(T));
        }
    };

    class ConstructAllocator : public AllocatorBase<ConstructAllocator> {
      public:
        using AllocatorBase<ConstructAllocator>::allocate;
        using AllocatorBase<ConstructAllocator>::deallocate;

        void *allocate(std::size_t size, std::size_t alignment);
        void  deallocate(const void *ptr, std::size_t size,
                         std::size_t alignment);
    };

    class MallocAllocator : public AllocatorBase<MallocAllocator> {
      public:
        using AllocatorBase<MallocAllocator>::allocate;
        using AllocatorBase<MallocAllocator>::deallocate;

        void *allocate(std::size_t size, std::size_t alignment);
        void  deallocate(const void *ptr, std::size_t size,
                         std::size_t alignment);
    };
} // namespace Z::Zirsakht
