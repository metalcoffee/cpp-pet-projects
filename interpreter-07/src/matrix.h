#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace except {
struct matrix_exceptions : std::runtime_error{
    matrix_exceptions(const std::string &error):  std::runtime_error(error){}
};

struct unable_to_open_file : matrix_exceptions {
    explicit unable_to_open_file(const std::string &filename)
        : matrix_exceptions("Unable to open file '" + filename + "'") {
    }
};

struct out_of_bounds : matrix_exceptions {
    explicit out_of_bounds()
        : matrix_exceptions("Requested element is out of bounds") {
    }
};

struct invalid_cmd_fmt : matrix_exceptions {
    explicit invalid_cmd_fmt() : matrix_exceptions("Invalid command format") {
    }
};

struct invalid_fmt_file : matrix_exceptions {
    explicit invalid_fmt_file() : matrix_exceptions("Invalid file format") {
    }
};

struct unknown_cmd : matrix_exceptions {
    explicit unknown_cmd(const std::string &cmd)
        : matrix_exceptions("Unknown command: '" + cmd + "'") {
    }
};
struct not_a_reg : matrix_exceptions {
    explicit not_a_reg(const std::string &reg)
        : matrix_exceptions("'" + reg + "' is not a register") {
    }
};

struct mismatch : matrix_exceptions {
    explicit mismatch(int32_t mismatch_a, int32_t mismatch_b)
        : matrix_exceptions(
              "Dimension mismatch: lhs=" + std::to_string(mismatch_a) +
              ", rhs=" + std::to_string(mismatch_b)){};
};
}  // namespace except

namespace matrix_interpreter {
struct matrix {
private:
    int32_t m_col{0};
    int32_t m_row{0};
    std::vector<std::vector<int32_t>> m_matrix;

public:
    matrix()= default;

    void load(std::string &);

    void print(std::ostream &os);

    int32_t elem(size_t row, size_t col);
    void operator+=(const matrix &other);

    void operator*=(const matrix &other);
};
}  // namespace matrix_interpreter
#endif  // MATRIX_H