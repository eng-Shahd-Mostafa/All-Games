#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

template <typename T>
class Numerical_Tic_Tac_Toe_Board : public Board<T> {
public:
    Numerical_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Numerical_Tic_Tac_Toe_Player : public Player<T> {

public:
    Numerical_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Numerical_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {

public:
    Numerical_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
Numerical_Tic_Tac_Toe_Board<T>::Numerical_Tic_Tac_Toe_Board()
{
    this->rows = this->columns = 3;
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = static_cast<T>(0);
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
void Numerical_Tic_Tac_Toe_Board<T>::display_board() {
    cout << "    0   1   2\n";
    cout << "  +---+---+---+\n";
    for (int i = 0; i < this->rows; i++) {
        cout << i << " |";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << (this->board[i][j] ? this->board[i][j] : 0) << " |";
        }
        cout << "\n  +---+---+---+\n";
    }
}

// Returns true if there is any winner
template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        // Check rows and columns
        if ((this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0 &&
            this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) ||
            (this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0 &&
                this->board[0][i] + this->board[1][i] + this->board[2][i] == 15))
            return true;
    }

    // Check diagonals
    if ((this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0 &&
        this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ||
        (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0 &&
            this->board[0][2] + this->board[1][1] + this->board[2][0] == 15))
        return true;

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for X_O_Player
template <typename T>
Numerical_Tic_Tac_Toe_Player<T>::Numerical_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Numerical_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlayer " << this->name << ", enter your move (0 to 2):\n";
    cin >> x >> y;
}

// Random Player class
template <typename T>
Numerical_Tic_Tac_Toe_Random_Player<T>::Numerical_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = "Random Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Numerical_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif // NUMERICAL_TIC_TAC_TOE_H
