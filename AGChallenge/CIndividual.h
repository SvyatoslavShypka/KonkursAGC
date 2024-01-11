#pragma once
#include <iostream>
#include <vector>

using namespace std;

class CIndividual {

private:
	
	vector<int> genotyp;
	int start_number;
	int end_number;
	int rand_number;
	int counter;

public:
	//CIndividual(int n);
	CIndividual::CIndividual(int n);
	CIndividual::CIndividual();
	double fitnessIndividual(vector<int> genotyp);
	void genotypeGenerator(int n);
	void printGenotyp();
	string toString() const;
	static pair<CIndividual, CIndividual> crossover(const CIndividual& parent1, const CIndividual& parent2);
	void mutate(double mutProb);

};
