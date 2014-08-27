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
--  file: fonts.h                                                          --
--                                                                         --
--  this file contains the functions used to print strings                 --
--  using a bitmap font                                                    --
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

void bmpfont_print(char *theString, int x, int y,int color,unsigned char *backBuffer);
