#include <iostream>
#include <vector>
#include <bitset>
#include "BitWriter.hpp"
#include "BitReader.hpp"
#include "Compression.hpp"
#include "Decompression.hpp"

int main() {
	std::vector<uint8_t> inputVector = { 55, 53, 53, 53, 53, 53, 10, 10, 11, 11 ,11, 11 };
	std::vector<uint8_t> inputVec = { 55, 10 };
	
	Compression compress;

    
	compress.compressInput(inputVec);

    std::cout << std::endl;

	Decompression decompress;

	decompress.decompress();

    std::vector<uint8_t> outputVector;


	return 0;
}