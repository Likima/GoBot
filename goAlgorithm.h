#ifndef GOALGORITHM_H
#define GOALGORITHM_H
#include "board.h"
#include <random>

std::pair<int, int> bestMove;

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

int alphaBeta(PlayingBoard &board, int depth, int alpha, int beta, int player){
    if(boardIsFull(board)){
        if (getIndividualScores(board).first > getIndividualScores(board).second){
            return INT_MAX;
        }
        else if (getIndividualScores(board).first < getIndividualScores(board).second){
            return INT_MIN;
        }
        else{
            return 0;
        }
    }
    
    if(depth == 0){
        return evaluatePos(board, player);
    }
    
    std::vector<std::pair<int, int>> legalMoves = getAllLegalMoves(board.getBoard(), player);

    if(legalMoves.size() == 0){
        return evaluatePos(board, player);
    }

    int maxEval, minEval;
    int value = 0;

    if(player == 1){
        maxEval = INT_MIN;
        for(auto& i : legalMoves){
            board.placePiece(8-i.second, i.first-1, player);
            value = alphaBeta(board, depth-1, alpha, beta, 2);
            if(value>maxEval){
                maxEval = std::max(maxEval, value);
                if(depth == DEPTH){
                    bestMove = i;
                }
            }
            board.removePiece(8-i.second, i.first-1);
            
            if(beta <= alpha){
                break;
            }
            alpha = std::max(alpha, value);
        }
        return maxEval;
    }

    else{
        minEval = INT_MAX;
        for(auto& i : legalMoves){
            board.placePiece(8-i.second, i.first-1, player);
            value = alphaBeta(board, depth-1, alpha, beta, 2);
            if(value<minEval){
                maxEval = std::min(minEval, value);
                if(depth == DEPTH){
                    bestMove = i;
                }
            }
            board.removePiece(8-i.second, i.first-1);
            
            if(beta <= alpha){
                break;
            }
            beta = std::min(beta, value);
        }
        return minEval;
    }
}

std::pair<int, int> chooseMove(PlayingBoard& board, int color){
    std::vector<std::pair<int, int>> legalMoves = getAllLegalMoves(board.getBoard(), color);
    //for(int x = 0; x<legalMoves.size(); x++){
    //    legalMoves[x].first = 8-legalMoves[x].first;
    //    legalMoves[x].second;
    //}
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, legalMoves.size()-1);
    alphaBeta(board, DEPTH, INT_MIN, INT_MAX, color);
    return(bestMove);
}

#endif