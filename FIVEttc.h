//
// Created by admin on 02/12/2024.
//
#ifndef _FIVEttc_H
#define _FIVEttc_H
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
#include <iomanip>
using namespace std;
#define loop1 for(int i=0;i<this->rows;i++)
#define loop2 for(int j=0;j<this->columns;j++)
#define  ll long long
# define arr this->board
//#include <bits/stdc++.h>
#define ll long long

#define allr(a) a.rbegin(), a.rend()
#define vi vector<int>
#define vll vector<ll>
#define vss vector<string>
#define el '\n'
using namespace std;
#define pb push_back
#define st string
#define clos 3
#define an &&
#define loop for (int i=0;i<n;i++)
#define awoo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
# include "FIVEttc.h"
# include "MinMaxPlayer.h"
#include"BoardGame_Classes.h"
template <typename T>
class FIVEttc: public Board<T>
{ public:

    FIVEttc() {
        this->rows = this->columns = 5;
        this->board = new char*[this->rows];
        loop1 {
            this->board[i] = new char[this->columns];
            loop2 {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int x,int y,T mark)override
    {
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
            if (mark == 0){
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
    void display_board()override{
        loop1 {
            cout << "\n| ";
            loop2 {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }

    bool is_win() override {
        ll cx = 0, co = 0; // Count for wins of 'X' and 'O'
        loop1 {
            loop2 {
                char current = arr[i][j];
                if (current != 0) {
                    // Vertical alignment
                    if (i - 1 >= 0 && i + 1 < this->rows && arr[i - 1][j] == current && arr[i + 1][j] == current) {
                        (current == 'X') ? cx++ : co++;
                    }
                    // Horizontal alignment
                    if (j - 1 >= 0 && j + 1 < this->columns && arr[i][j - 1] == current && arr[i][j + 1] == current) {
                        (current == 'X') ? cx++ : co++;
                    }
                    // Diagonal alignment (\ direction)
                    if (i - 1 >= 0 && i + 1 < this->rows && j - 1 >= 0 && j + 1 < this->columns &&
                        arr[i - 1][j - 1] == current && arr[i + 1][j + 1] == current) {
                        (current == 'X') ? cx++ : co++;
                    }
                    // Diagonal alignment (/ direction)
                    if (i - 1 >= 0 && i + 1 < this->rows && j + 1 < this->columns && j - 1 >= 0 &&
                        arr[i - 1][j + 1] == current && arr[i + 1][j - 1] == current) {
                        (current == 'X') ? cx++ : co++;
                    }
                }
            }
        }
        // Return true if a player has aligned three marks
        if (this->n_moves == this->rows * this->columns - 1) {
            cout<<"x "<<cx<<el;
            cout<<"o "<<co<<el;
            return (cx > co || co>cx); // If 'X' wins*//
        }
        return false;

    }

    bool is_draw() override {
        return (this->n_moves == this->rows * this->columns-1 && !is_win());
    }
    bool game_is_over()override{
        return is_win()||is_draw();
    }

};

template <typename T>
class game_player:public Player<T>{
public:
    game_player(st name,T sympol): Player<T>(name,sympol){}
    void getmove(int& x, int& y){
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin>>x>>y;
    }
};

template <typename T>
class game_random : public RandomPlayer<T> {
public:
    game_random(st s,T symbol)
            : RandomPlayer<T>(symbol) {
        this->dimension = 5;
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
void  game_random<T>:: getmove(int& x, int& y)  {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}
#endif
