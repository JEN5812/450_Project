// header files
#include <time.h>
#include "SudokuUtility.h"

// main program
int something()
   {
    // initialize function/variables

       // initialize variables
       CellNodeType **sudokuArray;
       int numToRemove = 15;
       bool showGrid = true;

       // initialize array
          // function: createSudokuArray
       sudokuArray = createSudokuArray();

       // seed random generator
          // function: srand
       srand( time( NULL ) );

       // show title
          // function: printf
       printf( "\nSudoku Generation Program\n" );
       printf( "=========================\n\n" );

    // get input

       // no user input acquired

    // implement processing, including display components
       // function: createSudokuGame
    createSudokuGame( sudokuArray, numToRemove, showGrid );

    // display results

       // result display is integrated into create game operation

    // end program

       // clear array
          // function: clearArray
       sudokuArray = clearSudokuArray( sudokuArray );

       // display end program
          // function: printf
       printf( "\nProgram End\n" );

       // return program success
       return 0;
   }