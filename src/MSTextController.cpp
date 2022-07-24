#include "MSTextController.hpp"
#include <iostream>
#include <string>

MSTextController::MSTextController(MinesweeperBoard &board, const MSBoardTextView &view)
    : board(board), 
      view(view)
{
}

void MSTextController::pause_and_clear_with_display() const
{
    char stopper;

    std::cout << "\nPress any key to continue . . . ";

    std::cin >> stopper;

    system("clear");

    view.display();
}

std::string whatGameMode(GameMode mode)
{
    if (mode == GameMode::EASY)
    {
        return "EASY";
    }
    else if (mode == GameMode::NORMAL)
    {
        return "NORMAL";
    }
    else
    {
        return "HARD";
    }
}

std::string whatGameState(GameState state)
{
    if (state == GameState::RUNNING)
    {
        return "RUNNING";
    }
    else if (state == GameState::FINISHED_LOSS)
    {
        return "FINISHED_LOSS";
    }
    else
    {
        return "FINISHED_WIN";
    }
}

void MSTextController::GameInformations() const
{
    std::cout << "- Game informations -" << std::endl;
    std::cout << "Game state: " << whatGameState(board.getGameState()) << std::endl;
    std::cout << "Game mode: " << whatGameMode(board.getGameMode()) << std::endl;
    std::cout << "The size of the board - 'height x width': " << board.getBoardWidth() << " x " << board.getBoardHeight() << std::endl;
    std::cout << "Number of mines: " << board.getMineCount() << std::endl;
}

void MSTextController::GameWinOrLoseInformtions(int movement, char quit) const
{
    if (board.getGameState() == GameState::FINISHED_WIN)
    {
        std::cout << "WIN!\nCongratulations on your victory!\n" << std::endl;
    }
    else
    {
        std::cout << "Lose :(\nNext time would be better!\n" << std::endl;
    }

    if (quit != 'q')
    {
        std::cout << "Game state: " << whatGameState(board.getGameState()) << std::endl;
        std::cout << "Number of movement: " << movement << std::endl; 
    }
}

void MSTextController::play() const
{   
    view.display();

    std::cout << std::endl;

    GameInformations();

    pause_and_clear_with_display();

    char quit = '0';

    int row, col, movement = 0, choice;

    while (board.getGameState() == GameState::RUNNING && quit != 'q')
    {
        ++movement;

        std::cout << "Enter a column number from 0 to " << board.getBoardWidth() - 1 << ": ";

        std::cin >> col;

        std::cout << "Enter a row number from 0 to " << board.getBoardHeight() - 1 << ": ";

        std::cin >> row;

        pause_and_clear_with_display();

        std::cout << "What you want to do?\n1 - toggle a flag,\n2 - reveal a field\nanything if no change" << std::endl;

        std::cout << std::endl;

        std::cin >> choice;

        switch(choice)
        {
            case 1: board.toggleFlag(row, col); break;
            case 2: board.revealField(row, col); break;
            default: break;
        }

        pause_and_clear_with_display();

        std::cout << "Press 'q' to quit the game or what ever to continue the game." << std::endl;
        
        std::cout << std::endl;

        std::cin >> quit;

        pause_and_clear_with_display();
    }

    GameWinOrLoseInformtions(movement, quit);

    pause_and_clear_with_display();
}