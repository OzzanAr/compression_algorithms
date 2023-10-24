#ifndef BITWRITER_HPP
#define BITWRITER_HPP

#include <iostream>
#include <fstream>

class BinWriter {
public:
	int k;
	std::ofstream f;
	char x;

	BinWriter(const char* p);
	~BinWriter();

	void writeByte(char x);
	void writeTwoByte(int x);
	void writeInt(int y);
	void writeBit(bool b);
};

#endif
