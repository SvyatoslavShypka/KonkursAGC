﻿#include "CIndividual.h"
#include <random>

using namespace std;

CIndividual::CIndividual(vector<int> genotyp, CLFLnetEvaluator* evaluatorPointer)
{
	this->genotyp = genotyp;
	this->evaluatorPointer = evaluatorPointer;
	this->fitness = NULL;
}

string CIndividual::toString() const {
	string result = "*";
		for (int i : genotyp) {
			result += to_string(i);
	}
	return result + "*"; }

double CIndividual::getFitness()
{
	if (fitness == NULL) { fitness = evaluatorPointer->dEvaluate(&genotyp); }
	return fitness;
}

void CIndividual::mutate(double mutProb, int pathsQuantity)
{
	for (int i = 0; i < genotyp.size(); i++) 
	{
		double isMutated = dRand();
		//cout << this->toString() << isMutated << endl;
		if (isMutated < mutProb)
		{
			genotyp.at(i) = randRange(0, pathsQuantity - 1);
			//cout << "Mutation index: " << i << endl;
			if (fitness != NULL) { fitness = NULL; } // new genotype - new fitness
			//cout << this->toString() << endl;
		}
	}
}

vector<CIndividual> CIndividual::cross(CIndividual& other)
{
	// cross and create children
	int crossPunkt = randRange(1, genotyp.size() - 1);
	//cout << "crossPunkt: " << crossPunkt << endl;
	//cout << "paren1: " << this->toString() << endl;
	//cout << "paren2: " << other.toString() << endl;

	vector<int> genotype1, genotype2;
	for (int i = 0; i < genotyp.size(); i++)
	{
		if (i < crossPunkt)
		{
			genotype1.push_back(genotyp.at(i));
			genotype2.push_back(other.genotyp.at(i));
		}
		else
		{
			genotype1.push_back(other.genotyp.at(i));
			genotype2.push_back(genotyp.at(i));
		}
	}
	vector<CIndividual> children = vector<CIndividual>{ CIndividual(genotype1, evaluatorPointer), CIndividual(genotype2, evaluatorPointer) };
	//cout << "child1: " << children.at(0).toString() << endl;
	//cout << "child2: " << children.at(1).toString() << endl;
	return children;
}



CIndividual CIndividual::vCross(CIndividual& second, CIndividual& third)
{
	vector<int> resultGenotype = this->genotyp;
	for (int i = 0; i < genotyp.size(); i++)
	{
		if (second.getGenotyp().at(i) == third.getGenotyp().at(i))
		{
			resultGenotype.at(i) = second.getGenotyp().at(i);
		}
		else {
			resultGenotype.at(i) = genotyp.at(i);
		}
	}
	return CIndividual(resultGenotype, evaluatorPointer);
}

int CIndividual::randRange(int from, int to)
{
	random_device					rand_dev;
	mt19937						generator(rand_dev());
	uniform_int_distribution<int>  distr(from, to);
	return distr(generator);
}
