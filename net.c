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
--  file: net.c                                                            --
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

//net code based on the marteos ethernet code example by sangorrin :)

#include "net.h"

int init_net(){
    
    protocol = LOGGER_PROTOCOL;
    
    fd = open("/dev/eth0", O_RDWR);
    assert(fd != -1);

    err = ioctl(fd, ETH_HWADDR, src_mac.ether_addr_octet);
    assert(err == 0);

    err = ioctl(fd, SET_PROTOCOL_FILTER, (void *)&protocol);
    assert(err == 0);

    ether_ntoa (&src_mac, mac_str);

    err = ether_aton(SERVER_MAC, &dest_mac);
    assert(err == 0);

    isServer = (memcmp(&dest_mac, &src_mac, sizeof(src_mac)) == 0);
    
    if (isServer) {//is the server
        err = ether_aton(CLIENT_MAC, &dest_mac);
        assert(err == 0);
        return 1;
    }else{//is client
        return 0;
    }
    
}

void sendMovement(int x1, int y1, int x2, int y2){
    
    char msg[4];
    int temp;
    //the other board is all the way around so i have to mirror the coordinates
    swapCoordinates(&x1);
    swapCoordinates(&y1);
    swapCoordinates(&x2);
    swapCoordinates(&y2);
    
    temp=1000*x1+100*y1+10*x2+y2;
    sprintf(msg,"%d",temp);
    
    *(struct ether_addr * )eth_frame.header.h_dest = dest_mac;
    *(struct ether_addr * )eth_frame.header.h_source = src_mac;
    eth_frame.header.h_proto= htons(LOGGER_PROTOCOL);
    strncpy(eth_frame.data, msg, sizeof(msg));

    ether_ntoa (&dest_mac, mac_str);
    
    //SEND THE DATA!!!!
    count = write(fd, &eth_frame, sizeof(eth_frame));
    assert (count > 0);
    
}

int receiveMovement(){
    
    count = read(fd, &read_frame, ETH_FRAME_LEN);
    assert (count > 0);
    ether_ntoa (&read_frame.header.h_source, mac_str);
    return atoi(read_frame.data);
    
}

inline void swapCoordinates(int *coord){
    *coord=abs(*coord-7);
}
