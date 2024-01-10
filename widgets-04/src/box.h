#ifndef BOX_H
#define BOX_H

#include <memory>
#include <vector>
#include "abstract_widgets.h"
namespace widgets {

struct box : container {
    enum class kind { HORIZONTAL, VERTICAL };

private:
    std::vector<std::unique_ptr<widget>> into_box;
    const kind m_kind;

public:
    explicit box(widgets::box::kind k) : m_kind(k) {
    }

    [[nodiscard]] int size() const {
        return static_cast<int>(into_box.size());
    }

    [[nodiscard]] widget *get(std::size_t ind) const {
        return into_box.at(ind).get();
    }

    widget *add(std::unique_ptr<widget> child) {
        into_box.emplace_back(std::move(child));
        update_layout();
        return into_box.back().get();
    }

    std::unique_ptr<widget> remove(int index) {
        std::unique_ptr<widget> removed_w;
        if (into_box.at(index)) {
            removed_w = std::move(into_box[index]);
            into_box.erase(into_box.begin() + index);
            update_layout();
        }
        return removed_w;
    }

    [[nodiscard]] widget *child_at(int x, int y) override {
        if (y == m_height || widget::child_at(x, y) == nullptr) {
            return nullptr;
        }
        if (m_kind == kind::HORIZONTAL) {
            int horizontal_offset = 0;
            for (auto &row : into_box) {
                horizontal_offset += row->width();
                if (x < horizontal_offset) {
                    return row->child_at(x - (horizontal_offset - row->width()),
                                         y - (m_height - row->height()) / 2);
                }
            }

        } else if (m_kind == kind::VERTICAL) {
            int bottom_offset = 0;
            for (auto &column : into_box) {
                bottom_offset += column->height();
                if (y < bottom_offset) {
                    return column->child_at(
                        x - (m_width - column->width()) / 2,
                        y - (bottom_offset - column->height()));
                }
            }
        }
        return nullptr;
    }

    void update_layout() override {
        m_height = 0;
        m_width = 0;
        if (m_kind == kind::HORIZONTAL) {
            for (auto &row : into_box) {
                m_width += row->width();
                m_height = std::max(row->height(), m_height);
            }
        } else {
            for (auto &column : into_box) {
                m_height += column->height();
                m_width = std::max(column->width(), m_width);
            }
        }
    }
};

[[nodiscard]] inline std::unique_ptr<box> make_box(widgets::box::kind k) {
    return std::make_unique<box>(k);
}

}  // namespace widgets

#endif  // BOX_H
