#ifndef GOALGORITHM_H
#define GOALGORITHM_H
#include "board.h"
#include <random>

std::pair<int, int> getIndividualScores(PlayingBoard& board){
    int firstScore = 0; int secondScore = 0;
    for(int x = 0; x<8; x++){
        for(int y = 0; y<8; y++){
            if(board.getBoard()[x][y].color == 1) firstScore++;
            else if(board.getBoard()[x][y].color == 2) secondScore++;
        }
    }
    return(std::make_pair(firstScore, secondScore));
}

int evaluatePos(PlayingBoard& board, int color){
    return(getIndividualScores(board).first - getIndividualScores(board).second);
}

std::pair<int, int> chooseMove(PlayingBoard& board, int color){
    std::vector<std::pair<int, int>> legalMoves = getAllLegalMoves(board.getBoard(), color);
    for(int x = 0; x<legalMoves.size(); x++){
        legalMoves[x].first--;
        legalMoves[x].second--;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, legalMoves.size()-1);
    return(legalMoves[dis(gen)]);
}

#endif