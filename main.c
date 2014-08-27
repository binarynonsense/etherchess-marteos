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
--  file: main.c                                                           --
--                                                                         --
--  this file contains the main logic of the game                          --
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

#include "main.h"

int main(void){
    
    init();
    gameLoop();
    return 0;
}

/////////////////////////////////////////////////    
int gameLoop(){
    
    if(playerIsWhites){        
        while(!gameOver){                 
            movePiece();
            if(gameOver)break;
            receivePiece();
        }
    }else{        
        while(!gameOver){
            receivePiece();
            if(gameOver)break;
            movePiece();
        }
    }
    //THE END 
    draw();
    if(playerWins){
        bmpfont_print("YOU WIN!", screenWidth/2-8*4,screenHeight/2-8,231,backBuffer);
    }else{
        bmpfont_print("YOU LOSE", screenWidth/2-8*4,screenHeight/2-8,231,backBuffer);
    }
    blit(backBuffer,screenWidth,screenHeight);//swap buffers
    while(getchar()==-1){
    }
    

    
    return 0;
}

/////////////////////////////////////////////////    
void init(){

    period = 1.0/30.0;
    //period_ts = double_to_timespec(period);  //old versions of MaRTE OS
    double_to_timespec(period,&period_ts); //new versions of MaRTE OS
    
    //make getchar() non-blocking:
    reset_blocking_mode ();
    set_raw_mode ();
    
    ////init vga///////////////////////////
    screenWidth=320;
    screenHeight=200;
    int ret = init_vga(G320x200x256, VGA, PCI_DEVICE_ID_S3_TRIO64V2);
    assert (ret == 0); 
    backBuffer = (unsigned char *)malloc(screenWidth*screenHeight);//virtual canvas for blitting
    memset(backBuffer, 0, screenWidth*screenHeight);
    //////////////////////////////////////
    
    initPalette();//fill palette's colors

    chessBoardY=20;
    //chessBoardX=screenWidth/2-20*8/2;
    chessBoardX=20;
    
    
    piecesImages[0]=pawn_img;
    piecesImages[1]=rook_img;
    piecesImages[2]=knight_img;
    piecesImages[3]=bishop_img;
    piecesImages[4]=king_img;
    piecesImages[5]=queen_img;
    
    cursorX=4;
    cursorY=4;
    //NET
    playerIsWhites=init_net();
    reset_board();
    
    playerWins=0;
    
    //needed for castling
    rookLeftMoved=0;
    rookRightMoved=0;
    kingMoved=0;
    
    gameOver = 0;
     
}

void reset_board(){
    int x,y;
    for(x=0;x<8;x++){
        for(y=0;y<8;y++){
            if(playerIsWhites){//whites
                chessBoard[x][y]=initialChessboardWhites[x][y];
            }else{
                chessBoard[x][y]=initialChessboardBlacks[x][y];
            }
        }
    }
}

void draw(){
    bmpfont_print("EtherChess", 200, screenHeight-16-20,240,backBuffer);
    draw_board(backBuffer,screenWidth,chessBoardX,chessBoardY);
    draw_pieces(backBuffer,screenWidth,chessBoard,chessBoardX,chessBoardY);
}

void movePiece(){
    
    int validMovement=0;
    int x1=-1,y1,x2=-1,y2;
    int pieceSelected=0;
    int killedPiece;
    
    bmpfont_print("Your turn      ", 200, 20,87,backBuffer);
    
    while(!validMovement){
        
        draw();
        draw_cursor(backBuffer,screenWidth,chessBoardX,chessBoardY,cursorX,cursorY);
        if(pieceSelected){
            draw_selected(backBuffer,screenWidth,chessBoardX,chessBoardY,x1,y1);
        }
        blit(backBuffer,screenWidth,screenHeight);//swap buffers
        
        //check keyboard
        char key;
        key=getchar();
        //flush buffer
        while(getchar()!=-1){
        }
        
        if (key=='w' || key=='8'){//move up
            if(cursorY>0)cursorY--;
        }else if (key=='s' || key=='2'){//move down
            if(cursorY<7)cursorY++;
        }else if (key=='d' || key=='6'){//move right
            if(cursorX<7)cursorX++;
        }else if (key=='a' || key=='4'){//move left
            if(cursorX>0)cursorX--;
        }else if (key=='\n' || key=='5'){//enter
            if(x1==-1){//no piece selected yet
                if(checkSelectedPiece()){//check if valid piece
                    x1=cursorX;
                    y1=cursorY;
                    pieceSelected=chessBoard[cursorX][cursorY];
                }
            }else{//select destiny pending 
                if((cursorX==x1)&&(cursorY==y1)){//deselect piece
                    pieceSelected=0;
                    x1=-1;
                }else if(checkSelectedDestiny(x1,y1)){//check if valid movement 
                    x2=cursorX;
                    y2=cursorY;
                    validMovement=1;
                    killedPiece=chessBoard[x2][y2];
                    chessBoard[x2][y2]=chessBoard[x1][y1];
                    chessBoard[x1][y1]=0;
                    pieceSelected=0;
                    checkIfGameOVer(1,killedPiece);
                }
            }
            
        } 
        
    }
    sendMovement(x1,y1,x2,y2);
}

