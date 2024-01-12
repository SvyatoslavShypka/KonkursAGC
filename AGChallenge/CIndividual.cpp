#include "CIndividual.h"
#include <random>

using namespace std;


CIndividual::CIndividual(vector<int> genotyp, CLFLnetEvaluator* evaluatorPointer)
{
	this->genotyp = genotyp;
	this->evaluatorPointer = evaluatorPointer;
	this->fitness = NULL;
}

double CIndividual::fitnessIndividual(vector<int> genotyp) {
	CLFLnetEvaluator eval;
	return eval.dEvaluate(&genotyp);
}

void CIndividual::genotypeGenerator(int n) {
	
	int start_number = 0;
	int rand_number;
	
	for (int i = 0; i < n; i++) {
		rand_number = rand() % n + start_number;
		//cout << rand_number << endl;
		genotyp.push_back(rand_number);
	}
}

void CIndividual::printGenotyp() {
	for (int i : genotyp)
		cout << i << ' ';
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
	for (int i = 0; i < genotyp.size(); i++) // For each gene roll if mutation should happen or not
	{
		double isMutated = dRand();
		cout << this->toString() << isMutated << endl;
		if (isMutated < mutProb)
		{
			genotyp.at(i) = randRange(0, pathsQuantity - 1);
			cout << "Mutation index: " << i << endl;
			if (fitness != NULL) { fitness = NULL; } // If mutation happens, fitness needs to be recalculated
			cout << this->toString() << endl;
		}
	}
}

vector<CIndividual> CIndividual::cross(CIndividual& other)
{
	// cross and create children
	int crossPunkt = randRange(1, genotyp.size() - 1);
	cout << "crossPunkt: " << crossPunkt << endl;
	cout << "paren1: " << this->toString() << endl;
	cout << "paren2: " << other.toString() << endl;

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
	cout << "child1: " << children.at(0).toString() << endl;
	cout << "child2: " << children.at(1).toString() << endl;
	return children;
}

int CIndividual::randRange(int from, int to)
{
	random_device					rand_dev;
	mt19937						generator(rand_dev());
	uniform_int_distribution<int>  distr(from, to);
	return distr(generator);
}
