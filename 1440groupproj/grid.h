//Mason Crippen
//Jack Fontenot
//Connor Griffin
//Andrei Kuvshinikov

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "config.h"

//building boards
void copyBoard(char newBoard[][SIZE], char copiedBoard[][SIZE]);
void drawBoard(char board[][SIZE]);
void createBoard(char board[][SIZE]);
void drawBoard(SDL_Plotter& g, token tokenBoard[][SIZE]);
void drawGrid(SDL_Plotter& g);
void createTokenBoard(char currBoard[][SIZE], token tokenBoard[][SIZE]);
void updateTokenBoard(char currBoard[][SIZE], token tokenBoard[][SIZE]);

#endif // GRID_H_INCLUDED
