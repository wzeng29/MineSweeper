#ifndef MAIN_GAME_WINDOW_H
#define MAIN_GAME_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include "game_model.h" 
namespace Ui {
class MainGameWindow;
}

class GameModel;

class MainGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainGameWindow(QWidget *parent = 0);
    ~MainGameWindow();
protected:
    virtual void paintEvent(QPaintEvent *event) override;   
    virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::MainGameWindow *ui;
    GameModel *game;
    void handleGameState(GameModel *game);
private slots:
    void onStartGameClicked();
    void onQuitClicked();  
    void onQuitGameClicked();
    void onRestartGameClicked();
};

#endif // MAIN_GAME_WINDOW_H
