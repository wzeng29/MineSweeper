#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>

#include "main_game_window.h"
#include "ui_maingamewindow.h"
#include "game_model.h"

// ---------Vars------------ //
const int blockSize = 20;
const int offsetX = 10; 
const int offsetY = 10; 
const int spaceY = 10; 


MainGameWindow::MainGameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);
    game = new GameModel;
    game->createGame();
    setFixedSize(game->mCol * blockSize + offsetX * 2, game->mRow * blockSize + offsetY * 2 + spaceY);
    

}


MainGameWindow::~MainGameWindow()
{

    delete game;
    game = NULL;
    delete ui;
}

void MainGameWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bmpBlocks(":/res/blocks.bmp");
    QPixmap newFlag(":/res/mine_flag.png");
    QPixmap newBomb(":/res/bomb.png");
    QPixmap newB(":/res/bomb_explode.png");
    for(int i = 0; i < game->mRow; i++)
    {
        for(int j = 0; j < game->mCol; j++)
        {
            switch(game->gameMap[i][j].curState)
            {
            case UN_DIGGED:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY , bmpBlocks, blockSize * 10, 0, blockSize, blockSize);
                break;
            case DIGGED:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * game->gameMap[i][j].valueFlag, 0, blockSize, blockSize);
                break;
            case FLAGGED:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 11, 0, blockSize, blockSize);
                break;
            case BOMB:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 9, 0, blockSize, blockSize);
                break;
            default:
                if(game->gameState == ON || game->gameState == FAULT)
                {
                    // Show flags
                    painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 11, 0, blockSize, blockSize);
                }
                break;
            }
        }
    }

    handleGameState(game);
}

void MainGameWindow::handleGameState(GameModel *game)
{
    // Check game state only for win or lose conditions
    if(game->gameState == LOSE || game->gameState == WIN)
    {
        // Log game outcome
        qDebug() << (game->gameState == LOSE ? "DEFEATED" : "VICTORY");
        game->restartGame();
        // Remove any existing buttons
        qDeleteAll(this->findChildren<QPushButton*>());

        // Create Restart Button
        QPushButton *restartButton = new QPushButton("Restart", this);
        restartButton->setGeometry(QRect(QPoint(100, game->mRow * blockSize + offsetY + 20), QSize(100, 30))); // Adjust position and size as needed
        connect(restartButton, &QPushButton::clicked, this, &MainGameWindow::onRestartGameClicked);

        // Create Quit Button
        QPushButton *quitButton = new QPushButton("Quit", this);
        quitButton->setGeometry(QRect(QPoint(210, game->mRow * blockSize + offsetY + 20), QSize(100, 30))); // Adjust position and size as needed
        connect(quitButton, &QPushButton::clicked, this, &MainGameWindow::onQuitGameClicked);

        // Show buttons
        restartButton->show();
        quitButton->show();
    }
}


void MainGameWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    // Check if the click is within the interactive game area
    if(y >= spaceY + offsetY)
    {
        if(game->gameState == LOSE || game->gameState == WIN)
            return; // Do not handle clicks if the game is over or won

        // Calculate which block was clicked
        int col = (x - offsetX) / blockSize;
        int row = (y - offsetY - spaceY) / blockSize;

        // Check if the click is within the bounds of the minefield
        if(col >= 0 && col < game->mCol && row >= 0 && row < game->mRow)
        {
            // Process the click according to the mouse button used
            if(event->button() == Qt::LeftButton)
            {
                game->digMine(row, col);
            }
            else if(event->button() == Qt::RightButton)
            {
                game->markMine(row, col);
            }
            update(); // Refresh the display to show changes
        }
    }
    else // Click is within the top UI area
    {
        // Check for click on the restart area (smiley face)
        int centerX = (game->mCol * blockSize + offsetX * 2) / 2;
        if(x >= centerX - 12 && x <= centerX + 12 && y >= spaceY / 2 && y <= spaceY / 2 + 24)
        {
            game->restartGame(); // Restart the game
            update(); // Refresh the display immediately
        }
    }
}

void MainGameWindow::onStartGameClicked()
{
    qDebug()<<"START";
    game->restartGame(); 
    update();
}
void MainGameWindow::onRestartGameClicked()
{   
    game->restartGame(); // Restart the game logic
    update(); // Redraw the window
    // Optionally, remove the buttons or disable them until needed again
}
void MainGameWindow::onQuitGameClicked()
{
    QCoreApplication::quit(); // Quit the application
}

void MainGameWindow::onQuitClicked()
{
    QCoreApplication::quit();
}
