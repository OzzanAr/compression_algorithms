#include "BitWriter.hpp"
#include <iostream>

BitWriter::BitWriter(const char* p) : k(0) {
	f.open(p, std::ios::binary);
}

BitWriter::~BitWriter() {
	if (k > 0) writeByte(x);
	f.close();
}

void BitWriter::writeByte(char x) {
	f.write((char*)&x, 1);
}

void BitWriter::writeTwoByte(int x) {
	f.write((char*)&x, 2);
}

void BitWriter::writeInt(int y) {
	f.write((char*)&y, 4);
}

void BitWriter::writeBit(bool b) {
	if (k == 8) {
		writeByte(x);
		k = 0;
		x = 0;
	}
	x ^= (-b ^ x) & (1 << k);
	k++;
	std::cout << (b) ? "1" : "0";
}

void BitWriter::finish() {
	if (k > 0) writeByte(x);
}