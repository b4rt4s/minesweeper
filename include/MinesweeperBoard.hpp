#pragma once
#include <vector>

enum class GameMode
{
  DEBUG = 0,
  EASY = 10,
  NORMAL = 20,
  HARD = 30
};

enum class GameState
{
  RUNNING,
  FINISHED_WIN,
  FINISHED_LOSS
};

struct Field
{
  bool hasMine;
  bool isRevealed;
  bool hasFlag;
};

class MinesweeperBoard
{
public:
  MinesweeperBoard(int width, int height, GameMode mode);
  
  void debug_display() const;

  int getBoardWidth() const;
  int getBoardHeight() const;
  int getMineCount() const;
  GameMode getGameMode() const;

  int countMines(int row, int col) const; 
  bool hasFlag(int row, int col) const;
  void toggleFlag(int row, int col);
  void revealField(int row, int col);
  bool isRevealed(int row, int col) const;
  GameState getGameState() const;
  char getFieldInfo(int row, int col) const;

private:
  int width;
  int height;
  int mine_count;
  GameMode mode;
  std::vector<Field> board;
  GameState state;

  Field &cartesian_To_Index(int row, int col);
  const Field &cartesian_To_Index(int row, int col) const;
  
  bool isOffTheBoard(int row, int col) const;

  int countRevealedFields();
};