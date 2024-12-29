#include <iostream>
#include "BoardGame_Classes.h"
#include "FIVEttc.h"
#include "3x3X_O.h"
# include "Connect4_game.h"
#include "utilate_TTToe.h"
# include "Tic_Tac_Toe4x4.h"
#include "Numerical_Tic_Tac_Toe.h"

using namespace std;
class menu{
public:
    menu(){
        cout << "Welcome to FCAI X-O Games. :)\n";
        int choice;
        // Set up player 1
        cout << "Choose X O game type:\n";
        cout << "[1]. Tic_Tac_Toe4x4\n";
        cout << "[2]. Misere_Tic_Tac_Toe \n";
        cout << "[3]. Five_Tic_Tac_Toe\n";
        cout << "[4]. Ultimate_Tic_Tac_Toe\n";
        cout << "[5]. Connect4_game\n";
        cout << "[6]. Numerical_Tic_Tac_Toe\n";
        cin >> choice;
        switch(choice) {
            case 1:
                F_by_F_xo();
                break;
            case 2:
                mesire_xo();
                break;
            case 3 :
                fivetttoe();
                break;
            case 4:
                ultimate_xo();
                break;
            case 5:
                connect_four();
                break;
            case 6:
                numrical_tttoe();
                break;
            default:
                cout << "Invalid choice for Exiting the game.\n";
                return;
        }
    }
    void fivetttoe()
    {   Player<char>* players[2];
        //FIVEttc<char>*B=new FIVEttc<char>();
        int choice;
        FIVEttc<char>* B = new FIVEttc<char>();
        string playerXName, player2Name;
        cout << "Welcome to FCAI X-O Game. :)\n";
        // Set up player 1
        cout << "Enter Player X name: ";
        cin >> playerXName;
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
     //   cout << "3. Smart Computer (AI)\n";
        cin >> choice;
        //
        switch(choice) {
            case 1:
                players[0] = new game_player<char>(playerXName, 'X');
                break;
            case 2:
                players[0] = new game_random<char>(playerXName,'X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return ;
        }

        // Set up player 2


        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
      //  cout << "3. Smart Computer (AI)\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[1] = new game_player<char>(player2Name , 'O');
                break;
            case 2:
                players[1] = new game_random<char>(player2Name,'O');
                break;

            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return ;
        }

        // Create the game manager and run the game    swap(playerXName,player2Name);
        GameManager<char> five_game(B ,players);

        five_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }
    void mesire_xo()
    { int choice;
        Player<char>* players[2];
        X_O_Board<char>* B = new X_O_Board<char>();
        string playerXName, player2Name;
        cout << "Welcome to FCAI X-O Game. :)\n";
        // Set up player 1
        cout << "Enter Player X name: ";
        cin >> playerXName;
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        //cout << "3. Smart Computer (AI)\n";
        cin >> choice;
        //
        switch(choice) {
            case 1:
                players[0] = new X_O_Player<char>(player2Name, 'X');
                break;
            case 2:
                players[0] = new X_O_Random_Player<char>(player2Name,'X');
                break;
//            case 3:
//                players[0] = new X_O_MinMax_Player<char>('X');
//                players[0]->setBoard(B);
//                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return ;
        }

        // Set up player 2


        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        //cout << "3. Smart Computer (AI)\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[1] = new X_O_Player<char>( playerXName, 'O');
                break;
            case 2:
                players[1] = new X_O_Random_Player<char>(playerXName,'O');
                break;
//            case 3:
//                players[1] = new X_O_MinMax_Player<char>('O');
//                players[1]->setBoard(B);
//                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return ;
        }

        // Create the game manager and run the game    swap(playerXName,player2Name);
        GameManager<char> x_o_game(B ,players);

