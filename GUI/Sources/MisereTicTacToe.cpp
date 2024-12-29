#include "MisereTicTacToe.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>

MisereTicTacToe::MisereTicTacToe(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Misere Tic Tac Toe");
    setFixedSize(500, 600);  // Size window
    playerTurn = true; // start player X
    createUI();
}

MisereTicTacToe::~MisereTicTacToe()
{

}

void MisereTicTacToe::createUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Background window
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#FFEC8B"));  // لون خلفية (أصفر فاتح)
    setPalette(palette);

    // title
    QLabel *title = new QLabel("🦁 Misere Tic Tac Toe 🦁", this);
    QFont titleFont("Comic Sans MS", 24, QFont::Bold);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setHorizontalSpacing(10);  // المسافة بين الأزرار أفقيًا
    gridLayout->setVerticalSpacing(10);  // المسافة بين الأزرار عموديًا

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton *btn = new QPushButton("", this);
            btn->setFixedSize(100, 100);  // size button
            btn->setStyleSheet("font-size: 24px; font-weight: bold; color: #fff; background-color: #FF5733; border-radius: 12px;");
            connect(btn, &QPushButton::clicked, [=]() { makeMove(i, j); });
            grid[i][j] = btn;
            gridLayout->addWidget(btn, i, j);
        }
    }

    mainLayout->addLayout(gridLayout);

    // control Button
    QHBoxLayout *controlLayout = new QHBoxLayout;

    // reset
    QPushButton *resetButton = new QPushButton("🔄 Reset", this);
    resetButton->setStyleSheet("background-color: #28A745; font-size: 18px; font-weight: bold; border-radius: 12px; padding: 8px 20px; color: white;");
    connect(resetButton, &QPushButton::clicked, this, &MisereTicTacToe::resetGame);
    controlLayout->addWidget(resetButton);

    // exit
    QPushButton *exitButton = new QPushButton("🚪Exit", this);
    exitButton->setStyleSheet("background-color: #C70039; font-size: 18px; font-weight: bold; border-radius: 12px; padding: 8px 20px; color: white;");
    connect(exitButton, &QPushButton::clicked, this, &MisereTicTacToe::exitGame);
    controlLayout->addWidget(exitButton);

    mainLayout->addLayout(controlLayout);
    setLayout(mainLayout);
}

void MisereTicTacToe::makeMove(int i, int j)
{
    if (grid[i][j]->text() != "") {
        return; // الخانة مشغولة
    }

    QString symbol = playerTurn ? "X" : "O";
    grid[i][j]->setText(symbol);

    if (checkLoss()) {
        QString loser = playerTurn ? "X" : "O";
        QMessageBox::information(this, "Game Over", "Player " + loser + " loses!");
        resetGame();
    }
    else if (checkDraw()) {
        QMessageBox::information(this, "Game Over", "It's a draw!");
        resetGame();
    }
    else {
        playerTurn = !playerTurn;  // التبديل بين اللاعبين
    }
}

void MisereTicTacToe::resetGame()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j]->setText("");
        }
    }
    playerTurn = true;
}

void MisereTicTacToe::exitGame()
{
    close();
}

bool MisereTicTacToe::checkLoss()
{
    // Check
    for (int i = 0; i < 3; ++i) {
        // تحقق من الصفوف
        if (grid[i][0]->text() == grid[i][1]->text() && grid[i][1]->text() == grid[i][2]->text() && grid[i][0]->text() != "") {
            return true;
        }
        // تحقق من الأعمدة
        if (grid[0][i]->text() == grid[1][i]->text() && grid[1][i]->text() == grid[2][i]->text() && grid[0][i]->text() != "") {
            return true;
        }
    }

    // تحقق من الأقطار
    if (grid[0][0]->text() == grid[1][1]->text() && grid[1][1]->text() == grid[2][2]->text() && grid[0][0]->text() != "") {
        return true;
    }
    if (grid[0][2]->text() == grid[1][1]->text() && grid[1][1]->text() == grid[2][0]->text() && grid[0][2]->text() != "") {
        return true;
    }

    return false;
}

bool MisereTicTacToe::checkDraw()
{
    // تحقق من التعادل (إذا كانت كل الخلايا ممتلئة ولم يوجد فائز)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i][j]->text() == "") {
                return false;
            }
        }
    }
    return true;
}
