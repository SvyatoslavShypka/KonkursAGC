#include "CIndividual.h"
//#include "Evaluator.h"
//#include <cstdlib>
//#include <time.h>
//#include <string> 
#include <random>

using namespace std;


CIndividual::CIndividual(vector<int> genotyp, CLFLnetEvaluator* evaluatorPointer)
{
	this->genotyp = genotyp;
	this->evaluatorPointer = evaluatorPointer;
	this->fitness = NULL;
	//fitness = evaluatorPointer->dEvaluate(&genotyp);
}

//CIndividual::CIndividual(int n) {
//	genotyp.push_back(1);
//	genotyp.push_back(0);
//	genotyp.push_back(3);
//	genotyp.push_back(1);
//
//};

//CIndividual::CIndividual() {};



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

//pair<CIndividual, CIndividual> CIndividual::crossover(const CIndividual& parent1, const CIndividual& parent2) {
//	// Punkt krzyżowania
//	int crossover_point = rand() % (parent1.genotyp.size() - 1) + 1;
//
//	// Dziecko nr 1
//	vector<int> child1_genotyp(parent1.genotyp.begin(), parent1.genotyp.begin() + crossover_point);
//	child1_genotyp.insert(child1_genotyp.end(), parent2.genotyp.begin() + crossover_point, parent2.genotyp.end());
//	CIndividual child1;
//	child1.genotyp = child1_genotyp;
//
//	// Dziecko nr 2
//	vector<int> child2_genotyp(parent2.genotyp.begin(), parent2.genotyp.begin() + crossover_point);
//	child2_genotyp.insert(child2_genotyp.end(), parent1.genotyp.begin() + crossover_point, parent1.genotyp.end());
//	CIndividual child2;
//	child2.genotyp = child2_genotyp;
//
//	return make_pair(child1, child2);
//}

//void CIndividual::mutate(double mutProb) {
//	random_device rd;
//	mt19937 gen(rd());
//	uniform_real_distribution<> dis(0, 1);
//
//	for (int i = 0; i < genotyp.size(); i++) {
//		if (dis(gen) < mutProb) {
//			// Mutacja genotypu
//			int new_value = rand() % genotyp.size();
//			genotyp[i] = new_value;
//		}
//	}
//}


double CIndividual::getFitness()
{
	if (fitness == NULL) { fitness = evaluatorPointer->dEvaluate(&genotyp); }
	return fitness;
}

void CIndividual::mutate(double mutProb)
{
	for (int i = 0; i < genotyp.size(); i++) // For each gene roll if mutation should happen or not
	{
		if (dRand() < mutProb)
		{
			genotyp.at(i) = lRand(evaluatorPointer->iGetNumberOfValues(i));
			if (fitness != NULL) { fitness = NULL; } // If mutation happens, fitness needs to be recalculated
		}
	}
}

vector<CIndividual> CIndividual::cross(CIndividual& other)
{
	// randomize crossover point:
	int crossIndex = randRange(1, genotyp.size() - 1);
	cout << "paren1";
	cout << "paren1";

	vector<int> genotype1, genotype2;
	for (int i = 0; i < genotyp.size(); i++)
	{
		if (i < crossIndex)
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

	return vector<CIndividual> {CIndividual(genotype1, evaluatorPointer), CIndividual(genotype2, evaluatorPointer)};
}

int CIndividual::randRange(int from, int to)
{
	random_device					rand_dev;
	mt19937						generator(rand_dev());
	uniform_int_distribution<int>  distr(from, to);
	return distr(generator);
}




