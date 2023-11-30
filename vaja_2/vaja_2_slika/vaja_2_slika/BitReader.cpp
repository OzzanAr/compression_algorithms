#include "BitReader.hpp"

BitReader::BitReader(const char* p) : k(8) {
	f.open(p, ios::binary);
}

char BitReader::readByte() {
	f.read((char*)&x, 1);
	return x;
}

int BitReader::readTwoBytes() {
	int tmp = 0;
	f.read((char*)&tmp, 2);
	return tmp;
}

int BitReader::readFourBytes() {
	int tmp = 0;
	f.read((char*)&tmp, 4);
	return tmp;
}

bool BitReader::readBit() {
	if (k == 8) {
		readByte();
		k = 0;
	}
	bool b = (x >> k) & 1;
	k++;
	return b;
}

bool BitReader::isEOF() const
{
	return f.eof();
}
