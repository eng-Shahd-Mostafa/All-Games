#ifndef _CONNECT4_GAME_H
#define _CONNECT4_GAME_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib> // For rand()

using namespace std;

template <typename T>
class Connect4_Board : public Board<T> 
{
    bool check_is_win(int rows, int cols, int rows1, int cols1);
public:
    Connect4_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Connect4_Player : public Player<T> {
public:
    Connect4_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Connect4_Random_Player : public RandomPlayer<T> {
public:
    Connect4_Random_Player(string s,T symbol);
    void getmove(int& x, int& y);
};


// Implementation of Connect4_Board
template <typename T>
Connect4_Board<T>::Connect4_Board() 
{
    this->rows = 6; 
    this->columns = 7; 
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) 
    {
        this->board[i] = new char[this->columns];
        fill(this->board[i], this->board[i] + this->columns, 0);
    }
    this->n_moves = 0;
}

template <typename T>
bool Connect4_Board<T>::update_board(int x, int y, T symbol)
{
    if (y < 0 || y >= this->columns || x != 0 || this->board[0][y] != 0)
        return false;
    for (int i = this->rows - 1;i >= 0;i--)
    {
        if (this->board[i][y] == 0)
        {
            this->board[i][y] = symbol;
            this->n_moves++;
            return true;
        }
    }
    return false; //columns is full
}

template <typename T>
void Connect4_Board<T>::display_board() 
{
    cout << "    0   1   2   3   4   5   6\n";
    cout << "  +---+---+---+---+---+---+---+\n";
    for (int i = 0; i < this->rows; i++) {
        cout << i << " |";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << (this->board[i][j] ? this->board[i][j] : ' ') << " |";
        }
        cout << "\n  +---+---+---+---+---+---+---+\n";
    }
}

template <typename T>
bool Connect4_Board<T>::is_win() {
    // Horizontal, vertical, diagonal checks (same logic)
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0 && (check_is_win(i, j, 0, 1) || check_is_win(i, j, 1, 0) || check_is_win(i, j, 1, 1) || check_is_win(i, j, 1, -1)))
                return true;
        }
    }
    return false;
    
}

template <typename T>
bool Connect4_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool Connect4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
bool Connect4_Board<T>::check_is_win(int rows, int cols, int rows1, int cols1)
{
    T symbol=this->board[rows][cols];
    for (int i = 1;i < 4;i++)
    {
        int newR = rows + i * rows1;
        int newC = cols + i * cols1;
        if (newR < 0 || newR >= this->rows || newC < 0 || newC >= this->columns || this->board[newR][newC] != symbol)
            return false;

    }
    return true;
}

// Connect4_Player
template <typename T>
Connect4_Player<T>::Connect4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Connect4_Player<T>::getmove(int& x, int& y) {
    cout << "Enter your column from 0 to 6\n";
    cin >> y;
    x = 0;
       
       
}

// Connect4_Random_Player
template <typename T>
Connect4_Random_Player<T>::Connect4_Random_Player(string s,T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 7;
    this->name = s;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Connect4_Random_Player<T>::getmove(int& x, int& y) {
    y = rand() % this->dimension;
    x = 0;
}

#endif
