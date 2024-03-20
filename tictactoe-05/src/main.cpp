#include <boost/dll/import.hpp>
// #include <boost/version.hpp>
#include <iostream>
#include <map>
#include <string>
#include "../include/game.h"
#include "../include/view.h"

using namespace tictactoe;

#if BOOST_VERSION >= 107600
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import
#endif

int main() {
    bool game_on = true;
    Game game;
    View *view = nullptr;

    std::unordered_map<game_step, View *> views{{CompactView, new ViewCompact()},
                                      {PrettyView, new ViewPretty()}};

    while (game_on) {
        std::string command;
        std::getline(std::cin, command);
        game_step state = game.parsing(command);
        view = views[game.get_view()];

        switch (state) {
            case BadMove:
                std::cout << "Bad move!" << '\n';
                break;
            case Exit:
                game_on = false;
                break;
            case CompactView:
                view = views[CompactView];
                break;
            case PrettyView:
                view = views[PrettyView];
                break;
            case Draw:
                std::cout << "Draw." << '\n';
                break;
            case OWin:
                std::cout << "O wins!" << '\n';
                break;
            case XWin:
                std::cout << "X wins!" << '\n';
                break;
            case Move:
                view->print_view(game);
                game.change_curr_player();
                std::cout << (game.get_curr_player() == player::Zero
                                  ? "O move:"
                                  : "X move:");
                break;
        }
    }

    return 0;
}
