//Section A
/*
Q4. Suppose you are managing the construction of billboards on the university road,
	a heavily travelled stretch of road that runs west-east for M miles. The possible
	sites for billboards are given by numbers x1,x2,...xn each in the interval [0,M]
	(specifying their position along the roads, measured in miles from its western end).
	If you place billboard at location ‫xi , you receive revenue of  ri > 0
	Regulations imposed by the Delhi road authority require that no two billboards be
	within less than or equal to 5 miles of each other. You had like to place billboards at
	a subset of the sites so as to maximize your total revenue, subject to this restriction.
	Example: Suppose M=20, n=4
	{x1, x2, x3, x4} = {6, 7, 12, 14} and {r1, r2, r3, r4} = {5, 6, 5, 1}
	Then the optimal solution would be to place billboards at ‫x1 and x3 for total revenue
	of 10.
	Give an algorithm that takes an instance of this problem as input and returns the
	maximum total revenue that can be obtained from any valid subsets of sites.
*/

/*

Approach: Dynamic Programming

Time Complexity : O(M) , where M is total miles

*/

//Author: Divya Agarwal

#include<iostream>
using namespace std;


int maxRevenue(int billboard[], int revenue[], int M_miles, int milesRes, int billboard_length)
{

        int MR[M_miles + 1] = {0};    //Max revenue for M miles
        //  bool billboard_placed[billboard_length] = {0};

        //Next billboard which can be used will start from index 0 in billboard[]
        int nextBillBoard = 0;

        // if milesRes = 5 miles then any 2 bill boards has to be more than
        //5 miles away so actually we can put at 6th mile so we can add one mile milesRes
        milesRes = milesRes + 1; // actual minimum distance can be between 2 billboards

        MR[0] = 0;

        for (int i = 1; i <= M_miles; i++)
        {

            //check if all the billboards are not already placed
            if(nextBillBoard < billboard_length)
            {

                //check if we have billboard for that particular mile
                //if not then copy the optimal solution from i-1th mile
                if (billboard[nextBillBoard] != i)
                {
                    //we do not have billboard for this particular mile
                    MR[i] = MR[i - 1];
                }
                else
                {
                    //we do have billboard for this particular mile

                    //check if no billboard placed yet
                    if(MR[i-1]==0)
                        //there are no billboard placed prior to ith mile
                        //we will just place the billboard
                        MR[i] = revenue[nextBillBoard];

                    else
                    {

                      //now we have 2 options, either place the billboard or ignore it
                      //we will choose the optimal solution
                        if(i>=milesRes)
                            MR[i] = max(MR[i - milesRes] + revenue[nextBillBoard], MR[i - 1]);
                        else
                            MR[i] = max(MR[i - 1],revenue[nextBillBoard]);
                    }

                    nextBillBoard++;
                }
            }
            else
            {
                //All the billboards are already placed
                //for rest of the miles copy the previous optimal solution
                MR[i] = MR[i - 1];
            }

        }

        return MR[M_miles];
}


int main()
{
        int tot_billboardNum;
        cout<<"Enter total number of billboards: ";
        cin>>tot_billboardNum;

        int billboard_pos[tot_billboardNum];
        int revenue[tot_billboardNum];

        cout<<"\nEnter billboard position and its revenue \n";
        for(int i=0; i<tot_billboardNum; i++)
        {
            cout<<"\nBillboard position: ";
            cin>>billboard_pos[i];

            cout<<"Billboard revenue: ";
            cin>>revenue[i];
        }

        int M;
        cout<<"\nEnter total miles: ";
        cin>>M;

        int milesRestriction = 5;

        int max_rev = maxRevenue(billboard_pos, revenue, M, milesRestriction, tot_billboardNum);
        cout<<"Maximum revenue that can be generated :"<<max_rev;

        return 0;
}
