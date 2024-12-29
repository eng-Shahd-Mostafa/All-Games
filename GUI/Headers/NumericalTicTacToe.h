#ifndef NUMERICALTICTACTOE_H
#define NUMERICALTICTACTOE_H

#include <QWidget>
#include <QPushButton>

class NumericalTicTacToe : public QWidget
{
    Q_OBJECT

public:
    explicit NumericalTicTacToe(QWidget *parent = nullptr);
    ~NumericalTicTacToe();

private slots:
    void makeMove(int i, int j);
    void resetGame();
    void exitGame();

private:
    void createUI();
    bool checkWin();
    bool isNumberUsed(int number);

    QPushButton* grid[3][3];  // مصفوفة الأزرار
    bool playerTurn;           // متغير يتحكم في من هو اللاعب الذي دوره
    int playerNumber;          // المتغير الذي يعبر عن الرقم الذي يختاره كل لاعب
    QVector<int> usedNumbers;  // مصفوفة الأرقام المستخدمة
};

#endif // NUMERICALTICTACTOE_H
