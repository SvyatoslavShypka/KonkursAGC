#pragma once
//#include <iostream>
#include <vector>
#include "Evaluator.h"

using namespace std;

class CIndividual {

private:
	
	vector<int> genotyp;
	//int start_number;
	//int end_number;
	//int rand_number;
	//int counter;
	double fitness;
	CLFLnetEvaluator* evaluatorPointer;

public:
	//CIndividual(int n);
	CIndividual(vector<int> genotyp, CLFLnetEvaluator* evaluatorPointer);
	//CIndividual(int n);
	//CIndividual();
	double fitnessIndividual(vector<int> genotyp);
	void genotypeGenerator(int n);
	void printGenotyp();
	string toString() const;
	//static pair<CIndividual, CIndividual> crossover(const CIndividual& parent1, const CIndividual& parent2);
	void mutate(double mutProb);

	double getFitness();
	//void mutate(float mutProb);
	vector<CIndividual> cross(CIndividual& other);
	inline vector<int> getGenotyp() { return genotyp; }

	static int randRange(int from, int to);

};

