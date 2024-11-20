#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

const int SIZE = 19;

//Turn
isBlackTurn(int turn){
    return (turn % 2 == 0);
}

//building boards
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

//Checking for captures
bool spaceCaptured(char currBoard[][SIZE], int r, int c, bool blackTurn){
    bool up, down, left, right;
    if(r < 0 || r > SIZE-1 || c < 0 || c > SIZE-1 || currBoard[r][c] == 'p'){
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
bool surrondingCaptured(char currBoard[][SIZE], int r, int c, bool blackTurn){
    bool up = false, down = false, left = false, right = false;
    if(r > 0 && r < SIZE-1 && c > 0 && c < SIZE-1){
        up    = spaceCaptured(currBoard, r-1, c, blackTurn);
        down  = spaceCaptured(currBoard, r+1, c, blackTurn);
        left  = spaceCaptured(currBoard, r, c-1, blackTurn);
        right = spaceCaptured(currBoard, r, c+1, blackTurn);
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
validPlay(char next[][SIZE], char past[][SIZE], char curr[][SIZE], int xCord, int yCord, int turn){
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

    cout << endl << endl;
    cout << "Black Score: " << blackScore << endl;
    cout << "White Score: " << whiteScore << endl;
}

#endif // RULES_H_INCLUDED
