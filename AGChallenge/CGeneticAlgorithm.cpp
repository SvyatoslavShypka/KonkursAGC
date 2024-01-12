#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

	CGeneticAlgorithm::CGeneticAlgorithm() {
		this->popSize = POPULATION_SIZE;
		this->crossProb = CROSS_PROBABILITY;
		this->mutProb = MUTATION_PROBABILITY;
		this->requestQuantity = REQUEST_QUANTITY;
		this->pathsQuantity = PATHS_QUANTITY;
		this->stopCriterion = STOP_CRITERION;
		this->evaluatorPointer = evaluatorPointer;

		for (int i = 0; i < popSize; i++)
		{
			vector<int> genotyp;	// First population is random
			for (int j = 0; j < evaluatorPointer->iGetNumberOfBits(); j++)
			{
				genotyp.push_back(CIndividual::randRange(0, pathsQuantity));
			}
			vectorPopulation.push_back(CIndividual(genotyp, evaluatorPointer));
		}
	};

	CGeneticAlgorithm::CGeneticAlgorithm(int popSize, double crossProb, double mutProb, int requestQuantity, int pathsQuantity, int stopCriterion, CLFLnetEvaluator* evaluatorPointer) {
		this->popSize = popSize;
		this->crossProb = crossProb;
		this->mutProb = mutProb;
		this->requestQuantity = requestQuantity;
		this->pathsQuantity = pathsQuantity;
		this->stopCriterion = stopCriterion;
		this->evaluatorPointer = evaluatorPointer;

		for (int i = 0; i < popSize; i++)
		{
			vector<int> genotyp;	// First population is random
			for (int j = 0; j < evaluatorPointer->iGetNumberOfBits(); j++)
			{
				genotyp.push_back(CIndividual::randRange(0, pathsQuantity));
				//genotyp.push_back(lRand(evaluatorPointer->iGetNumberOfValues(j)));
			}
			vectorPopulation.push_back(CIndividual(genotyp, evaluatorPointer));
		}
	}

	CGeneticAlgorithm::~CGeneticAlgorithm() {};

	CIndividual CGeneticAlgorithm::runOneIteration()
	{
		vector<CIndividual> parents, newPopulation;
		//printPopulation(vectorPopulation);
		while (newPopulation.size() < vectorPopulation.size())
		{
			// Selection of Individuals to cross:
			for (int i = 0; i <= 3; i++) // execute 4 times, choose four parents
			{
				int parentIndex = CIndividual::randRange(0, vectorPopulation.size() - 1);
				CIndividual candidate1 = vectorPopulation.at(parentIndex);
				CIndividual *candidat1Pointer = &vectorPopulation.at(parentIndex);

				//cout << "candidate1: " << candidate1.toString() << endl;
				parentIndex = CIndividual::randRange(0, vectorPopulation.size() - 1);
				CIndividual candidate2 = vectorPopulation.at(parentIndex);
				//cout << "candidate2??: " << candidate2.toString() << endl;
				CIndividual *candidat2Pointer = &vectorPopulation.at(parentIndex);
				//cout << "Pointers eaqual? :" << (candidat1Pointer == candidat2Pointer) << endl;
				while (candidat1Pointer == candidat2Pointer) {
					parentIndex = CIndividual::randRange(0, vectorPopulation.size() - 1);
					candidate2 = vectorPopulation.at(parentIndex);
					candidat2Pointer = &vectorPopulation.at(parentIndex);
				}
				//cout << "candidate2: " << candidate2.toString() << endl;
				CIndividual parent = candidate1.getFitness() > candidate2.getFitness() ? candidate1 : candidate2; // better candidate
				CIndividual *parentPointer = &parent;
				if (i > 0) {
					for (CIndividual parentInVector : parents) {
						if (&parentInVector == candidat1Pointer) {
							parent = candidate2;
						}
						else if (&parentInVector == candidat2Pointer) {
							parent = candidate1;
						}
					}
				}
				//cout << "parent: " << parent.toString() << endl;
				parents.push_back(parent);
			}
			//test
			vector<int> first = { 1,0,2,3,1,4 };
			vector<int> second = { 1,2,3,4,0,1 };
			vector<int> third = { 0,2,0,4,1,1 };
						parents.at(0) = CIndividual(first, evaluatorPointer);
			parents.at(1) = CIndividual(second, evaluatorPointer);
			parents.at(2) = CIndividual(third, evaluatorPointer);
			CIndividual childResult = parents.at(0).vCross(parents.at(1), parents.at(2));
			cout << "Test result: " << childResult.toString() << endl;
			//test-end

			// Parents crossing
			for (int i = 0; i <= 2; i = i + 2) {
				double randCross = dRand();
				//cout << "randCross: " << randCross << endl;
				if (randCross < crossProb) // cross probability
				{
					vector<CIndividual> children = parents.at(i).cross(parents.at(i + 1)); // cross parents 
					newPopulation.push_back(children.at(0)); //add childrens
					newPopulation.push_back(children.at(1));
				}
				else // no need of crossing
				{
					newPopulation.push_back(CIndividual(parents.at(i).getGenotyp(), evaluatorPointer)); // children like parents
					newPopulation.push_back(CIndividual(parents.at(i + 1).getGenotyp(), evaluatorPointer));
				}
			}
		} //while

		//Mutation
		//cout << "Population before mutation" << endl;
		//printPopulation(newPopulation);
		for (int i = 0; i < newPopulation.size(); i++) 
		{
			newPopulation.at(i).mutate(mutProb, pathsQuantity); // mutation probability is checked for each gene inside the mutate function
		}
		vectorPopulation = newPopulation; // replace old population by new one
		//cout << "Population after mutation" << endl;
		//printPopulation(newPopulation);
		// Look for the best individual
		CIndividual bestIndividual = vectorPopulation.at(0);
		for (int i = 1; i < vectorPopulation.size(); i++)
		{
			if (vectorPopulation.at(i).getFitness() > bestIndividual.getFitness()) { bestIndividual = vectorPopulation.at(i); }
		}
		//cout << "Best individual" << bestIndividual.toString() << endl;
		return bestIndividual;
	}

	void CGeneticAlgorithm::printPopulation(vector<CIndividual> vectorCIndividual) {
		//cout << "Vector population: " << vectorCIndividual.size() << ": ";
		for (int i = 0; i < vectorCIndividual.size(); i++) {
			cout << vectorCIndividual.at(i).toString();
		}
		cout << endl;
	}
