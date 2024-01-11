﻿#include "CGeneticAlgorithm.h"
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
			vector<int> genotyp;	// First population is random
			//cout << "Create genotype..." << endl;
			//for (int j = 0; j < evaluatorPointer->iGetNumberOfBits(); j++)
			for (int j = 0; j < 4; j++)
			{
				//genotyp.push_back(lRand(evaluatorPointer->iGetNumberOfValues(j)));
				genotyp.push_back(CIndividual::randRange(0, 3));
				//cout << "evaluatorPointer->iGetNumberOfValues(j): " << evaluatorPointer->iGetNumberOfValues(j) << " ----//---- ";
				//cout << "genotype[" << j << "]: " << genotyp.at(j) << endl;
			}
			vectorPopulation.push_back(CIndividual(genotyp, evaluatorPointer));
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

	//void CGeneticAlgorithm::printPopulation() {
	//	//for (CIndividual* const& individual : *vectorPopulation) {
	//	//	cout << individual->toString() << ' ';
	//	//}
	//		
	//}

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
		printPopulation();
		while (newPopulation.size() < vectorPopulation.size()) // while new population is not full, keep adding individuals
		{
			//TODO
			// Selection of Individuals to cross:
			for (int i = 0; i <= 3; i++) // exectue twice, choose two parents
			{
				int parentIndex = CIndividual::randRange(0, vectorPopulation.size() - 1);
				CIndividual candidate1 = vectorPopulation.at(parentIndex);
				cout << "candidate1: " << candidate1.toString() << endl;
				CIndividual candidate2 = vectorPopulation.at(CIndividual::randRange(0, vectorPopulation.size() - 1));;
				cout << &candidate1 << " && " << &candidate2 << endl;
				while (&candidate1 == &candidate2) {
					cout << "while is here" << endl;
					candidate2 = vectorPopulation.at(CIndividual::randRange(0, vectorPopulation.size() - 1));
				}

				cout << "candidate2: " << candidate2.toString() << endl;
				CIndividual parent = candidate1.getFitness() > candidate2.getFitness() ? candidate1 : candidate2; // if candidate1 is better than candidate2, parent1 = candidate1, else parent1 = candidate2
				if (i > 0) {
					for (CIndividual parentInVector : parents) {
						if (&parentInVector == &candidate1) {
							parent = candidate2;
						}
						else if (&parentInVector == &candidate2) {
							parent = candidate1;
						}
					}
				}
				//cout << "candidate1.getFitness(): " << candidate1.getFitness() << endl;
				cout << "parent: " << parent.toString() << endl;
				parents.push_back(parent);
			}

			// Crossing:
			for (int i = 0; i <= 2; i = i + 2) {
				double randCross = dRand();
				cout << "randCross: " << randCross << endl;
				if (randCross < crossProb) // if crossover happens
				{
					vector<CIndividual> children = parents.at(i).cross(parents.at(i + 1)); // cross parents and add children to the new population
					newPopulation.push_back(children.at(0));
					newPopulation.push_back(children.at(1));
				}
				else // if crossover doesn't happen
				{
					newPopulation.push_back(CIndividual(parents.at(i).getGenotyp(), evaluatorPointer)); // simply add parents to the new population
					newPopulation.push_back(CIndividual(parents.at(i + 1).getGenotyp(), evaluatorPointer));
				}
			}
		} // end of while (newPopulation.size() < population.size())

		// Mutation:
		//for (int i = 0; i < newPopulation.size(); i++) // mutate each individual in the new population
		//{
		//	newPopulation.at(i).mutate(mutProb); // mutation probability is checked for each gene inside the mutate function
		//}
		//cout << vectorPopulation.at(0).toString() << endl;
		//printPopulation();
		vectorPopulation = newPopulation; // replace old population with the new one
		printPopulation();
		// Find the best individual to return:
		CIndividual bestIndividual = vectorPopulation.at(0);
		for (int i = 1; i < vectorPopulation.size(); i++)
		{
			if (vectorPopulation.at(i).getFitness() > bestIndividual.getFitness()) { bestIndividual = vectorPopulation.at(i); }
		}
		return bestIndividual;
	}

	void CGeneticAlgorithm::printPopulation() {
		cout << "Vector population: " << vectorPopulation.size() << ": ";

		for (CIndividual ind : vectorPopulation) {
			cout << ind.toString();
		}
		cout << endl;
	}


