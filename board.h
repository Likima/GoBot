#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <utility>

const int BOARD_SIZE = 8;
const int DEPTH = 3;


//implement a part of piece that is a bool that is true if it is fully surrounded
//implement a function that checks if a piece is fully surrounded
class PlayingBoard;
struct piece{
    int x;
    int y;
    int color = 0; // 0 = empty, 1 = black, 2 = white
    int type;
    bool surrounded = false;
    bool justPlaced = false;
    std::pair<int, int> changedBy;
};

std::vector<std::pair<int, int>> getAllLegalMoves(const std::vector<std::vector<piece>>&, int);
bool boardIsFull(PlayingBoard);

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
            board[x][y].justPlaced = true;
        }

        //std::vector<std::pair<int, int>> getLegal(int color){
        //    
        //}

        void printBoard(){
            for(int x = 0; x<8; x++){
                for(int y = 0; y<8; y++){
                    if(y == 0){std::cout<<" "<<8-x<<" ";}
                    if(board[x][y].color==0){std::cout<<" . ";}
                    else if(board[x][y].color==1){std::cout<<"\033[0;31m"<<" O "<<"\033[0m";}
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

        void flipPieces(int color){
            int oppositeColor = color == 1 ? 2 : 1;
            int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            for(int x = 0; x<8; x++){
                for(int y = 0; y<8; y++){
                    if(board[x][y].justPlaced){
                        for(int dir = 0; dir<8; dir++){
                            int r = x + dr[dir];
                            int c = y + dc[dir];
                            bool hasOpponentPieceBetween = false;
                            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c].color == oppositeColor) {
                                r += dr[dir];
                                c += dc[dir];
                                hasOpponentPieceBetween = true;
                            }
                            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && hasOpponentPieceBetween && board[r][c].color == color) {
                                r = x + dr[dir];
                                c = y + dc[dir];
                                while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c].color == oppositeColor) {
                                    board[r][c].color = color;
                                    board[r][c].changedBy = std::make_pair(x, y);
                                    r += dr[dir];
                                    c += dc[dir];
                                }
                            }
                        }
                    }
                    board[x][y].justPlaced = false;
                }
            }
        }
        void removePiece(int x, int y){
            board[x][y].color = 0;
            for(int x = 0; x<8; x++){
                for(int y = 0; y<8; y++){
                    if (board[x][y].changedBy.first == x && board[x][y].changedBy.second == y) {
                        board[x][y].color = board[x][y].color == 1 ? 2 : 1;
                        board[x][y].changedBy = std::make_pair(-1, -1);
                    }
                }
            }
        }

    private:
        std::vector<std::vector<piece>> board;
};

#endif