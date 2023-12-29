#include <iostream>
#include <string>
#include <vector>
const std::vector<int> dx_fwd = {1, 0, -1, 0};
const std::vector<int> dy_fwd = {0, 1, 0, -1};
// [0] - right [1] - up [2] - left [3] - down

const std::vector<int> dx_bwd = {-1, 0, 1, 0};
const std::vector<int> dy_bwd = {0, -1, 0, 1};
// ~[0] - left [1] - down [2] - right [3] - up

enum class cmd_type {
    SHERLOCK,
    CAT_JEOFFRY,
    EXIT,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    SHOW_MAP,
    START_MACRO,
    RUN_MACRO,
    END_MACRO,
    INVALID
};

cmd_type parse_command(const std::string &cmd_line) {
    std::size_t ind_start = 0;
    std::size_t ind_end = cmd_line.length() - 1;
    while (std::isspace(cmd_line[ind_start]) != 0) {
        ind_start++;
    }
    while (std::isspace(cmd_line[ind_end]) != 0) {
        ind_end--;
    }
    std::string const command =
        cmd_line.substr(ind_start, ind_end - ind_start + 1);
    if (command == "sherlock" || command == "sherlock-holmes") {
        return cmd_type::SHERLOCK;
    } else if (command == "cat" || command == "cat-jeoffry") {
        return cmd_type::CAT_JEOFFRY;
    } else if (command == "quit" || command == "exit") {
        return cmd_type::EXIT;
    } else if (command == "forward" || command == "fwd") {
        return cmd_type::FORWARD;
    } else if (command == "backward" || command == "bwd") {
        return cmd_type::BACKWARD;
    } else if (command == "left" || command == "turn-left") {
        return cmd_type::LEFT;
    } else if (command == "right" || command == "turn-right") {
        return cmd_type::RIGHT;
    } else if (command == "show-map") {
        return cmd_type::SHOW_MAP;
    } else if (command == "start-macro") {
        return cmd_type::START_MACRO;
    } else if (command == "end-macro") {
        return cmd_type::END_MACRO;
    } else if (command == "run-macro") {
        return cmd_type::RUN_MACRO;
    } else {
        return cmd_type::INVALID;
    }
}

class Action {
private:
    std::vector<std::vector<char>> field;
    std::vector<cmd_type> macro;
    std::size_t left_corner_x{1000};
    std::size_t left_corner_y{1000};
    std::size_t right_corner_x{1000};
    std::size_t right_corner_y{1000};
    std::size_t coord_x{1000};
    std::size_t coord_y{1000};

    void moving(const std::vector<int> &horizontal_dx,
                const std::vector<int> &vertical_dy) {
        int dx_dy = 0;
        char const prev_char = field[coord_x][coord_y];
        if (field[coord_x][coord_y] == '^') {
            dx_dy = 1;
        } else if (field[coord_x][coord_y] == '<') {
            dx_dy = 2;
        } else if (field[coord_x][coord_y] == 'v') {
            dx_dy = 3;
        }

        field[coord_x][coord_y] = 'o';
        coord_x += horizontal_dx[dx_dy];
        coord_y += vertical_dy[dx_dy];
        field[coord_x][coord_y] = prev_char;

        left_corner_x = std::min(left_corner_x, coord_x);
        left_corner_y = std::min(left_corner_y, coord_y);
        right_corner_x = std::max(right_corner_x, coord_x);
        right_corner_y = std::max(right_corner_y, coord_y);
    }

public:
    Action() {
        field =
            std::vector<std::vector<char>>(2000, std::vector<char>(2000, '.'));
        field[coord_x][coord_y] = '^';
    }

    void backward() {
        moving(dx_bwd, dy_bwd);
    }

    void forward() {
        moving(dx_fwd, dy_fwd);
    }

    void right() {
        if (field[coord_x][coord_y] == '^') {
            field[coord_x][coord_y] = '>';
        } else if (field[coord_x][coord_y] == '>') {
            field[coord_x][coord_y] = 'v';
        } else if (field[coord_x][coord_y] == '<') {
            field[coord_x][coord_y] = '^';
        } else {
            field[coord_x][coord_y] = '<';
        }
    }

