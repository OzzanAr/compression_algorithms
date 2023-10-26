#include <iostream>
#include <vector>
#include <bitset>
#include "BitWriter.hpp"
#include "Compression.hpp"

int main() {
	std::vector<uint8_t> inputVector = { 55, 53, 53, 53, 53, 53, 10, 10, 11, 11 ,11, 11 };
	std::vector<uint8_t> inputVec = { 55, 75 };
	
	Compression compress;

	compress.compressInput(inputVector);




	return 0;
}