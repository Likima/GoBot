#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

struct piece{
    int x;
    int y;
    int color = 0; // 0 = empty, 1 = black, 2 = white
    int type;
};

class PlayingBoard{
    public:
        PlayingBoard(){
            std::vector<piece> row;
            piece empty;
            //empty.color;
            for(int x = 0; x<8; x++){
                for(int y = 0; y<8; y++){
                    //if((x == 3 && y == 3) || (x == 4 && y == 4)){
                    //    empty.color = 2;
                    //}
                    //else if((x == 3 && y == 4) || (x == 4 && y == 3)){
                    //    empty.color = 1;
                    //}
                    //else empty.color = 0;
                    empty.x = x;
                    empty.y = y;
                    row.emplace_back(empty);
                }
                board.emplace_back(row);
            }
            placePiece(3,3,2);
            placePiece(4,4,2);
            placePiece(3,4,1);
            placePiece(4,3,1);
        }

        void placePiece(int x, int y, int color){
            board[x][y].color = color;
        }

        void printBoard(){
            for(int x = 0; x<8; x++){
                for(int y = 0; y<8; y++){
                    if(board[x][y].color==0){std::cout<<" . ";}
                    else if(board[x][y].color==1){std::cout<<"\033[0;31m"<<" O "<<"\033[0m";}
                    else std::cout<<"\033[0;36m"<<" O "<<"\033[0m";
                }
                std::cout<<std::endl;
            }
        }

    private:
        std::vector<std::vector<piece>> board;
};

#endif