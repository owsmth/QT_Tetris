#include "gameboard.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

GameBoard::GameBoard(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 600);           // Adjust widget size

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameBoard::updateGame);
    timer->start(500);                // Set the game loop interval

    initializeBoard();
    startNewPiece();
}

void GameBoard::startNewPiece() {
    currentPiece = LineShape;  // Example: Start with a LineShape
    currentX = boardWidth / 2 - 1;  // Center horizontally
    currentY = 0;                  // Start at the top
}

void GameBoard::initializeBoard() {
    board.resize(boardHeight, QVector<int>(boardWidth, NoShape));
}

const int GameBoard::TetrominoShapes[8][4][4][4] = {
    // NoShape
    {{{0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}},

     {{0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}},

     {{0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}},

     {{0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},

    // ZShape
    {
     {{0, 0, 0, 0},
      {0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0}},

     {{1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}},

     {{0, 0, 0, 0},
      {0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0}},

     {{1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}}
    },

    //Lshape
    {
     {{0, 1, 0, 0},
      {0, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0}},

     {{0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}},

     {{0, 0, 0, 0},
      {0, 0, 0, 1},
      {0, 1, 1, 1},
      {0, 0, 0, 0}},

     {{0, 0, 0, 0},
      {0, 0, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 1, 0}}
    },
    //Lineshape
    {
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}},

        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}}
    }

    };

bool GameBoard::isCellOccupied(Tetromino piece, int rotation, int i, int j) {
    return TetrominoShapes[piece][rotation][i][j] == 1;
}


void GameBoard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Draw the static board
    for (int y = 0; y < boardHeight; ++y) {
        for (int x = 0; x < boardWidth; ++x) {
            if (board[y][x] != NoShape) {
                qDebug() << "currentX: " << currentX << ", currentY: " << currentY;
                drawSquare(painter, x, y, Qt::blue);  // Draw non-empty cells
            }
        }
    }

    // Draw the current piece
    for (int i = 0; i < PieceSize; ++i) {
        for (int j = 0; j < PieceSize; ++j) {
            // Check if the piece occupies the current (i, j) location
            if (i >= currentY && i < currentY + PieceSize &&
                j >= currentX && j < currentX + PieceSize &&
                TetrominoShapes[currentPiece][currentRotation][i - currentY][j - currentX] == 1) {
                drawSquare(painter, currentX + j, currentY + i, Qt::red);  // Draw the piece in red
            }
        }
    }
}


void GameBoard::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        // Move piece left
        if (isValidMove(currentPiece, currentRotation, currentX - 1, currentY)) {
            currentX--;
        }
    } else if (event->key() == Qt::Key_Right) {
        // Move piece right
        if (isValidMove(currentPiece, currentRotation, currentX + 1, currentY)) {
            currentX++;
        }
    } else if (event->key() == Qt::Key_Down) {
        // Move piece down
        if (isValidMove(currentPiece, currentRotation, currentX, currentY + 1)) {
            currentY++;
        }
    } else if (event->key() == Qt::Key_Up) {
        // Rotate piece
        int newRotation = (currentRotation + 1) % 4; // Rotates through 0, 1, 2, 3
        if (isValidMove(currentPiece, newRotation, currentX, currentY)) {
            currentRotation = newRotation;
        }
    }

    update();  // Repaint the widget to reflect the new piece position
}

void GameBoard::updateGame() {
    // Game logic (e.g., move current piece down)
    currentY++;
    // Check for collision and place piece on board
    update();  // Trigger a repaint
}

void GameBoard::placePiece() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i >= currentY && i < currentY + PieceSize &&
                j >= currentX && j < currentX + PieceSize &&
                TetrominoShapes[currentPiece][currentRotation][i - currentY][j - currentX] == 1) {
                board[currentY + j][currentX + i] = currentPiece;
            }
        }
    }

    startNewPiece();  // Start a new piece
}

bool GameBoard::isValidMove(Tetromino piece, int rotation, int newX, int newY) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i >= currentY && i < currentY + PieceSize &&
                j >= currentX && j < currentX + PieceSize &&
                TetrominoShapes[currentPiece][currentRotation][i - currentY][j - currentX] == 1) {
                int x = newX + i;
                int y = newY + j;

                if (x < 0 || x >= boardWidth || y < 0 || y >= boardHeight) {
                    return false;  // Out of bounds
                }

                if (board[y][x] != NoShape) {
                    return false;  // Collides with existing block
                }
            }
        }
    }
    return true;
}

void GameBoard::drawSquare(QPainter &painter, int x, int y, QColor color) {
    QRect rect(x * 30, y * 30, 30, 30);
    painter.fillRect(rect, color);
    painter.setPen(Qt::black);
    painter.drawRect(rect);
}
