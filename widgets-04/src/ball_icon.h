#ifndef BALL_ICON_H
#define BALL_ICON_H

#include <cmath>
#include <memory>
#include <utility>
#include "abstract_widgets.h"

namespace widgets {
struct ball_icon final : widget {
private:
    int m_radius;

public:
    explicit ball_icon(int radius) : m_radius(radius) {
    }

    [[nodiscard]] int height() const final {
        return 2 * m_radius + 1;
    }

    [[nodiscard]] int width() const final {
        return 2 * m_radius + 1;
    }

    [[nodiscard]] const int &radius() const {
        return m_radius;
    }

    void radius(int new_radius) {
        m_radius = new_radius;
    }

    [[nodiscard]] widget *child_at(int x, int y) override {
        int const delta_x = m_radius - x;
        int const delta_y = m_radius - y;
        int const distance = delta_x * delta_x + delta_y * delta_y;
        int const squared_radius = m_radius * m_radius;
        if (distance <= squared_radius) {
            return this;
        }
        return nullptr;
    }
};

[[nodiscard]] inline std::unique_ptr<ball_icon> make_ball_icon(int radius) {
    return std::make_unique<ball_icon>(radius);
}
}  // namespace widgets

#endif  // BALL_ICON_H
