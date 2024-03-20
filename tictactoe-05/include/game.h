#pragma once
#include <sstream>
#include <regex>
#include <memory>
#include <boost/algorithm/string/trim.hpp>

namespace tictactoe {

const int size = 10;

enum player {
    Cross, Zero, Empty
};

enum game_step {
    BadMove, Exit, CompactView, PrettyView, Draw, OWin, XWin, Move
};
typedef std::vector<std::vector<player>> Field;

class Game {
public:
    game_step who_wins();
    game_step parsing(std::string cmd);
    player get_curr_player();
    Field get_field() const;
    void change_curr_player();
    game_step get_view();

private:
    int moves_made = 0;
    Field field = Field(size, std::vector<player>(size, player::Empty));
    player curr_player = player::Zero;
    game_step move_curr_player(int x, int y);
    game_step curr_view = CompactView;
    int prev_step_x;
    int prev_step_y;

};
}