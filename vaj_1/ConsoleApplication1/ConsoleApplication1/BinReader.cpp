#include "BinReader.hpp"

BinReader::BinReader(const char* p) : k(0) {
	f.open(p, ios::binary);
}

char BinReader::readByte() {
	f.read((char*)&x, 1);
	return x;
}

bool BinReader::readBit() {
	if (k == 8) {
		readByte();
		k = 0;
	}
	bool b = (x >> k) & 1;
	k++;
	return b;
}