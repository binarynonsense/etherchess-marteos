EtherChess for MaRTE OS
==================

EtherChess is a chess game for 2 players connected through ethernet 
for MaRTE OS. To play it you need two machines running the compiled 
program with a local ethernet link connecting them (or you can 
simulate this setup using virtual machines, with qemu for example).
    
License: GPL v2 (see COPYING file).

Video: https://www.youtube.com/watch?v=l5S4Zq712CE

/////////////////////////////////////////////////////

0- INSTALLATION:

First, you need to change the mac adresses in net.h 
(SERVER_MAC and CLIENT_MAC) to the ones corresponding to 
your machines. 

A makefile is provided to easily generate the program, however, 
you may need to change the path to the svga driver to the one 
corresponding to your MaRTE OS installation.

A bash script called qemu_ether.sh is provided to help you in case 
you want to try it using qemu (you need a qemu image called disk.img
including the program in order for it to work, check the MARTE OS 
webpage tutorials if you need help with this).

This is the version I made in 2009, the qemu test doesn't seem to work anymore, I'll have to look into it.

1- BASIC CONTROLS:

Use the arrow keys to move to the piece you want to move, press intro 
to select it; use the arrow keys to go to the place you want to move the 
piece to, press intro to move the piece (the piece will only move if the 
destination is valid).

To deselect a piece, move to it and press intro.

To do a castling movement you need to select the king and move it to 
the rook, the other way around doesn't work.

Hope you enjoy the game!!!!
Alvaro.
