#include <iostream>
#include <vector>

int main() {
	std::vector<uint8_t> inputVector = { 55, 53, 53, 53, 53, 53, 10, 10, 11, 11 ,11, 11 };
	std::vector<int> differenceVector; 

	differenceVector.push_back(inputVector[0]);
	for (int i = 1; i < inputVector.size(); i++) {
		differenceVector.push_back(inputVector[i] - inputVector[i - 1]);
	}

	for (int i = 0; i < differenceVector.size(); i++)
		std::cout << differenceVector.at(i) << ' ';



	return 0;
}