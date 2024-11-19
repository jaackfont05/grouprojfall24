#include <iostream>
#include "SDL_Plotter.h"

using namespace std;

void checkCapture(char currBoard[][5], bool blackTurn);
bool spaceCaptured(char currBoard[][5], int x, int y, bool blackTurn);

int main(int argc, char** argv){
    char currBoard[5][5];
    char pastBoard[5][5];
    char nextBoard[5][5];
    int xCord, yCord;
    int turn = 0;
    int pass = 0;
    bool validPlay;
    bool blackTurn;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            currBoard[i][j] = 'e';
            pastBoard[i][j] = 'e';
            nextBoard[i][j] = 'e';
        }
    }


    while(pass != 2){
        blackTurn = (turn % 2 == 0);
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                cout << currBoard[i][j] << " ";
            }
            cout << endl;
        }

        if(blackTurn){
            cout << "Black choose space to play or choose -1 to pass" << endl;
        }
        else{
            cout << "White choose space to play or choose -1 to pass" << endl;
        }
        do{
            validPlay = false;
            cin >> xCord >> yCord;
            if(xCord != -1/*Function to check if space is valid*/){

                if(blackTurn){
                    nextBoard[xCord][yCord] = 'b';
                }
                else{
                    nextBoard[xCord][yCord] = 'w';
                }
                for(int i = 0; i < 5; i++){
                    for(int j = 0; j < 5; j++){
                        if(nextBoard[i][j] != pastBoard[i][j]){
                            validPlay = true;
                        }
                    }
                }
                if(currBoard[xCord][yCord] != 'e'){
                    validPlay = false;
                    for(int i = 0; i < 5; i++){
                        for(int j = 0; j < 5; j++){
                            nextBoard[i][j] = currBoard[i][j];
                        }
                    }
                }
                if(validPlay){
                    for(int i = 0; i < 5; i++){
                        for(int j = 0; j < 5; j++){
                            pastBoard[i][j] = currBoard[i][j];
                            currBoard[i][j] = nextBoard[i][j];
                        }
                    }
                }
                pass = 0;
            }
            else{
                pass++;
                validPlay = true;
            }
        }while(validPlay == false);
        checkCapture(currBoard, blackTurn);
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                nextBoard[i][j] = currBoard[i][j];
            }
        }
        turn++;

    }

    return 0;
}



void checkCapture(char currBoard[][5], bool blackTurn){
    bool captured[5][5];
    char checkedBoard[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            checkedBoard[i][j] = currBoard[i][j];
        }
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            captured[i][j] = spaceCaptured(checkedBoard, i, j, blackTurn);
            for(int r = 0; r < 5; r++){
                for(int c = 0; c < 5; c++){
                    checkedBoard[r][c] = currBoard[r][c];
                }
            }
        }
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(captured[i][j]){
                if(blackTurn && currBoard[i][j] != 'b'){
                    currBoard[i][j] = 'e';
                }
                if(!blackTurn && currBoard[i][j] != 'w'){
                    currBoard[i][j] = 'e';
                }
            }
        }
    }
}

bool spaceCaptured(char currBoard[][5], int r, int c, bool blackTurn){
    bool up, down, left, right;
    if(currBoard[r][c] == 'e'){
        return false;
    }
    if(r == -1 || r == 5 || c == -1 || c == 5 || currBoard[r][c] == 'p'){
        return true;
    }
    if(blackTurn){
        if(currBoard[r][c] == 'b'){
            return true;
        }
    }
    else{
        if(currBoard[r][c] == 'w'){
            return true;
        }
    }
    currBoard[r][c] = 'p';

    up    = spaceCaptured(currBoard, r-1, c, blackTurn);
    down  = spaceCaptured(currBoard, r+1, c, blackTurn);
    left  = spaceCaptured(currBoard, r, c-1, blackTurn);
    right = spaceCaptured(currBoard, r, c+1, blackTurn);
    if(up && down && left && right){
        return true;
    }
    return false;
}
