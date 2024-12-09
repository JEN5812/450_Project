// header file
#include "SudokuUtility.h"

// local constants
const int LOWEST_SUDOKU_VALUE = 1;
const int HIGHEST_SUDOKU_VALUE = 9;
const int GRID_SIDE = 9;
const int SUB_GRID_SIDE = 3;
const int SUDOKU_RANGE = 9;

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
CellNodeType **clearSudokuArray( CellNodeType **arrayPtr )
   {
    int rowIndex;

    for( rowIndex = 0; rowIndex < GRID_SIDE; rowIndex++ )
       {
        free( arrayPtr[ rowIndex ] );
       }

    free( arrayPtr );

    return NULL;
   }

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
CellNodeType **createSudokuArray()
   {
    CellNodeType **arrayPtr;
    int rowIndex, colIndex;

    arrayPtr = (CellNodeType **)malloc( GRID_SIDE * sizeof( CellNodeType *) );

    for( rowIndex = 0; rowIndex < GRID_SIDE; rowIndex++ )
       {
        arrayPtr[ rowIndex ]
                 = (CellNodeType *)malloc( GRID_SIDE * sizeof( CellNodeType ) );

        for( colIndex = 0; colIndex < GRID_SIDE; colIndex++ )
           {
            arrayPtr[ rowIndex ][ colIndex ].fixedCell = false;
            arrayPtr[ rowIndex ][ colIndex ].value = 0;
           }
       }

    return arrayPtr;
   }

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
                                                 int numEmpties, bool showGrid )
   {
    setDiagonalSubGrids( gameArray );
    bool forceDisplay = true;

    if( showGrid )
       {
        printf( "Starting Grid:" );

        displayGrid( gameArray, showGrid );
       }

    createSudokuGameHelper( gameArray, 0, 0, showGrid );

    removeNumbers( gameArray, numEmpties );

    printf( "\nSolutionFound:" );

    displayGrid( gameArray, forceDisplay );
   }

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
                                         int rowPos, int colPos, bool showGrid )
   {
    // ToDo: complete this function
    // We are Creating the Solution

    // Initialize Variables
    int game;

    // Making Sure There are Enough Rows
    if(rowPos == GRID_SIDE)
     {
       // Return True
       return true;
     }

     // When Row Ends, Go to Next Row
     if(colPos == GRID_SIDE)
      {
        // Printing the Grid
          // Function: displayGrid
        displayGrid(gameArray, showGrid);

        // Starting Next Row
          // Function: createSudokuGameHelper
        return createSudokuGameHelper(gameArray, rowPos + 1, 0, showGrid);
      }

      // Checking If Cell Has Value
      if(gameArray[rowPos][colPos].value != 0)
       {
         // Solving It
           // Function: createSudokuGameHelper
         return createSudokuGameHelper(gameArray, rowPos, colPos + 1, showGrid);
       }
       // When It Does Not Have a Value
       else
       {
         // Looping Through the Numbers
         for(game = LOWEST_SUDOKU_VALUE; game <= HIGHEST_SUDOKU_VALUE; game++)
          {
            // Testing For Conflict
              // Function: hasConflict
            if(!hasConflict(gameArray, rowPos, colPos, game))
             {
               // Assigning Game to Array
               gameArray[rowPos][colPos].value = game;

               // Making Sure if True
               if(showGrid)
                {
                  // Printing the Try Message
                    // Function: printf
                  printf("	        Trying %d at row: %d and column: %d\n",
                          game, rowPos, colPos);
                }

                // When the Puzzle is Solved
                  // Function: createSudokuGameHelper
                if(createSudokuGameHelper(gameArray, rowPos, colPos, showGrid))
                 {
                   // Return True
                   return true;
                 }
                    // Printing Backtracking Message
                      // printf
                    printf("	Backtracking from row: %d and column: %d\n",
                          rowPos, colPos);

                    // Assiging the Value to Zero
                    gameArray[rowPos][colPos].value = 0;
                  }
             }
          }
          // Return False
          return false;   // temporary stub return
       }

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
void displayGrid( CellNodeType **gameArray, bool showGrid )
   {
    int rowIndex, colIndex;

    if( showGrid )
       {
        printf( "\n\t#===|===|===#===|===|===#===|===|===#\n" );

        for( rowIndex = 0; rowIndex < GRID_SIDE; rowIndex++ )
           {
            printf( "\t# " );

            for( colIndex = 0; colIndex < GRID_SIDE; colIndex++ )
               {
                if( gameArray[ rowIndex ][ colIndex ].value > 0 )
                   {
                    printf( "%d", gameArray[ rowIndex ][ colIndex ].value );
                   }

                else
                   {
                    printf( " " );
                   }

                if( ( colIndex + 1 ) % SUB_GRID_SIDE == 0 )
                   {
                    printf( " # " );
                   }

                else
                   {
                    printf( " | " );
                   }
               }

            if( ( rowIndex + 1 ) % SUB_GRID_SIDE == 0 )
               {
                printf( "\n\t#===|===|===#===|===|===#===|===|===#\n" );
               }

            else
               {
                printf( "\n\t#---|---|---#---|---|---#---|---|---#\n" );
               }
           }
       }

    printf( "\n" );
   }

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
int genRandSudokuValue()
   {
    int numLoops = getRandBetween( LOWEST_SUDOKU_VALUE, HIGHEST_SUDOKU_VALUE );
    int loopCount, randValue = 5;

    // find a random number of random values
    for( loopCount = 0; loopCount < numLoops; loopCount++ )
       {
        randValue = getRandBetween( LOWEST_SUDOKU_VALUE, HIGHEST_SUDOKU_VALUE );
       }

    return randValue;
   }

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
int getRandBetween( int lowVal, int highVal )
   {
    int range = highVal - lowVal + 1;

    return rand() % range + lowVal;
   }

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
                                   int rowLocIndex, int colLocIndex, int value )
   {
    return isInRow( gameArray, rowLocIndex, value )
              || isInCol( gameArray, colLocIndex, value )
                   || isInSubGrid( gameArray, rowLocIndex, colLocIndex, value );
   }

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
bool isInCol( CellNodeType **gameArray, int colIndex, int value )
   {
    int rowIndex;

    for( rowIndex = 0; rowIndex < GRID_SIDE; rowIndex++ )
       {
        if( gameArray[ rowIndex ][ colIndex ].value == value )
           {
            return true;
           }
       }

    return false;
   }

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
bool isInRow( CellNodeType **gameArray, int rowIndex, int value )
   {
    int colIndex;

    for( colIndex = 0; colIndex < GRID_SIDE; colIndex++ )
       {
        if( gameArray[ rowIndex ][ colIndex ].value == value )
           {
            return true;
           }
       }

    return false;
   }

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
                                   int rowLocIndex, int colLocIndex, int value )
   {
    int rowStart = rowLocIndex - rowLocIndex % SUB_GRID_SIDE;
    int colStart = colLocIndex - colLocIndex % SUB_GRID_SIDE;
    int rowIndex, colIndex;

    for( rowIndex = rowStart;
                            rowIndex < rowStart + SUB_GRID_SIDE; rowIndex++ )
       {
        for( colIndex = colStart;
                            colIndex < colStart + SUB_GRID_SIDE; colIndex++ )
           {
            if( gameArray[ rowIndex ][ colIndex ].value == value )
               {
                return true;
               }
           }
       }

    return false;
   }

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
void removeNumbers( CellNodeType **gameArray, int numbersToBeRemoved )
   {
    int removeCount, remRow, remCol;

    for( removeCount = 0; removeCount < numbersToBeRemoved; removeCount++ )
       {
        do
           {
            remRow = genRandSudokuValue() - 1;
            remCol = genRandSudokuValue() - 1;
           }
        while( gameArray[ remRow ][ remCol ].value == 0 );

        gameArray[ remRow ][ remCol ].value = 0;
       }
   }

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
void setDiagonalSubGrids( CellNodeType ** gameArray )
   {
    int rowIndex = 0, colIndex = 0;

    setInitialSubGrid( gameArray, rowIndex, colIndex );

    rowIndex += SUB_GRID_SIDE; colIndex += SUB_GRID_SIDE;
    setInitialSubGrid( gameArray, rowIndex, colIndex );

    rowIndex += SUB_GRID_SIDE; colIndex += SUB_GRID_SIDE;
    setInitialSubGrid( gameArray, rowIndex, colIndex );
   }

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
void setInitialSubGrid( CellNodeType **gameArray, int startRow, int startCol )
   {
    int rowIndex, colIndex, randValue = 5;

    for( rowIndex = startRow;
                        rowIndex < startRow + SUB_GRID_SIDE; rowIndex++ )
       {
        for( colIndex = startCol;
                        colIndex < startCol + SUB_GRID_SIDE; colIndex++ )
           {
            do
               {
                randValue = genRandSudokuValue();
               }
            while( isInSubGrid( gameArray, rowIndex, colIndex, randValue ) );

            gameArray[ rowIndex ][ colIndex ].value = randValue;

            gameArray[ rowIndex ][ colIndex ].fixedCell = true;
           }
       }
   }