    void left() {
        if (field[coord_x][coord_y] == '^') {
            field[coord_x][coord_y] = '<';
        } else if (field[coord_x][coord_y] == '>') {
            field[coord_x][coord_y] = '^';
        } else if (field[coord_x][coord_y] == '<') {
            field[coord_x][coord_y] = 'v';
        } else {
            field[coord_x][coord_y] = '>';
        }
    }

    void print_map() {
        std::size_t const size_x = right_corner_x - left_corner_x + 1;
        for (std::size_t i = 0; i < size_x * 2 + 1; i++) {
            std::cout << " ";
        }
        std::cout << '\n';
        for (std::size_t i = right_corner_y; i >= left_corner_y; --i) {
            for (std::size_t j = left_corner_x; j <= right_corner_x; ++j) {
                std::cout << " " << field[j][i];
            }
            std::cout << " \n";
            for (std::size_t j = 0; j < size_x * 2 + 1; ++j) {
                std::cout << " ";
            }
            std::cout << '\n';
        }
    }

    void record_macro() {
        macro.clear();
        std::string cmd;
        while (std::getline(std::cin, cmd)) {
            cmd_type const command = parse_command(cmd);
            switch (command) {
                case cmd_type::LEFT:
                case cmd_type::RIGHT:
                case cmd_type::FORWARD:
                case cmd_type::BACKWARD:
                case cmd_type::SHOW_MAP:
                    macro.push_back(command);
                    std::cout << "Recorded" << '\n';
                    break;
                case cmd_type::END_MACRO:
                    std::cout << "New macro of " << macro.size()
                              << " command(s)" << '\n';
                    return;
                default:
                    std::cout << "Invalid command: '" << cmd << "'" << '\n';
            }
        }
    }

    void run_macro() {
        for (auto &cmd : macro) {
            switch (cmd) {
                case cmd_type::FORWARD:
                    forward();
                    break;
                case cmd_type::BACKWARD:
                    backward();
                    break;
                case cmd_type::LEFT:
                    left();
                    break;
                case cmd_type::RIGHT:
                    right();
                    break;
                case cmd_type::SHOW_MAP:
                    print_map();
                    break;
                default:
                    break;
            }
        }
    }
};

int main() {
    const char *HOLMES =
        R"(I had had so many reasons to believe in my friend's subtle powers of
reasoning and extraordinary energy in action that I felt that he must
have some solid grounds for the assured and easy demeanour with which
he treated the singular mystery which he had been called upon to
fathom. Once only had I known him to fail, in the case of the King of
Bohemia and of the Irene Adler photograph; but when I looked back to
the weird business of the Sign of Four, and the extraordinary
circumstances connected with the Study in Scarlet, I felt that it would
be a strange tangle indeed which he could not unravel.)";

    const char *JEOFFRY = R"(For he is of the tribe of Tiger.
For the Cherub Cat is a term of the Angel Tiger.
For he has the subtlety and hissing of a serpent, which in goodness he suppresses.
For he will not do destruction, if he is well-fed, neither will he spit without provocation.
For he purrs in thankfulness, when God tells him he's a good Cat.
For he is an instrument for the children to learn benevolence upon.
For every house is incomplete without him and a blessing is lacking in the spirit.
For the Lord commanded Moses concerning the cats at the departure of the Children of Israel from Egypt.
For every family had one cat at least in the bag.
For the English Cats are the best in Europe.)";

    std::string raw_command;
    Action act;
    while (std::getline(std::cin, raw_command)) {
        cmd_type const command_type = parse_command(raw_command);
        switch (command_type) {
            case cmd_type::SHERLOCK:
                std::cout << HOLMES << '\n';
                break;
            case cmd_type::CAT_JEOFFRY:
                std::cout << JEOFFRY << '\n';
                break;
            case cmd_type::EXIT:
                return 0;
            case cmd_type::FORWARD:
                act.forward();
                break;
            case cmd_type::BACKWARD:
                act.backward();
                break;
            case cmd_type::LEFT:
                act.left();
                break;
            case cmd_type::RIGHT:
                act.right();
                break;
            case cmd_type::SHOW_MAP:
                act.print_map();
                break;
            case cmd_type::START_MACRO:
                act.record_macro();
                break;
            case cmd_type::RUN_MACRO:
                act.run_macro();
                break;
            case cmd_type::INVALID:
                std::cout << "Invalid command: '" << raw_command << "'" << '\n';
                break;
            default:
                break;
        }
    }
    return 0;
}
