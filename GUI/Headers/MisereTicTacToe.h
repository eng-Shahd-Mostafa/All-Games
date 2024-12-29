#ifndef MISERETICTACTOE_H
#define MISERETICTACTOE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

class MisereTicTacToe : public QWidget
{
    Q_OBJECT

public:
    explicit MisereTicTacToe(QWidget *parent = nullptr);
    ~MisereTicTacToe();
    void createUI();

private slots:
    void makeMove(int i, int j);
    void resetGame();
    void exitGame();

private:
    QPushButton* grid[3][3];
    bool playerTurn; // true for "X", false for "O"
    bool checkLoss(); // دالة للتحقق من الخسارة
    bool checkDraw(); // دالة للتحقق من التعادل
};

#endif // MISERETICTACTOE_H
