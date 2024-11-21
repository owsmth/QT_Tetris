#include "mainwindow.h"
#include "gameboard.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    gameBoard = new GameBoard(this);  // Create the GameBoard widget

    setCentralWidget(gameBoard);      // Set GameBoard as the central widget

    setWindowTitle("Tetris");
    resize(300, 600);                 // Adjust size to match GameBoard
}

MainWindow::~MainWindow() {
    // Qt automatically deletes child widgets
}
