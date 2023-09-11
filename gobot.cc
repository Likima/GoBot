#include "board.h"
#include "goAlgorithm.h"
//realized that this is not go, this is reversi

bool boardIsFull(PlayingBoard board){
    for(int x = 0; x<8; x++){
        for(int y = 0; y<8; y++){
            if(board.getBoard()[x][y].color==0){return false;}
        }
    }
    return true;
}

bool isValidMove(const std::vector<std::vector<piece>>& board, int row, int col, int player) {
    if (board[row][col].color != 0) return false; // Check if the cell is empty

    const int opponent = (player == 1) ? 2 : 1;

    // Directions for checking all eight possible directions (horizontally, vertically, and diagonally)
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int dir = 0; dir < 8; ++dir) {
        int r = row + dr[dir];
        int c = col + dc[dir];
        bool hasOpponentPieceBetween = false;

        while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c].color == opponent) {
            r += dr[dir];
            c += dc[dir];
            hasOpponentPieceBetween = true;
        }

        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && hasOpponentPieceBetween && board[r][c].color == player) {
            return true;
        }
    }

    return false;
}

std::vector<std::pair<int, int>> getAllLegalMoves(const std::vector<std::vector<piece>>& board, int player) {
    std::vector<std::pair<int, int>> legalMoves;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (isValidMove(board, row, col, player)) {
                legalMoves.emplace_back(std::make_pair(col+1, 8-row));
            }
        }
    }

    return legalMoves;
}


int main(){
    PlayingBoard board;
    int col, row;
    int turn = 1;
    board.printBoard();
    std::cout<<"You are "<<"\033[0;31m"<<"RED"<<"\033[0m"<<std::endl;
    while(!boardIsFull(board)){
        std::vector<std::pair<int, int>> legalMoves = getAllLegalMoves(board.getBoard(), turn%2+1);

        if(legalMoves.size()==0){
            std::cout<<"No legal moves for player "<<turn%2+1<<std::endl;
            turn++;
            continue;
        }

        if(turn%2+1 == 1){
            std::cout<<"Enter column: ";
            std::cin>>col;
            std::cout<<"Enter row: ";
            std::cin>>row;

            //if(col == 99){
            //    for(int i = 0; i<legalMoves.size(); i++){
            //        std::cout<<"["<<legalMoves[i].first<<", "<<legalMoves[i].second<<"] ";
            //    }
            //    std::cout<<std::endl;
            //}

            if(col>8 || col<1 || row>8 || row<1){
                std::cout<<"Invalid move"<<std::endl;
                continue;
            }

            if(isValidMove(board.getBoard(), 8-row, col-1, turn%2+1)){
                board.placePiece(8-row, col-1, turn%2+1);
            }
            else{
                std::cout<<"Invalid move"<<std::endl;
                continue;
            }
        }
        else{
            std::pair<int, int> move = chooseMove(board, turn%2+1);
            board.placePiece(8-move.first, move.second-1, turn%2+1);
        }

        board.flipPieces(turn%2+1);

        std::cout<<"RED has: "<<getIndividualScores(board).first<<" points"<<std::endl;
        std::cout<<"BLUE has: "<<getIndividualScores(board).second<<" points"<<std::endl;

        board.printBoard();
        turn++;
    }
    if(evaluatePos(board, 1)>0){
        std::cout<<"BLUE wins!"<<std::endl;
    }
    else if(evaluatePos(board, 1)<0){
        std::cout<<"RED wins!"<<std::endl;
    }
    else{
        std::cout<<"Tie!"<<std::endl;
    }
    return 0;
}