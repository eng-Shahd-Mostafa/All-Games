#ifndef ULTIMETICTACTOE_H
#define ULTIMETICTACTOE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVector>

class UltimateTicTacToe : public QWidget
{
    Q_OBJECT

public:
    explicit UltimateTicTacToe(QWidget *parent = nullptr);

private slots:
    void handleCellClick(int boardIndex, int cellIndex);
    void resetGame();
    void closeGame();

private:
    void checkSmallBoard(int boardIndex);
    void replaceSmallBoardWithWinner(int boardIndex);
    void checkMainBoard();

    QVector<QVector<QPushButton*>> boards;
    QVector<QWidget*> smallBoards;
    QVector<int> boardWinners;  // 0: no winner, 1: X, 2: O

    QPushButton *resetButton;
    QPushButton *exitButton;
    QLabel *statusLabel;

    QGridLayout *mainGrid;
    char currentPlayer;
    bool gameWon;
};

#endif // ULTIMETICTACTOE_H
