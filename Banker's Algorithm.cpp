#include <pthread.h>
#include <iostream>
using namespace std;

// Number of processes
const int numcustomers = 4;

// Number of resources
const int numresources = 3;
pthread_t custoers[4];
int processes[numcustomers];
int avail[numcustomers];
int maxm[numcustomers][numresources];
int allocated[numcustomers][numresources];
bool finish[numcustomers];
pthread_mutex_t customerlock;

// Threads creation is implemented here
// Function to find the need of each process
void calcNeed(int need[numresources],int procindex)
{
    // Calculating Need of each P
        for (int j = 0 ; j < numresources ; j++){
            // we made a nested loop to loop through each element in maximum and allocated to find the need for each process
            need[j] = maxm[procindex][j] - allocated[procindex][j];
        }
}

// function to implement safety algorithm and is passed to it the four arrays
bool isSafe(int customers[], int available[], int maximum[][numresources],int allocated[][numresources])
{
    int need[numresources];

    // First we find the need for the passed arrays
    calcNeed(need, +);

    // the we make every finish is false by default
    bool finish[numcustomers] = {false};

    // This is to save the safe sequence that commits to the algorithm
    int safeSeq[numcustomers];

    // COPY AVAILABLE INTO WORK
    int work[numresources];
    for(int i = 0; i < numresources ; i++)
        work[i] = available[i];
    // While all processes are not finished
    // or system is not in safe state.
    int counter = 0;
    while (counter < numcustomers)
    {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        bool found = false;
        for (int p = 0; p < numcustomers; p++)
        {
            // HERE WE MUST MAKE A QUICK CHECK IF IT'S TRUE OR NOT
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < numresources; j++)
                    if (need[p][j] > work[j])
                        break;

                // If all needs of p were satisfied.
                if (j == numresources)
                {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources free the resources

                    for (int k = 0 ; k < numresources ; k++)
                        work[k] += allocated[p][k];
                    // AND NOW WE Add this process to safe sequence.





                    safeSeq[counter++] = p;

                    // Mark this p as finished
                    finish[p] = true;

                    found = true;
                }
            }
        }

        // If we could not find a next process in safe
        // sequence.
        if (found == false)
        {
            cout << "Deadlock might happen, system isn't in safe state";
            return false;
        }
    }

    // If system is in safe state then
    // safe sequence will be as below
    cout << "Don't worry, No Deadlocks\nSafe"
         " sequence is: ";
    for (int i = 0; i < numcustomers ; i++)
        cout << safeSeq[i] << " ";

    return true;
}

// Driver code
int main()
{
    int processes[] = {0, 1, 2, 3};
    int avail[] = {3, 3, 2};
    int maxm[][numresources] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2}};
    int allocated[][numresources] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1}};
    isSafe(processes, avail, maxm, allocated);
    return 0;
}
/* please try this sequence also it will produce a deadlock
    int maxm[][numresources] = {{7, 5, 3},
                     {5, 2, 6},
                     {7, 0, 2},
                     {7, 2, 4}};*/
