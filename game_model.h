#ifndef GAMEMODEL_H
#define GAMEMODEL_H


#include <vector>

enum BlockState
{
    UN_DIGGED,
    DIGGED,
    FLAGGED,
    BOMB
};

struct MineBlock
{
    BlockState curState; 
    int valueFlag; // int，0-8， -1 = Mine
    // Adding a constructor that accepts BlockState and int

};


enum GameState
{
    ON,
    FAULT,
    LOSE,
    WIN
};

const int kRow = 16;
const int kCol = 30;
const int mines = 99;

class GameModel
{
public:
    GameModel();
    virtual ~GameModel();
public:
    void digMine(int m, int n); 
    void markMine(int m, int n); 
    void createGame(int row = kRow, int col = kCol, int mineCount = mines); 
    void restartGame();
    void checkGame();
public:
    std::vector<std::vector<MineBlock>> gameMap;
    int mRow; 
    int mCol; 
    int totalMineNumber; 
  

    GameState gameState; 
};

#endif 
