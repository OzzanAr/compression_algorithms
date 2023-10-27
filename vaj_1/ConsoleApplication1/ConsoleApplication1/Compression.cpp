#include "Compression.hpp"
#include <cstdlib>
#include <bitset>

void Compression::twoBitDifference(int8_t value) {
	bitWriter.writeBit(0);
	bitWriter.writeBit(0);

	value += (value < 0) ? 2 : 1;

	bitWriter.writeBit((value >> 1) & 1);
	bitWriter.writeBit(value & 1);
}

void Compression::threeBitDifference(int8_t value)
{
	bitWriter.writeBit(0);
	bitWriter.writeBit(1);

	value += (value < 0) ? 6 : 1;
	
	bitWriter.writeBit((value >> 2) & 1);
	bitWriter.writeBit((value >> 1) & 1);
	bitWriter.writeBit(value & 1);
}

void Compression::fourBitDifference(int8_t value)
{
	bitWriter.writeBit(1);
	bitWriter.writeBit(0);

	value += (value < 0) ? 14 : 1;

	bitWriter.writeBit((value >> 3) & 1);
	bitWriter.writeBit((value >> 2) & 1);
	bitWriter.writeBit((value >> 1) & 1);
	bitWriter.writeBit(value & 1);
}

void Compression::fiveBitDifference(int8_t value)
{
	bitWriter.writeBit(1);
	bitWriter.writeBit(1);

	value += (value < 0) ? 30 : 1;

	bitWriter.writeBit((value >> 4) & 1);
	bitWriter.writeBit((value >> 3) & 1);
	bitWriter.writeBit((value >> 2) & 1);
	bitWriter.writeBit((value >> 1) & 1);
	bitWriter.writeBit(value & 1);
}

void Compression::absoluteEncode(int8_t value) {
	bitWriter.writeBit(1);
	bitWriter.writeBit(0);

	if (value < 0) {
		bitWriter.writeBit(1);
		value = -1 * value;
	}
	else
	{
		bitWriter.writeBit(0);
	}

	uint8_t amountOfBits = value;
	
	for (int i = 7; i >= 0; i--) {
		bitWriter.writeBit(amountOfBits & 1 << i);
	}
}

void Compression::repetitionEncode(int8_t value) {
	bitWriter.writeBit(0);
	bitWriter.writeBit(1);

	bitWriter.writeBit(value & 4);
	bitWriter.writeBit(value & 2);
	bitWriter.writeBit(value & 1);
}

void Compression::differenceEncode(int8_t value)
{
	bitWriter.writeBit(0);
	bitWriter.writeBit(0);

	if (abs(value) <= 2) {
		twoBitDifference(value);
	}
	else if (abs(value) <= 6) {
		threeBitDifference(value);
	}
	else if (abs(value) <= 14) {
		fourBitDifference(value);
	}
	else if (abs(value) <= 30) {
		fiveBitDifference(value);
	}
}

void Compression::compressInput(std::vector<uint8_t>& inputVector) {
	std::vector<int16_t> differenceVector;

	differenceVector.push_back(inputVector[0]);
	for (int i = 1; i < inputVector.size(); i++) {
		differenceVector.push_back(inputVector[i] - inputVector[i - 1]);
	}

	for (int i = 0; i < differenceVector.size(); i++)
		std::cout << differenceVector.at(i) << ' ';
	std::cout << std::endl;

	int8_t a = inputVector[0];
	std::bitset<8> x(a);
	std::cout << x;


	// Write the first number which is alwyas 1 byte
	bitWriter.writeByte(differenceVector[0]);
	
	for (int i = 1; i < differenceVector.size(); i++) {
		// Cheacking for repition - 01
		int16_t val = differenceVector[i];

		if (val == 0) {
			int zeroCounter = -1;
			for (; i < differenceVector.size() && zeroCounter < 7; i++, zeroCounter++) {
				val = differenceVector[i];
				if (val != 0) break;
			}
			repetitionEncode(zeroCounter);
			i--;
		}

		if (abs(val) > 30) {
			absoluteEncode(val);
		}
		else if(val != 0) {
			differenceEncode(val);
		}
	}

	bitWriter.writeBit(1);
	bitWriter.writeBit(1);
	bitWriter.finish();

}