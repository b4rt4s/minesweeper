#include "MinesweeperBoard.hpp"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

char display_sign(bool value, char sign)
{
    if (value)
    {
        return sign;
    }

    return '.';
}

std::string display_field(const Field &f)
{
    std::string result = "[";

    result += display_sign(f.hasMine, 'M');

    result += display_sign(f.isRevealed, 'o');

    result += display_sign(f.hasFlag, 'f');

    result += "]";

    return result;
}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode)
    : width(width),
      height(height),
      mine_count((static_cast<int>(mode) * width * height) / 100),
      mode(mode),
      board(width * height, Field{false, false, false}),
      state(GameState::RUNNING)
{
    if (mine_count > 0)
    {
        int random_row;
        int random_col;

        std::random_device seed;
        std::mt19937 rng(seed());
        std::uniform_int_distribution<> distrib_row(0, height - 1);
        std::uniform_int_distribution<> distrib_col(0, width - 1);

        for (int i = 0; i < mine_count; ++i)
        {
            random_row = distrib_row(rng);
            random_col = distrib_col(rng);

            if (cartesian_To_Index(random_row, random_col).hasMine == false)
            {
                cartesian_To_Index(random_row, random_col) = {1, 0, 0};
            }
            else
            {
                --i;
            }
        }
    }
    else if (mode == GameMode::DEBUG)
    {
        for (int row = 0; row < height; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                if (row == col || row == 0 || (col == 0 && row % 2 == 0))
                {
                    cartesian_To_Index(row, col) = {1, 0, 0};
                }
            }
        }
    }
}

Field &MinesweeperBoard::cartesian_To_Index(int row, int col)
{
    return board.at(row * width + col);
}

const Field &MinesweeperBoard::cartesian_To_Index(int row, int col) const
{
    return board.at(row * width + col);
}

void MinesweeperBoard::debug_display() const
{
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            std::cout << display_field(cartesian_To_Index(row, col));
        }

        std::cout << std::endl;
    }
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return height;
}

int MinesweeperBoard::getMineCount() const
{
    return mine_count;
}

GameMode MinesweeperBoard::getGameMode() const
{
    return mode;
}

bool MinesweeperBoard::isOffTheBoard(int row, int col) const
{
    return (row < 0 || row >= height) || (col < 0 || col >= width);
}

int MinesweeperBoard::countMines(int row, int col) const
{
    if (isOffTheBoard(row, col) || (cartesian_To_Index(row, col).isRevealed == false))
    {
        return -1;
    }
    else
    {
        int count_of_mines = 0;

        for (int i = row - 1; i <= row + 1; ++i)
        {
            for (int j = col - 1; j <= col + 1; ++j)
            {
                {
                    if ((i != row || j != col) 
                        && ((i >= 0 && i <= height - 1) && (j >= 0 && j <= width - 1))
                        && cartesian_To_Index(i, j).hasMine == true)
                    {
                        count_of_mines++;
                    }
                }
            }
        }

        return count_of_mines;
    }
}

bool MinesweeperBoard::hasFlag(int row, int col) const
{
    if (isOffTheBoard(row, col) || (cartesian_To_Index(row, col).isRevealed == true))
    {
        return false;
    }

    return cartesian_To_Index(row, col).hasFlag;
}

void MinesweeperBoard::toggleFlag(int row, int col)
{
    if (isOffTheBoard(row, col)
        || cartesian_To_Index(row, col).isRevealed
        || (state == GameState::FINISHED_WIN)
        || (state == GameState::FINISHED_LOSS))
    {
        return;
    }
    
    if (cartesian_To_Index(row, col).hasFlag == false)
    {
        cartesian_To_Index(row, col).hasFlag = true;
        return;
    }

    cartesian_To_Index(row, col).hasFlag = false;
}

void MinesweeperBoard::revealField(int row, int col)
{
    if (isOffTheBoard(row, col)
        || cartesian_To_Index(row, col).isRevealed 
        || cartesian_To_Index(row, col).hasFlag == true 
        || (state == GameState::FINISHED_WIN) 
        || (state == GameState::FINISHED_LOSS))
    {
        return;
    }

    cartesian_To_Index(row, col).isRevealed = true;

    if (cartesian_To_Index(row, col).hasMine == true)
    {
        state = GameState::FINISHED_LOSS;
        return;
    }

    if (width * height - mine_count == countRevealedFields())
    {
        state = GameState::FINISHED_WIN;
    }
}

bool MinesweeperBoard::isRevealed(int row, int col) const
{ 
    return !(isOffTheBoard(row, col)) && cartesian_To_Index(row, col).isRevealed;
}

int MinesweeperBoard::countRevealedFields()
{
    return std::count_if(board.begin(), board.end(), [](Field &f){return f.isRevealed == true;});
}

GameState MinesweeperBoard::getGameState() const
{
    return state;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if (isOffTheBoard(row, col))
    {
        return '#';
    }

    if (cartesian_To_Index(row, col).isRevealed == false)
    {
        if (cartesian_To_Index(row, col).hasFlag == true)
        {
            return 'F';
        }

        return '_';
    }

    if (cartesian_To_Index(row, col).hasMine == true)
    {
        return 'x';
    }
        
    if (countMines(row, col) == 0)
    {
        return ' ';
    }

    return '0' + countMines(row, col);
}
