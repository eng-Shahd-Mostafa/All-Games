#include "TicTacToe4x4.h"
#include <QPainter>
#include <QMessageBox>

TicTacToe4x4::TicTacToe4x4(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Tic Tac Toe 4x4");
    setFixedSize(420, 500);

    currentPlayer = "Player 1 (X)";
    currentSymbol = "X";
    selectedPiece = "";

    // CreatBoard
    setStyleSheet("background-color: #FFFAF0;");

    createBoard();
}

TicTacToe4x4::~TicTacToe4x4() {}

void TicTacToe4x4::createBoard()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // currentPlayer
    statusLabel = new QLabel(currentPlayer + "'s Turn");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #333;");
    mainLayout->addWidget(statusLabel);

    // GridLayout
    QGridLayout *layout = new QGridLayout;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            buttons[row][col] = new QPushButton(this);
            buttons[row][col]->setFixedSize(100, 100);
            buttons[row][col]->setStyleSheet(
                "font-size: 28px; font-weight: bold; "
                "background-color: #F0F8FF; "
                "border: 2px solid #4682B4; "
                "border-radius: 15px;"
                );
            connect(buttons[row][col], &QPushButton::clicked, [this, row, col]() { buttonClicked(row, col); });
            layout->addWidget(buttons[row][col], row, col);

            // إعداد القطع الأولية
            if (row == 0) {
                board[row][col] = (col % 2 == 0) ? "X" : "O";
                buttons[row][col]->setText(board[row][col]);
                buttons[row][col]->setStyleSheet(
                    board[row][col] == "X"
                        ? "font-size: 28px; font-weight: bold; color: red; background-color: #FFCCCB;"
                        : "font-size: 28px; font-weight: bold; color: blue; background-color: #B0E0E6;"
                    );
            } else if (row == 3) {
                board[row][col] = (col % 2 == 0) ? "O" : "X";
                buttons[row][col]->setText(board[row][col]);
                buttons[row][col]->setStyleSheet(
                    board[row][col] == "X"
                        ? "font-size: 28px; font-weight: bold; color: red; background-color: #FFCCCB;"
                        : "font-size: 28px; font-weight: bold; color: blue; background-color: #B0E0E6;"
                    );
            } else {
                board[row][col] = "";
            }
        }
    }
    mainLayout->addLayout(layout);

    // أزرار السفلية
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *resetButton = new QPushButton("🔄 Reset");
    resetButton->setFixedSize(120, 40);
    resetButton->setStyleSheet(
        "font-size: 18px; font-weight: bold; color: white; "
        "background-color: #32CD32; border-radius: 10px;"
        );
    connect(resetButton, &QPushButton::clicked, this, &TicTacToe4x4::resetBoard);
    buttonLayout->addWidget(resetButton);

    QPushButton *exitButton = new QPushButton("🚪 Exit");
    exitButton->setFixedSize(120, 40);
    exitButton->setStyleSheet(
        "font-size: 18px; font-weight: bold; color: white; "
        "background-color: #FF4500; border-radius: 10px;"
        );
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
    buttonLayout->addWidget(exitButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void TicTacToe4x4::buttonClicked(int row, int col)
{
    if (!selectedPiece.isEmpty()) {
        // Move السماح بالحركة الرأسية أو الأفقية فقط
        if (board[row][col].isEmpty() &&
            ((qAbs(row - selectedRow) == 1 && qAbs(col - selectedCol) == 0) ||  // حركة عمودية
             (qAbs(row - selectedRow) == 0 && qAbs(col - selectedCol) == 1)))   // حركة أفقية
        {
            // نقل القطعة
            board[row][col] = selectedPiece;
            buttons[row][col]->setText(selectedPiece);
            buttons[row][col]->setStyleSheet(
                selectedPiece == "X"
                    ? "font-size: 28px; font-weight: bold; color: red; background-color: #FFCCCB;"
                    : "font-size: 28px; font-weight: bold; color: blue; background-color: #B0E0E6;"
                );
            board[selectedRow][selectedCol] = "";
            buttons[selectedRow][selectedCol]->setText("");
            buttons[selectedRow][selectedCol]->setStyleSheet(
                "font-size: 28px; font-weight: bold; "
                "background-color: #F0F8FF; "
                "border: 2px solid #4682B4; "
                "border-radius: 15px;"
                );

            selectedPiece = "";
            checkWinner();
            currentPlayer = (currentPlayer == "Player 1 (X)") ? "Player 2 (O)" : "Player 1 (X)";
            currentSymbol = (currentSymbol == "X") ? "O" : "X";
            statusLabel->setText(currentPlayer + "'s Turn");
        }
    } else if (board[row][col] == currentSymbol) {
        selectedPiece = currentSymbol;
        selectedRow = row;
        selectedCol = col;
    }
}

void TicTacToe4x4::checkWinner()
{
    // Check V (Vertical) for 3 or more consecutive symbols
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row <= 1; ++row) { // Check from top row
            if (!board[row][col].isEmpty() &&
                board[row][col] == board[row + 1][col] &&
                board[row][col] == board[row + 2][col]) {
                showWinner(board[row][col]);
                return;
            }
        }
    }

    // Check H (Horizontal) for 3 or more consecutive symbols
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col <= 1; ++col) { // Check from left column
            if (!board[row][col].isEmpty() &&
                board[row][col] == board[row][col + 1] &&
                board[row][col] == board[row][col + 2]) {
                showWinner(board[row][col]);
                return;
            }
        }
    }

    // Check Diagonal (Top-Left to Bottom-Right) for 3 or more consecutive symbols
    for (int row = 0; row <= 1; ++row) {  // Start from top rows
        for (int col = 0; col <= 1; ++col) {  // Start from left columns
            if (!board[row][col].isEmpty() &&
                board[row][col] == board[row + 1][col + 1] &&
                board[row][col] == board[row + 2][col + 2]) {
                showWinner(board[row][col]);
                return;
            }
        }
    }

    // Check Diagonal (Bottom-Left to Top-Right) for 3 or more consecutive symbols
    for (int row = 3; row >= 2; --row) {  // Start from bottom rows
        for (int col = 0; col <= 1; ++col) {  // Start from left columns
            if (!board[row][col].isEmpty() &&
                board[row][col] == board[row - 1][col + 1] &&
                board[row][col] == board[row - 2][col + 2]) {
                showWinner(board[row][col]);
                return;
            }
        }
    }
}

