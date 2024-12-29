#include "NumericalTicTacToe.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QPixmap>
#include <QPalette>
#include <QLabel>
#include <QInputDialog>
#include <QVector>

NumericalTicTacToe::NumericalTicTacToe(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Numerical Tic Tac Toe");
    setFixedSize(500, 600);  // Size Window
    playerTurn = true;  //  من هو اللاعب الذي يبدأ اللعبة
    playerNumber = 1;   //  اللاعب الأول بالأرقام الفردية
    createUI();
}

NumericalTicTacToe::~NumericalTicTacToe() {}

void NumericalTicTacToe::createUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Background
    QPixmap background(":/images/Yellow.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    // title
    QLabel *title = new QLabel("🐰Numerical Tic Tac Toe🐰", this);
    QFont titleFont("Comic Sans MS", 24, QFont::Bold);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #000000;");
    mainLayout->addWidget(title);

    // GridLayout
    QGridLayout *gridLayout = new QGridLayout;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton *btn = new QPushButton("", this);
            btn->setFixedSize(100, 100);
            btn->setStyleSheet("font-size: 24px; font-weight: bold; color: #000; background-color: #FF5733; border-radius: 8px;");
            connect(btn, &QPushButton::clicked, [=]() { makeMove(i, j); });
            grid[i][j] = btn;
            gridLayout->addWidget(btn, i, j);
        }
    }

    mainLayout->addLayout(gridLayout);

    // controlLayout
    QHBoxLayout *controlLayout = new QHBoxLayout;

    QPushButton *resetButton = new QPushButton("🔄 Reset", this);
    resetButton->setStyleSheet("background-color: #28A745; font-size: 22px; font-weight: bold; border-radius: 15px; padding: 15px 25px; color: white;");
    connect(resetButton, &QPushButton::clicked, this, &NumericalTicTacToe::resetGame);
    controlLayout->addWidget(resetButton);

    QPushButton *exitButton = new QPushButton("🚪Exit", this);
    exitButton->setStyleSheet("background-color: #C70039; font-size: 22px; font-weight: bold; border-radius: 15px; padding: 15px 25px; color: white;");
    connect(exitButton, &QPushButton::clicked, this, &NumericalTicTacToe::exitGame);
    controlLayout->addWidget(exitButton);

    mainLayout->addLayout(controlLayout);
    setLayout(mainLayout);
}

void NumericalTicTacToe::makeMove(int i, int j)
{
    if (grid[i][j]->text() != "") {
        return;
    }

    bool ok;
    int number;
    if (playerTurn) {
        number = QInputDialog::getInt(this, "Choose Number", "Enter an odd number (1, 3, 5, 7, 9):", 1, 1, 9, 2, &ok);
        if (!ok || number % 2 == 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter an odd number.");
            return;
        }
    } else {
        number = QInputDialog::getInt(this, "Choose Number", "Enter an even number (2, 4, 6, 8):", 2, 2, 8, 2, &ok);
        if (!ok || number % 2 != 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter an even number.");
            return;
        }
    }

    if (isNumberUsed(number)) {
        QMessageBox::warning(this, "Invalid Move", "This number has already been used. Please choose another.");
        return;
    }

    grid[i][j]->setText(QString::number(number));
    usedNumbers.append(number);

    if (checkWin()) {
        QMessageBox::information(this, "Game Over", "Player " + QString::number(playerNumber) + " wins!");
        resetGame();
        return;
    }

    playerTurn = !playerTurn;
    playerNumber = (playerNumber == 1) ? 2 : 1;
}

void NumericalTicTacToe::resetGame()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j]->setText("");
        }
    }
    playerTurn = true;
    playerNumber = 1;
    usedNumbers.clear();
}

void NumericalTicTacToe::exitGame()
{
    close();
}

bool NumericalTicTacToe::checkWin()
{
    // Check
    for (int i = 0; i < 3; ++i) {
        int sum = 0, filledCells = 0;
        for (int j = 0; j < 3; ++j) {
            if (!grid[i][j]->text().isEmpty()) {
                sum += grid[i][j]->text().toInt();
                filledCells++;
            }
        }
        if (sum == 15 && filledCells == 3) return true;
    }

    // Ckeck
    for (int i = 0; i < 3; ++i) {
        int sum = 0, filledCells = 0;
        for (int j = 0; j < 3; ++j) {
            if (!grid[j][i]->text().isEmpty()) {
                sum += grid[j][i]->text().toInt();
                filledCells++;
            }
        }
        if (sum == 15 && filledCells == 3) return true;
    }

    // Ckeck
    int sum1 = 0, filledCells1 = 0;
    int sum2 = 0, filledCells2 = 0;
    for (int i = 0; i < 3; ++i) {
        if (!grid[i][i]->text().isEmpty()) {
            sum1 += grid[i][i]->text().toInt();
            filledCells1++;
        }
        if (!grid[i][2 - i]->text().isEmpty()) {
            sum2 += grid[i][2 - i]->text().toInt();
            filledCells2++;
        }
    }
    if ((sum1 == 15 && filledCells1 == 3) || (sum2 == 15 && filledCells2 == 3)) return true;

    return false;
}

bool NumericalTicTacToe::isNumberUsed(int number)
{
    return usedNumbers.contains(number);
}
