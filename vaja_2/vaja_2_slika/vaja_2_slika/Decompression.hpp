#ifndef DECOMPRESSION_HPP
#define DECOMPRESSION_HPP


#include <vector>
#include <cmath>
#include "BitWriter.hpp"
#include "BitReader.hpp"




class Decompression {
public:
	Decompression() : reader("output.bin") {}
	~Decompression() = default;
	std::vector<std::vector<int>> decompress();
	BitReader reader;

private:
	void decodeHeader(int& height, int& n, int& cFirst, int& cLast);
	int getBits(int g);
	void DeIC(std::vector<int>& C, int L, int H);
	std::vector<std::vector<int>> predictInverse(std::vector<int> E, int width, int height);

};


#endif // !DECOMPRESSION_HPP
