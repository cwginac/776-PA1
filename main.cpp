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
	srand(time(NULL));
	// Overall best array
	int bestArray[100];
	double bestFitness = 0;
	
	vector<thread> threads;
	for(int i = 0; i < 4; i++) //4 is the number of cores my laptop has
	{
		threads.push_back(thread(thread_entry, bestArray, &bestFitness, i));
	}
	
	for(auto& th : threads) th.join();
	
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
		iArray[i] = rand()%2;
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
	
	for (int i = 0; i < 100; i++)
    {
        cout << iArray[i] << ",";
    }
    cout << "]" << endl;
}

void thread_entry(int* bestArray, double* bestFitness, int threadId)
{
	long randomCounter = 0;
	
	double oldFitness = 0;
	int oldArray[100];
	double newFitness = 0;
	int newArray[100];
	
	while(randomCounter < 10000000)//2000000000)
	{
		if(randomCounter % 100000 == 0)
		{
			cout << ((double)(randomCounter)/(double)(10000000)) * 100.0 << "% random starting points explored on thread " << threadId << endl;
		}
		// Find a new random starting point
		init(newArray);
		
		newFitness = eval(newArray);
		while(newFitness > oldFitness)
		{
			copy(newArray, oldArray);
			oldFitness = newFitness;
			
			increment(newArray);
			newFitness = eval(newArray);	
		}
		
		if(oldFitness > *bestFitness)
		{
			copy(oldArray, bestArray);
			*bestFitness = oldFitness;
			cout << "New Maximum: " << newFitness << endl;
		}
		
		randomCounter++;
	}
}
