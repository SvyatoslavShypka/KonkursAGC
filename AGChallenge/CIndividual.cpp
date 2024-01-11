#include "CIndividual.h"
#include "Evaluator.h"
#include <cstdlib>
#include <time.h>
#include <string> 
#include <random>

using namespace std;


CIndividual::CIndividual(int n) {
	genotyp.push_back(1);
	genotyp.push_back(0);
	genotyp.push_back(3);
	genotyp.push_back(1);

};

CIndividual::CIndividual() {};



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
	string result = "";
		for (int i : genotyp) {
			result += to_string(i);
	}
	return result; }

pair<CIndividual, CIndividual> CIndividual::crossover(const CIndividual& parent1, const CIndividual& parent2) {
	// Punkt krzyżowania
	int crossover_point = rand() % (parent1.genotyp.size() - 1) + 1;

	// Dziecko nr 1
	vector<int> child1_genotyp(parent1.genotyp.begin(), parent1.genotyp.begin() + crossover_point);
	child1_genotyp.insert(child1_genotyp.end(), parent2.genotyp.begin() + crossover_point, parent2.genotyp.end());
	CIndividual child1;
	child1.genotyp = child1_genotyp;

	// Dziecko nr 2
	vector<int> child2_genotyp(parent2.genotyp.begin(), parent2.genotyp.begin() + crossover_point);
	child2_genotyp.insert(child2_genotyp.end(), parent1.genotyp.begin() + crossover_point, parent1.genotyp.end());
	CIndividual child2;
	child2.genotyp = child2_genotyp;

	return make_pair(child1, child2);
}

void CIndividual::mutate(double mutProb) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);

	for (int i = 0; i < genotyp.size(); i++) {
		if (dis(gen) < mutProb) {
			// Mutacja genotypu
			int new_value = rand() % genotyp.size();
			genotyp[i] = new_value;
		}
	}
}




