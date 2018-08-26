#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>

void uniformDist(int bins[], int numLoops);
void triangluarDist(int bins[], int numLoops);
void graphBins(int bins[], int numLoops);
void printArray(int arry[], int size);
int sumArray(int arry[], int size);
void clearScreen();

int main(void) {
	int numLoops = 10000000;	// How many values that are to be binned
	int numBins = 10;			// Number of total bins
	int bins[numBins];
	clearScreen();
	
	// Fill bins array with zereos
	std::fill(bins,bins+numBins,0);
	std::cout << "============Uniform Distribution============\n";
	uniformDist(bins, numLoops);
	graphBins(bins,numLoops);
	std::cout << "\nThe frequency for numbers generated 0.0-0.1, 0.1-0.2,..., 0.9-1.0\n";
	printArray(bins, numBins);
	std::cout << "\n";
	std::cout << "The expected sum of the bin array is : " << numLoops << "\n";
	std::cout << "The actual sum of the bin array is: " << sumArray(bins,numBins) << "\n\n";;
	std::cout << "Please Press Enter to move to the next distribution: ";
	std::cin.get();
	clearScreen();
	
	// Reset the bins array
	std::fill(bins,bins+numBins,0); 
	std::cout << "============Triangular Distribution============\n";
	triangluarDist(bins,numLoops);
	graphBins(bins, numLoops);
	std::cout << "\nThe frequency for numbers generated between 0.0-0.1, 0.1-0.2,..., 0.9-1.0\n";
	printArray(bins, numBins);
	std::cout << "\n";
	std::cout << "The expected sum of the bin array is : " << numLoops << "\n";
	std::cout << "The actual sum of the bin array is: " << sumArray(bins,numBins) << "\n\n";
	
	return 0;
	
}

void uniformDist(int bins[], int numLoops) {
/* Function determines random numbers
 * between 0 and 1. The occurances of numbers 
 * in the range 0.0-0.1, 0.1-0.2, ...., 0.9-1.0
 * are stored in an array, where each index is refering
 * to one of these 10 ranges */
	
	// Create a seed
	srand(time(NULL));
	double randNum = 0;
	
	for(int loop=0; loop < numLoops; loop++) {
		randNum = ((double)rand()/RAND_MAX);
		randNum = floor(randNum*10);
		if(randNum >= 10.0) {
			randNum = 9.0;
		}
		bins[(int)randNum]++;
		
	}
}

void triangluarDist(int bins[], int numLoops) {
/* Function takes two random numbers between 0 and 1 and averages them.
 * The average of the two numbers is used to place them in a bin array
 * The bins are bucketing values between 0.0-0.1, 0.1-0.2,...,0.9-1.0*/
	 
	srand(time(NULL));		// Creating seed for random number generation
	double randNum = 0;
	
	for(int loop=0; loop<numLoops; loop++) {
		randNum = ((double)rand()/RAND_MAX);
		randNum += ((double)rand()/RAND_MAX);
		randNum /= (double)(2);
		randNum = floor(randNum*10);
		if(randNum >= 10.0) {
			randNum = 9.0;
		}
		bins[(int)randNum]++;
	}
}

void graphBins(int bins[], int numLoops) {
/* Graphs the values in the bin array in a scaled manner */

	int numPrints = 0;
	int graphScaling = numLoops/100;
	
	for(int counter=0; counter<10; counter++) {
		numPrints = (bins[counter]/graphScaling);
		std::cout << counter << "|";
		for(int numAstrix=0; numAstrix<numPrints; numAstrix++) {
			std::cout << "*";
		}
		std::cout << "\n";
	}
}

void printArray(int arry[], int size) {
	for(int i=0; i<size; i++) {
		std::cout << arry[i] << ",";
	}
	std::cout << "\n";
}

void clearScreen(){
	std::cout << std::string(100, '\n');
}

int sumArray(int arry[], int size) {
	int total = 0;
	for(int i=0; i<size; i++) {
		total += arry[i];
	}
	return total;
}