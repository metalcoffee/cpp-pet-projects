#include "../include/view.h"

void tictactoe::ViewPretty::print_view(Game& game)
{
    const Field & field = game.get_field();
    std::cout << '\n';
    const std::string between_rows = "  +----+----+----+----+----+----+----+----+----+----+";
    for (int i = 9; i >= 0; i--) {
        std::string line = std::to_string(i) + " ", sub_line = "  ";
        std::cout << between_rows << '\n';
        for (int j = 0; j < 10; j++) {
            if (field[j][i] == player::Zero) {
                line += "| @@ ";
                sub_line += "| @@ ";
            } else if (field[j][i] == player::Cross) {
                line += "| \\/ ";
                sub_line += "| /\\ ";
            } else {
                line += "|    ";
                sub_line += "|    ";
            }
        }
        std::cout << line << "|" << '\n';
        std::cout << sub_line << "|" << '\n';
    }
    std::cout << between_rows << '\n';
    std::cout << "    a    b    c    d    e    f    g    h    i    j " << '\n';
}
