QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ConnectFour.cpp \
    MainWindow.cpp \
    MisereTicTacToe.cpp \
    NumericalTicTacToe.cpp \
    TicTacToe4x4.cpp \
    TicTacToe5x5.cpp \
    UltimateTicTacToe.cpp \
    main.cpp

HEADERS += \
    ConnectFour.h \
    MainWindow.h \
    MisereTicTacToe.h \
    NumericalTicTacToe.h \
    TicTacToe4x4.h \
    TicTacToe5x5.h \
    UltimateTicTacToe.h \

FORMS += \
    ConnectFour.ui \
    MainWindow.ui \
    MisereTicTacToe.ui \
    NumericalTicTacToe.ui \
    TicTacToe4x4.ui \
    TicTacToe5x5.ui \
    UltimateTicTacToe.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    reg.qrc

DISTFILES += \
    ../PIC/Des2.png
