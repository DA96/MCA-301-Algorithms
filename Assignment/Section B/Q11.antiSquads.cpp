// Section B
/*
Q.11: Save Delhi City

Suppose you are Shaktimaan and you have decided to do something to save your
favorite city (Delhi) against the attack of Tamraj Kilvish, since no one else
surprisingly seems bothered about it, and are just suffering through various attacks by
various different creatures.
Seeing your passion, N people of Delhi decided to come forward to try their best in
saving their city. Now you have decided to strategize these N people into a formation
of AT LEAST K people in a group. Otherwise, that group won't survive.
Let's demonstrate this by an example. Let's say that there were 10 people, and each
group required at least 3 people in it for its survival. Then, the following 5 groups can
be made:
· 10 - Single group of 10 members.
· 7, 3 - Two groups. One consists of 7 members, the other one of 3 members.
· 6, 4 - Two groups. One consists of 6 members, the other one of 4 members.
· 5, 5 - Two groups. One consists of 5 members, the other one of 5 members.
· 4, 3, 3 - Three groups. One consists of 4 members, the other two of 3 members.
Given the value of N, and K - find out the number of ways you can form these groups
(anti-squads) to save Delhi city.
*/

//Submitted By: Divya Agarwal

//Approach: Recursion and dynamic programming.


#include<iostream>
using namespace std;

int **partition_count; //2D array containing values returned by function call antiSquad(N,max_ppl,K) for every valid combination of N and max_ppl.

int antiSquad(int N, int max_ppl, int K){

	/*
	Input parameters:
                    N : total number of people to be partitioned
	                max_ppl : maximum number of people allowed in each group
	                K : minimum number of people required in each group

    Approach: Recursion and dynamic programming.
    */

	//when there are zero people, only one partition is possible
	if(N == 0)
		return 1;
	//when the total no. of people is less than minimum people required for each group
	if(N < K )
		return 0;
	//when value of maximum people allowed is less than minimum people required.
	if(max_ppl < K)
		return 0;

	// two recursive call
	//	1. returns partition count containing max_ppl
	// 	2. returns partition count not containing max_ppl
	// together they give total number of possible partitions

	//when the value is not already present in the table
	if(partition_count[N][max_ppl] == -1)
			partition_count[N][max_ppl] = antiSquad(N - max_ppl, max_ppl, K) + antiSquad(N, max_ppl - 1, K);

	return partition_count[N][max_ppl];
}

int main(){

	cout<<"\n\n\t\t\tANTI-SQAUD PARTITIONING PROBLEM";
	int N,K;

	while(true){
		cout<<"\n\nEnter total number of people : ";
		cin>>N;
		if(N>0)
			break;
		cout<<"\n\nNumber of people cannot be less than 1";
	}

	while(true){
		cout<<"\n\nEnter minimum count of people required in each group : ";
		cin>>K;

		if(K>0 && K<N)
			break;

        if(K>N)
            cout<<"Minimum count cannot be more than total number N";
        else
            cout<<"\n\nMinimum count cannot be less than 1";
	}

	partition_count = new int*[N+1];
	for(int i=0;i<=N;i++)
		partition_count[i] = new int[N+1];

	for(int i=0;i<=N;i++)
		for(int j=0;j<=N;j++)
			partition_count[i][j] = -1;

	cout<<"\n\nNo. of ways in which anti sqauds can be formed is : "<<anti_squad(N,N,K);
	return 0;
}

