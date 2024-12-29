#include "ConnectFour.h"
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QApplication>

ConnectFour::ConnectFour(QWidget *parent) : QDialog(parent), playerRedTurn(true), gameEnded(false) {
    mainLayout = new QVBoxLayout(this);
    gridLayout = new QGridLayout();

    board.resize(6, std::vector<int>(7, 0)); // Creator

    // BackGround (Board)
    setStyleSheet("background-color: #1569C7;");

    // Creat Button
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            buttons[row][col] = new QPushButton(this);
            buttons[row][col]->setFixedSize(80, 80); // Size
            buttons[row][col]->setStyleSheet(
                "background-color: #E0FFFF	;" // خلفية للمكان الفارغ
                "border: 2px solid #4682B4;" // Border
                "border-radius: 40px;" // Convert
                "font-size: 18px;" // Size
                );
            gridLayout->addWidget(buttons[row][col], row, col);
            connect(buttons[row][col], &QPushButton::clicked, this, [this, row, col]() { makeMove(col); });
        }
    }

    // Reset
    resetButton = new QPushButton("Restart Game", this);
    resetButton->setStyleSheet(
        "background-color: #32CD32;" // أخضر لامع
        "color: white;" // لون النص أبيض
        "border-radius: 15px;" // Border
        "font-size: 20px;" // Size
        "padding: 15px;" // Space
        );
    connect(resetButton, &QPushButton::clicked, this, &ConnectFour::resetGame);

    // Exit
    exitButton = new QPushButton("🚪Exit", this);
    exitButton->setStyleSheet(
        "background-color: #FF6347;" // أحمر فاتح
        "color: white;" // لون النص أبيض
        "border-radius: 15px;" // Border
        "font-size: 20px;" // Size
        "padding: 15px;" // Space
        );
    connect(exitButton, &QPushButton::clicked, this, &ConnectFour::close);

    // الأزرار بجانب بعض
    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->addWidget(resetButton);
    controlLayout->addWidget(exitButton);

    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(controlLayout);

    setWindowTitle("Connect Four");
    setFixedSize(700, 600); // Size Wundow
}

ConnectFour::~ConnectFour() {}

void ConnectFour::makeMove(int col) {
    if (gameEnded) return;

    for (int row = 5; row >= 0; --row) {
        if (board[row][col] == 0) {
            board[row][col] = playerRedTurn ? 1 : 2;
            buttons[row][col]->setStyleSheet(playerRedTurn
                                                 ? "background-color: #FF0000; border: 2px solid #C11B17; border-radius: 40px;" // أحمر للاعب الأول
                                                 : "background-color: #FFFF00; border: 2px solid #FFD700; border-radius: 40px;" // أصفر للاعب الثاني
                                             );
            playerRedTurn = !playerRedTurn;
            if (checkWin(playerRedTurn ? 2 : 1)) {
                showWinnerMessage(playerRedTurn ? "Player 2 (Yellow)" : "Player 1 (Red)");
                gameEnded = true;
            } else if (isFull()) {
                showDrawMessage();
                gameEnded = true;
            }
            return;
        }
    }
}

bool ConnectFour::checkWin(int player) {
    // فحص الفوز: تحقق من جميع الاتجاهات (أفقي، رأسي، قطري)
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (board[row][col] == player) {
                if (col + 3 < 7 && board[row][col + 1] == player && board[row][col + 2] == player && board[row][col + 3] == player)
                    return true;
                if (row + 3 < 6 && board[row + 1][col] == player && board[row + 2][col] == player && board[row + 3][col] == player)
                    return true;
                if (row + 3 < 6 && col + 3 < 7 && board[row + 1][col + 1] == player && board[row + 2][col + 2] == player && board[row + 3][col + 3] == player)
                    return true;
                if (row - 3 >= 0 && col + 3 < 7 && board[row - 1][col + 1] == player && board[row - 2][col + 2] == player && board[row - 3][col + 3] == player)
                    return true;
            }
        }
    }
    return false;
}

bool ConnectFour::isFull() {
    for (int col = 0; col < 7; ++col) {
        if (board[0][col] == 0)
            return false;
    }
    return true;
}

void ConnectFour::resetGame() {
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            board[row][col] = 0;
            buttons[row][col]->setStyleSheet("background-color: white; border: 2px solid #4682B4; border-radius: 40px;");
        }
    }
    playerRedTurn = true;
    gameEnded = false;
}

void ConnectFour::showWinnerMessage(const QString &winner) {
    QMessageBox messageBox(this);
    messageBox.setText(winner + " Wins!");
    messageBox.setStyleSheet("background-color: #ADDFFF; font-size: 16px; color: black;"); // خلفية أخضر ليموني
    messageBox.exec();
    resetGame();
}

void ConnectFour::showDrawMessage() {
    QMessageBox messageBox(this);
    messageBox.setText("The game is a draw. Start a new game?");
    messageBox.setStyleSheet("background-color: #ADD8E6; font-size: 16px; color: black;"); // خلفية زرقاء فاتحة
    QPushButton* newGameButton = messageBox.addButton("New Game", QMessageBox::AcceptRole);
    QPushButton* exitButton = messageBox.addButton("Exit", QMessageBox::RejectRole);

    messageBox.exec();

    if (messageBox.clickedButton() == newGameButton) {
        resetGame();
    } else if (messageBox.clickedButton() == exitButton) {
        close();
    }
}
