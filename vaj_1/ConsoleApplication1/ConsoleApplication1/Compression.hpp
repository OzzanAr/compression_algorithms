#ifndef COMPRESSION_HPP
#define COMPRESSION_HPP

#include <iostream>
#include <vector>
#include "BitWriter.hpp"

class Compression {
public:
	Compression() : bitWriter("output.bin") {}
	~Compression() = default;
	
	void compressInput(std::vector<uint8_t> &inputVector);
	BitWriter bitWriter;

private:
	// Methods for encoding bit differences
	void twoBitDifference(int8_t value);
	void threeBitDifference(int8_t value);
	void fourBitDifference(int8_t value);
	void fiveBitDifference(int8_t value);

	// Methods for encoding
	void differenceEncode(int8_t value);
	void absoluteEncode(int8_t value);
	void repetitionEncode(int8_t value);

};




#endif