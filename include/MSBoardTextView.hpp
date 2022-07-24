#pragma once
#include "MinesweeperBoard.hpp"

class MSBoardTextView
{
    const MinesweeperBoard &board;

public:
    MSBoardTextView(const MinesweeperBoard &board);
    void display() const;
};