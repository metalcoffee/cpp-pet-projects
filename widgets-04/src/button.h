#ifndef BUTTON_H_
#define BUTTON_H_

#include <memory>
#include <string>
#include <utility>
#include "abstract_widgets.h"

namespace widgets {
struct button final : widget {
private:
    std::string m_label;

public:
    [[nodiscard]] int width() const final {
        return 10 + 8 * static_cast<int>(m_label.length());
    }

    [[nodiscard]] int height() const final {
        return 10 + 12;
    }

    explicit button(std::string label) : m_label(std::move(label)) {
    }

    [[nodiscard]] const std::string &label() const {
        return m_label;
    }

    void label(std::string new_label) {
        m_label = std::move(new_label);
    }
};

[[nodiscard]] inline auto make_button(std::string label) {
    return std::make_unique<button>(std::move(label));
}
}  // namespace widgets

#endif  // BUTTON_H_
