#pragma once
#include "MinesweeperBoard.hpp"
#include "MSBoardTextView.hpp"

class MSTextController
{
    MinesweeperBoard &board;
    const MSBoardTextView &view;

public:
    MSTextController(MinesweeperBoard &board, const MSBoardTextView &view);
    
    void pause_and_clear_with_display() const;
    void GameInformations() const;
    void GameWinOrLoseInformtions(int movement, char quit) const;

    void play() const;
};