#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "knightType.h"
#define DEFAULT_DIMENSION (8) // 8*8 chessboard

using namespace std;

// Constructor that allocates a dim × dim vector to the board
// object and sets each element to 0, sets functionsCalled to 0

knightType::knightType(int dim)
{
    knightType::chessboard = new int *[dim];
    knightType::dimension = dim; // set the given dimension to make it available globally
    for (int i = 0; i < dim; i++)
    {
        // initializing chessboard
        chessboard[i] = new int[dim];
        for (int j = 0; j < dim; j++)
            chessboard[i][j] = 0; // sets each element to zero
    }
    outputTour();
    knightType::functionsCalled = 0; // sets functionsCalled to 0
}

static int IsInBoundaries(int x_pos, int y_pos)
{
    return (((0 <= x_pos) && (x_pos < 8)) && (0 <= y_pos) && (y_pos < 8));
}

static int IsMoveValid(int **chessboard, int x_pos, int y_pos)
{
    cout<<"In for check"<<x_pos<<y_pos<<endl;
    cout<<"In for IsInBoundaries(x_pos, y_pos)"<<IsInBoundaries(x_pos, y_pos)<<endl;
    if(IsInBoundaries(x_pos, y_pos) == 1) {
       if( chessboard[x_pos][y_pos] == 0){
           return 1;
       }else{
           return 0;
       }
    }else{
         cout<<"In for IsInBoundaries(x_pos, y_pos) ELsE"<<IsInBoundaries(x_pos, y_pos)<<endl;
        return 0;
    }
}

vector<knightType::position> knightType::getAvailableMoves(int r, int c)
{

    std::vector<position> knightMoves;

    // knightMoves.push_back(knightType::position(0, 0, 0));

    // calculate the possible onward moves
    int maxMoves = 8;

    // The possible moves a Knight can make
    const int possibleMoves[maxMoves][2] = {{1, 2},
                                            {1, -2},
                                            {2, 1},
                                            {2, -1},
                                            {-1, 2},
                                            {-1, -2},
                                            {-2, 1},
                                            {-2, -1}};

    // local on ward move counter
    int onwardMoveCounter = 0, i = 0;

    // stores the tour index after each knight move
    vector<knightType::position> currentMove;

    // Iterate through the possible moves for the Knight  ++onwardMoveCounter;
    for (i = 0; i < maxMoves; ++i)
    {
        if (IsMoveValid(knightType::chessboard, r + possibleMoves[i][0], c + possibleMoves[i][1]) == 1)
        {
            // New spots
            int newRow = r + possibleMoves[i][0];
            int newCol = c + possibleMoves[i][1];

            // the Knight can move to this direction . Thus get all the possible moves from this location
            for (int j = 0; j < maxMoves; ++j)
            {

                if (IsMoveValid(knightType::chessboard, newRow + possibleMoves[j][0], newCol + possibleMoves[j][1]) == 1)
                {
                    cout << "IsMoveValid" << IsMoveValid(knightType::chessboard, newRow + possibleMoves[j][0], newCol + possibleMoves[j][1]) << endl;
                    ++onwardMoveCounter; // if this possible move is valid then increase the onward move by 1
                }
            }

            // Set the Knight onward moves from this specific location

            knightMoves.push_back(knightType::position(r + possibleMoves[i][0], c + possibleMoves[i][1], onwardMoveCounter));
            // reset the onwardMove Counter
            onwardMoveCounter = 0;
        }else{
            continue;
        }

        cout << "r =>" << i << "===>" << knightMoves[i].row << "\t";
        cout << "c "
             << "===>" << knightMoves[i].col << "\t";
        cout << "o "
             << "===>" << knightMoves[i].onwardMoves << endl;
    }

    //  return all the available knight moves
    return knightMoves;
}

// true if the knight tour is complete
bool knightType::fullBoard()
{
    int row = knightType::dimension;
    int col = knightType::dimension;
    // stores the counter filled (every cell in board contains an integer larger than 0
    int totalCellsMoved = 0;

    // total cells possible to assert everything is full
    int totalBoardSize = row * col;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            // check if value is greater than zero and increase counter
            if (knightType::chessboard[i][j] > 0)
            {
                ++totalCellsMoved;
            }
        }
    }

    // if the knight tour is completed cells moved is equal to one less of the total size
    if (totalCellsMoved == totalBoardSize - 1)
    {
        return true;
    }

    return false;
}
// set the cell with tour Index on the chessboard
void knightType::setCell(int r, int c, int tourIndex)
{
    knightType::chessboard[r][c] = tourIndex;
}

