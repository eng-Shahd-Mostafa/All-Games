#ifndef _TIC_TAC_TOE4X4_H
#define _TIC_TAC_TOE4X4_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
using namespace std;

class Tic_Tac_Toe4x4_Board : public Board<char>
{
public:
    Tic_Tac_Toe4x4_Board()
    {
        this->rows = this->columns = 4;
        this->board = new char* [this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                if (i == 0) {
                    this->board[i][j] = (j % 2 == 0) ? 'O' : 'X';
                }
                else if (i == 3) {
                    this->board[i][j] = (j % 2 == 0) ? 'X' : 'O';
                }
                else {
                    this->board[i][j] = ' ';
                }
            }
        }
        this->n_moves = 0;
    }


    bool update_board(int x, int y, char symbol) override
    {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != ' ') {
            return false;
        }
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    void display_board() override 
    {
        cout << "    0   1   2   3\n";
        cout << "  +---+---+---+---+\n";
        for (int i = 0; i < this->rows; i++) {
            cout << i << " |";
            for (int j = 0; j < this->columns; j++) {
                cout << " " << (this->board[i][j] ? this->board[i][j] : ' ') << " |";
            }
            cout << "\n  +---+---+---+---+\n";
        }
    }

    bool is_win() override
    {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns - 2; ++j) {
                if (this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2] &&
                    this->board[i][j] != ' ') {
                    return true;
                }
            }
        }

        for (int j = 0; j < this->columns; ++j) {
            for (int i = 0; i < this->rows - 2; ++i) {
                if (this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j] &&
                    this->board[i][j] != ' ') {
                    return true;
                }
            }
        }

        for (int i = 0; i < this->rows - 2; ++i) {
            for (int j = 0; j < this->columns - 2; ++j) {

                if (this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2] &&
                    this->board[i][j] != ' ') {
                    return true;
                }

                if (this->board[i][j + 2] == this->board[i + 1][j + 1] &&
                    this->board[i][j + 2] == this->board[i + 2][j] &&
                    this->board[i][j + 2] != ' ') {
                    return true;
                }
            }
        }

        return false;
    }

    bool is_draw() override
    {
        return this->n_moves == this->rows * this->columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    char** getBoard() {
        return this->board;
    }

};



class Tic_Tac_Toe4x4_Player : public Player<char>
{
public:
    Tic_Tac_Toe4x4_Player(string name, char symbol) : Player<char>(name, symbol) {}

    Tic_Tac_Toe4x4_Player(char symbol) : Player<char>(symbol) {}

    string get_name()
    {
        return this->name;
    }

    char get_symbol()
    {
        return this->symbol;
    }

    void getmove(int& x, int& y)
    {
        cout << "Enter Row and Column of the token you want to move: ";
        cin >> x >> y;
    }

    void movement(int& oldX, int& oldY, int& x, int& y, Tic_Tac_Toe4x4_Board& game)
    {

        while (game.getBoard()[oldX][oldY] != this->symbol)
        {
            cout << "Error: The Position must contain your symbol (" << this->symbol << "). Please choose a valid number with your token: \n\a";
            cin >> oldX >> oldY;
        }

        cout << "Now, Enter the new position (Row and Column) where you want to move the piece: ";
        cin >> x >> y;


        while (!((abs(oldX - x) == 1 && oldY == y) ||
            (abs(oldY - y) == 1 && oldX == x)) ||
            game.getBoard()[x][y] != ' ') {
            cout << "Invalid move! The piece must move only one step in the same row or column and the target cell must be empty. \n";
            cin >> x >> y;
        }

        game.getBoard()[x][y] = this->symbol;
        game.getBoard()[oldX][oldY] = ' ';
    }

};

class TicTacToeRandomPlayer : public Player<char>
{
private:
    Tic_Tac_Toe4x4_Board& game;

public:
    TicTacToeRandomPlayer(std::string name, char symbol, Tic_Tac_Toe4x4_Board& game)
        : Player<char>(name, symbol), game(game) {}

    TicTacToeRandomPlayer(char symbol, Tic_Tac_Toe4x4_Board& game)
        : Player<char>(symbol), game(game)
    {
        this->name = "Computer";
    }
    void getmove(int& oldX, int& oldY) override
    {
        int tries = 0;
        bool Move = false;
        int x, y;

        while (!Move && tries < 100)
        {
            oldX = rand() % 4;
            oldY = rand() % 4;

            if (game.getBoard()[oldX][oldY] == this->symbol)
            {
                bool moveFound = false;
                for (int i = 0; i < 4 && !moveFound; ++i)
                {

                    if (game.getBoard()[oldX][i] == ' ' && i != oldY && abs(i - oldY) == 1)
                    {
                        x = oldX;
                        y = i;
                        moveFound = true;
                    }
                    if (game.getBoard()[i][oldY] == ' ' && i != oldX && abs(i - oldX) == 1)
                    {
                        x = i;
                        y = oldY;
                        moveFound = true;
                    }
                }
                if (moveFound)
                {
                    Move = true;
                    cout << "(" << this->name << ") moves from (" << oldX << ", " << oldY << ") to (" << x << ", " << y << ")\n";
                    game.getBoard()[x][y] = this->symbol;
                    game.getBoard()[oldX][oldY] = ' ';
                }
            }
            tries++;
        }
        if (!Move)
            cout << "No valid move found after 100 attempts.\n";
    }


    string get_name()
    {
        return this->name;
    }

    char get_symbol()
    {
        return this->symbol;
    }
};

#endif
