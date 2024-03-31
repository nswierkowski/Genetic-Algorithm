#include "CKnapsackProblem.h"
#include <string>
#include <fstream>
#include <iostream>
#include <exception>

CKnapsackProblem::CKnapsackProblem()
{
	numberOfItems = 0;
	itemsSize = nullptr;
	values = nullptr;
	knapsackSize = 0;
}

CKnapsackProblem::CKnapsackProblem(int newNumberOfItems, float newKnapsackSize, float* newItemsSize, float* newValues)
{
	correctAttributes(newNumberOfItems, newKnapsackSize, newItemsSize, newValues);
	numberOfItems = newNumberOfItems;
	itemsSize = newItemsSize;
	values = newValues;
	knapsackSize = newKnapsackSize;
}

void CKnapsackProblem::correctAttributes(int newNumberOfItems, float newKnapsackSize, float*& newItemsSize, float*& newValues)
{
	if (newNumberOfItems < 0) throw std::runtime_error("Number of Item can't be negative number");
	if (newKnapsackSize < 0) throw std::runtime_error("Size of knapsack can't be negative number");
	for (int i = 0; i < newNumberOfItems; i++) {
		if(newItemsSize[i] < 0) throw std::runtime_error("In newItemSize one of the value is negative number");
		if(newValues[i] < 0) throw std::runtime_error("In newValues one of the value is negative number");
	}
}

CKnapsackProblem::~CKnapsackProblem()
{
	delete[] itemsSize;
	delete[] values;
}

int CKnapsackProblem::getNumberOfItems()
{
	return numberOfItems;
}

float CKnapsackProblem::getKnapsackSize()
{
	return knapsackSize;
}

float** CKnapsackProblem::getItemsSize()
{
	return &itemsSize;
}

float** CKnapsackProblem::getValues()
{
	return &values;
}

void CKnapsackProblem::readFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	int newNumberOfItems;
	float newKnapsackSize;
	if (file.is_open()) {
		file >> newNumberOfItems;
		file >> newKnapsackSize;
		float* newItemsSize = new float[newNumberOfItems];
		float* newValues = new float[newNumberOfItems];
		int i = 0;
		while (!file.fail()){
			file >> newValues[i];
			file >> newItemsSize[i];
			i++;
		}
		file.close();
		if(values != nullptr) delete[] values;
		if(itemsSize != nullptr) delete[] itemsSize;
		correctAttributes(numberOfItems, newKnapsackSize, newItemsSize, newValues);
		values = newValues;
		itemsSize = newItemsSize;
		knapsackSize = newKnapsackSize;
		numberOfItems = newNumberOfItems;
	}
	else {
		throw std::runtime_error("File not found");
	}
}

void CKnapsackProblem::show() {
	std::cout << "Waga przedmiotow: ";
	for (int i = 0; i < numberOfItems; i++) {
		std::cout << itemsSize[i] << " ";
	}
	std::cout << "\n";

	std::cout << "Wartosci: ";
	for (int i = 0; i < numberOfItems; i++) {
		std::cout << values[i] << " ";
	}
	std::cout << "\n";

	std::cout << "Rozmiar plecaka: " << knapsackSize << std::endl;
}
;
