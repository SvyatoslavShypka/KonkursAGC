#include "CGeneticAlgorithm.h"
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
		this->vectorPopulation = new vector<CIndividual>;
		this->evaluatorPointer = evaluatorPointer;
	};

	CGeneticAlgorithm::CGeneticAlgorithm(int popSize, double crossProb, double mutProb, int requestQuantity, int pathsQuantity, int stopCriterion, CLFLnetEvaluator* evaluatorPointer) {

		this->popSize = popSize;
		this->crossProb = crossProb;
		this->mutProb = mutProb;
		this->requestQuantity = requestQuantity;
		this->pathsQuantity = pathsQuantity;
		this->stopCriterion = stopCriterion;
		this->vectorPopulation = new vector<CIndividual*>;
		this->evaluatorPointer = evaluatorPointer;

	}


	// TODO deallocating memory
	CGeneticAlgorithm::~CGeneticAlgorithm() {};

	void CGeneticAlgorithm::vInitialize() {

		for (int i = 0; i < popSize; i++) {
			CIndividual* obj1 = new CIndividual();
			obj1->genotypeGenerator(pathsQuantity);
			vectorPopulation->push_back(obj1);
		}
	}

	void CGeneticAlgorithm::printPopulation() {
		for (CIndividual* const& individual : *vectorPopulation) {
			cout << individual->toString() << ' ';
		}
			
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
	CIndividual* CGeneticAlgorithm::bestResult() const {
		return bestRes;
	}

	


