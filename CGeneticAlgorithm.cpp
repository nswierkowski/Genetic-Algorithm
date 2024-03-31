#include "CGeneticAlgorithm.h"
#include <iostream>

CGeneticAlgorithm::CGeneticAlgorithm()
{
	popSize = 0;
	crossProb = 0;
	mutProb = 0;
	problem = nullptr;
}

CGeneticAlgorithm::CGeneticAlgorithm(CKnapsackProblem* newProblem, int newSizeOfPopulation, float newCrossPossibility, float newMutationPossibility)
{
	problem = newProblem;
	popSize = newSizeOfPopulation;
	crossProb = newCrossPossibility;
	mutProb = newMutationPossibility;
}

CIndividual* CGeneticAlgorithm::generate(int numberOfIteration)
{
	int* newSolution;
	CIndividual* population = new CIndividual[popSize];
	for (int i = 0; i < popSize; i++) {
		newSolution = new int[problem->getNumberOfItems()];
		for (int j = 0; j < problem->getNumberOfItems(); j++) {
			newSolution[j] = rand() % 2;
		}
		population[i].setAttributes(newSolution, problem->getNumberOfItems());
	}

	for (int i = 0; i < numberOfIteration; i++) {
		createNewPopulation(population);
		mutation(population);
		for (int j = 0; j < numberOfIteration; j++) {
			population[j].print();
			std::cout << population[j].countFitness(&problem) << std::endl;
		}
		std::cout << i << std::endl;
		std::cout << "\n";
	}

	int bestFit = population[0].countFitness(&problem);
	int indexOfBest = 0;
	for (int i = 1; i < popSize; i++) {
		int newOne = population[i].countFitness(&problem);
		if (newOne > bestFit) {
			bestFit = newOne;
			indexOfBest = i;
		}
	}
	CIndividual* theBest = new CIndividual(std::move(population[indexOfBest]));
	delete[] population;
	return theBest;
}

void CGeneticAlgorithm::createNewPopulation(CIndividual*& population)
{

	CIndividual* newPopulation = new CIndividual[popSize];
	int j = -1;
	if (popSize % 2 == 1) j = rand() % popSize;
	int i = 0;
	while (i < popSize)
	{
		CIndividual* newChildren = cross(population);
		if (i == j) {
			newPopulation[i] = population[i];
		}
		else {
			newPopulation[i] = std::move(newChildren[0]);
		}
		if(i < popSize-1) newPopulation[++i] = std::move(newChildren[1]);
		i++;
		delete[] newChildren;
	}

	delete[] population;
	population = newPopulation;
}

int CGeneticAlgorithm::chooseParent(CIndividual*& population)
{
	int firstPotentialParent = rand() % popSize;
	int secondPotentialParent = rand() % popSize;
	while (firstPotentialParent == secondPotentialParent) {
		secondPotentialParent = rand() % popSize;
	}
	if (population[firstPotentialParent].countFitness(&problem) > population[secondPotentialParent].countFitness(&problem)) return firstPotentialParent;
	else return secondPotentialParent;
}

CIndividual* CGeneticAlgorithm::cross(CIndividual*& population)
{
	int firstParent = chooseParent(population);
	int secondParent = chooseParent(population);
	float chanceForCross = (rand() % 101) / 100.0;

	CIndividual* children;
	if (crossProb > chanceForCross) {
		int splitIndex = rand() % (problem->getNumberOfItems());
		children = population[firstParent].cross(&population[secondParent], splitIndex);
	}
	else {
		children = new CIndividual[2];
		children[0] = population[firstParent];
		children[1] = population[secondParent];
	}
	return children;
}

void CGeneticAlgorithm::mutation(CIndividual*& population)
{
	for (int i = 0; i < popSize; i++) {
		population[i].mutation(mutProb);
	}
}

;