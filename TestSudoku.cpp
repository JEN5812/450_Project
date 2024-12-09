#include <algorithm>
#include <sstream>
#include <iostream>

#include <deepstate/DeepState.hpp>

using namespace deepstate;

#include "SudokuUtility.h"

// #define MAX_SIZE 20

#define GRID_SIZE 9                
#define SUB_GRID_SIZE 3 

// local constants
const int LOWEST_SUDOKU_VALUE = 1;
const int HIGHEST_SUDOKU_VALUE = 9;
const int GRID_SIDE = 9;
const int SUB_GRID_SIDE = 3;
const int SUDOKU_RANGE = 9;


TEST(SudokuUtility, ClearSudokuArray) {
  
  CellNodeType **sudokuArray = createSudokuArray();
 
  sudokuArray = clearSudokuArray(sudokuArray);

  ASSERT_EQ(sudokuArray, nullptr);
}

TEST(SudokuUtility, CreateSudokuArray) {

  CellNodeType **sudokuArray = createSudokuArray();

  ASSERT_NE(sudokuArray, nullptr);


  for (int i = 0; i < GRID_SIDE; i++) {
    for (int j = 0; j < GRID_SIDE; j++) {
      ASSERT_EQ(sudokuArray[i][j].value, 0);
      ASSERT_EQ(sudokuArray[i][j].fixedCell, false);
    }
  }


  sudokuArray = clearSudokuArray(sudokuArray);
}

TEST(SudokuUtility, CreateSudokuGame) {
  CellNodeType **sudokuArray = createSudokuArray();
 
  createSudokuGame(sudokuArray, 10, false);

  
  int emptyCount = 0;
  for (int i = 0; i < GRID_SIDE; i++) {
    for (int j = 0; j < GRID_SIDE; j++) {
      if (sudokuArray[i][j].value == 0) {
        emptyCount++;
      }
    }
  }

  
  ASSERT_EQ(emptyCount, 10);


  sudokuArray = clearSudokuArray(sudokuArray);
}

TEST(SudokuUtility, CreateSudokuGameHelper) {
 
  CellNodeType **sudokuArray = createSudokuArray();

  bool result = createSudokuGameHelper(sudokuArray, 0, 0, false);
  ASSERT_TRUE(result);

  
  sudokuArray = clearSudokuArray(sudokuArray);
}



TEST(SudokuUtility, DisplayGrid) {

  CellNodeType **sudokuArray = createSudokuArray();
  setDiagonalSubGrids(sudokuArray);

 
  std::ostringstream output;
  std::streambuf* old_buf = std::cout.rdbuf();  
  std::cout.rdbuf(output.rdbuf());  

 
  displayGrid(sudokuArray, true);

  
  std::cout.rdbuf(old_buf);

  
  std::string captured_output = output.str();

  
  ASSERT_FALSE(captured_output.empty());


  sudokuArray = clearSudokuArray(sudokuArray);
}



TEST(SudokuUtility, GenRandSudokuValue) {
  for (int i = 0; i < 100; i++) {
    int value = genRandSudokuValue();
    ASSERT_GE(value, LOWEST_SUDOKU_VALUE);
    ASSERT_LE(value, HIGHEST_SUDOKU_VALUE);
  }
}

TEST(SudokuUtility, GetRandBetween) {
  for (int i = 0; i < 100; i++) {
    int value = getRandBetween(3, 7);
    ASSERT_GE(value, 3);
    ASSERT_LE(value, 7);
  }
}

TEST(SudokuUtility, HasConflict) {
 
  CellNodeType **sudokuArray = createSudokuArray();
  sudokuArray[0][0].value = 5;

 
  ASSERT_TRUE(hasConflict(sudokuArray, 0, 1, 5)); 
  ASSERT_TRUE(hasConflict(sudokuArray, 1, 0, 5)); 
  ASSERT_TRUE(hasConflict(sudokuArray, 1, 1, 5)); 
  ASSERT_FALSE(hasConflict(sudokuArray, 2, 2, 5)); 


  sudokuArray = clearSudokuArray(sudokuArray);
}

TEST(SudokuUtility, IsInRow) {
  CellNodeType **sudokuArray = createSudokuArray();
  sudokuArray[0][0].value = 5;

  ASSERT_TRUE(isInRow(sudokuArray, 0, 5));
  ASSERT_FALSE(isInRow(sudokuArray, 1, 5));

  sudokuArray = clearSudokuArray(sudokuArray);
}

TEST(SudokuUtility, IsInCol) {
  CellNodeType **sudokuArray = createSudokuArray();
  sudokuArray[0][0].value = 5;

  ASSERT_TRUE(isInCol(sudokuArray, 0, 5));
  ASSERT_FALSE(isInCol(sudokuArray, 1, 5));

  sudokuArray = clearSudokuArray(sudokuArray);
}

TEST(SudokuUtility, IsInSubGrid) {
  CellNodeType **sudokuArray = createSudokuArray();
  sudokuArray[0][0].value = 5;

  ASSERT_TRUE(isInSubGrid(sudokuArray, 0, 0, 5));
  ASSERT_FALSE(isInSubGrid(sudokuArray, 3, 3, 5));

  sudokuArray = clearSudokuArray(sudokuArray);
}

TEST(SudokuUtility, RemoveNumbers) {
  CellNodeType **sudokuArray = createSudokuArray();
  setDiagonalSubGrids(sudokuArray);

  removeNumbers(sudokuArray, 15);

  int emptyCount = 0;
  for (int i = 0; i < GRID_SIDE; i++) {
    for (int j = 0; j < GRID_SIDE; j++) {
      if (sudokuArray[i][j].value == 0) {
        emptyCount++;
      }
    }
  }

  ASSERT_EQ(emptyCount, 15);

  sudokuArray = clearSudokuArray(sudokuArray);
}

TEST(SudokuUtility, SetDiagonalSubGrids) {
  CellNodeType **sudokuArray = createSudokuArray();
  setDiagonalSubGrids(sudokuArray);

  for (int i = 0; i < GRID_SIDE; i += SUB_GRID_SIDE) {
    for (int r = i; r < i + SUB_GRID_SIDE; r++) {
      for (int c = i; c < i + SUB_GRID_SIDE; c++) {
        ASSERT_NE(sudokuArray[r][c].value, 0);
        ASSERT_TRUE(sudokuArray[r][c].fixedCell);
      }
    }
  }

  sudokuArray = clearSudokuArray(sudokuArray);
}

TEST(SudokuUtility, SetInitialSubGrid) {
  CellNodeType **sudokuArray = createSudokuArray();
  setInitialSubGrid(sudokuArray, 0, 0);

  for (int r = 0; r < SUB_GRID_SIDE; r++) {
    for (int c = 0; c < SUB_GRID_SIDE; c++) {
      ASSERT_NE(sudokuArray[r][c].value, 0);
      ASSERT_TRUE(sudokuArray[r][c].fixedCell);
    }
  }

  sudokuArray = clearSudokuArray(sudokuArray);
}


