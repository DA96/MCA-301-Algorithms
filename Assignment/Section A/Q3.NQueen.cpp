//Section A
//Q.3: Implement N Queen's problem using Back Tracking.

//Author: Divya Agarwal

#include<iostream>
using namespace std;

#define N 8


/* Function to check if a queen can be placed on board[row][col]. This function is called when "col" queens are already placed in columns from 0 to col -1. So we need to check only left side for attacking queens */
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;

    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    /* Check upper diagonal on left side */
    for (i=row, j=col; i>=0 && j>=0; i--, j--)
        if (board[i][j])
            return false;

    /* Check lower diagonal on left side */
    for (i=row, j=col; j>=0 && i<N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

/* A recursive utility function to solve N
   Queen problem */
bool solveNQ(int board[N][N], int col)
{
    // base case: If all queens are placed then return true */
    if (col >= N)
        return true;

    /* Consider this column and try placing
       this queen in all rows one by one */
    for (int i = 0; i < N; i++)
    {
        /* Check if the queen can be placed on
          board[i][col] */
        if ( isSafe(board, i, col) )
        {
            /* Place this queen in board[i][col] */
            board[i][col] = 1;

            /* recur to place rest of the queens */
            if ( solveNQ(board, col + 1) )
                return true;

            /* If placing queen in board[i][col]
               doesn't lead to a solution, then
               remove queen from board[i][col] */
            board[i][col] = 0; // BACKTRACK
        }
    }

     /* If the queen cannot be placed in any row in
        this colum col  then return false */
    return false;
}


/* prints placement of queens in the form of 1s.
   There may be more than one
   solutions, this function prints one  of the
   feasible solutions.*/
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout<<"  "<<board[i][j];
        cout<<endl;
    }
}


int main()
{
    int board[N][N] = {0};

    if (!solveNQ(board,0))
        cout<<"Solution does not exist";

    else
        printSolution(board);

    return 0;
}
