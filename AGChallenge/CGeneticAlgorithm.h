#pragma once
#include <vector>
#include "CIndividual.h"

class CGeneticAlgorithm {

private:
	int popSize;
	double crossProb;
	double mutProb;
	int stopCriterion;

	int requestQuantity; // ilosc żądań
	int pathsQuantity; // np. 0-3 dostepne sciezki 
	vector<CIndividual> vectorPopulation;
	CLFLnetEvaluator* evaluatorPointer;

public:
	CGeneticAlgorithm();
	CGeneticAlgorithm(int popSize, double crossProb, double mutProb, int requestQuantity, int pathsQuantity, int stopCriterion, CLFLnetEvaluator* evaluatorPointer);
	~CGeneticAlgorithm();
	void printPopulation(vector<CIndividual> vectorCIndividual);
	CIndividual runOneIteration();
};

const int POPULATION_SIZE = 4;
const double CROSS_PROBABILITY = 0.6;
const double MUTATION_PROBABILITY = 0.1;
const int REQUEST_QUANTITY = 4;
const int PATHS_QUANTITY = 4;
const int STOP_CRITERION = 6;
