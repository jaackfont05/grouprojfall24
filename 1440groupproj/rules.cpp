//Mason Crippen
//Jack Fontenot
//Andrei Kuvshinikov
//Connor Griffin

#include "rules.h"

//Turn
bool isBlackTurn(int turn){
    return (turn % 2 == 0);
}

//Pass
void turnPassed(int turn){
    if(isBlackTurn(turn)){
        cout << "Black";
    }
    else{
        cout << "White";
    }
    cout << " passed their turn." << endl << endl;
}

//building boards
void copyBoard(char newBoard[][SIZE], char copiedBoard[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            newBoard[i][j] = copiedBoard[i][j];
        }
    }
}
void drawBoard(char board[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
void createBoard(char board[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            board[i][j] = '.';
        }
    }
}
void drawBoard(SDL_Plotter& g, token tokenBoard[][SIZE]){
    for(int i = 0; i < BOARDSIZE; i++){
        for(int j = 0; j < BOARDSIZE; j++){
            g.plotPixel(i, j, boardColor);
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(tokenBoard[i][j].getColor().R != emptyColor.R){
                tokenBoard[i][j].draw(g);
            }
        }
    }
}
void createTokenBoard(char currBoard[][SIZE], token tokenBoard[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            point center(SIDE*j+SIDE/2, SIDE*i+SIDE/2);
            tokenBoard[i][j].setColor(emptyColor);
            tokenBoard[i][j].setRadius((SIDE/2)-5);
            tokenBoard[i][j].setCenter(center);
        }
    }
}
void updateTokenBoard(char currBoard[][SIZE], token tokenBoard[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(currBoard[i][j] == 'b'){
                tokenBoard[i][j].setColor(blackColor);
            }
            else if(currBoard[i][j] == 'w'){
                tokenBoard[i][j].setColor(whiteColor);
            }
            else{
                tokenBoard[i][j].setColor(emptyColor);
            }
        }
    }
}

//Checking for captures
bool spaceCaptured(char currBoard[][SIZE], int r, int c, bool blackTurn){
    bool captured;
    if(blackTurn){
        captured = whiteCaptured(currBoard, r, c);
    }
    else{
        captured = blackCaptured(currBoard, r, c);
    }
    return captured;
}
bool whiteCaptured(char currBoard[][SIZE], int r, int c){
    bool up, down, left, right;
    if(r < 0 || r > SIZE-1 || c < 0 || c > SIZE-1 || currBoard[r][c] == 'p'){
        return true;
    }
    if(currBoard[r][c] == '.'){
        return false;
    }
    if(currBoard[r][c] == 'b'){
        return true;
    }

    currBoard[r][c] = 'p';

    up    = whiteCaptured(currBoard, r-1, c);
    down  = whiteCaptured(currBoard, r+1, c);
    left  = whiteCaptured(currBoard, r, c-1);
    right = whiteCaptured(currBoard, r, c+1);

    currBoard[r][c] = 'w';

    if(up && down && left && right){
        return true;
    }
    return false;
}
bool blackCaptured(char currBoard[][SIZE], int r, int c){
    bool up, down, left, right;
    if(r < 0 || r > SIZE-1 || c < 0 || c > SIZE-1 || currBoard[r][c] == 'p'){
        return true;
    }
    if(currBoard[r][c] == '.'){
        return false;
    }
    if(currBoard[r][c] == 'w'){
        return true;
    }

    currBoard[r][c] = 'p';

    up    = blackCaptured(currBoard, r-1, c);
    down  = blackCaptured(currBoard, r+1, c);
    left  = blackCaptured(currBoard, r, c-1);
    right = blackCaptured(currBoard, r, c+1);

    currBoard[r][c] = 'b';

    if(up && down && left && right){
        return true;
    }
    return false;
}
bool surrondingCaptured(char currBoard[][SIZE], int r, int c, bool blackTurn){
    bool up = false, down = false, left = false, right = false;
    if(r > 0){
        if(blackTurn){
            if(currBoard[r-1][c] != 'b'){
                up    = whiteCaptured(currBoard, r-1, c);
            }
        }
        else{
            if(currBoard[r-1][c] != 'w'){
                up    = blackCaptured(currBoard, r-1, c);
            }
        }
    }
    if(r < SIZE-1){
        if(blackTurn){
            if(currBoard[r+1][c] != 'b'){
                down  = whiteCaptured(currBoard, r+1, c);
            }
        }
        else{
            if(currBoard[r+1][c] != 'w'){
                down  = blackCaptured(currBoard, r+1, c);
            }
        }
    }
    if(c > 0){
        if(blackTurn){
            if(currBoard[r][c-1] != 'b'){
                left  = whiteCaptured(currBoard, r, c-1);
            }
        }
        else{
            if(currBoard[r][c-1] != 'w'){
                left  = blackCaptured(currBoard, r, c-1);
            }
        }
    }
    if(c < SIZE-1){
        if(blackTurn){
            if(currBoard[r][c+1] != 'b'){
                right = whiteCaptured(currBoard, r, c+1);
            }
        }
        else{
            if(currBoard[r][c+1] != 'w'){
                right = blackCaptured(currBoard, r, c+1);
            }
        }
    }
    if(up || down || left || right){
        return true;
    }
    return false;
}
void checkCapture(char currBoard[][SIZE], bool blackTurn){
    bool captured[SIZE][SIZE];
    char checkedBoard[SIZE][SIZE];
    copyBoard(checkedBoard, currBoard);
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            captured[i][j] = spaceCaptured(checkedBoard, i, j, blackTurn);
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(captured[i][j]){
                if(blackTurn && currBoard[i][j] != 'b'){
                    currBoard[i][j] = '.';
                }
                if(!blackTurn && currBoard[i][j] != 'w'){
                    currBoard[i][j] = '.';
                }
            }
        }
    }
}

