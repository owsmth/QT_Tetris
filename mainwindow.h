#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GameBoard;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GameBoard *gameBoard;  // The main game board widget
};

#endif // MAINWINDOW_H
