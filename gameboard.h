#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QVector>

enum Tetromino { NoShape, ZShape, SShape, LineShape, TShape, SquareShape, LShape, MirroredLShape };

class GameBoard : public QWidget {
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

private:
    QTimer *timer;                    // Timer for game loop
    QVector<QVector<int>> board;      // 2D array to store the game board state
    int boardWidth = 10;              // Board dimensions
    int boardHeight = 20;
    Tetromino currentPiece;
    int currentX, currentY; // Top left position of falling piece
    int currentRotation; // (0 to 3)

    const int PieceSize = 4; // Each Tetromino is a 4x4 grid
    static const int TetrominoShapes[8][4][4][4];  // Shape definitions

    void drawSquare(QPainter &painter, int x, int y, QColor color);
    void initializeBoard();
    void startNewPiece(); //intiializes a new piece
    void placePiece(); //places piece on board
    bool isCellOccupied(Tetromino piece, int rotation, int i, int j); //checks if a cell is occupied
    bool isValidMove(Tetromino piece, int rotation, int newX, int newY); // checks if a move is valid




};

#endif // GAMEBOARD_H
