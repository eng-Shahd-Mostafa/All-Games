#include "TicTacToe5x5.h"
#include <QMessageBox>
#include <QFont>
#include <QPushButton>

TicTacToe5x5::TicTacToe5x5(QWidget *parent)
    : QWidget(parent), currentPlayer('X'), xThreeCount(0), oThreeCount(0), movesCount(0)
{
    // Front
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // BackGround
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#87CEFA")); // Blue
    setPalette(palette);

    // Current Player
    statusLabel = new QLabel("Player X's Turn", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 30px; font-weight: bold; color: #000000;"); // Black
    mainLayout->addWidget(statusLabel);

    QGridLayout* layout = new QGridLayout();

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            buttons[i][j] = new QPushButton(" ");
            buttons[i][j]->setFixedSize(80, 80);
            buttons[i][j]->setStyleSheet("background-color: #F39C12; font-size: 36px; color: #FFFFFF; border: 2px solid #E67E22; border-radius: 10px;");
            layout->addWidget(buttons[i][j], i, j);
            board[i][j] = ' ';
            connect(buttons[i][j], &QPushButton::clicked, [this, i, j]() { buttonClicked(i, j); });
        }
    }

    mainLayout->addLayout(layout);

    // controlLayout (Reset و Exit)
    QHBoxLayout* controlLayout = new QHBoxLayout();

    resetButton = new QPushButton("🔄 Reset", this);
    resetButton->setStyleSheet("background-color: #32CD32; font-size: 22px; color: white; border-radius: 10px;");
    resetButton->setFixedSize(150, 60); // SizeButton
    connect(resetButton, &QPushButton::clicked, this, &TicTacToe5x5::resetGame);

    exitButton = new QPushButton("🚪Exit", this);
    exitButton->setStyleSheet("background-color: #DC143C; font-size: 22px; color: white; border-radius: 10px;");
    exitButton->setFixedSize(150, 60); // SizeButton
    connect(exitButton, &QPushButton::clicked, this, &TicTacToe5x5::exitGame);

    controlLayout->addWidget(resetButton);
    controlLayout->addWidget(exitButton);

    mainLayout->addLayout(controlLayout);

    setLayout(mainLayout);
}

TicTacToe5x5::~TicTacToe5x5() {}

void TicTacToe5x5::buttonClicked(int row, int col)
{
    if (board[row][col] == ' ') {
        updateButton(row, col);
        movesCount++;
        if (movesCount == 25) { // GameOver
            checkWinner();
        }
    }
}

void TicTacToe5x5::updateButton(int row, int col)
{
    board[row][col] = currentPlayer;
    buttons[row][col]->setText(QString(currentPlayer));
    buttons[row][col]->setStyleSheet("background-color: #2980B9; font-size: 36px; color: white; border: 2px solid #1F5D85; border-radius: 10px;");
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    statusLabel->setText(currentPlayer == 'X' ? "Player X's Turn" : "Player O's Turn");
}

void TicTacToe5x5::checkWinner()
{
    xThreeCount = countThreeInARows('X');
    oThreeCount = countThreeInARows('O');

    QString resultMessage = "Game Over!\n";
    resultMessage += "X scored " + QString::number(xThreeCount) + " three-in-a-rows.\n";
    resultMessage += "O scored " + QString::number(oThreeCount) + " three-in-a-rows.\n";

    if (xThreeCount > oThreeCount) {
        resultMessage += "X Wins!";
    } else if (oThreeCount > xThreeCount) {
        resultMessage += "O Wins!";
    } else {
        resultMessage += "It's a Draw!";
    }

    QMessageBox::information(this, "Game Over", resultMessage);
    resetGame();
}

int TicTacToe5x5::countThreeInARows(char player)
{
    int count = 0;

    // Check rows and columns
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player)
                count++;
            if (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == player)
                count++;
        }
    }

    // Check diagonals
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player)
                count++;
            if (board[i + 2][j] == player && board[i + 1][j + 1] == player && board[i][j + 2] == player)
                count++;
        }
    }

    return count;
}

void TicTacToe5x5::resetGame()
{
    currentPlayer = 'X';
    xThreeCount = 0;
    oThreeCount = 0;
    movesCount = 0;
    statusLabel->setText("Player X's Turn");

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            board[i][j] = ' ';
            buttons[i][j]->setText(" ");
            buttons[i][j]->setStyleSheet("background-color: #F39C12; font-size: 36px; color: #FFFFFF; border: 2px solid #E67E22; border-radius: 10px;");
        }
    }
}

void TicTacToe5x5::exitGame()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to exit?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        close();
    }}
