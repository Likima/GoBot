#ifndef GOALGORITHM_H
#define GOALGORITHM_H
#include "board.h"

std::pair<int, int> getIndividualScores(std::vector<std::vector<piece>> board){
    int firstScore = 0; int secondScore = 0;
    for(int x = 0; x<8; x++){
        for(int y = 0; y<8; y++){
            if(board[x][y].color == 1) firstScore++;
            else if(board[x][y].color == 2) secondScore++;
        }
    }
    return(std::make_pair(firstScore, secondScore));
}

int evaluatePos(std::vector<std::vector<piece>> board, int color){
    return(getIndividualScores(board).first - getIndividualScores(board).second);
}

#endif