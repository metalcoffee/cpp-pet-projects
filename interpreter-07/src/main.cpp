#include <sstream>
#include <string>
#include <vector>
#include "matrix.h"

const int REGISTERS_NM = 10;
const int32_t M_MAX = 1'000'000;

bool ensure_empty(std::istringstream &is, bool before_reading) {
    int const is_next = is.peek();
    if (before_reading && is_next == EOF){
        throw except::invalid_cmd_fmt();
    } else if (!before_reading && is_next != EOF) {
        throw except::invalid_cmd_fmt();
    }
    return false;
}

int read_reg(std::istringstream &is) {
    ensure_empty(is, true);
    std::string reg;
    is >> reg;
    if (reg[0] != '$' || !std::isdigit(reg[1])) {
        throw except::not_a_reg(reg);
    }
    return (reg[1] - '0');
}


int main() {
    const static std::vector<std::string> commands{"load", "elem", "print",
                                                   "exit", "add",  "mul"};
    std::vector<matrix_interpreter::matrix> registers(REGISTERS_NM);
    std::string input;

    while (std::getline(std::cin, input)) {
        try {
            std::istringstream is(input);
            std::string cmd;
            ensure_empty(is, true);
            is >> cmd;

            int reg_num = 0;
            if (cmd == "exit") {
                ensure_empty(is, false);
            } else if (cmd == "load") {
                reg_num = read_reg(is);

                std::string filename;
                ensure_empty(is, true);
                is >> filename;
                ensure_empty(is, false);
                registers[reg_num].load(filename);
            } else if (cmd == "elem") {
                reg_num = read_reg(is);

                int32_t coord_row = 0;
                int32_t coord_col = 0;
                ensure_empty(is, true);
                is >> coord_row;
                ensure_empty(is, true);
                is >> coord_col;
                ensure_empty(is, false);

                if (M_MAX < coord_row || coord_row < 0 ||
                    M_MAX < coord_col || coord_col < 0) {
                    throw except::invalid_cmd_fmt();
                }

                std::cout << registers[reg_num].elem(coord_row, coord_col)
                          << '\n';
            } else if (cmd == "print") {
                reg_num = read_reg(is);
                ensure_empty(is, false);

                registers[reg_num].print(std::cout);
            } else if (cmd == "add" || cmd == "mul") {
                reg_num = read_reg(is);
                int const reg_num2 = read_reg(is);
                ensure_empty(is, false);
                if(cmd == "mul") {
                    registers[reg_num] *= registers[reg_num2];
                } else if(cmd == "add") {
                    registers[reg_num] += registers[reg_num2];
                }
            } else {
                throw except::unknown_cmd(cmd);
            }

        } catch (const except::matrix_exceptions &e) {
            std::cout << e.what() << '\n';
            continue;
        }
    }
}
