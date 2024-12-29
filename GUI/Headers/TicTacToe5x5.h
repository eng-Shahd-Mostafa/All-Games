#ifndef TICTACTOE5X5_H
#define TICTACTOE5X5_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>

class TicTacToe5x5 : public QWidget
{
    Q_OBJECT

public:
    explicit TicTacToe5x5(QWidget *parent = nullptr);
    ~TicTacToe5x5();

private slots:
    void buttonClicked(int row, int col);
    void resetGame();
    void exitGame();

private:
    QPushButton* buttons[5][5];
    QLabel* statusLabel;
    QPushButton* resetButton;
    QPushButton* exitButton;

    char board[5][5];
    char currentPlayer;
    int xThreeCount;
    int oThreeCount;
    int movesCount;

    void updateButton(int row, int col);
    void checkWinner();
    int countThreeInARows(char player);
};

#endif // TICTACTOE5X5_H
