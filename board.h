#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

struct piece{
    int x;
    int y;
    int color; // 0 = empty, 1 = black, 2 = white
    int type;
};

class PlayingBoard{
    public:
        PlayingBoard(){
            std::vector<piece> row;
            piece empty;
            empty.color = 0;
            for(int x = 0; x<9; x++){
                for(int y = 0; y<9; y++){
                    empty.color = 0;
                    empty.x = x;
                    empty.y = y;
                    row.emplace_back(empty);
                }
                board.emplace_back(row);
            }
        }
        void printBoard(){
            for(int x = 0; x<9; x++){
                for(int y = 0; y<9; y++){
                    if(board[x][y].color==0){std::cout<<" . ";}
                    else if(board[x][y].color==1){std::cout<<"\033[0;31m"<<" O "<<"\033[0m";}
                    else std::cout<<"\033[0;36m"<<" O "<<"\033[0m";
                }
                std::cout << std::endl;
            }
        }

    private:
        std::vector<std::vector<piece>> board;
};

#endif