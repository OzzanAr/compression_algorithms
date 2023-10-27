#include "BitReader.hpp"

BitReader::BitReader(const char* p) : k(0) {
	f.open(p, ios::binary);
}

char BitReader::readByte() {
	f.read((char*)&x, 1);
	return x;
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
