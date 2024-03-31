#pragma once
#include "CKnapsackProblem.h"

class CIndividual {
public:
	CIndividual();
	CIndividual(int* newSolution, int newLength);
	CIndividual(CIndividual&& cOther);
	~CIndividual();
	float getCountFitness(float knapsackSize, float** values, float** wages);
	void mutation(float mutProb);
	CIndividual* cross(CIndividual* parent, int index);
	void print();
	void setValue(int value, int index);
	int getValue(int index);
	void setAttributes(int* newSolution, int newLength);
	void operator=(CIndividual&& cOther);
	void operator=(const CIndividual& cOther);
	float countFitness(CKnapsackProblem** ckp);
private:
	int* solution;
	int length;
};
