#ifndef PLACEHOLDER_H_
#define PLACEHOLDER_H_

#include <memory>
#include <utility>
#include "abstract_widgets.h"

namespace widgets {
struct placeholder : widgets::widget {
    [[nodiscard]] int width() const final {
        return m_width;
    }

    [[nodiscard]] int height() const final {
        return m_height;
    }

    explicit placeholder(int width_, int height_)
        : m_width(width_), m_height(height_) {
    }

    // NOLINTNEXTLINE(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    int m_width;
    // NOLINTNEXTLINE(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    int m_height;
};

[[nodiscard]] inline auto make_placeholder(int width, int height) {
    return std::make_unique<placeholder>(width, height);
}
}  // namespace widgets

#endif  // PLACEHOLDER_H_