        x_o_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

    }
    void  connect_four()
    {
        int choice;
        Player<char>* players[2];
        Connect4_Board<char>* Board = new Connect4_Board<char>();
        string player1Name, player2Name;
        cout << string(35, ' ') << "Welcome to FCAI Connect4 Game ^_^\n";
        cout << string(33, ' ') << string(37, '=') << "\n";    // Set up player 1
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                players[0] = new Connect4_Player<char>(player1Name, 'X');
                break;
            case 2:
                players[0] = new Connect4_Random_Player<char>(player1Name,'X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return ;
        }

        // Set up player 2


        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                players[1] = new Connect4_Player<char>(player2Name, 'O');
                break;
            case 2:
                players[1] = new Connect4_Random_Player<char>(player2Name,'O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return ;
        }

        // Create the game manager and run the game    swap(player1Name,player2Name);
        GameManager<char> Connect4_game(Board, players);

        Connect4_game.run();

        // Clean up
        delete Board;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }
    void ultimate_xo()
    {
        int choice;
        Player<char>* players[2];
        //FIVEttc<char>*B=new FIVEttc<char>();
        UltimateTicTacToe<char>* B = new UltimateTicTacToe<char>();
        string playerXName, player2Name;
        cout << "Welcome to FCAI X-O Game. :)\n";
        // Set up player 1
        cout << "Enter Player X name: ";
        cin >> playerXName;
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
       // cout << "3. Smart Computer (AI)\n";
        cin >> choice;
        //
        switch(choice) {
            case 1:
                players[0] = new game_player2<char>(playerXName, 'X');
                break;
            case 2:
                players[0] = new game_random2<char>(playerXName,'X');
                break;
//        case 3:
//            players[0] = new X_O_MinMax_Player<char>('X');
//            players[0]->setBoard(B);
//            break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return ;
        }

        // Set up player 2


        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
       // cout << "3. Smart Computer (AI)\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[1] = new game_player2<char>(player2Name , 'O');
                break;
            case 2:
                players[1] = new game_random2<char>(player2Name,'O');
                break;
//        case 3:
//            players[1] = new X_O_MinMax_Player<char>('O');
//            players[1]->setBoard(B);
//            break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return ;
        }

        // Create the game manager and run the game    swap(playerXName,player2Name);
        GameManager<char>game(B ,players);

      game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

    }
    void  F_by_F_xo()
    {
        string player1Name, player2Name;
        int choice;

        Tic_Tac_Toe4x4_Board* board = new Tic_Tac_Toe4x4_Board();

        cout << string(35, ' ') << "Welcome to FCAI Tic Tac Toe4x4 Game ^_^\n";
        cout << string(34, ' ') << string(42, '=') << "\n";
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        Player<char>* players[2];


        switch (choice) {
            case 1:
                players[0] = new Tic_Tac_Toe4x4_Player(player1Name, 'X');
                break;
            case 2:
                players[0] = new TicTacToeRandomPlayer('X', *board);
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                delete board;
                return ;
        }

        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;


        switch (choice) {
            case 1:
                players[1] = new Tic_Tac_Toe4x4_Player(player2Name, 'O');
                break;
            case 2:
                players[1] = new TicTacToeRandomPlayer('O', *board);
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                delete board;
                for (int i = 0; i < 2; ++i) {
                    delete players[i];
                }
                return ;
        }

        int old_x, old_y, new_x, new_y;
        board->display_board();

        // Main game loop
        while (!board->game_is_over()) {
            for (int i = 0; i < 2; ++i) {
                cout << players[i]->getname() << "'s turn (symbol: " << players[i]->getsymbol() << ")\n";


                if (dynamic_cast<Tic_Tac_Toe4x4_Player*>(players[i])) {
                    players[i]->getmove(old_x, old_y);
                    Tic_Tac_Toe4x4_Player* humanPlayer = dynamic_cast<Tic_Tac_Toe4x4_Player*>(players[i]);
                    humanPlayer->movement(old_x, old_y, new_x, new_y, *board);
                }
                else {
                    TicTacToeRandomPlayer* randomPlayer = dynamic_cast<TicTacToeRandomPlayer*>(players[i]);
                    if (randomPlayer != nullptr) {
                        randomPlayer->getmove(old_x, old_y);
                    }
                }

                if (board->is_win()) {
                    board->display_board();
                    if (i == 0)
                        cout << player1Name << " wins!" << endl;
                    else
                        cout << player2Name << " wins!" << endl;

                    delete board;
                    for (int i = 0; i < 2; ++i) {
                        delete players[i];
                    }
                    return ;
                }

                board->display_board();
            }
        }

        board->display_board();
        cout << "The game is a draw!" << endl;

        delete board;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

    }
    void   numrical_tttoe()
    {
        int choice;
        Player<int>* players[2];
        Numerical_Tic_Tac_Toe_Board<int>* Board = new Numerical_Tic_Tac_Toe_Board<int>();
        string player1Name, player2Name;

        cout << string(33, ' ') << "Welcome to FCAI Numerical Tic Tac Toe Game ^_^\n";
        cout << string(31, ' ') << string(50, '=') << "\n";

        // Set up player 1
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                players[0] = new Numerical_Tic_Tac_Toe_Player<int>(player1Name, 0);
                break;
            case 2:
                players[0] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0);
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return ;
        }

        // Set up player 2
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                players[1] = new Numerical_Tic_Tac_Toe_Player<int>(player2Name, 0);  // 2 يستخدم للأرقام الزوجية
                break;
            case 2:
                players[1] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0);  // 2 يستخدم للأرقام الزوجية
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return ;
        }


        set<int>usedNumbers;
        int x, y, num;
        bool gameOver = false;
        Board->display_board();

        while (!gameOver) {
            for (int i = 0; i < 2 && !gameOver; ++i) {
                if (dynamic_cast<Numerical_Tic_Tac_Toe_Random_Player<int>*>(players[i])) {
                    cout << "Player " << (i == 0 ? player1Name : player2Name) << " (Random Computer) is playing...\n";
                    do {
                        num = rand() % 10 + 1;
                    } while ((i == 0 && (num % 2 == 0 || num > 9)) ||
                             (i == 1 && (num % 2 != 0 || num > 8 || num == 0)) ||
                             usedNumbers.count(num));

                    players[i]->getmove(x, y);
                    std::cout << "Computer chose: (" << x << ", " << y << ") with number: " << num << std::endl;
                }

                else
                {
                    std::cout << "Player " << (i == 0 ? player1Name : player2Name) << ", enter a number: ";
                    std::cin >> num;

                    if ((i == 0 && (num % 2 == 0 || num > 9)) || (i == 1 && (num % 2 != 0 || num > 8 || num == 0)) || usedNumbers.count(num))
                    {
                        if (usedNumbers.count(num) && i == 0)
                            cout << "This number is already used. Choose an odd number (1, 3, 5, 7, 9).\n";

                        else if (usedNumbers.count(num) && i == 1)
                            cout << "This number is already used. Choose an odd number (2, 4, 6, 8).\n";

                        else if (i == 0)
                            cout << "Please enter odd numbers (1, 3, 5, 7, 9)\n";

                        else
                            cout << "Please enter even numbers (2, 4, 6, 8)\n";
                        --i;
                        continue;
                    }
                    players[i]->getmove(x, y);
                }

                if (!Board->update_board(x, y, num)) {
                    cout << "Invalid move! Try again.\n";
                    --i;
                    continue;
                }

                usedNumbers.insert(num);
                Board->display_board();

                if (Board->is_win())
                {
                    std::cout << "Player " << (i == 0 ? player1Name : player2Name) << " wins!\n";
                    gameOver = true;
                }
                else if (Board->is_draw())
                {
                    std::cout << "The game is a draw!\n";
                    gameOver = true;
                }
            }
        }
        delete Board;
        for (int i = 0; i < 2; ++i)
        {
            delete players[i];
        }
    }
};

int main() {
menu();
}
