#ifndef COMPRESSION_HPP
#define COMPRESSION_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "BitWriter.hpp"

class Compression {
public:
	Compression() : bitWriter("output.bin") {}
	~Compression() = default;
	BitWriter bitWriter;

	void compress(std::vector<std::vector<int>> P, int width, int height);


private:
	void predict(std::vector<int>& E, std::vector<std::vector<int>> P, int width, int height);
	void IC(std::vector<int> C, int low, int H);
	void encode(int g, int diff);
};

#endif