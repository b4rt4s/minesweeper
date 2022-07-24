#include "MinesweeperBoard.hpp"
#include "MSBoardTextView.hpp"
#include "MSTextController.hpp"
#include <iostream>

void gameWelcome()
{
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "|      Welcome to the Minesweeper!      |" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    std::cout << std::endl;

    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "|                  Menu                 |" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "| 1. Type a number 1 to start the game. |" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "| 2. Type a number 2 to end the game.   |" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    std::cout << std::endl;
}

void pause_and_clear()
{
    char stopper;

    std::cout << "\nPress any key to continue . . . ";

    std::cin >> stopper;

    system("clear");
}

void gameStart(char &start_or_end)
{
    system("clear");

    gameWelcome();

    while (true)
    {
        std::cin >> start_or_end;

        pause_and_clear();

        if (start_or_end == '1')
        {
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << "|                 Play                  |" << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
            
            pause_and_clear();

            break;
        }

        if (start_or_end == '2')
        {
            std::cout << "Please confirm your choose.\nType number 2 if you want to end the game.\nPressing another button will cause an error." << std::endl;

            std::cout << std::endl;

            std::cin >> start_or_end;

            pause_and_clear();

            if (start_or_end == '2')
            {
                std::cout << "-----------------------------------------" << std::endl;
                std::cout << "|                Goodbye!               |" << std::endl;
                std::cout << "-----------------------------------------" << std::endl;

                pause_and_clear();

                break;
            }
        }

        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "|                 Error!                |" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        std::cout << std::endl;

        std::cout << "Please press number 1 or 2!" << std::endl;

        pause_and_clear();

        gameWelcome();
    }
}

void chooseSizeOfBoard(int &width, int &height)
{
    std::cout << "Choose the size of the board!" << std::endl;

    std::cout << std::endl;

    std::cout << "Width: ";
    std::cin >> width;

    std::cout << "Height: ";
    std::cin >> height;

    std::cout << std::endl;
}

void chooseGameMode(int &number_of_mode, GameMode &mode)
{
    std::cout << "Choose the game mode!\n\nPress:" << std::endl;
    std::cout << "1 - EASY" << std::endl;
    std::cout << "2 - NORMAL" << std::endl;
    std::cout << "3 - HARD" << std::endl;

    std::cout << std::endl;

    std::cin >> number_of_mode;
    
    if (number_of_mode == 1)
    {
        mode = GameMode::EASY;
    }
    else if (number_of_mode == 2)
    {
        mode = GameMode::NORMAL;
    }
    else
    {
        mode = GameMode::HARD;
    }
}

int main()
{
    char start_or_end = '0';

    gameStart(start_or_end);

    if (start_or_end == '1')
    {
        int width, height;

        chooseSizeOfBoard(width, height);

        GameMode mode;

        int number_of_mode;

        chooseGameMode(number_of_mode, mode);

        pause_and_clear();

        MinesweeperBoard board{width, height, mode};

        MSBoardTextView view{board};
        
        MSTextController ctrl{board, view};

        ctrl.play();
    }

    return 0;
}
