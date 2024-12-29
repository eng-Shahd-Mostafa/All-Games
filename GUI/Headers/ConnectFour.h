#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <vector>

class ConnectFour : public QDialog {
    Q_OBJECT

public:
    explicit ConnectFour(QWidget *parent = nullptr);
    ~ConnectFour();

private slots:
    void makeMove(int col);          // دالة لإجراء حركة اللاعب
    void resetGame();                // دالة لإعادة تعيين اللعبة
    void showWinnerMessage(const QString &winner); // رسالة فوز اللاعب
    void showDrawMessage();          // رسالة التعادل

private:
    bool checkWin(int player);       // التحقق من فوز اللاعب
    bool isFull();                   // التحقق من امتلاء اللوحة

    QVBoxLayout* mainLayout;         // التخطيط الرئيسي للشاشة
    QGridLayout* gridLayout;         // شبكة الأزرار (اللوحة)
    QPushButton* buttons[6][7];      // الأزرار (تمثل خانات اللعبة)
    QPushButton* resetButton;        // زار إعادة اللعبة
    QPushButton* exitButton;         // زار الخروج

    std::vector<std::vector<int>> board; // مصفوفة تمثل لوحة اللعبة (0=فارغ، 1=أحمر، 2=أصفر)
    bool playerRedTurn;              // حالة اللاعب الحالي (true = الأحمر)
    bool gameEnded;                  // حالة انتهاء اللعبة
};

#endif // CONNECTFOUR_H
