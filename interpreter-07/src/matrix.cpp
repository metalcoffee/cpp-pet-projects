#include "matrix.h"

#include <cstddef>

namespace matrix_interpreter {
void matrix::load(std::string &filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw except::unable_to_open_file(filename);
    }
    if (!(f >> m_row >> m_col)) {
        throw except::invalid_fmt_file();
    }
    if(m_row == 0 || m_col == 0){
        m_row = 0;
        m_col = 0;
        return;
    }
    m_matrix.resize(m_row);
    for (int32_t i = 0; i < m_row; ++i) {
        m_matrix[i].resize(m_col);
    }
    for (int32_t i = 0; i < m_row; ++i) {
        for (int32_t j = 0; j < m_col; ++j) {
            if (!(f >> m_matrix[i][j])) {
                throw except::invalid_fmt_file();
            }
        }
    }
}

void matrix::print(std::ostream &os) {
    if (m_row == 0 || m_col == 0) {
        return;
    }
    for (int32_t i = 0; i < m_row; ++i) {
        for (int32_t j = 0; j < m_col; ++j) {
            if (j != 0) {
                os << ' ';
            }
            os << m_matrix[i][j];
        }
        os << '\n';
    }
}

int32_t matrix::elem(size_t row, size_t col) {
    if (m_matrix.size() > row && m_matrix[row].size() > col) {
        return m_matrix[row][col];
    } else {
        throw except::out_of_bounds();
    }
}

void matrix::operator+=(const matrix &other) {
    if (m_row != other.m_row) {
        throw except::mismatch(m_row, other.m_row);
    } else if (m_col != other.m_col) {
        throw except::mismatch(m_col, other.m_col);
    }

    for (int32_t i = 0; i < m_row; ++i) {
        for (int32_t j = 0; j < m_col; ++j) {
            m_matrix[i][j] += other.m_matrix[i][j];
        }
    }
}

void matrix::operator*=(const matrix &other) {
    if (m_col != other.m_row) {
        throw except::mismatch(m_col, other.m_row);
    }

    matrix res = *this;
    m_matrix.resize(res.m_row);
    for (int32_t i = 0; i < res.m_row; ++i) {
        m_matrix[i].resize(other.m_col);
    }
    m_row = res.m_row;
    m_col = other.m_col;
    for (int32_t i = 0; i < res.m_row; ++i) {
        for (int32_t j = 0; j < other.m_col; ++j) {
            int64_t sum = 0;
            for (int32_t k = 0; k < res.m_col; ++k) {
                sum += (static_cast<int64_t>(res.m_matrix[i][k] * other.m_matrix[k][j]));
            }
            m_matrix[i][j] = static_cast<int32_t>(sum);
        }
    }
}
}  // namespace matrix_interpreter