void receivePiece(){
    int x1,y1,x2,y2,temp,killedPiece;
    bmpfont_print("Waiting...     ", 200, 20,87,backBuffer);
    draw();
    blit(backBuffer,screenWidth,screenHeight);//swap buffers
        
    temp=receiveMovement();
    x1=temp/1000;
    y1=(temp-x1*1000)/100;
    x2=(temp-x1*1000-y1*100)/10;
    y2=(temp-x1*1000-y1*100-x2*10);
    killedPiece=chessBoard[x2][y2];
    chessBoard[x2][y2]=chessBoard[x1][y1];
    chessBoard[x1][y1]=0;
    checkIfGameOVer(0,killedPiece);
}

int checkSelectedPiece(){
    if(playerIsWhites && (chessBoard[cursorX][cursorY]>0) && (chessBoard[cursorX][cursorY]<7) ){
        return 1;
    }else if(!playerIsWhites && (chessBoard[cursorX][cursorY]>10) && (chessBoard[cursorX][cursorY]<17) ){
        return 1;
    }else{
        return 0;
    }
    
}

int checkSelectedDestiny(int x1, int y1){
    int diffX,diffY,x,y;
    
    if( (playerIsWhites && (chessBoard[cursorX][cursorY]<9) && (chessBoard[cursorX][cursorY]!=0)) 
        || (!playerIsWhites && (chessBoard[cursorX][cursorY]>10) ) ){

        //CASTLING
        if( (chessBoard[x1][y1]==5 && chessBoard[cursorX][cursorY]==2) 
            || (chessBoard[x1][y1]==15 && chessBoard[cursorX][cursorY]==12)){
            
            if(!kingMoved && !rookLeftMoved && cursorX==0 && cursorY==7){
                
                for (x=1;x<x1;x++){
                    if(chessBoard[x][7]!=0){return 0;}//bad move
                }
                //do castling
                //move king
                chessBoard[x1-2][y1]=chessBoard[x1][y1];
                chessBoard[x1][y1]=0;                
                //move rook
                chessBoard[x1-1][cursorY]=chessBoard[cursorX][cursorY];
                chessBoard[cursorX][cursorY]=0;
                
                kingMoved=1;
                rookLeftMoved=1;
                
            }else if(!kingMoved && !rookRightMoved && cursorX==7 && cursorY==7){
                
                for (x=x1+1;x<7;x++){
                    if(chessBoard[x][7]!=0){return 0;}//bad move
                }
                //do castling
                //move king
                chessBoard[x1+2][y1]=chessBoard[x1][y1];
                chessBoard[x1][y1]=0;                
                //move rook
                chessBoard[x1+1][cursorY]=chessBoard[cursorX][cursorY];
                chessBoard[cursorX][cursorY]=0;
                
                kingMoved=1;
                rookRightMoved=1;
                
            }else{return 0;}//NO CASTLING, SO BAD MOVE
            return 1;//castling done, trick
            
        }else{//NO CASTLING, SO BAD MOVE
            return 0;
        }
    }
    
    diffX=cursorX-x1;
    diffY=y1-cursorY;
    
    switch(chessBoard[x1][y1]){
        
        // 1/11     2/12     3/13     4/14      5/15    6/16
        //pawn      rook    knight    bishop    king    queen
        
        case 1://PAWN
        case 11:          
            if(diffY<0){
                return 0;
            }else if(diffY==1 && abs(diffX)==1 && chessBoard[cursorX][cursorY]!=0){
                break;//move one in angle to eat piece
            }else if(diffY==1 && diffX==0){
                break;
            }else if(diffY==2 && diffX==0 && y1==6 && chessBoard[x1][y1-1]==0 && chessBoard[cursorX][cursorY]==0){//can move 
                break;
            }else{
                return 0;
            }
            break;
            
        case 2://ROOK
        case 12:
            if( (diffX!=0 && diffY==0) || (diffY!=0 && diffX==0)){
                if(diffX>0){
                    for (x=x1+1;x<cursorX;x++){
                        if(chessBoard[x][y1]!=0){return 0;}
                    }
                }else if(diffX<0){
                    for (x=x1-1;x>cursorX;x--){
                        if(chessBoard[x][y1]!=0){return 0;}
                    }
                }if(diffY<0){
                    for (y=y1+1;y<cursorY;y++){
                        if(chessBoard[x1][y]!=0){return 0;}
                    }
                }else if(diffY>0){
                    for (y=y1-1;y>cursorY;y--){
                        if(chessBoard[x1][y]!=0){return 0;}
                    }
                }
                if(!rookLeftMoved || !rookRightMoved){//for castling
                    if(x1==0 && y1==7){rookLeftMoved=1;}
                    if(x1==7 && y1==7){rookRightMoved=1;}
                }
                break;
            }else{
                return 0;
            }
        case 3://KNIGHT
        case 13:
            if(abs(diffX)==2 && abs(diffY)==1){
                break;
            }else if(abs(diffY)==2 && abs(diffX)==1){
                break;
            }else{
                return 0;
            }
            break;
        case 4://BISHOP
        case 14:
            if( (diffX!=0 && diffY!=0 && abs(diffX)==abs(diffY))){
                if(diffX>0 && diffY>0){//up right
                    for (x=1;x<abs(diffX);x++){
                        if(chessBoard[x1+x][y1-x]!=0){return 0;}
                    }
                }else if(diffX<0 && diffY>0){//up left
                    for (x=1;x<abs(diffX);x++){
                        if(chessBoard[x1-x][y1-x]!=0){return 0;}
                    }
                }else if(diffX>0 && diffY<0){//down right
                    for (x=1;x<abs(diffX);x++){
                        if(chessBoard[x1+x][y1+x]!=0){return 0;}
                    }
                }else if(diffX<0 && diffY<0){//down left
                    for (x=1;x<abs(diffX);x++){
                        if(chessBoard[x1-x][y1+x]!=0){return 0;}
                    }
                }
            }else{
                return 0;
            }
            break;
        case 5://KING
        case 15:
            if(abs(diffX)<=1 && abs(diffY)<=1){
                if(!kingMoved){kingMoved=1;}//for castling
                break;
            }else{
                return 0;
            }
            break;
        case 6://QUEEN
        case 16:
            //bishop movement
            if( (diffX!=0 && diffY!=0 && abs(diffX)==abs(diffY))){
                if(diffX>0 && diffY>0){//up right
                    for (x=1;x<abs(diffX);x++){
                        if(chessBoard[x1+x][y1-x]!=0){return 0;}
                    }
                }else if(diffX<0 && diffY>0){//up left
                    for (x=1;x<abs(diffX);x++){
                        if(chessBoard[x1-x][y1-x]!=0){return 0;}
                    }
                }else if(diffX>0 && diffY<0){//down right
                    for (x=1;x<abs(diffX);x++){
                        if(chessBoard[x1+x][y1+x]!=0){return 0;}
                    }
                }else if(diffX<0 && diffY<0){//down left
                    for (x=1;x<abs(diffX);x++){
                        if(chessBoard[x1-x][y1+x]!=0){return 0;}
                    }
                }
            }else if( (diffX!=0 && diffY==0) || (diffY!=0 && diffX==0)){//tower movement
                if(diffX>0){
                    for (x=x1+1;x<cursorX;x++){
                        if(chessBoard[x][y1]!=0){return 0;}
                    }
                }else if(diffX<0){
                    for (x=x1-1;x>cursorX;x--){
                        if(chessBoard[x][y1]!=0){return 0;}
                    }
                }if(diffY<0){
                    for (y=y1+1;y<cursorY;y++){
                        if(chessBoard[x1][y]!=0){return 0;}
                    }
                }else if(diffY>0){
                    for (y=y1-1;y>cursorY;y--){
                        if(chessBoard[x1][y]!=0){return 0;}
                    }
                }
            }else{
                return 0;
            }
            break;
            
            
        default:
            break;
    }
    return 1;
}

void checkIfGameOVer(int isPlayerMove,int killedPiece){
    if(killedPiece==5 || killedPiece==15){
        gameOver=1;
        if(isPlayerMove){
            playerWins=1;
        }
    }
}
