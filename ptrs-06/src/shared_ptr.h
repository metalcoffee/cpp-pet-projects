#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <algorithm>

namespace ptrs::shared {

template <typename T>
struct shared_ptr {
private:
    T *m_ptr = nullptr;
    int *m_cnt = nullptr;

    void dec_cnt() {
        if (!m_ptr) {
            return;
        }
        (*m_cnt)--;
        if ((*m_cnt) <= 0) {
            delete m_ptr;
            delete m_cnt;
        }
    }

public:
    shared_ptr() = default;

    explicit shared_ptr(T *ptr) : m_ptr(ptr) {
        if (ptr) {
            m_cnt = new int(1);
        }
    }

    // cppcheck-suppress noExplicitConstructor
    shared_ptr(std::nullptr_t){};

    // cppcheck-suppress noExplicitConstructor
    shared_ptr(shared_ptr const &ptr)
        : m_ptr(ptr.m_ptr), m_cnt(std::move(ptr.m_cnt)) {
        if (m_ptr) {
            (*m_cnt)++;
        }
    }

    shared_ptr &operator=(shared_ptr const &ptr) {
        if (ptr.m_ptr != m_ptr) {
            dec_cnt();
            m_ptr = ptr.m_ptr;
            m_cnt = ptr.m_cnt;
            if (m_ptr) {
                (*m_cnt)++;
            }
        }
        if (!ptr && !ptr.m_ptr) {
            m_cnt = ptr.m_cnt;
        }
        return *this;
    }

    shared_ptr(shared_ptr &&being_moved)
        : m_ptr(std::exchange(being_moved.m_ptr, nullptr)),
          m_cnt(std::exchange(being_moved.m_cnt, nullptr)) {
    }

    shared_ptr &operator=(shared_ptr &&being_moved) noexcept {
        if (being_moved.m_ptr == m_ptr) {
            return *this;
        }
        dec_cnt();
        m_ptr = std::exchange(being_moved.m_ptr, nullptr);
        m_cnt = std::exchange(being_moved.m_cnt, nullptr);
        return *this;
    }

    ~shared_ptr() noexcept {
        dec_cnt();
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
        dec_cnt();
        m_cnt =  ptr ? new int(1) : nullptr;
        m_ptr = ptr;
    }

    [[nodiscard]] T *release() {
        return std::exchange(m_ptr, nullptr);
    }

    friend void swap(shared_ptr &left, shared_ptr &right) {
        std::swap(left.m_ptr, right.m_ptr);
        std::swap(left.m_cnt, right.m_cnt);
    }

    explicit operator bool() const {
        return (nullptr != m_ptr);
    }

    [[nodiscard]] friend bool operator==(const shared_ptr &ptr1,
                                         const shared_ptr &ptr2) {
        return (ptr1.m_ptr == ptr2.m_ptr);
    }

    [[nodiscard]] friend bool operator!=(const shared_ptr &ptr1,
                                         const shared_ptr &ptr2) {
        return (ptr1.m_ptr != ptr2.m_ptr);
    }
};
}  // namespace ptrs::shared

#endif  // SHARED_PTR_H