//Checking if play is valid
bool validPlay(char next[][SIZE], char past[][SIZE], char curr[][SIZE],
               int xCord, int yCord, int turn){
    bool validPlay;

    validPlay = !spaceCaptured(next, xCord, yCord, !isBlackTurn(turn));
    if(!validPlay){
        validPlay = surrondingCaptured(next, xCord, yCord, isBlackTurn(turn));
    }

    if(validPlay){
        checkCapture(next, isBlackTurn(turn));
        validPlay = false;
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(next[i][j] != past[i][j]){
                    validPlay = true;
                }
            }
        }
    }

    if(curr[xCord][yCord] != '.'){
        validPlay = false;
    }
    return validPlay;
}

//Scoring
bool scoredBlack(char currBoard[][SIZE], int r, int c){
    bool up, down, left, right;
    if(r < 0 || r > SIZE-1 || c < 0 || c > SIZE-1 || currBoard[r][c] == 'b'){
        return true;
    }
    if(currBoard[r][c] == 'w'){
        return false;
    }
    currBoard[r][c] = 'b';

    up    = scoredBlack(currBoard, r-1, c);
    down  = scoredBlack(currBoard, r+1, c);
    left  = scoredBlack(currBoard, r, c-1);
    right = scoredBlack(currBoard, r, c+1);
    if(up && down && left && right){
        return true;
    }
    return false;
}
bool scoredWhite(char currBoard[][SIZE], int r, int c){
    bool up, down, left, right;
    if(r < 0 || r > SIZE-1 || c < 0 || c > SIZE-1 || currBoard[r][c] == 'w'){
        return true;
    }
    if(currBoard[r][c] == 'b'){
        return false;
    }
    currBoard[r][c] = 'w';

    up    = scoredWhite(currBoard, r-1, c);
    down  = scoredWhite(currBoard, r+1, c);
    left  = scoredWhite(currBoard, r, c-1);
    right = scoredWhite(currBoard, r, c+1);
    if(up && down && left && right){
        return true;
    }
    return false;
}
void score(char currBoard[][SIZE]){
    int blackScore = 0, whiteScore = 0;
    char checkedBoard[SIZE][SIZE];
    copyBoard(checkedBoard, currBoard);
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(scoredBlack(checkedBoard, i, j)){
                blackScore++;
            }
            copyBoard(checkedBoard, currBoard);
            if(scoredWhite(checkedBoard, i, j)){
                whiteScore++;
            }
            copyBoard(checkedBoard, currBoard);
        }
    }

    cout << "Black Score: " << blackScore << endl;
    cout << "White Score: " << whiteScore << endl << endl;
}
void finalScore(char currBoard[][SIZE]){
    int blackScore = 0, whiteScore = 0;
    char checkedBoard[SIZE][SIZE];
    copyBoard(checkedBoard, currBoard);
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(scoredBlack(checkedBoard, i, j)){
                blackScore++;
            }
            copyBoard(checkedBoard, currBoard);
            if(scoredWhite(checkedBoard, i, j)){
                whiteScore++;
            }
            copyBoard(checkedBoard, currBoard);
        }
    }

    cout << "Black Score: " << blackScore << endl;
    cout << "White Score: " << whiteScore << endl;
    if(blackScore > whiteScore){
        cout << "Black wins!";
    }
    else if(blackScore < whiteScore){
        cout << "White wins!";
    }
    else{
        cout << "Tie";
    }
    cout << endl << endl;
}
