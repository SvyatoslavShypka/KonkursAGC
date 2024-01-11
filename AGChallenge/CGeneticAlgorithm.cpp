#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include <vector>
#include <iostream>

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
				genotyp.push_back(lRand(evaluatorPointer->iGetNumberOfValues(j)));
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
			vector<int> genotype;	// First population is random
			for (int j = 0; j < evaluatorPointer->iGetNumberOfBits(); j++)
			{
				genotype.push_back(lRand(evaluatorPointer->iGetNumberOfValues(j)));
			}
			vectorPopulation.push_back(CIndividual(genotype, evaluatorPointer));
		}
	}


	// TODO deallocating memory
	CGeneticAlgorithm::~CGeneticAlgorithm() {};

	void CGeneticAlgorithm::vInitialize() {

		//for (int i = 0; i < popSize; i++) {
		//	CIndividual* obj1 = new CIndividual();
		//	obj1->genotypeGenerator(pathsQuantity);
		//	vectorPopulation->push_back(obj1);
		//}
	}

	void CGeneticAlgorithm::printPopulation() {
		//for (CIndividual* const& individual : *vectorPopulation) {
		//	cout << individual->toString() << ' ';
		//}
			
	}

	void runGeneticAlgorithm(int max_iterations) {
		int iterator = 0;

		while (iterator < max_iterations) {
			// Tutaj dodaj implementację kolejnych kroków algorytmu genetycznego:
			// - Ewaluacja osobników
			// - Selekcja
			// - Krzyżowanie
			// - Mutacja
			// - Aktualizacja najlepszego rozwiązania
			// - Sprawdzenie kryterium stopu

			iterator++;
		}
	}
	//TODO how to check and return bestResult
	//CIndividual* CGeneticAlgorithm::bestResult() const {
	//	return bestRes;
	//}


	CIndividual CGeneticAlgorithm::runOneIteration()
	{
		vector<CIndividual> parents, newPopulation;
		while (newPopulation.size() < vectorPopulation.size()) // while new population is not full, keep adding individuals
		{
			// Selection of Individuals to cross:
			for (int i = 0; i <= 1; i++) // exectue twice, choose two parents
			{
				CIndividual candidate1 = vectorPopulation.at(CIndividual::randRange(0, vectorPopulation.size() - 1));
				CIndividual candidate2 = vectorPopulation.at(CIndividual::randRange(0, vectorPopulation.size() - 1));
				CIndividual parent1 = candidate1.getFitness() > candidate2.getFitness() ? candidate1 : candidate2; // if candidate1 is better than candidate2, parent1 = candidate1, else parent1 = candidate2
				parents.push_back(parent1);
			}

			// Crossing:
			if (dRand() < crossProb) // if crossover happens
			{
				vector<CIndividual> children = parents.at(0).cross(parents.at(1)); // cross parents and add children to the new population
				newPopulation.push_back(children.at(0));
				newPopulation.push_back(children.at(1));
			}
			else // if crossover doesn't happen
			{
				newPopulation.push_back(parents.at(0)); // simply add parents to the new population
				newPopulation.push_back(parents.at(1));
			}
		} // end of while (newPopulation.size() < population.size())

		// Mutation:
		for (int i = 0; i < newPopulation.size(); i++) // mutate each individual in the new population
		{
			newPopulation.at(i).mutate(mutProb); // mutation probability is checked for each gene inside the mutate function
		}

		vectorPopulation = newPopulation; // replace old population with the new one

		// Find the best individual to return:
		CIndividual bestIndividual = vectorPopulation.at(0);
		for (int i = 1; i < vectorPopulation.size(); i++)
		{
			if (vectorPopulation.at(i).getFitness() > bestIndividual.getFitness()) { bestIndividual = vectorPopulation.at(i); }
		}
		return bestIndividual;
	}


