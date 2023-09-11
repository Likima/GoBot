#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <utility>

const int BOARD_SIZE = 8;

//implement a part of piece that is a bool that is true if it is fully surrounded
//implement a function that checks if a piece is fully surrounded

struct piece{
    int x;
    int y;
    int color = 0; // 0 = empty, 1 = black, 2 = white
    int type;
    bool surrounded = false;
    bool justPlaced = false;
};

class PlayingBoard{
    public:
        PlayingBoard(){
            std::vector<piece> row;
            piece empty;
            //empty.color;
            for(int x = 0; x<8; x++){
                for(int y = 0; y<8; y++){
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

        //std::vector<std::pair<int, int>> getLegal(int color){
        //    
        //}

        void printBoard(){
            for(int x = 0; x<8; x++){
                for(int y = 0; y<8; y++){
                    if(y == 0){std::cout<<" "<<8-x<<" ";}
                    if(board[x][y].color==0){std::cout<<" . ";}
                    else if(board[x][y].color==2){std::cout<<"\033[0;31m"<<" O "<<"\033[0m";}
                    else std::cout<<"\033[0;36m"<<" O "<<"\033[0m";
                }
                std::cout<<std::endl;
            }
            std::cout<<"   ";
            for(int i = 0; i<8; i++){
                std::cout<<" "<<i+1<<" ";
            }
            std::cout<<std::endl;
        }
        std::vector<std::vector<piece>> getBoard(){
            return board;
        }

    private:
        std::vector<std::vector<piece>> board;
};

#endif