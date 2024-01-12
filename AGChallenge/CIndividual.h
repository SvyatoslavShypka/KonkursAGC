#pragma once
#include <vector>
#include "Evaluator.h"

using namespace std;

class CIndividual {

private:
	vector<int> genotyp;
	double fitness;
	CLFLnetEvaluator* evaluatorPointer;

public:
	CIndividual(vector<int> genotyp, CLFLnetEvaluator* evaluatorPointer);
	string toString() const;
	void mutate(double mutProb, int pathsQuantity);

	double getFitness();
	vector<CIndividual> cross(CIndividual& other);
	inline vector<int> getGenotyp() { return genotyp; }
	static int randRange(int from, int to);
};

