#ifndef knightType_h
#define knightType_h
#include <iostream>
#include <vector>

class knightType
{
public:
    struct position
    {
        position(int r = 0, int c = 0, int o = 0)
        {
            row = r;
            col = c;
            onwardMoves = o;
        }
        int row;
        int col;
        int onwardMoves;
    };
    knightType(int = 8);
    bool knightTour(int, int);
    void outputTour() const;
    bool withInBoundaries();
    bool isMoveValid();
    void setCell(int,int,int);
    int dimension = 8; // chess board default dimension is 8
    int **chessboard;  // the chess board 

private:
    bool knightTour(int, int, int);
    std ::vector<position> getAvailableMoves(int, int);
    bool fullBoard();
    std ::vector<std ::vector<int>> board;
    int functionsCalled;
};
#endif