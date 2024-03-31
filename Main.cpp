#include <iostream>
#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include <random>
#include <iostream>
#define NUMBER_OF_ITERATION 5

int main() {
	srand(time(NULL));
	CKnapsackProblem* ckp = new CKnapsackProblem();
	ckp->readFromFile("knapsack.txt");
	CGeneticAlgorithm* cga = new CGeneticAlgorithm(ckp, 12, 0.6, 0.9);
	CIndividual* ci = cga->generate(NUMBER_OF_ITERATION);
	ckp->show();
	std::cout << "Wynik: " << std::endl;
	ci->print();
	std::cout << ci->countFitness(&ckp) << std::endl;
}