#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

const int SIZE = 19;
const int BOARDSIZE = 760;
const int SIDE = BOARDSIZE / SIZE;
const color emptyColor(220, 220, 220);
const color whiteColor(255, 255, 255);
const color blackColor(0, 0, 0);
const color boardColor(227, 166, 86);

//Turn
bool isBlackTurn(int turn);

//Pass
void turnPassed(int turn);

//building boards
void copyBoard(char newBoard[][SIZE], char copiedBoard[][SIZE]);
void drawBoard(char board[][SIZE]);
void createBoard(char board[][SIZE]);
void drawBoard(SDL_Plotter& g, token tokenBoard[][SIZE]);
void createTokenBoard(char currBoard[][SIZE], token tokenBoard[][SIZE]);
void updateTokenBoard(char currBoard[][SIZE], token tokenBoard[][SIZE]);

//Checking for captures
bool spaceCaptured(char currBoard[][SIZE], int r, int c, bool blackTurn);
bool whiteCaptured(char currBoard[][SIZE], int r, int c);
bool blackCaptured(char currBoard[][SIZE], int r, int c);
bool surrondingCaptured(char currBoard[][SIZE], int r, int c, bool blackTurn);
void checkCapture(char currBoard[][SIZE], bool blackTurn);

//Checking if play is valid
bool validPlay(char next[][SIZE], char past[][SIZE], char curr[][SIZE],
               int xCord, int yCord, int turn);

//Scoring
bool scoredBlack(char currBoard[][SIZE], int r, int c);
bool scoredWhite(char currBoard[][SIZE], int r, int c);
void score(char currBoard[][SIZE]);
void finalScore(char currBoard[][SIZE]);

#endif // RULES_H_INCLUDED
