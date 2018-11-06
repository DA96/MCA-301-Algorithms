// Section A
// Q1. Given order of n matrices, find the minimum multiplication operations required for multiplying n matrices.

// Author: Divya Agarwal


#include<iostream>
#include<climits>
using namespace std;

int s[100][100];

int MatrixChainOrder(int p[], int n)
{
    int m[n][n];  // table m [1 to n][1 to n] to store m[i][j] costs
    s[n-1][n-1];  // table s [1 to n-1][2 to n] stores which index of k achieved the optimal cost in computing m[i][j]

    int i,j,k,l,q;

    for( i = 1; i <= n; i++ )
        m[i][i] = 0;

    for( l = 2; l <= n; l++ )   // l is the chain length
    {
        for( i = 1; i <= n-l+1; i++ )
        {
            j = i+l-1;
            m[i][j] = INT_MAX;

            for( k = i; k <= j-1; k++ )
            {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];

                if( q < m[i][j] )
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }

        }
    }

    return m[1][n];
}


void printOptimalParens(int s[][100], int i, int j)
{
    if( i==j )
        cout<<" A"<<i<<" ";
    else
    {
        cout<<"(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        cout<<")";
    }
}


int main()
{
    int n;
    cout<<"Enter number of matrices: ";
    cin>>n;

    int p[n+1]; //Dimensions

    cout<<"Enter dimensions: \n";
    for( int i=0; i<=n; i++ )
    {
        cout<<"p"<< i <<" : ";
        cin>>p[i];
    }

    int min_mul_ops = MatrixChainOrder(p,n);

    cout<<"\nMINIMUM MULTIPLICATION OPERATIONS required for multiplying "<< n <<" matrices: "<< min_mul_ops ;

    cout<<"\n\nOPTIMAL PARENTHESIZATION OF MATRICES : ";
    printOptimalParens(s,1,n);

    return 0;
}