// Compares two intervals according to onward moves in ascending order.
bool sortByOnwardMoves(knightType::position move1, knightType::position move2)
{
    return (move1.onwardMoves < move2.onwardMoves);
}

// Pick the available move with the minimal onward moves
vector<knightType::position> pickMinOnwardMove(vector<knightType::position> knightMoves, int backtrackCounter)
{
    // Always selected the first index after sorting since that will be the smallest onwardMove
    int moveIndex = 0;

    int selectedKnightMove = backtrackCounter + moveIndex;

    // First sort the knightMoves list of available positions

    std::sort(knightMoves.begin(), knightMoves.end(), sortByOnwardMoves);

    vector<knightType::position> knightMoveSelected;

    // Select the knightMove with the minimum onward move and return the value

    knightMoveSelected.push_back(knightMoves[selectedKnightMove]);

    return knightMoveSelected;
}

// function that makes the first initial call to the recursive function
bool knightType::knightTour(int r, int c)
{
    cout << "ROW Ent" << r << endl;

    cout << "Col Ent" << c << endl;

    return knightType::knightTour(r, c, 1);
}

// initially moving through the path with out backtracking thus zero
int backtrackCounter = 0 , fnc = 0; 

// recursive function simulates the knight movement
bool knightType::knightTour(int r, int c, int tourIndex)
{
    cout << "CALLS" << fnc <<endl;
    fnc++;
    
     cout << "TOUR#" << tourIndex <<endl;
    // Set the board[r][c] with tourIndex
   // setCell(r, c, tourIndex);
    
    // edge 
     if (tourIndex == 1){
              cout << "Tour Ent s" << tourIndex << endl;
               setCell(r, c, tourIndex);
              tourIndex++;
            knightTour(r, c, (int)tourIndex);
            return true;
        }
    // // Check if the board is full

    // // Get all the available moves from location [r,c]
    std::vector<knightType::position> knightMoves = getAvailableMoves(r, c);
      cout << "knightMoves CALLed"<<endl;
    for (auto x : knightMoves)
        cout << "[" << x.row << ", " << x.col << "," << x.onwardMoves << "] ";

    // Pick the available move with the minimal onward moves
    std::vector<knightType::position> knightMoveSelected = pickMinOnwardMove(knightMoves, backtrackCounter);

    cout << "Minimum"
         << "[" << knightMoveSelected[0].row << ", " << knightMoveSelected[0].col << "," << knightMoveSelected[0].onwardMoves << "] ";
      cout <<knightMoveSelected[0].row << endl;
      cout <<knightMoveSelected[0].col << endl; 
      cout <<knightMoveSelected[0].onwardMoves << endl;
        cout << tourIndex << endl; 
        
      
       
        
        if(tourIndex < 64){
            cout << "Tour Ent apass" << knightMoveSelected[0].row << knightMoveSelected[0].col << tourIndex << endl;
            
            // If there is no location the knight can move to
            if(knightMoveSelected.size() != 0){
                 setCell(knightMoveSelected[0].row, knightMoveSelected[0].col , tourIndex);
                  tourIndex++;
                  backtrackCounter = 0;
          knightTour(knightMoveSelected[0].row, knightMoveSelected[0].col, (int)tourIndex);
                          
              return true;
            }else{
                // If the function returns false then simply return to picking another minimal onward moves of previous
            backtrackCounter++;
        
            cout << "Tour BACK***" << tourIndex << endl;
             knightTour(r, c, tourIndex);
            }
            
        }
        
 
     return false; 
}

// Output the Knight Tour entire chessboard
void knightType::outputTour() const
{

    // loop through the chessboard and display all
    for (int i = 0; i < knightType::dimension; i++)
    {
        for (int j = 0; j < knightType::dimension; j++){
            cout << knightType::chessboard[i][j] << " ";
        }
          cout << "\n"
         << endl; // row end
    }

  
}
// Driver Code
int main(int agrc, const char *agrv[])
{

    int dimension, row, col;
    cout << "Enter board dimension:";
    cin >> dimension;

    // Enter the dimension and generate the chessboard
    knightType((int)dimension);

    cout << "\n Enter initial knight position :";
    cin >> row >> col;

    cout << "Row =>" << row << endl;

    cout << "col =>" << col << endl;

    // knightTour recursive Function Call

    knightType knight;

    knight.knightTour(row, col);
    
    knight.outputTour();

    return 0;
}