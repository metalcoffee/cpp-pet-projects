#pragma once
#include "../include/game.h"
#include <iostream>

namespace tictactoe {

class View {
public:
    virtual ~View() = default;
    virtual void print_view(Game& game) = 0;
};

class ViewCompact : public View
{
    void print_view(Game& game) override;
};

class ViewPretty : public View {
    void print_view(Game& game) override;
};
}