/*---------------------------------------------------------------------------
--                               EtherChess                                -- 
-----------------------------------------------------------------------------
--                                                                         --
--  EtherChess is an example game for MaRTE OS.                            --
--                                                                         --
--  author:   Alvaro Garcia Cuesta                                         --
--  email:    alvaro@binarynonsense.com                                    --
--  website:  www.binarynonsense.com                                       --
--                                                                         --
--  file: main.h                                                           --
--                                                                         --
--  this file is the header for main.c                                     --
-----------------------------------------------------------------------------
--                               License                                  -- 
-----------------------------------------------------------------------------
--                                                                         --
-- EtherChess is free software; you can redistribute it and/or modify it   --
-- under the terms of the GNU General Public License version 2 as          -- 
-- published by the Free Software Foundation.                              --
-- See COPYING file for more info about the license                        --
--                                                                         --
-----------------------------------------------------------------------------
--                        last update: 09 Jun 09                           --
---------------------------------------------------------------------------*/

#ifndef MAIN_H
#define MAIN_H

#include "vga.h"
#include <assert.h> // assert
#include <time.h>   // timespec, nanosleep
#include <math.h>   // sin
#include <misc/timespec_operations.h>  // double_to_timespec
#include <misc/console_management.h> // reset_blocking.. set_raw_mode
#include <string.h> //memset

#include "img/bishop.h" 
#include "img/knight.h"
#include "img/pawn.h"
#include "img/rook.h"
#include "img/queen.h"
#include "img/king.h"

#include "draw.h"
#include "net.h"
#include "fonts.h"

#define PCI_DEVICE_ID_S3_TRIO64V2 35073

//VARIABLES///////////////////

int gameOver;
double period;
struct timespec period_ts;
int screenWidth,screenHeight;

unsigned char *backBuffer;
// 1/11     2/12     3/13     4/14      5/15    6/16
//pawn      rook    knight    bishop    king    queen
int initialChessboardWhites[8][8]={
    {12,11,0,0,0,0,1,2},
    {13,11,0,0,0,0,1,3},
    {14,11,0,0,0,0,1,4},
    {16,11,0,0,0,0,1,6},
    {15,11,0,0,0,0,1,5},
    {14,11,0,0,0,0,1,4},
    {13,11,0,0,0,0,1,3},
    {12,11,0,0,0,0,1,2}
    
};

int initialChessboardBlacks[8][8]={
    {2,1,0,0,0,0,11,12},
    {3,1,0,0,0,0,11,13},
    {4,1,0,0,0,0,11,14},
    {5,1,0,0,0,0,11,15},
    {6,1,0,0,0,0,11,16},
    {4,1,0,0,0,0,11,14},
    {3,1,0,0,0,0,11,13},
    {2,1,0,0,0,0,11,12}
    
};

int chessBoard[8][8];
int chessBoardY,chessBoardX;

int cursorX,cursorY;

int playerIsWhites;

int rookLeftMoved,rookRightMoved,kingMoved;

int playerWins;

//FUNCTIONS///////////////////

void init();

void move();

int gameLoop();

void reset_board();

void draw();

void movePiece();

void receivePiece();

int checkSelectedPiece();

int checkSelectedDestiny(int x1, int y1);

void checkIfGameOVer(int isPlayerMove,int killedPiece);


#endif
