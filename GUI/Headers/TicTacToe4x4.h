#ifndef TICTACTOE4X4_H
#define TICTACTOE4X4_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class TicTacToe4x4 : public QWidget
{
    Q_OBJECT

public:
    explicit TicTacToe4x4(QWidget *parent = nullptr);
    ~TicTacToe4x4();

private slots:
    void buttonClicked(int row, int col);
    void resetBoard();

private:
    void createBoard();
    void checkWinner();
    void showWinner(const QString &winner);

    QString board[4][4];               // مصفوفة تمثل اللوحة
    QPushButton *buttons[4][4];       // أزرار اللعبة
    QLabel *statusLabel;              // حالة اللاعب الحالي
    QString currentPlayer;            // اللاعب الحالي
    QString currentSymbol;            // الرمز الحالي (X أو O)
    QString selectedPiece;            // القطعة المحددة للنقل
    int selectedRow, selectedCol;     // موقع القطعة المحددة
};

#endif // TICTACTOE4X4_H
