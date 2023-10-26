#ifndef BITWRITER_HPP
#define BITWRITER_HPP

#include <iostream>
#include <fstream>

class BitWriter {
public:
	int k;
	std::ofstream f;
	char x;

	BitWriter(const char* p);
	~BitWriter();

	//void saveToFile(const char* p);
	void writeByte(char x);
	void writeTwoByte(int x);
	void writeInt(int y);
	void writeBit(bool b);
	void finish();
};

#endif
