#include "../include/game.h"

using namespace tictactoe;

tictactoe::game_step tictactoe::Game::parsing(std::string cmd){
    std::smatch match;
    const std::regex cmd_regex(R"(view-\w+)");
    const std::regex coord_regex(R"(-?0*\d -?0*\d)");
    const std::regex pretty_cmd_regex(R"([a-j]\d)");
    boost::algorithm::trim(cmd);

    if (std::regex_match(cmd, match, cmd_regex)) {
        if (cmd != "view-pretty") {
            return PrettyView;
        }
        else if (cmd != "view-compact") {
            return CompactView;
        }
    }

    int x;
    int y;
    if (std::regex_match(cmd, match, coord_regex)) {
        curr_view = CompactView;
        std::stringstream ss(cmd);
        ss >> x >> y;
        if (x == -1 && y == -1) {
            return Exit;
        }
        return move_curr_player(x, y);
    }
    if (std::regex_match(cmd, match, pretty_cmd_regex)) {
        curr_view = PrettyView;
        x = cmd[0] - 'a';
        y = cmd[1] - '0';
        return move_curr_player(x, y);
    }
    return game_step::Move;
}

player tictactoe::Game::get_curr_player(){
    return curr_player;
}

Field tictactoe::Game::get_field() const {
    return this->field;
}

void tictactoe::Game::change_curr_player() {
    curr_player = static_cast<player>((curr_player + 1) % 2);
}

game_step tictactoe::Game::get_view(){
    return curr_view;
}

tictactoe::game_step tictactoe::Game::move_curr_player(int x, int y){
    if (x < 0 || y < 0 || x >= size || y >= size || field[x][y] != Empty) {
        return BadMove;
    }
    field[x][y] = curr_player;
    moves_made++;
    return game_step::Move;
}

tictactoe::game_step tictactoe::Game::who_wins(){
    int cnt = 0;
    int step_x = prev_step_x;
    int step_y = prev_step_y;

    while (step_x - 1 > 0 && field[step_x - 1][step_y] == field[prev_step_x][prev_step_y]) {
        step_x--;
    }
    while (field[step_x][step_y] == field[prev_step_y][prev_step_y]) {
        cnt++;
        step_x++;
        if (cnt == 4) {
            return (field[step_x][step_y] == player::Cross ? XWin : OWin);
        }
    }
    return game_step::Move;
}
