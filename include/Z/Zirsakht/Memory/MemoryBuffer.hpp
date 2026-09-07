#pragma once

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <memory>
#include <utility>

namespace Z::Zirsakht::Memory {

    template<typename T, std::size_t InlineSize = 256>
    class BasicMemoryBuffer {
      private:
        T m_inline[InlineSize];

        T          *m_data     = m_inline;
        std::size_t m_size     = 0;
        std::size_t m_capacity = InlineSize;

        void grow(std::size_t required) {
            std::size_t new_capacity = m_capacity + m_capacity / 2;

            if (new_capacity < required)
                new_capacity = required;

            T *new_data = static_cast<T *>(::operator new(
                new_capacity * sizeof(T), std::align_val_t(alignof(T))));

            // Move/copy existing elements.
            std::move(m_data, m_data + m_size, new_data);

            if (m_data != m_inline) {
                ::operator delete(m_data, std::align_val_t(alignof(T)));
            }

            m_data     = new_data;
            m_capacity = new_capacity;
        }

      public:
        using value_type = T;
        using size_type  = std::size_t;

        BasicMemoryBuffer() = default;

        ~BasicMemoryBuffer() {
            clear();

            if (m_data != m_inline) {
                ::operator delete(m_data, std::align_val_t(alignof(T)));
            }
        }

        BasicMemoryBuffer(const BasicMemoryBuffer &)            = delete;
        BasicMemoryBuffer &operator=(const BasicMemoryBuffer &) = delete;

        BasicMemoryBuffer(BasicMemoryBuffer &&other) noexcept {
            if (other.m_data == other.m_inline) {
                std::move(other.m_inline, other.m_inline + other.m_size,
                          m_inline);

                m_size     = other.m_size;
                m_capacity = InlineSize;
                m_data     = m_inline;

                other.clear();
            } else {
                m_data     = other.m_data;
                m_size     = other.m_size;
                m_capacity = other.m_capacity;

                other.m_data     = other.m_inline;
                other.m_size     = 0;
                other.m_capacity = InlineSize;
            }
        }

        BasicMemoryBuffer &operator=(BasicMemoryBuffer &&other) noexcept {
            if (this == &other)
                return *this;

            clear();

            if (m_data != m_inline) {
                ::operator delete(m_data, std::align_val_t(alignof(T)));
            }

            if (other.m_data == other.m_inline) {
                m_data     = m_inline;
                m_capacity = InlineSize;
                m_size     = other.m_size;

                std::move(other.m_inline, other.m_inline + other.m_size,
                          m_inline);

                other.clear();
            } else {
                m_data     = other.m_data;
                m_size     = other.m_size;
                m_capacity = other.m_capacity;

                other.m_data     = other.m_inline;
                other.m_size     = 0;
                other.m_capacity = InlineSize;
            }

            return *this;
        }

        void reserve(std::size_t capacity) {
            if (capacity <= m_capacity)
                return;

            grow(capacity);
        }

        void resize(std::size_t size) {
            if (size > m_capacity)
                grow(size);

            if (size > m_size) {
                std::fill(m_data + m_size, m_data + size, T{});
            }

            m_size = size;
        }

        void push_back(const T &value) {
            if (m_size == m_capacity)
                grow(m_size + 1);

            m_data[m_size++] = value;
        }

        void push_back(T &&value) {
            if (m_size == m_capacity)
                grow(m_size + 1);

            m_data[m_size++] = std::move(value);
        }

        template<typename... Args>
        T &emplace_back(Args &&...args) {
            if (m_size == m_capacity)
                grow(m_size + 1);

            T *element = m_data + m_size;
            std::construct_at(element, std::forward<Args>(args)...);
            ++m_size;

            return *element;
        }

        void clear() noexcept {
            if constexpr (!std::is_trivially_destructible_v<T>) {
                std::destroy(m_data, m_data + m_size);
            }

            m_size = 0;
        }

        T *data() noexcept {
            return m_data;
        }

        const T *data() const noexcept {
            return m_data;
        }

        T &operator[](std::size_t index) noexcept {
            return m_data[index];
        }

        const T &operator[](std::size_t index) const noexcept {
            return m_data[index];
        }

        T &back() noexcept {
            return m_data[m_size - 1];
        }

        const T &back() const noexcept {
            return m_data[m_size - 1];
        }

        std::size_t size() const noexcept {
            return m_size;
        }

        std::size_t capacity() const noexcept {
            return m_capacity;
        }

        bool empty() const noexcept {
            return m_size == 0;
        }

        bool using_inline_storage() const noexcept {
            return m_data == m_inline;
        }

        void append(const T *data, std::size_t count) {
            if (count == 0)
                return;

            const std::size_t required = m_size + count;

            if (required > m_capacity)
                grow(required);

            std::copy_n(data, count, m_data + m_size);
            m_size = required;
        }

        void append(std::basic_string_view<T> value) {
            append(value.data(), value.size());
        }

        void append(const T &value) {
            push_back(value);
        }
    };

    using MemoryBuffer = BasicMemoryBuffer<char>;

} // namespace Z::Zirsakht::Memory
