#include "../include/view.h"

void tictactoe::ViewCompact::print_view(Game& game)
{
    const Field & field = game.get_field();
    std::cout << '\n';
    for (const auto& line : field) {
        std::string res;
        for (const auto& player : line) {
            if (player == player::Zero) {
                res += "O";
            }
            else if (player == player::Cross) {
                res += "X";
            }
            else {
                res += ".";
            }
        }
        std::cout << res << '\n';
    }
}
