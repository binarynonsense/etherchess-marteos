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
--  file: net.h                                                            --
--                                                                         --
--  this file contains the network related functions declarations          --
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

#ifndef NET_H
#define NET_H

#include <assert.h>
#include <drivers/if_ether.h>
#include <drivers/eth_ioctl.h>
#include <drivers/osdep.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
        struct ethhdr header;
        unsigned char data[ETH_DATA_LEN];
} eth_frame_t;

#define LOGGER_PROTOCOL 0x1010

#define SERVER_MAC "00:30:64:07:A2:60"
#define CLIENT_MAC "00:30:64:06:B5:F2" //"FF:FF:FF:FF:FF:FF" // "00:30:64:05:74:73"

int err, fd, count;
eth_frame_t eth_frame, read_frame;
struct ether_addr src_mac, dest_mac;
bool isServer;
char mac_str[18];
char msg[10];
unsigned short protocol;

//FUNCTIONS

int init_net();
void sendMovement(int x1, int y1, int x2, int y2);
int receiveMovement();
inline void swapCoordinates(int *coord);

#endif
