//Section B
/*
Q.10: (Planning a party).
Alice wants to throw a party and is deciding whom to call. She has n (which is at least
11) people to choose from and she has made up a list of which pairs of these people
know each other. She wants to invite as many people as possible subject to the
following two constraints:
1. Every person invited should know at least five other people that are invited.
2. Every person invited should not know at least five other people that are invited.
Design an efficient algorithm for maximizing the number of people she can invite.
Remember to analyze the running time and correctness.
Hint: Maximizing the number of invitees is the same as minimizing the number of
people Alice doesn’t invite. Obviously Alice might not be able to invite everyone. For
example, if one of the n people knows less than five people out of the n potential
invitees then the first constraint can never be satisfied for that person.
*/

//Submitted By: Divya Agarwal

//Approach: Greedy


#include<iostream>
using namespace std;

bool **person_knows; //a boolean 2D matrix, where value at person_knows[x][y] states if person x knows person y
bool *isPotential;  //a boolean array, where value at isPotenital[i] states if a person i is potential invitee


int countknown(int n, int person)
{
	/*
	Objective: This function calculates number of people that a person knows
	Input parameters:

					n: total number of people
				    person: person for whom to count how many people he/she knows

	Return value: count of number of people, person knows
	*/

	int count=0;
	for(int i=1; i<=n; i++){
		// count if person i is a potenital invitee and also if that person knows person i
		if(isPotential[i] && person_knows[i][person])
			count++;
	}
	return count;
}


void maximize_invitees(int n)
{

	int potential_count = n;

	for(int p=1; p<=n; p++)
	{
			int known = countknown(n,p); //number of people p knows

			//number of people p doesn't know
			//eliminating self from potential count
			int unknown = potential_count - known - 1;

			//if a potential invitee knows or does not know atleast 5 people, then make him invalid and start checking from person 1 again
			if( isPotential[p] && (known < 5 || unknown < 5) )
			{
				isPotential[p] = 0;
				potential_count--;
				p = 0;
				//if number of potential invitee become less than 11, there is no way we can find a person who know 5 person and does not know 5 person
				//so make everyone invalid
				if(potential_count < 11)
				{
					for(int i=1; i<=n; i++)
						isPotential[i] = 0;
					break;
				}
			}
	}

}

void print_invitees(int n)  //prints invitees and their count
{

	int count = 0;
	cout<<"\n\n--- Invited People ---\n\n";
	for(int i=1; i<=n; i++){
		if(isPotential[i]){
			cout<<i<<"  ";
			count++;
		}
	}
	if(count == 0)
		cout<<"\nNo one can be invited.";
	else
		cout<<"\nMaximum number of people who can be invited is : "<<count;
}


int main()
{

	int n;
	while(true){
		cout<<"\nEnter total number of people n(greater than or equal to 11): ";
		cin>>n;
		if(n>=11)
			break;
	}

	person_knows = new bool*[n+1];
	for(int i=0;i<=n;i++)
		person_knows[i] = new bool[n+1];

	isPotential = new bool[n+1];

	//Initializing person_knows[][] to 0 since nobody knows each other
	//Initializing isPotential[] to 1 making everyone potential invitee
	for(int i=1; i<=n; i++)
	{
		isPotential[i] = 1;
		for(int j=1; j<=n; j++)
		{
			person_knows[i][j] = 0;
		}
	}

	//Entering list
	cout<<"\nEnter person number who know each other. Press 0 to move to next person\n\n";
	for(int i=1; i<=n; i++)
	{
		cout<<"  Person "<<i<<" knows \n";
		int max_num = n;

		while(max_num!=0)  //loop will not iterate more than n times in any case
		{
			int pn;
			cout<<"\n\t Person ";
			cin>>pn;

			if(pn==0)
				break;

			if(pn<1 || pn>n || pn==i)
			{
				cout<<"\nInvalid input! Enter again!\n";
				continue;
			}

			//since both know each other
			person_knows[i][pn] = 1;
			person_knows[pn][i] = 1;
			max_num--;
		}

	}

	maximize_invitees(n);
	print_invitees(n);
	return 0;
}
