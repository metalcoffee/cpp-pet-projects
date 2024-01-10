#ifndef GRID_H_
#define GRID_H_

#include <cassert>
#include <memory>
#include <numeric>
#include <vector>
#include "abstract_widgets.h"

namespace widgets {

struct grid : container {
private:
    std::vector<std::vector<std::unique_ptr<widgets::widget>>> m_grid;
    std::vector<int> m_max_height;
    std::vector<int> m_max_width;

    void update_row(int r_i) {
        m_height -= m_max_height[r_i];
        m_max_height[r_i] = 0;
        for (auto &column : m_grid[r_i]) {
            m_max_height[r_i] = std::max(column->height(), m_max_height[r_i]);
        }
        m_height += m_max_height[r_i];
    }

    void update_col(int c_i) {
        m_width -= m_max_width[c_i];
        m_max_width[c_i] = 0;
        for (auto &row : m_grid) {
            if (row[c_i]) {
                m_max_width[c_i] =
                    std::max(row[c_i]->width(), m_max_width[c_i]);
            }
        }
        m_width += m_max_width[c_i];
    }

public:
    explicit grid(int rows, int columns)
        : m_max_height(rows, 0), m_max_width(columns, 0) {
        assert(0 < rows);
        assert(0 < columns);
        m_grid.resize(rows);
        for (int i = 0; i < rows; i++) {
            m_grid[i].resize(columns);
        }
    }

    [[nodiscard]] int rows() const {
        return static_cast<int>(m_grid.size());
    }

    [[nodiscard]] int columns() const {
        return static_cast<int>(m_grid[0].size());
    }

    [[nodiscard]] widget *get(std::size_t rows, std::size_t columns) const {
        return m_grid[rows][columns].get();
    }

    widget *add(std::unique_ptr<widget> child, int r_i, int c_i) {
        m_grid[r_i][c_i] = std::move(child);
        // update_layout();
        update_row(r_i);
        update_col(c_i);
        return m_grid[r_i][c_i].get();
    }

    std::unique_ptr<widget> remove(int r_i, int c_i) {
        std::unique_ptr<widget> removed_w = std::move(m_grid[r_i][c_i]);
        // update_layout();
        update_row(r_i);
        update_col(c_i);
        return removed_w;
    }

    void update_layout() override {
        m_height = 0;
        m_width = 0;
        std::fill(m_max_height.begin(), m_max_height.end(), 0);
        std::fill(m_max_width.begin(), m_max_width.end(), 0);

        for (std::size_t i = 0; i < m_grid.size(); i++) {
            for (std::size_t j = 0; j < m_grid[0].size(); j++) {
                if (m_grid[i][j]) {
                    m_max_height[i] =
                        std::max(m_grid[i][j]->height(), m_max_height[i]);
                    m_max_width[j] =
                        std::max(m_grid[i][j]->width(), m_max_width[j]);
                }
            }
        }

        m_height = std::accumulate(m_max_height.begin(), m_max_height.end(), 0);
        m_width = std::accumulate(m_max_width.begin(), m_max_width.end(), 0);
    }

    [[nodiscard]] widget *child_at(int x, int y) override {
        if (y == m_height || widget::child_at(x, y) == nullptr) {
            return nullptr;
        }
        int now_height = 0;
        std::size_t row_i = 0;
        while (row_i < m_grid.size()) {
            now_height += m_max_height[row_i];
            if (now_height > y) {
                now_height -= m_max_height[row_i];
                break;
            }
            row_i++;
        }

        assert(row_i == m_grid.size());

        int now_width = 0;
        for (std::size_t j = 0; j < m_grid[0].size(); j++) {
            now_width += m_max_width[j];
            if (x < now_width) {
                if (m_grid[row_i][j] != nullptr) {
                    now_width -= m_max_width[j];
                    return m_grid[row_i][j]->child_at(x - now_width,
                                                      y - now_height);
                }
            }
        }
        return nullptr;
    }
};

[[nodiscard]] inline std::unique_ptr<grid> make_grid(int rows, int columns) {
    return std::make_unique<grid>(rows, columns);
}
}  // namespace widgets

#endif  // GRID_H_
