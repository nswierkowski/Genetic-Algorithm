#pragma once
#include "CIndividual.h"
#include "CKnapsackProblem.h"

class CGeneticAlgorithm {
public:
	CGeneticAlgorithm();
	CGeneticAlgorithm(CKnapsackProblem* newProblem, int sizeOfPopulation, float crossPossibility, float mutationPossibility);
	CIndividual* generate(int numberOfIteration);
private:
	void createNewPopulation(CIndividual*& population);
	CIndividual* cross(CIndividual*& population);
	int chooseParent(CIndividual*& population);
	void mutation(CIndividual*& population);
	int popSize;
	float crossProb;
	float mutProb;
	CKnapsackProblem* problem;

};