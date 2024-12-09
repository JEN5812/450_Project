#ifndef SUDOKU_UTILITY_H
#define SUDOKU_UTILITY_H

// header files
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// data structure
typedef struct CellNodeStruct
   {
    bool fixedCell;

    int value;
   } CellNodeType;

// prototypes

/*
Name: clearSudokuArray
Process: returns allocated two dimensional array data to OS,
         returns NULL
Function input/parameters: sudoku array (CellNodeType **)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
CellNodeType **clearSudokuArray( CellNodeType **arrayPtr );

/*
Name: createSudokuArray
Process: creates dynamically allocated two dimensional array of CellNodeTypes
         sets all element members to value of zero and fixedCell of false
Function input/parameters: none
Function output/parameters: none
Function output/returned: pointer to two dimensional array of CellNodeTypes,
                          with elements set to defaults (CellNodeType **)
Device input/---: none
Device output/---: none
Dependencies: malloc
*/
CellNodeType **createSudokuArray();

/*
Name: createSudokuGame
Process: creates complete sudoku game with given number of entries,
         also displays some game creation actions,
         uses helper function
Function input/parameters: pointer to game array (CellNodeType **),
                           number of empty cells specified (int),
                           option to show recursive backtracking operations 
                                                                          (bool)
Function output/parameters: pointer to updated game array (CellNodeType **)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: printf, createSudokuGameHelper, removeNumbers, displayGrid
*/
void createSudokuGame( CellNodeType **gameArray, 
                                                int numEmpties, bool showGrid );

/*
Name: createSudokuGameHelper
Process: Recursive helper function that searches for the right number
         for a given cell,
         implements backtracking if solution cannot be found
         with a given number,
         displays "trying" operation, "backtracking" operation,
         and grids as the numbers are added,
         see sample runs for format
Function input/parameters: pointer to game array (CellNodeType **),
                           row and column positions (int)
                           option to show recursive backtracking operations 
                                                                          (bool)
Function output/parameters: pointer to updated game array (CellNodeType **)
Function output/returned: Boolean result of each attempt (bool)
Device input/---: none
Device output/---: none
Dependencies: displayGrid, createSudokuHelper (recursively), 
              hasConflict, printf
*/
bool createSudokuGameHelper( CellNodeType **gameArray, 
                                        int rowPos, int colPos, bool showGrid );
    
/*
Name: displayGrid
Process: if Boolean is set,
         displays complete grid with horizontal and vertical lines
         to show cells,
         if Boolean is not set, no action is taken
Function input/parameters: pointer to game array (CellNodeType **),
                           row and column positions (int)
                           option to show recursive backtracking operations 
                                                                          (bool)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: printf
*/
void displayGrid( CellNodeType **gameArray, bool showGrid );

/*
Name: genRandSudokuValue
Process: generates a random sudoku value (1-9) with a double random strategy,
         generates a random number of random generations,
         then generates random values, and returns the last one found
Function input/parameters: none
Function output/parameters: none
Function output/returned: result of random value generation (int)
Device input/---: none
Device output/---: none
Dependencies: getRandBetween
*/
int genRandSudokuValue();
    
/*
Name: getRandBetween
Process: generates and returns a random value 
         between low and high values inclusive
Function input/parameters: low and high value (int)
Function output/parameters: none
Function output/returned: result of random value generation (int)
Device input/---: none
Device output/---: none
Dependencies: rand
*/
int getRandBetween( int lowVal, int highVal );

/*
Name: hasConflict
Process: tests given cell for conflict between same row, same column,
         or within same grid, returns true if conflict, false otherwise
Function input/parameters: pointer to game array (CellNodeType **),
                           row and column locations (int),
                           test value (int)
Function output/parameters: none
Function output/returned: result of specified tests (bool)
Device input/---: none
Device output/---: none
Dependencies: isInRow, isInCol, isInSubGrid
*/
bool hasConflict( CellNodeType **gameArray, 
                                  int rowLocIndex, int colLocIndex, int value );

/*
Name: isInCol
Process: checks for given value at location having duplicate in the same column
Function input/parameters: pointer to game array (CellNodeType **),
                           column location (int), test value (int)
Function output/parameters: none
Function output/returned: result of specified test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isInCol( CellNodeType **gameArray, int colIndex, int value );

/*
Name: isInRow
Process: checks for given value at location having duplicate in the same row
Function input/parameters: pointer to game array (CellNodeType **),
                           row location (int), test value (int)
Function output/parameters: none
Function output/returned: result of specified test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isInRow( CellNodeType **gameArray, int rowIndex, int value );

/*
Name: isInSubGrid
Process: checks for given value at location having duplicate 
         in the same sub grid
Function input/parameters: pointer to game array (CellNodeType **),
                           row and column locations (int), test value (int)
Function output/parameters: none
Function output/returned: result of specified test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isInSubGrid( CellNodeType **gameArray, 
                                   int rowLocIndex, int colLocIndex, int value );

/*
Name: removeNumbers
Process: finds a specified number of random locations in sudoku array, 
         and removes each number if that number has not already been removed,
Function input/parameters: pointer to game array (CellNodeType **),
                           number of values to be removed (int)
Function output/parameters: pointer to game array (CellNodeType **),
                            number of values to be removed
Function output/returned: result of specified test (bool)
Device input/---: none
Device output/---: none
Dependencies: genRandSudokuValue
*/
void removeNumbers( CellNodeType **gameArray, int numbersToBeRemoved );
   
/*
Name: setDiagonalSubGrids
Process: creates the three diagonal sub grids that will not be modified
         during the creation of the rest of the game
Function input/parameters: pointer to game array (CellNodeType **)
Function output/parameters: updated pointer to game array (CellNodeType **)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: setInitialSubGrid
*/
void setDiagonalSubGrids( CellNodeType ** gameArray );

/*
Name: setInitialSubGrid
Process: creates one sub grid given the indices 
         of the upper left cell of the grid
Function input/parameters: pointer to game array (CellNodeType **),
                           upper left start row and column (int)
Function output/parameters: updated pointer to game array (CellNodeType **)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: genRandSudokuValue, isInSubGrid
*/
void setInitialSubGrid( CellNodeType **gameArray, int startRow, int startCol );

#endif   // SUDOKU_UTILITY_H

