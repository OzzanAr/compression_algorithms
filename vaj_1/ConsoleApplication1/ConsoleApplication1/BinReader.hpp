#ifndef BINREADER_HPP
#define BINREADER_HPP

#include <iostream>
#include <fstream>
using namespace std;

class BinReader {
public:
	int k;
	ifstream f;
	char x;

	BinReader(const char* p);

	char readByte();
	bool readBit();
};

#endif