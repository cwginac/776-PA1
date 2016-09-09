#include <iostream>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <time.h>

using namespace std;

double eval(int *pj);
void printArray(int* iArray);
void increment(int* iArray);
void init(int* iArray);
void copy(int* fromArray, int* toArray);
void thread_entry(int* bestArray, double* bestFitness, int threadId);

int main()
{
	// Seed random number generator
	srand(time(NULL));
	
	// Overall best array
	int bestArray[100];
	double bestFitness = 0;
	
	// Spawn threads
	vector<thread> threads;
	for(int i = 0; i < 4; i++) //4 is the number of cores my laptop has
	{
		threads.push_back(thread(thread_entry, bestArray, &bestFitness, i));
	}
	
	// Join threads
	for(auto& th : threads) th.join();
	
	// Once threads are finished, print out the best array and it's fitness.
	cout << "Best Fitness: " << bestFitness;
	printArray(bestArray);
}

void copy(int* fromArray, int* toArray)
{
	for(int i = 0; i < 100; i++)
	{
    	toArray[i] = fromArray[i];
 	}
}

void init(int* iArray)
{
	for(int i = 0; i < 100; i++)
	{
		iArray[i] = rand() % 2; // Generates random number bit.
	}
}

void increment(int* iArray)
{
    for (int i = 99; i >= 0; i--)
    {
        if (iArray[i] == 0)
        {
            iArray[i] = 1;
            return;
        }
        else
        {
            iArray[i] = 0;
        }
    }
}

void printArray(int* iArray)
{
	cout << "[";
	
	for (int i = 0; i < 99; i++)
    {
        cout << iArray[i] << ",";
    }
    cout << iArray[99];
    cout << "]" << endl;
}

void thread_entry(int* bestArray, double* bestFitness, int threadId)
{
	long randomCounter = 0;
	
	double oldFitness = 0;
	int oldArray[100];
	double newFitness = 0;
	int newArray[100];
	
	// Generate X amount of random starting points per thread.
	while(randomCounter < 10000000)//2000000000)
	{
		// Print out status of search every so often
		if(randomCounter % 100000 == 0)
		{
			system("clear");
			cout << ((double)(randomCounter)/(double)(10000000)) * 100.0 << "% random starting points explored on thread " << threadId << endl;
			cout << "Current Maximum: " << *bestFitness << endl;
		}
		
		// Find a new random starting point
		init(newArray);
		oldFitness = 0;
		newFitness = eval(newArray);
		
		// While the new point is higher, keep climbing
		while(newFitness > oldFitness)
		{
			copy(newArray, oldArray);
			oldFitness = newFitness;
			
			increment(newArray);
			newFitness = eval(newArray);	
		}
		
		// If this local maxima is better than the best known maxima, then save it off.
		if(oldFitness > *bestFitness)
		{
			copy(oldArray, bestArray);
			*bestFitness = oldFitness;
			cout << "New Maximum: " << newFitness << endl;
		}
		
		randomCounter++;
	}
}