void TicTacToe4x4::showWinner(const QString &winner)
{
    QString player = (winner == "X") ? "Player 1" : "Player 2";
    QMessageBox::information(
        this,
        "🎉 Congratulations! 🎉",
        QString("<h2 style='font-size:24px; color:green;'>🎊 Congratulations! 🎊</h2>"
                "<p style='font-size:18px; color:#333;'>"
                "✨ %1 has won the game! ✨</p>"
                "<p style='font-size:16px; color:blue;'>Keep playing and have fun! 🎮</p>")
            .arg(player),
        QMessageBox::Ok
        );
    resetBoard();
}

void TicTacToe4x4::resetBoard()
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (row == 0) {
                board[row][col] = (col % 2 == 0) ? "X" : "O";
            } else if (row == 3) {
                board[row][col] = (col % 2 == 0) ? "O" : "X";
            } else {
                board[row][col] = "";
            }
            buttons[row][col]->setText(board[row][col]);
            buttons[row][col]->setStyleSheet(
                board[row][col] == "X"
                    ? "font-size: 28px; font-weight: bold; color: red; background-color: #FFCCCB;"
                    : (board[row][col] == "O"
                           ? "font-size: 28px; font-weight: bold; color: blue; background-color: #B0E0E6;"
                           : "font-size: 28px; font-weight: bold; "
                             "background-color: #F0F8FF; "
                             "border: 2px solid #4682B4; "
                             "border-radius: 15px;"));
        }
    }

    selectedPiece = "";
    currentPlayer = "Player 1 (X)";
    currentSymbol = "X";
    statusLabel->setText(currentPlayer + "'s Turn");
}
