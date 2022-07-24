#include "MSBoardTextView.hpp"
#include <iostream>

MSBoardTextView::MSBoardTextView(const MinesweeperBoard &board)
    : board(board)
{
}

void MSBoardTextView::display() const
{
    for (int row = -2; row < board.getBoardHeight(); ++row)
    {
        for (int col = -2; col < board.getBoardWidth(); ++col)
        {
            if (row > -1 && col > -1)
            {
                std::cout << "[" << board.getFieldInfo(row, col) << "]";
            }
            
            if (row == -2)
            {
                if (col == -2)
                {
                    std::cout << "    ";
                }
                if (col > -1)
                {
                    std::cout << " " << col << " ";
                }
            }

            if (row > -1)
            {
                if (col == -2)
                {
                    std::cout << " " << row;
                }

                if (col == -1)
                {
                    std::cout << "  ";
                }
            }
        }
        
        std::cout << std::endl;
    }

    std::cout << std::endl;
}