#include "Optimizer.h"
//#include "CGeneticAlgorithm.h"

#include <cfloat>
#include <iostream>
#include <windows.h>

using namespace std;

COptimizer::COptimizer(CLFLnetEvaluator &cEvaluator)
	: c_evaluator(cEvaluator), c_genetic_algorithm(POPULATION_SIZE, CROSS_PROBABILITY, MUTATION_PROBABILITY, REQUEST_QUANTITY, PATHS_QUANTITY, STOP_CRITERION, &c_evaluator)
{
	random_device c_seed_generator;
	c_rand_engine.seed(c_seed_generator());

	d_current_best_fitness = 0;
}//COptimizer::COptimizer(CEvaluator &cEvaluator)

void COptimizer::vInitialize()
{
	d_current_best_fitness = -DBL_MAX;
	v_current_best.clear();
}//void COptimizer::vInitialize()

void COptimizer::vRunIteration()

{

	/*while ¬stopCondition do
	 newP op empty;
	while size(newP op) < size(population) do
	par1 ← selectIndividual(population);
	par2 ← selectIndividual(population);
	7: of f spr1, of f spr2 ← crossover(par1, par2);
	8: Mutate(of f spr1);
	9: Mutate(of f spr2);
	10: InsertToPopulation(newP op, of f spr1);
	11: InsertToPopulation(newP op, of f spr2);
	12: end while
		13 : population ← newP op;
	14: end while*/

	vector<int> v_candidate;
	v_fill_randomly(v_candidate);
	//v_candidate = c_genetic_algorithm.runOneIteration().getGenotyp();

	double d_candidate_fitness = c_evaluator.dEvaluate(&v_candidate);

	if (d_candidate_fitness > d_current_best_fitness)
	{
		v_current_best = v_candidate;
		d_current_best_fitness = d_candidate_fitness;

		cout << d_current_best_fitness << endl;
	}//if (d_candidate_fitness > d_current_best_fitness)
}//void COptimizer::vRunIteration()



void COptimizer::v_fill_randomly(vector<int> &vSolution)
{
	vSolution.resize((size_t)c_evaluator.iGetNumberOfBits());

	for (int ii = 0; ii < vSolution.size(); ii++)
	{
		vSolution.at(ii) = lRand(c_evaluator.iGetNumberOfValues(ii));
	}//for (size_t i = 0; i < vSolution.size(); i++)
}//void COptimizer::v_fill_randomly(const vector<int> &vSolution)
