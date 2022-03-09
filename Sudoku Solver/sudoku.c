// Authors: Jeffrey Jordan
// Date: 2/12/20
// File: sudoku.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 9

typedef struct{ // referenced from assignment page
  int row;
  int col;
} parameters;

int board[SIZE][SIZE]; // global variable holding board

pthread_t tRow, tCol, t1, t2, t3, t4, t5, t6, t7, t8, t9; // 

void setThreads();
/*
 * Program's main function. Defines threads and starts their functionality.
 *
 *
 * Input - None
 *
 *
 *
 * Return - None
 */

void* checkRow(void* p);  //man7.org/linux/man-pages/man3/pthread_create.3.html
void* checkCol(void* p);
void* checkSquare1(void* p);
void* checkSquare2(void* p);
void* checkSquare3(void* p);
void* checkSquare4(void* p);
void* checkSquare5(void* p);
void* checkSquare6(void* p);
void* checkSquare7(void* p);
void* checkSquare8(void* p);
void* checkSquare9(void* p);

/* Block of void pointer functions that determine whether a specific portion of the board is valid
 *
 *
 * Input - Void pointer to struct parameters
 *
 *
 * Return - An empty void pointer or !NULL void pointer
 */

void *rowPtr; // pthread requires a void pointer
void *colPtr;
void *c1;
void *c2;
void *c3;
void *c4;
void *c5;
void *c6;
void *c7;
void *c8;
void *c9;

/*
 * Block of void pointers to hold return values of the solution functions
 */

int main(int argc, char **argv){ // referenced project 1. Supplies command line input for file

  FILE *fp;

  if (argc == 0) // if no file was given on command line compilation
    printf("recompile with file as command line argument\n");
  
  fp = fopen(argv[1], "r");
  
  if (fp == NULL) // validity check
    exit(1);

  for (int i = 0; i < SIZE; i++){ // read in file
      for(int j = 0; j < SIZE; j++){
	fscanf(fp, "%d", &board[i][j]);
      }
  }

  setThreads(); // starts the multithreading process
  
  if (rowPtr != NULL) //The program wouldn't reach this point if invalid
    printf("rows check out\n");

  if (colPtr != NULL)
    printf("cols check out\n");

  if (c1 != NULL && c2 != NULL  && c3 != NULL
      && c4 != NULL  && c5 != NULL  && c6 != NULL
      && c7 != NULL  && c8 != NULL  && c9 != NULL) 
    printf("squares check out\n");
  
  return 0;
  
}

void setThreads(){

  parameters *rowcolparameter = (parameters *) malloc(sizeof(parameters)); //referenced 485 notes
  rowcolparameter -> row = 0;
  rowcolparameter -> col = 0;
  
  parameters *square1 = (parameters *) malloc(sizeof(parameters));
  square1 -> row = 0;
  square1 -> col = 0;

  parameters *square2 = (parameters *) malloc(sizeof(parameters));
  square2 -> row = 0;
  square2 -> col = 3;

  parameters *square3 = (parameters *) malloc(sizeof(parameters));
  square3 -> row = 0;
  square3 -> col = 6;

  parameters *square4 = (parameters *) malloc(sizeof(parameters));
  square4 -> row = 3;
  square4 -> col = 0;

  parameters *square5 = (parameters *) malloc(sizeof(parameters));
  square5 -> row = 3;
  square5 -> col = 3;

  parameters *square6 = (parameters *) malloc(sizeof(parameters));
  square6 -> row = 3;
  square6 -> col = 6;

  parameters *square7 = (parameters *) malloc(sizeof(parameters));
  square7 -> row = 6;
  square7 -> col = 0;

  parameters *square8 = (parameters *) malloc(sizeof(parameters));
  square8 -> row = 6;
  square8 -> col = 3;

  parameters *square9 = (parameters *) malloc(sizeof(parameters));
  square9 -> row = 6;
  square9 -> col = 6;

  pthread_create(&tRow, NULL, checkRow, rowcolparameter); // linux manual on creating threads
  pthread_create(&tCol, NULL, checkCol, rowcolparameter);
  pthread_create(&t1, NULL, checkSquare1, square1);
  pthread_create(&t2, NULL, checkSquare2, square2);
  pthread_create(&t3, NULL, checkSquare3, square3);
  pthread_create(&t4, NULL, checkSquare4, square4);
  pthread_create(&t5, NULL, checkSquare5, square5);
  pthread_create(&t6, NULL, checkSquare6, square6);
  pthread_create(&t7, NULL, checkSquare7, square7);
  pthread_create(&t8, NULL, checkSquare8, square8);
  pthread_create(&t9, NULL, checkSquare9, square9);
  
  pthread_join(tRow, &rowPtr); // stack overflow
  pthread_join(tCol, &colPtr);
  pthread_join(t1, &c1);
  pthread_join(t2, &c2);
  pthread_join(t3, &c3);
  pthread_join(t4, &c4);
  pthread_join(t5, &c5);
  pthread_join(t6, &c6);
  pthread_join(t7, &c7);
  pthread_join(t8, &c8);
  pthread_join(t9, &c9);
    
}

