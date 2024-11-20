#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

const int SIZE = 5;

isBlackTurn(int turn){
    return (turn % 2 == 0);
}

bool spaceCaptured(char currBoard[][SIZE], int r, int c, bool blackTurn){
    bool up, down, left, right;
    if(r == -1 || r == SIZE || c == -1 || c == SIZE || currBoard[r][c] == 'p'){
        return true;
    }
    if(currBoard[r][c] == '.'){
        return false;
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
    if(blackTurn){
        currBoard[r][c] = 'w';
    }
    else{
        currBoard[r][c] = 'b';
    }
    if(up && down && left && right){
        return true;
    }
    return false;
}

void checkCapture(char currBoard[][SIZE], bool blackTurn){
    bool captured[SIZE][SIZE];
    char checkedBoard[SIZE][SIZE];
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            checkedBoard[i][j] = currBoard[i][j];
        }
    }
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



bool surrondingCaptured(char currBoard[][SIZE], int r, int c, bool blackTurn){
    bool up = false, down = false, left = false, right = false;
    if(r-1 >= 0){
        up    = spaceCaptured(currBoard, r-1, c, blackTurn);
    }
    if(r+1 < SIZE){
        down  = spaceCaptured(currBoard, r+1, c, blackTurn);
    }
    if(c-1 >= 0){
        left  = spaceCaptured(currBoard, r, c-1, blackTurn);
    }
    if(c+1 < SIZE){
        right = spaceCaptured(currBoard, r, c+1, blackTurn);
    }
    if(up || down || left || right){
        return true;
    }
    return false;
}

validPlay(char nextBoard[][SIZE], char pastBoard[][SIZE], char currBoard[][SIZE], int xCord, int yCord, int turn){
    bool validPlay;

    validPlay = !spaceCaptured(nextBoard, xCord, yCord, !isBlackTurn(turn));
    if(!validPlay){
        validPlay = surrondingCaptured(nextBoard, xCord, yCord, isBlackTurn(turn));
    }

    if(validPlay){
        checkCapture(nextBoard, isBlackTurn(turn));
        validPlay = false;
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(nextBoard[i][j] != pastBoard[i][j]){
                    validPlay = true;
                }
            }
        }
    }

    if(currBoard[xCord][yCord] != '.'){
        validPlay = false;
    }
    return validPlay;
}

copyBoard(char newBoard[][SIZE], char copiedBoard[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            newBoard[i][j] = copiedBoard[i][j];
        }
    }
}

printBoard(char board[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

createBoard(char board[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            board[i][j] = '.';
        }
    }
}


#endif // RULES_H_INCLUDED
