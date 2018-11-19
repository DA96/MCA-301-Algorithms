//SECTION B
/*
Q.9: Your friend is working as a camp counselor, and he is in charge of organizing
activities for a set of junior-high-school-age campers. One of his plans is the
following mini-triathlon exercise: each contestant must swim 20 laps of a pool, then
bike 10 miles, and then run 3 miles. The plan is to send the contestants out in a
staggered fashion, via the following rule: the contestants must use the pool one at a
time. In other words, first one contestant swims the 20 laps, gets out, and starts biking.
As soon as this first person is out of the pool, a second contestant begins swimming
the 20 laps; as soon as he/she's out and starts biking, a third contestant begins
swimming... and so on.)
Each contestant has a projected swimming time (the expected time it will take him or
her to complete the 20 laps), a projected biking time (the expected time it will take
him or her to complete the 10 miles of bicycling), and a projected running time (the
time it will take him or her to complete the 3 miles of running). Your friend wants to
decide on a schedule for the triathalon: an order in which to sequence the starts of the
contestants. Let's say that the completion time of a schedule is the earliest time at
which all contestants will be finished with all three legs of the triathalon, assuming
they each spend exactly their projected swimming, biking, and running times on the
three parts. (Again, note that participants can bike and run simultaneously, but at most
one person can be in the pool at any time.) What's the best order for sending people
out, if one wants the whole competition to be over as early as possible? More
precisely, give an efficient algorithm that produces a schedule whose completion time
is as small as possible.
*/

//Author: Divya Agarwal


#include<bits/stdc++.h>
using namespace std;

int **projected_time;  //stores projected activity time for each contestant
vector< pair <int,int> > sum_bikerun_time;  //where first value stores sum of bike and run time for each contestant and second value stores for which contestant
int *completion_time;  //stores completion time of each contestant after scheduling


// Driver function to sort the vector elements by
// first element of pair in descending order
bool sortinrev(const pair<int,int> &a, const pair<int,int> &b)
{
       return (a.first > b.first);
}


void scheduleTriathlon(int n)
{

    /*
    Approach:   To compute smallest completion time of triathlon
                Contestants are scheduled in order such that they have decreasing sum of bike and run time
    */

    // using modified sort() function to sort
    //sorts in decreasing order of sum of bike and run time, with the respective contestant number stored in second value of pair
    sort(sum_bikerun_time.begin(), sum_bikerun_time.end(), sortinrev);
    //Now schedule is set by the second value in sum_bikerun_time.


    completion_time = new int[n+1];
    completion_time[0] = 0;
    int contestant_num_byschedule;
    int start_time = 0;  //start time for each contestant

    for(int i=0; i<n; i++)
    {
        //tells which contestant is in order by schedule
        contestant_num_byschedule = sum_bikerun_time[i].second;

        //completion time for each constestant = when it started + his/her swimming time + his/her bike and run time
        completion_time[contestant_num_byschedule] = start_time + projected_time[contestant_num_byschedule][0] + sum_bikerun_time[i].first;

        //updating start time for next contestant in order
        //for next contestant, start time will be sum of previous start time of previous contestant and swimming time of previous contestant
        //since next contestant can only go after previous one is out of pool
        start_time += projected_time[contestant_num_byschedule][0];
    }
}


void print_schedule(int n)
{
    cout<<"\n\nSCHEDULE\n";
    cout<<"\nOrder for sending contestants: ";

    //contestants with decreasing order of sum of bike and run time
    for(int i=0; i<n; i++)
        cout<<"\nCONTESTANT "<<sum_bikerun_time[i].second;

    // triathlon will end with the longest completion time of a contestant(contestants are sent in order)
    int completion_time_triathlon = *max_element(completion_time, completion_time+n+1);
    cout<<"\nEarliest completion time is: "<<completion_time_triathlon;
}


int main()
{
    int n;
    cout<<"Enter total number of contestants: ";
    cin>>n;

    projected_time = new int*[n+1];
    for(int i=1; i<=n; i++)
        projected_time[i] = new int[3];

    cout<<"\nEnter projected time of each activity for each contestant.\n";

    for(int i=1; i<=n; i++)
    {
        cout<<"\nCONTESTANT "<<i<<" : \n";

        cout<<"\n\tEnter projected Swimming time: ";
        cin>>projected_time[i][0];

        cout<<"\n\tEnter projected Biking time: ";
        cin>>projected_time[i][1];

        cout<<"\n\tEnter projected Running time: ";
        cin>>projected_time[i][2];

        sum_bikerun_time.push_back( make_pair(projected_time[i][1] + projected_time[i][2], i));
    }

    scheduleTriathlon(n);
    print_schedule(n);

    return 0;
}