void* checkRow(void* p){ // Received forum help on dreamincode.com

  int check[9] = {0}; // this will be the equivalent of an array of booleans
  parameters* temp = (parameters*) p;
  int tempRow = temp -> row;
  int tempCol = temp -> col;

  for (int i = tempRow; i < SIZE; i++){

    for (int j = tempCol; j < SIZE; j++){

      if (board[i][j] == 1) // if it finds any int from 1 to 9, it sets the "boolean" array to 1
	check[0] = 1;
      if (board[i][j] == 2)
	check[1] = 1;
      if (board[i][j] == 3)
	check[2] = 1;
      if (board[i][j] == 4)
	check[3] = 1;
      if (board[i][j] == 5)
	check[4] = 1;
      if (board[i][j] == 6)
	check[5] = 1;
      if (board[i][j] == 7)
	check[6] = 1;
      if (board[i][j] == 8)
	check[7] = 1;
      if (board[i][j] == 9)
	check[8] = 1;
    }
    
      int k = 0;
      
      while(k < 9){ // loops through the "boolean". If a zero is found, solution is invalid.
	if (check[k] == 0){
	  printf("invalid solution");
	  return (void*) 0;
	}
	k++;
      }

      memset(check, 0, sizeof(check)); // resets array to all zeroes.

    }
  
  return (void*) 1;

}

void* checkCol(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int i = cTempRow; i < SIZE; i++){ 

    for (int j = cTempCol; j < SIZE; j++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

    int k = 0;

    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution");
	return (void*) 0;
      }
      k++;
    }
  
    memset(check, 0, sizeof(check));

  }

  return (void*) 1; // null pointer return.

}


void* checkSquare1(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){

    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	    check[0] = 1;
      if (board[j][i] == 2)
	    check[1] = 1;
      if (board[j][i] == 3)
	    check[2] = 1;
      if (board[j][i] == 4)
	    check[3] = 1;
      if (board[j][i] == 5)
	    check[4] = 1;
      if (board[j][i] == 6)
	    check[5] = 1;
      if (board[j][i] == 7)
	    check[6] = 1;
      if (board[j][i] == 8)
	    check[7] = 1;
      if (board[j][i] == 9)
	    check[8] = 1;
    }

  }
  
  int k = 0;
  while(k < 9){
    if (check[k] == 0){
      printf("square 1 is an invalid solution");
      return (void*) 0;
    }
    
  k++;
  }

  return (void*) 1;
  
}       

void* checkSquare2(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){

    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

  }
  
    int k = 0;
    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution on square 2");
	return (void*) 0;
      }
      k++;
    }

    return (void*) 1;
    
}

void* checkSquare3(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){
    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

  }
  
    int k = 0;
    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution on square 3");
	return (void*) 0;
      }
      k++;
    }

    return (void*) 1;
    
}

void* checkSquare4(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){

    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

  }
  
    int k = 0;
    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution on square 4");
	return (void*) 0;
      }
      k++;
    }

    return (void*) 1;
    
}

void* checkSquare5(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){

    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

  }
  
    int k = 0;
    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution on square 5");
	return (void*) 0;
      }
      k++;
    }

    return (void*) 1;
    
}

void* checkSquare6(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){

    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

  }
  
    int k = 0;
    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution on square 6");
	return (void*) 0;
      }
      k++;
    }

   return (void*) 1;

}

void* checkSquare7(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){

    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

  }
  
    int k = 0;
    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution on square 7");
	return (void*) 0;
      }
      k++;
    }

  return (void*) 1;
}

void* checkSquare8(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){

    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

  }
  
    int k = 0;
    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution on square 8");
	return (void*) 0;
      }
      k++;
    }

    return (void*) 1;

}

void* checkSquare9(void* p){

  int check[9] = {0};
  parameters* temp = (parameters*) p;
  int cTempRow = temp -> row;
  int cTempCol = temp -> col;

  for (int j = cTempRow; j  < cTempRow + 3; j++){

    for (int i  = cTempCol; i < cTempCol + 3; i++){

      if (board[j][i] == 1)
	check[0] = 1;
      if (board[j][i] == 2)
	check[1] = 1;
      if (board[j][i] == 3)
	check[2] = 1;
      if (board[j][i] == 4)
	check[3] = 1;
      if (board[j][i] == 5)
	check[4] = 1;
      if (board[j][i] == 6)
	check[5] = 1;
      if (board[j][i] == 7)
	check[6] = 1;
      if (board[j][i] == 8)
	check[7] = 1;
      if (board[j][i] == 9)
	check[8] = 1;
    }

  }
    int k = 0;
    while(k < 9){
      if (check[k] == 0){
	printf("invalid solution on square 9");
	return (void*) 0;
      }
      k++;
    }

    return (void*) 1;
}
