//Mason Crippen
//Jack Fontenot
//Connor Griffin
//Andrei Kuvshinikov

#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

#include "SDL_Plotter.h"
#include "token.h"
#include "grid.h"

//Turn
bool isBlackTurn(int turn);

//Pass
void turnPassed(int turn);

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
