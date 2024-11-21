#include <iostream>
#include "SDL_Plotter.h"
#include "rules.h"
#include "token.h"
#include "line.h"

using namespace std;

int main(int argc, char** argv){
    char currBoard[SIZE][SIZE];
    char pastBoard[SIZE][SIZE];
    char nextBoard[SIZE][SIZE];
    int xCord, yCord;
    int turn = 0;
    int pass = 0;
    bool valid;

    createBoard(currBoard);
    createBoard(pastBoard);
    createBoard(nextBoard);


    while(pass < 2){
        printBoard(currBoard);

        if(isBlackTurn(turn)){
            cout << "Black choose space to play or choose -1 to pass" << endl;
        }
        else{
            cout << "White choose space to play or choose -1 to pass" << endl;
        }
        do{
            valid = false;
            cin >> xCord >> yCord;
            if(xCord > -1 && yCord > -1 && xCord < SIZE && yCord < SIZE){

                if(isBlackTurn(turn)){
                    nextBoard[xCord][yCord] = 'b';
                }
                else{
                    nextBoard[xCord][yCord] = 'w';
                }

                valid = validPlay(nextBoard, pastBoard, currBoard, xCord, yCord, turn);

                if(valid){
                    copyBoard(pastBoard, currBoard);
                    copyBoard(currBoard, nextBoard);
                }
                else{
                    copyBoard(nextBoard, currBoard);
                }
                pass = 0;
            }
            else{
                pass++;
                valid = true;
            }
        }while(valid == false);
        turn++;
    }
    score(currBoard);

    return 0;
}
