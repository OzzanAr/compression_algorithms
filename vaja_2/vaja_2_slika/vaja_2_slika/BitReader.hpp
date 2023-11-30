#ifndef BITREADER_HPP
#define BITREADER_HPP

#include <iostream>
#include <fstream>
using namespace std;

class BitReader {
public:
	int k;
	ifstream f;
	char x;

	BitReader(const char* p);

	char readByte();
	int readTwoBytes();
	int readFourBytes();
	bool readBit();
	bool isEOF() const;
};

#endif