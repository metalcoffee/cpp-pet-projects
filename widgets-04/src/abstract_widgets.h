#ifndef ABSTRACT_WIDGETS_H_
#define ABSTRACT_WIDGETS_H_

#include <cassert>

namespace widgets {
struct widget {
    [[nodiscard]] virtual int width() const = 0;
    [[nodiscard]] virtual int height() const = 0;
    [[nodiscard]] virtual widget *child_at(int x, int y) {
        if (0 <= x && x < this->width() && 0 <= y && y < this->height()) {
            return this;
        }
        return nullptr;
    }

    widget(const widget &) = delete;
    widget(widget &&) = delete;
    widget &operator=(const widget &) = delete;
    widget &operator=(widget &&) = delete;

    virtual ~widget() = default;

protected:
    widget() = default;
};

struct container : widget {
    virtual void update_layout() = 0;
    [[nodiscard]] int width() const final {
        return m_width;
    }

    [[nodiscard]] int height() const final {
        return m_height;
    }
protected:
    int m_height = 0;
    int m_width = 0;

};
}  // namespace widgets

#endif  // ABSTRACT_WIDGETS_H_
