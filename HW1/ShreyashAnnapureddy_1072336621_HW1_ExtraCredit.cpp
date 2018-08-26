#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>

void paretoDistribution(int bins[], int numLoops);
void printBins(int bins[], int numLoops);
void printArray(int arry[], int size);
int sumArray(int arry[], int size);

int main(void) {
	
	int numLoops = 120;			// How many values that are to be binned
	int binLen = 10;			// Number of total bins
	int bins[binLen];
	
	
	std::fill(bins,bins+binLen,0);
	std::cout << "============Pareto Distribution============\n";
	paretoDistribution(bins,numLoops);
	printBins(bins, numLoops);
	std::cout << "\nThe frequency for numbers generated 0.0-0.1, 0.1-0.2,..., 0.9-1.0\n";
	printArray(bins,binLen);
	std::cout << "\n";
	std::cout << "The expected sum of the bin array is : " << numLoops << "\n";
	std::cout << "The actual sum of the bin array is: " << sumArray(bins,binLen) << "\n";
	return 0;
}

void paretoDistribution(int bins[], int numLoops) {
	/* Function determines values from a pareto distribution
	 * The values are then normalized to be between 1 and 0.
	 * The values are then placed in buckets based on the following
	 * ranges:
	 * 		0.0 - 0.1
	 * 		0.1 - 0.2
	 * 		0.3 - 0.4
	 * 		0.4 - 0.5
	 * 		.........
	 * 		0.9 - 1.0 												*/
	
	// alpha, scale pareto distribution tuning parameters
	double alpha = 1500.0;
	
	double p = 0.0;				// p is a number generated from the pareto distribution
	double pNorm = 0.0;			// pNorm is normalised value of p between 0 and 1
	double pMax = -1000000.0;
	double pMin = 1000000.0;
	
	double randNum = 0;
	unsigned int seed = time(NULL);		// Seed reuse to rescale the pareto distribution
	srand(seed);
	
	// Using a known seed, determine the max an min p values in order to
	// nomralize data between 0 and 1
	for(int loop=0; loop < numLoops; loop++) {
		randNum = (double)rand()/RAND_MAX;
		p = (double)1/pow(randNum, 1/alpha);		//Calculating Pareto value using 1/randNum^(1/a)
		if(p > pMax){
			pMax = p;
		} else if(p < pMin) {
			pMin = p;
		}
	}

	
	srand(seed);
	// Using the known seed recalculate the p values and normalize between 0 and 1 
	for(int loop=0; loop < numLoops; loop++) {
		
		randNum = (double)rand()/RAND_MAX;
		p = (double)1/pow(randNum, 1/alpha);		//Calculating Pareto value using 1/randNum^(1/a)
		pNorm = (p-pMin)/(pMax-pMin);				// Normalzing Pareto value to be between 1 and 0
		pNorm = floor(pNorm*10);					// Rounding value to between 0 and 9 i.e. index in bins array to increment
		if(pNorm >= 10.0) {
			pNorm = 9.0;
		}
		bins[(int)pNorm]++;
	}
}

void printBins(int bins[], int numLoops) {
	
	
	for(int counter=0; counter<10; counter++) {
		std::cout << counter << "|";
		for(int numAstrix=0; numAstrix<bins[counter]; numAstrix++) {
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

int sumArray(int arry[], int size) {
	int total = 0;
	for(int i=0; i<size; i++) {
		total += arry[i];
	}
	return total;
}