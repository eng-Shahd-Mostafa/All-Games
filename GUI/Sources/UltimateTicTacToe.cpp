#include "UltimateTicTacToe.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QApplication>

UltimateTicTacToe::UltimateTicTacToe(QWidget *parent)
    : QWidget(parent), currentPlayer('X'), gameWon(false)
{
    setWindowTitle("🎮 Ultimate Tic Tac Toe 🎮");
    setFixedSize(700, 700);

    mainGrid = new QGridLayout(this);
    mainGrid->setSpacing(10);

    setStyleSheet("background-color: #FFE4B5;");

    statusLabel = new QLabel("🎲 Player X's Turn 🎲", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 20px; color: #2E8B57; font-weight: bold; font-family: Comic Sans MS;");
    mainGrid->addWidget(statusLabel, 0, 0, 1, 3);

    for (int i = 0; i < 9; ++i) {
        QGridLayout *smallBoardLayout = new QGridLayout;
        smallBoardLayout->setSpacing(3);

        QVector<QPushButton*> smallBoard;
        for (int j = 0; j < 9; ++j) {
            QPushButton *cell = new QPushButton;
            cell->setFixedSize(60, 60);
            cell->setStyleSheet(
                "font-size: 20px; font-weight: bold;"
                "color: #8B4513;"
                "background-color: #FFDAB9;"
                "border: 2px solid #CD853F;"
                "border-radius: 10px;"
                );
            smallBoard.push_back(cell);
            connect(cell, &QPushButton::clicked, [=]() { handleCellClick(i, j); });
            smallBoardLayout->addWidget(cell, j / 3, j % 3);
        }

        boards.push_back(smallBoard);
        boardWinners.push_back(0);

        QWidget *smallBoardWidget = new QWidget;
        smallBoardWidget->setLayout(smallBoardLayout);
        smallBoardWidget->setStyleSheet("border: 3px dashed #8B0000; border-radius: 15px;");
        smallBoards.push_back(smallBoardWidget);
        mainGrid->addWidget(smallBoardWidget, (i / 3) + 1, i % 3);
    }

    resetButton = new QPushButton("🔄 Reset", this);
    resetButton->setStyleSheet("background-color: #32CD32; color: white; font-size: 16px; font-weight: bold; border-radius: 10px; padding: 5px;");
    connect(resetButton, &QPushButton::clicked, this, &UltimateTicTacToe::resetGame);

    exitButton = new QPushButton("🚪 Exit", this);
    exitButton->setStyleSheet("background-color: #FF4500; color: white; font-size: 16px; font-weight: bold; border-radius: 10px; padding: 5px;");
    connect(exitButton, &QPushButton::clicked, this, &UltimateTicTacToe::closeGame);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(exitButton);

    mainGrid->addLayout(buttonLayout, 4, 0, 1, 3);
}

void UltimateTicTacToe::handleCellClick(int boardIndex, int cellIndex)
{
    if (gameWon || boardWinners[boardIndex] != 0)
        return;

    QPushButton *cell = boards[boardIndex][cellIndex];
    if (!cell->text().isEmpty())
        return;

    cell->setText(QString(currentPlayer));
    cell->setStyleSheet(currentPlayer == 'X'
                            ? "color: red; font-size: 20px; font-weight: bold;"
                            : "color: blue; font-size: 20px; font-weight: bold;"
                        );

    checkSmallBoard(boardIndex);

    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    statusLabel->setText(QString("Player %1's Turn").arg(currentPlayer));
    statusLabel->setStyleSheet(
        currentPlayer == 'X'
            ? "font-size: 20px; color: red; font-weight: bold;"
            : "font-size: 20px; color: blue; font-weight: bold;"
        );

    checkMainBoard();
}

void UltimateTicTacToe::checkSmallBoard(int boardIndex)
{
    QVector<QPushButton*> &board = boards[boardIndex];

    QVector<QVector<int>> winPatterns = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto &pattern : winPatterns) {
        if (!board[pattern[0]]->text().isEmpty() &&
            board[pattern[0]]->text() == board[pattern[1]]->text() &&
            board[pattern[1]]->text() == board[pattern[2]]->text()) {
            boardWinners[boardIndex] = currentPlayer;
            replaceSmallBoardWithWinner(boardIndex);
            return;
        }
    }
}

void UltimateTicTacToe::replaceSmallBoardWithWinner(int boardIndex)
{
    QLabel *winnerLabel = new QLabel(QString("%1").arg(currentPlayer), this);
    winnerLabel->setAlignment(Qt::AlignCenter);
    winnerLabel->setStyleSheet(currentPlayer == 'X'
                                   ? "font-size: 180px; font-weight: bold; color: red; background-color: transparent;"
                                   : "font-size: 180px; font-weight: bold; color: blue; background-color: transparent;");

    mainGrid->addWidget(winnerLabel, (boardIndex / 3) + 1, boardIndex % 3);
}

void UltimateTicTacToe::checkMainBoard()
{
    QVector<QVector<int>> winPatterns = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    char winner = 0;

    // Check if there's a winner in the main board
    for (const auto &pattern : winPatterns) {
        if (boardWinners[pattern[0]] != 0 &&
            boardWinners[pattern[0]] == boardWinners[pattern[1]] &&
            boardWinners[pattern[1]] == boardWinners[pattern[2]]) {
            winner = boardWinners[pattern[0]];
            break;
        }
    }

    if (winner != 0) {
        gameWon = true;
        QMessageBox::information(this, "Game Over", QString("🎉 Player %1 Wins! 🎉").arg(winner));
        resetGame();
        return;
    }

    bool isFull = true;
    // Check if the main board is full (i.e., all small boards have a winner or are filled)
    for (int i = 0; i < 9; ++i) {
        if (boardWinners[i] == 0) {
            isFull = false;
            break;
        }
    }

    // If full and no winner, it's a draw
    if (isFull) {
        QMessageBox::information(this, "Game Over", "😢 It's a Draw! 😢");
        resetGame();
    }
}

void UltimateTicTacToe::resetGame()
{
    for (int i = 0; i < 9; ++i) {
        boardWinners[i] = 0;
        if (smallBoards[i]) {
            delete smallBoards[i];
        }

        QGridLayout *smallBoardLayout = new QGridLayout;
        smallBoardLayout->setSpacing(3);

        QVector<QPushButton*> smallBoard;
        for (int j = 0; j < 9; ++j) {
            QPushButton *cell = new QPushButton;
            cell->setFixedSize(60, 60);
            cell->setStyleSheet(
                "font-size: 20px; font-weight: bold; color: #8B4513; background-color: #FFDAB9; border: 2px solid #CD853F; border-radius: 10px;"
                );
            smallBoard.push_back(cell);
            connect(cell, &QPushButton::clicked, [=]() { handleCellClick(i, j); });
            smallBoardLayout->addWidget(cell, j / 3, j % 3);
        }

        boards[i] = smallBoard;

        QWidget *smallBoardWidget = new QWidget;
        smallBoardWidget->setLayout(smallBoardLayout);
        smallBoardWidget->setStyleSheet("border: 3px dashed #8B0000; border-radius: 15px;");
        smallBoards[i] = smallBoardWidget;
        mainGrid->addWidget(smallBoardWidget, (i / 3) + 1, i % 3);
    }

    currentPlayer = 'X';
    gameWon = false;
    statusLabel->setText("🎲 Player X's Turn 🎲");
    statusLabel->setStyleSheet("font-size: 20px; color: red; font-weight: bold;");
}

void UltimateTicTacToe::closeGame()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to exit?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        close();
    }
}
