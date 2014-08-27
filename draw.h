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
--  file: draw.h                                                           --
--                                                                         --
--  this file contains the draw functions declarations                     --
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

#ifndef DRAW_H
#define DRAW_H

int *piecesImages[6];

void initPalette();

void draw_board(unsigned char *backBuffer,int screenWidth,int chessBoardX, int chessBoardY);

void draw_pieces(unsigned char *backBuffer,int screenWidth, int chessBoard[8][8],int chessBoardX, int chessBoardY);

void draw_cursor(unsigned char *backBuffer,int chessBoardX, int chessBoardY,int screenWidth,int cursorX,int cursorY);

void draw_selected(unsigned char *backBuffer,int chessBoardX, int chessBoardY,int screenWidth,int x1,int y1);

void blit(unsigned char *backBuffer,int screenWidth,int screenHeight);

#endif

