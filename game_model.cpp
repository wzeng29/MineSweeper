#include <time.h>
#include <stdlib.h>
#include "game_model.h"
#include <queue>
#include <algorithm>
#include <vector>
#include <random>
GameModel::GameModel()
    : mRow(kRow),
      mCol(kCol),
      totalMineNumber(mines),
      gameState(ON)
{//***Empty***//
}

GameModel::~GameModel()
{

}

void GameModel::createGame(int row, int col, int mineCount){
    // Clear and initialize the game map with default MineBlock values
    gameMap = std::vector<std::vector<MineBlock>>(row, std::vector<MineBlock>(col, MineBlock()));

    // Update class members
    mRow = row;
    mCol = col;
    totalMineNumber = mineCount;
    gameState = ON;

    // Create a flat list of all coordinates for easy random access
    std::vector<std::pair<int, int>> allCoordinates;
    for (int i = 0; i < mRow; ++i) {
        for (int j = 0; j < mCol; ++j) {
            allCoordinates.emplace_back(i, j);
        }
    }

    // Randomly shuffle coordinates and place mines on the first mineCount elements
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allCoordinates.begin(), allCoordinates.end(), g);

    for (int k = 0; k < mineCount; ++k) {
        auto [i, j] = allCoordinates[k];
        gameMap[i][j].valueFlag = -1; // Place mine
    }

    // Calculate numbers for each cell based on neighboring mines
    for (int i = 0; i < mRow; ++i) {
        for (int j = 0; j < mCol; ++j) {
            if (gameMap[i][j].valueFlag == -1) continue; // Skip mine cells

            // Check all eight neighbors
            for (int y = -1; y <= 1; ++y) {
                for (int x = -1; x <= 1; ++x) {
                    int ni = i + y;
                    int nj = j + x;
                    // Skip out-of-bounds and self
                    if (ni >= 0 && ni < mRow && nj >= 0 && nj < mCol && !(y == 0 && x == 0)) {
                        // Increment count if neighbor is a mine
                        gameMap[i][j].valueFlag += gameMap[ni][nj].valueFlag == -1 ? 1 : 0;
                    }
                }
            }
        }
    }
}


void GameModel::markMine(int m, int n) {
    // Directly toggle between UN_DIGGED and FLAGGED states if the cell is not already dug
    if (gameMap[m][n].curState == UN_DIGGED || gameMap[m][n].curState == FLAGGED) {
        gameMap[m][n].curState = gameMap[m][n].curState == UN_DIGGED ? FLAGGED : UN_DIGGED;
    }

    // Optionally, after marking or unmarking a mine, you might want to check if the player has won
    checkGame();
}



void GameModel::digMine(int m, int n) {
    // Check for initial conditions to avoid unnecessary processing
    if(gameMap[m][n].valueFlag == -1 || gameMap[m][n].curState != UN_DIGGED) {
        if (gameMap[m][n].valueFlag == -1) {
            gameState = LOSE;
            gameMap[m][n].curState = BOMB;
            checkGame();
        }
        return;
    }

    std::queue<std::pair<int, int>> cellsToReveal;
    cellsToReveal.push({m, n});

    while (!cellsToReveal.empty()) {
        auto [row, col] = cellsToReveal.front();
        cellsToReveal.pop();

        // Skip if out of bounds or already processed
        if (row < 0 || row >= mRow || col < 0 || col >= mCol || gameMap[row][col].curState == DIGGED) {
            continue;
        }

        // Reveal the cell
        gameMap[row][col].curState = DIGGED;

        // If the cell has no adjacent mines, add its neighbors to the queue
        if (gameMap[row][col].valueFlag == 0) {
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (!(x == 0 && y == 0)) { // Skip the cell itself
                        int newRow = row + y, newCol = col + x;
                        // Add neighbor if within bounds and not already revealed
                        if (newRow >= 0 && newRow < mRow && newCol >= 0 && newCol < mCol && gameMap[newRow][newCol].curState == UN_DIGGED) {
                            cellsToReveal.push({newRow, newCol});
                        }
                    }
                }
            }
        }
    }

    // Check game state after processing
    checkGame();
}
// Check game states
void GameModel::checkGame() {
    // First, check if the game has already been lost
    if (gameState == LOSE) {
        // Reveal all mines
        for (int i = 0; i < mRow; ++i) {
            for (int j = 0; j < mCol; ++j) {
                if (gameMap[i][j].valueFlag == -1) { // Mine found
                    gameMap[i][j].curState = BOMB;
                }
            }
        }
    } else {
        // Assume the game is won until proven otherwise
        bool isWin = true;

        for (int i = 0; i < mRow; ++i) {
            for (int j = 0; j < mCol; ++j) {
                // If there's an undug cell that's not a mine, game is still on
                if (gameMap[i][j].curState == UN_DIGGED && gameMap[i][j].valueFlag != -1) {
                    isWin = false;
                    break; // Exit the loop early as we've found the game cannot yet be won
                }
            }
            if (!isWin) break; // Exit the outer loop early for efficiency
        }

        // If all non-mine cells are dug, the player wins
        if (isWin) {
            gameState = WIN;
        } else {
           gameState = gameState == LOSE ? LOSE : ON;
        }
    }
}


void GameModel::restartGame()
{
    createGame(mRow, mCol, totalMineNumber);
}