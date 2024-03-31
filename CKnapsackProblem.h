#pragma once
#include <string>

class CKnapsackProblem {
public:
	CKnapsackProblem();
	CKnapsackProblem(int newNumberOfItems, float newKnapsackSize, float* newItemsSize, float* newValues);
	~CKnapsackProblem();
	void readFromFile(std::string fileName);
	int getNumberOfItems();
	float getKnapsackSize();
	float** getItemsSize();
	float** getValues();
	void show();
private:
	void correctAttributes(int newNumberOfItems, float newKnapsackSize, float*& newItemsSize, float*& newValues);
	int numberOfItems;
	float* itemsSize;
	float* values;
	float knapsackSize;
};
