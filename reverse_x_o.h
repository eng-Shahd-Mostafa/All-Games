#ifndef reverse_x_o
#define reverse_x_o
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
template <typename T>
//#include <bits/stdc++.h>
class reverse_x_oBoard :public Board<T> {
public:
    reverse_x_oBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class reverse_x_oPlayer : public Player<T> {
public:
    reverse_x_oPlayer(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class reverse_x_oRandom_Player : public RandomPlayer<T> {
public:
    reverse_x_oRandom_Player(string name, T symbol);
    void getmove(int& x, int& y);
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
reverse_x_oBoard<T>::reverse_x_oBoard() {
    this->rows = this->columns = 3;
    this->board = new char* [this->rows];
    loop1{
            this->board[i] = new char[this->columns];
            loop2 {
                this->board[i][j] = 0;
            }
    }
    this->n_moves = 0;
}

template <typename T>
bool reverse_x_oBoard<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void reverse_x_oBoard<T>::display_board() {
    loop1
    {
        cout << "\n| ";
        loop2 {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool reverse_x_oBoard<T>::is_win() {
    bool a, b, d1, d2;
    ll cx, co;
    // Check rows
    loop1
    { cx = co = 0;
        loop2
        {
            if (arr[i][j] == 'X')cx++;
            else if (arr[i][j] == 'O')co++;
        }
        if (cx == 3 || co == 3)return 1;
    }
    cx = co = 0;
    // Check columns
    loop1
    {
        loop2
        {
            if (arr[j][i] == 'X')cx++;
            else if (arr[i][j] == 'O')co++;
        }
        if (cx == 3 || co == 3)return 1;

    }

    cx = co = 0;
    // Check diagonals
    loop1{
            if (arr[i][i] == 'x')cx++;
            else if (arr[i][i] == 'O')co++;
    } if (cx == 3 || co == 3)return 1;
    cx = co = 0;
    for (int i = 0, j = this->rows - 1; i < this->rows; i++, j--)
    {
        if (arr[i][j] == 'X')cx++;
        else if (arr[i][j] == 'O')co++;
    }
    if (cx == 3 || co == 3)return 1;
    // No winner found
    return false;
}
// Return true if 9 moves are done and no winner
template <typename T>
bool reverse_x_oBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool reverse_x_oBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
reverse_x_oPlayer<T>::reverse_x_oPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void reverse_x_oPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
reverse_x_oRandom_Player<T>::reverse_x_oRandom_Player(string Name, T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
reverse_x_oRandom_Player<T>::reverse_x_oRandom_Player(string Name, T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = Name;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void reverse_x_oRandom_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //reverse_x_o
