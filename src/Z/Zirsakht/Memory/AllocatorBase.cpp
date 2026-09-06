#include <Z/Zirsakht/Common.hpp>
#include <Z/Zirsakht/Memory/AllocatorBase.hpp>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <new>
#include <stdexcept>

namespace Z::Zirsakht {
#ifdef ZIRSAKHT_OS_WINDOWS
    static int check_align(size_t align) {
        for (size_t i = sizeof(void *); i != 0; i *= 2)
            if (align == i)
                return 0;
        return EINVAL;
    }
#endif

    void *ConstructAllocator::allocate(std::size_t size,
                                       std::size_t alignment) {
        void *buf = ::operator new(size,
#ifdef __cpp_aligned_new
                                   std::align_val_t(alignment),
#endif
                                   std::nothrow);

        if (buf == nullptr) {
            // TODO: report error.
            exit(EXIT_FAILURE);
        }

        ++this->m_allocation_count;

        return buf;
    }

    void ConstructAllocator::deallocate(const void *ptr, std::size_t size,
                                        std::size_t alignment) {
        if (ptr == nullptr)
            return;

        ::operator delete(const_cast<void *>(ptr)
#ifdef __cpp_sized_deallocation
                              ,
                          size
#endif
#ifdef __cpp_aligned_new
                          ,
                          std::align_val_t(alignment)
#endif
        );
        --this->m_allocation_count;
    }

    void *MallocAllocator::allocate(std::size_t size, std::size_t alignment) {
        if (size == 0)
            return nullptr;

        if (alignment == 0)
            alignment = alignof(std::max_align_t);

        // Alignment must be a power of two.
        if ((alignment & (alignment - 1)) != 0)
            throw std::invalid_argument("alignment must be a power of two");

        void *ptr = nullptr;

#if ZIRSAKHT_OS_WINDOWS
        // malloc() already provides at least max_align_t alignment.
        if (alignment <= alignof(std::max_align_t)) {
            ptr = std::malloc(size);
        } else {
            ptr = _aligned_malloc(size, alignment);
        }
#elif ZIRSAKHT_POSIX
        if (alignment <= alignof(std::max_align_t)) {
            ptr = std::malloc(size);
        } else {
            const int result = posix_memalign(&ptr, alignment, size);

            if (result != 0)
                ptr = nullptr;
        }
#else
        // Generic fallback.
        if (alignment <= alignof(std::max_align_t)) {
            ptr = std::malloc(size);
        } else {
            // No portable aligned allocation available here.
            throw std::bad_alloc();
        }

#endif

        if (ptr == nullptr)
            throw std::bad_alloc();

        ++this->m_allocation_count;

        return ptr;
    }

    void MallocAllocator::deallocate(const void *ptr, std::size_t size,
                                     std::size_t alignment) {
        if (ptr == nullptr)
            return;
        (void) size;

#if ZIRSAKHT_OS_WINDOWS

        if (alignment <= alignof(std::max_align_t)) {
            std::free(const_cast<void *>(ptr));
        } else {
            _aligned_free(const_cast<void *>(ptr));
        }

#elif ZIRSAKHT_POSIX

        // Both malloc() and posix_memalign() are released with free().
        std::free(const_cast<void *>(ptr));

#else

        std::free(const_cast<void *>(ptr));
#endif

        --this->m_allocation_count;
    }
} // namespace Z::Zirsakht
