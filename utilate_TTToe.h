//
// Created by admin on 10/12/2024.
//

#ifndef UNTITLED_UTILATE_TTTOE_H
#define UNTITLED_UTILATE_TTTOE_H
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
#include <iomanip>
using namespace std;
#define loop1 for (int i = 0; i < this->rows; i++)
#define loop2 for (int j = 0; j < this->columns; j++)
# define el endl;
#define loop3 for (int   a=0; a < 3; a++)
#define loop4 for (int b = 0; b< 3; b++)
#define ll long long
#define arr this->board
//#include <bits/stdc++.h>
#define ll long long
# define row i
# define col j
#include "utilate_TTToe.h"
template <typename T>
class UltimateTicTacToe : public Board<T> {
private:
    T board[9][9];
    T sub_winners[3][3];
    pair<int, int> last_move;
    vector<vector<pair<int, int>>> coordinates_grid;
public:
    UltimateTicTacToe() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = 0;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                sub_winners[i][j] = 0;
            }
        }
        coordinates_grid = {
                {{0, 0}, {3, 0}, {6, 0}, {0, 3}, {3, 3}, {6, 3}, {0, 6}, {3, 6}, {6, 6}},
                {{1, 0}, {4, 0}, {7, 0}, {1, 3}, {4, 3}, {7, 3}, {1, 6}, {4, 6}, {7, 6}},
                {{2, 0}, {5, 0}, {8, 0}, {2, 3}, {5, 3}, {8, 3}, {2, 6}, {5, 6}, {8, 6}},
                {{0, 1}, {3, 1}, {6, 1}, {0, 4}, {3, 4}, {6, 4}, {0, 7}, {3, 7}, {6, 7}},
                {{1, 1}, {4, 1}, {7, 1}, {1, 4}, {4, 4}, {7, 4}, {1, 7}, {4, 7}, {7, 7}},
                {{2, 1}, {5, 1}, {8, 1}, {2, 4}, {5, 4}, {8, 4}, {2, 7}, {5, 7}, {8, 7}},
                {{0, 2}, {3, 2}, {6, 2}, {0, 5}, {3, 5}, {6, 5}, {0, 8}, {3, 8}, {6, 8}},
                {{1, 2}, {4, 2}, {7, 2}, {1, 5}, {4, 5}, {7, 5}, {1, 8}, {4, 8}, {7, 8}},
                {{2, 2}, {5, 2}, {8, 2}, {2, 5}, {5, 5}, {8, 5}, {2, 8}, {5, 8}, {8, 8}}
        };

        last_move = {-1, -1};
    }
    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= 9 || y < 0 || y >= 9) return false;
        ll subgrid_row = x / 3;
        ll subgrid_col = y / 3;
        if (sub_winners[subgrid_row][subgrid_col] == 'X' || sub_winners[subgrid_row][subgrid_col] == 'O') {
            cout << "invalid move. This submatrix has won by "
                 << sub_winners[subgrid_row][subgrid_col] << "!\n";
            return false;
        }
        if (board[x][y] == 0 || symbol == 0) {
            if (symbol == 0) {
                this->n_moves--;
                board[x][y] = 0;
            } else {
                this->n_moves++;
                board[x][y] = toupper(symbol);
            }
            return true;
        }
        cout << "invalid move cell is already used!\n";
        return false;
    }
    void display_board() override {
        ll n = 9;
        cout << "   ";
        for (int j = 0; j < n; j++) {
            if (j % 3 == 0 && j != 0) cout << "  ";
            cout << setw(2) << j << " ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++) {
            if (i % 3 == 0 && i != 0) {
                cout << "   ";
                for (int j = 0; j < n + 2; j++) {
                    if (j % 12 == 0 && j != 0) {
                        cout << "+";
                    } else {
                        cout << "-";
                    }
                }
                cout << el;
            }
            cout << setw(2) << i << " ";
            for (int j = 0; j < n; j++) {
                if (j % 3 == 0 && j != 0) cout << "| ";
                cout << " " << (board[i][j] == 0 ? '.' : char(board[i][j])) << " ";
            }
            cout << el;
        }
    }
    bool is_win() override {

        check_subgrid_win(); print_sub_winners();
        // row
        for (int i = 0; i < 3; i++) {
            if (check_three(sub_winners[i][0], sub_winners[i][1], sub_winners[i][2])) {
                return true;
            }
        }
        //coloumn
        for (int j = 0; j < 3; j++) {
            if (check_three(sub_winners[0][j], sub_winners[1][j], sub_winners[2][j])) {
                return true;
            }
        }
// principle disag
        if (check_three(sub_winners[0][0], sub_winners[1][1], sub_winners[2][2])) {
            return true;
        }
        // diag 2
        if (check_three(sub_winners[0][2], sub_winners[1][1], sub_winners[2][0])) {
            return true;
        }


        return false;
    }

    void print_sub_winners() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                if (sub_winners[i][j]=='X' ||sub_winners[i][j]=='O')
                    cout<<sub_winners[i][j]<<"  ";
                else cout<<" * ";
            }
            cout << el;
        }
    }

    bool check_subgrid_win() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ll r = i * 3;
                ll c = j * 3;

                //  row
                for (int k = 0; k < 3; k++) {
                    if (board[r+ k][c] != 0 &&
                        board[r + k][c] == board[r + k][c + 1] &&
                        board[r+ k][c + 1] == board[r + k][c + 2]) {
                        sub_winners[i][j] = board[r + k][c];
//
                    }
                }

                //  column
                for (int k = 0; k < 3; k++) {
                    if (board[r][c + k] != 0 &&
                        board[r][c + k] == board[r + 1][c + k] &&
                        board[r + 1][c + k] == board[r + 2][c + k]) {
                        sub_winners[i][j] = board[r][c + k];
//
                    }
                }

                // principle diag
                if (board[r][c] != 0 &&
                    board[r][c] == board[r + 1][c + 1] &&
                    board[r + 1][c + 1] == board[r + 2][c + 2]) {
                    sub_winners[i][j] = board[r][c];

                }
                //diag2
                if (board[r][c + 2] != 0 &&
                    board[r][c + 2] == board[r + 1][c + 1] &&
                    board[r + 1][c + 1] == board[r + 2][c]) {
                    sub_winners[i][j] = board[r][c + 2];

                }
            }
        }
        return false;
    }
    bool check_three(T a, T b, T c) {
        return (a == b && b == c && a != 0);
    }
    bool is_draw() override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (sub_winners[i][j] == 0) {
                    bool full = true;
                    for (int r = i * 3; r < (i + 1) * 3; r++) {
                        for (int c = j * 3; c < (j + 1) * 3; c++) {
                            if (board[r][c] == 0) {
                                full = false;
                                break;
                            }
                        }
                        if (!full) break;
                    }
                    if (!full) {
                        return false;
                    }
                }
            }
        }
        return !is_win();
    }
    bool game_is_over() override {
        return is_win() || is_draw();
    }
};
template <typename T>
class game_player2 : public Player<T> {
public:
    game_player2(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << "  enter your move x and y (0 to 8) separated by spaces: "<<el;
        cin >> x >> y;
        while (x < 0 || x >= 9 || y < 0 || y >= 9) {
            cout << "invalid move Please enter values for x and y between 0 and 8: ";
            cin >> x >> y;
        }
    }
};
template <typename T>
class game_random2 : public RandomPlayer<T> {
public:
    game_random2(st s,T symbol)
            : RandomPlayer<T>(symbol) {
        this->dimension = 9;
        this->name = s;
        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned int>(time(0)));
            seeded = true;
        }
    }
    void getmove(int& x, int& y) ;
};
template <typename T>
void  game_random2<T>::getmove(int& x, int& y)  {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}



#endif
