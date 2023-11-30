#ifndef DECOMPRESSION_HPP
#define DECOMPRESSION_HPP

#include <vector>
#include "BitWriter.hpp"

class Decompression {
public:
	std::vector<uint8_t> decompress(int *outputSize);

private:
	int8_t twoDifference(int);
	int8_t threeDifference(int);
	int8_t fourDifference(int);
	int8_t fiveDifference(int);

};


#endif // !DECOMPRESSION_HPP
