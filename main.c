#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const int size = 3;
int board[3][3];
int winnerValue;
bool isFull(){
    for(int i = 0; i < size;  i++){
        for(int j = 0; j < size; j++){
            int value = board[i][j];
            if (value == 0){
                return false;
            }
        }

    }
    return true;
}

void printBoard(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (j == 0) {

                printf("|%d|", board[i][j]);
            }else{
                printf("%d|", board[i][j]);
            }

        }
        printf("\n-------\n");
    }
}

bool checkOccupied(int targetX, int targetY){
    if (board[targetY][targetX] != 0){

        return true;
    }
    return false;


}

void testArrayPointer(int *array){
    array[0] = 3;
    printf("%p\n", array);
}

int *inputValueBoard(int strike){
    if(strike == 3){
        return NULL;
    }
    int x, y;
    printf("Enter x axis:");
    scanf("%d", &x);
    printf("Enter y axis:");
    scanf("%d", &y);

    if (x > 3 || y > 3){
        printf("out of range\n");
        return inputValueBoard(strike + 1);
    }

    if (checkOccupied(x, y)){
        printf("Already occupied\n");
        return inputValueBoard(strike+1);
    }
    // using malloc and free dynamic allocated memeory
    // instead of *result
    // when dynamic allocated it will be in the heap, and if it doens't free we can access it


    int *values = malloc(sizeof(int) * 2); // a pointr to an int store into array


//    int values[] = {x, y}; this in the stack and when retrun it doens't exist
//
//    int *result = values;


    values[0] = x;
    values[1]= y;
    printf("pX: %d\n", values[0]);
    printf("pValues: %p\n", values);
//    printf("x: %p\n", result);
//    return result; // we need to return result this is because value mem no longer exist
    return values;

}

bool checkHortizontal(){

    for (int i = 0; i < 3; i++) {
        int target;
        bool winner = true;
        for (int j = 0; j < 3; j++){
            int y = board[j][i];
            if (j == 0 && y != 0) target = board[j][i];

            if(target != y ){
                winner = false;
                break;
            }

        }
        if(winner){
            winnerValue = target;
            return true;
        }
    }

    return false;
}

bool checkVert(){

    for (int i = 0; i < 3; i++) {
        int target;
        bool winner = true;
        for (int j = 0; j < 3; j++){
            int x = board[i][j];

            if (j == 0 && x != 0 ) target = board[i][j];

            if(target != x){
                winner = false;
                break;
            }

        }
        if(winner){
            winnerValue = target;
            return true;
        }
    }
    return false;
}

bool checkDiagonalRL(){
    int target;
    for(int i = 0; i < 3; i++){
        int value = board[i][i];
        if(value == 0){
            return false;
        }
        if(i == 0) target = value;
        if(target != value){
            return false;
        }

    }
    winnerValue = target;
    return true;
}

bool checkDiagonalLR(){
    int target;
    for(int i = 0; i < 3; i++){
        int value = board[2-i][0+i]; //[2,0] [1,1] [0,2]
        if(value == 0){
            return false;
        }
        if(i == 0) target = value;
        if(target != value){
            return false;
        }

    }
    winnerValue = target;
    return true;
}



bool checkWinner(){
   if(checkHortizontal() || checkVert() || checkDiagonalLR() || checkDiagonalRL()){
       return true;
   }
}
int main() {

//    printf("%d\n", isFull()); // 0 is false 1 is true
    if (isFull()){
        printf("Game is finshed \n");
        return 0;
    }

   int turn = 0;
   while (!isFull()) {

       if(turn % 2 == 0){
           printf("player 1 \n");
       } else {
           printf("player 2 \n");
       }

       int x, y;
//
//       int array[2];
//       testArrayPointer(array);
//       printf("%d\n", array[0]);
//


       int *array = inputValueBoard(0);
       printf("pointer: %d\n", array[0]);


        x = array[1];
        y = array[0];
       printf("x: %d. y: %d\n", x , y);

       if (turn % 2 == 0){
           board[x][y] = 1;
       } else {
           board[x][y] = 2;
       }
       free(array);
       printBoard();
       if(checkWinner()){
           printf("winner is plyaer: %d\n", winnerValue);
           return 0;
       }

       turn++;



   }


    return 0;
}
