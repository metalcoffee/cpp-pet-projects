#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <algorithm>

namespace ptrs::unique {

template <typename T>
struct default_delete {
    void operator()(T *ptr) const {
        delete ptr;
    }
};

template <typename T, typename Deleter = default_delete<T>>
struct unique_ptr {
private:
    T *m_ptr = nullptr;
    Deleter m_del;

public:
    unique_ptr() = default;

    explicit unique_ptr(T *ptr) : m_ptr(std::move(ptr)) {
    }

    explicit unique_ptr(T *ptr, Deleter del)
        : m_ptr(ptr), m_del(std::move(del)) {
    }
    // cppcheck-suppress noExplicitConstructor
    unique_ptr(std::nullptr_t){};

    unique_ptr(unique_ptr const &ptr) = delete;

    unique_ptr &operator=(unique_ptr const &ptr) = delete;

    unique_ptr(unique_ptr &&being_moved) noexcept
        : m_ptr(std::exchange(being_moved.m_ptr, nullptr)),
          m_del(std::move(being_moved.m_del)) {
    }

    unique_ptr &operator=(unique_ptr &&being_moved) noexcept {
        reset(being_moved.release());
        m_del = std::move(being_moved.m_del);
        return *this;
    }

    ~unique_ptr() noexcept {
        if (m_ptr != nullptr) {
            m_del(m_ptr);
        }
    }

    [[nodiscard]] T *operator->() const {
        return m_ptr;
    }

    [[nodiscard]] T &operator*() const {
        return *m_ptr;
    }

    [[nodiscard]] T *get() const {
        return m_ptr;
    }

    void reset(T *ptr = nullptr) {
        if (m_ptr != nullptr) {
            m_del(m_ptr);
        }
        m_ptr = ptr;
    }

    [[nodiscard]] T *release() {
        return std::exchange(m_ptr, nullptr);
    }

    friend void swap(unique_ptr &left, unique_ptr &right) {
        std::swap(left.m_ptr, right.m_ptr);
        std::swap(left.m_del, right.m_del);
    }

    explicit operator bool() const {
        return (nullptr != m_ptr);
    }

    [[nodiscard]] friend bool operator==(const unique_ptr &ptr1,
                                         const unique_ptr &ptr2) {
        return (ptr1.m_ptr == ptr2.m_ptr);
    }

    [[nodiscard]] friend bool operator!=(const unique_ptr &ptr1,
                                         const unique_ptr &ptr2) {
        return (ptr1.m_ptr != ptr2.m_ptr);
    }
};
}  // namespace ptrs::unique

#endif  // UNIQUE_PTR_H