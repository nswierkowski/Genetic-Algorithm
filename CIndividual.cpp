#include "CIndividual.h"
#include <iostream>
#include <random>

CIndividual::CIndividual()
{
	length = 0;
	solution = nullptr;
}

CIndividual::CIndividual(int* newSolution, int newLength)
{
	length = newLength;
	solution = newSolution;
}

CIndividual::CIndividual(CIndividual&& cOther)
{
	length = cOther.length;
	solution = cOther.solution;
	cOther.solution = nullptr;
}

CIndividual::~CIndividual()
{
	if (solution != nullptr) delete[] solution;
}

void CIndividual::setAttributes(int* newSolution, int newLength)
{
	if (solution != nullptr) {
		delete[] solution;
	}
	solution = newSolution;
	length = newLength;
}

void CIndividual::operator=(CIndividual&& cOther)
{
	if (solution != nullptr) {
		delete[] solution;
	}
	solution = cOther.solution;
	length = cOther.length;
	cOther.solution = nullptr;
}

void CIndividual::operator=(const CIndividual& cOther)
{
	if (solution != nullptr) {
		delete[] solution;
	}
	length = cOther.length;
	solution = new int[length];
	for (int i = 0; i < length; i++) {
		solution[i] = cOther.solution[i];
	}
}

float CIndividual::countFitness(CKnapsackProblem** ckp)
{
	int valuesSum = 0;
	float wage = 0.0;
	float* pvalue = *((*ckp)->getValues());
	float* pwages = *((*ckp)->getItemsSize());
	for (int i = 0; i < length; i++) {
		valuesSum += pvalue[i] * solution[i];
		wage += pwages[i] * solution[i];
	}
	if (wage > (*ckp)->getKnapsackSize()) return 0;
	else return valuesSum;
}

float CIndividual::getCountFitness(float knapsackSize, float** values, float** wages)
{
	int valuesSum = 0;
	float wage = 0.0;
	float* pvalue = *values;
	float* pwages = *wages;
	for (int i = 0; i < length; i++) {
		valuesSum += pvalue[i] * solution[i];
		wage += pwages[i] * solution[i];
	}

	if (wage > knapsackSize) return 0;
	else return valuesSum;
}

void CIndividual::mutation(float mutProb)
{
	for (int i = 0; i < length; i++) {
		float mut = (rand() % 101);
		if(mutProb*100 > mut) {
			solution[i] = 1 - solution[i];
		}
	}
}

void CIndividual::setValue(int value, int index)
{
	solution[index] = value;
}

CIndividual* CIndividual::cross(CIndividual* parent, int index)
{
	int* firstChildsSolution = new int[length];
	int* secondChildsSolution = new int[length];
	for (int i = 0; i < length; i++) {
		if (i <= index) {
			firstChildsSolution[i] = solution[i];
			secondChildsSolution[i] = parent->getValue(i);
		}
		else {
			firstChildsSolution[i] = parent->getValue(i);
			secondChildsSolution[i] = solution[i];
		}
	}

	CIndividual* children = new CIndividual[2];
	children[0].setAttributes(firstChildsSolution, length);
	children[1].setAttributes(secondChildsSolution, length);

	return children;
}

int CIndividual::getValue(int index)
{
	return solution[index];
}

void CIndividual::print()
{
	for (int i = 0; i < length; i++)
	{
		std::cout << solution[i];
	}
	std::cout << "\n";
}
;