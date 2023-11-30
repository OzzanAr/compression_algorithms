#include "Decompression.hpp"
#include <fstream>
#include <iostream>

int8_t Decompression::twoDifference(int value)
{
    if ((value >> 1) & 1) {
        return (value & 1) + 1;
    }
    else {
        return (value & 1) - 2;
    }
}

int8_t Decompression::threeDifference(int value)
{
    if ((value >> 2) & 1) {
        return (value & 3) + 3;
    }
    else {
        return (value & 3) - 6;
    }
}

int8_t Decompression::fourDifference(int value)
{
    if ((value >> 3) & 1) {
        return (value & 7) + 7;
    }
    else {
        return (value & 7) - 14;
    }
}

int8_t Decompression::fiveDifference(int value)
{
    if ((value >> 4) & 1) {
        return (value & 15) + 15;
    }
    else {
        return (value & 15) - 30;
    }
}


std::vector<uint8_t> Decompression::decompress(int *outputSize)
{
    std::ifstream inputFile("output.bin", std::ios::binary);
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        exit;
    }

    std::vector<bool> bitVector;
    char byte;

    while (inputFile.read(&byte, 1)) {
        for (int i = 0; i < 8; i++) {
            bool bit = (byte >> (7 - i)) & 1;
            bitVector.push_back(bit);
        }
    }

    inputFile.close();

    // Now, bitVector contains all the bits from the binary file.
    int counter = 0;
    //for (bool bit : bitVector) {
    //    std::cout << bit;
    //    counter++;
    //    if (counter == 8) {
    //        std::cout << " ";
    //        counter = 0;
    //    }
    //}

    *outputSize = (bitVector.size() * sizeof(uint8_t)) / 8;
    
    std::vector<int8_t> razlikeData;
    int8_t firstByte = 0;

    for (int i = 0; i < 8; i++) {
        firstByte += bitVector[i] << 7-i;
    }
    razlikeData.push_back(firstByte);

    for (int i = 8; !(bitVector[i] && bitVector[i + 1]) && i < bitVector.size() - 1;) {
        // Determine packet type

        // Packet type 00
        if (!bitVector[i] && !bitVector[i + 1]) {
            // Determine difference type
            i += 2;
            int bitCount = 0;
            bitCount += bitVector[i] << 1;
            bitCount += bitVector[i+1];

            // Type is used to check the differec type in the switch case 0 to 3
            int type = bitCount;

            i += 2;
            bitCount++;
            int value = 0;
            while (bitCount >= 0) {
                value += bitVector[i] << bitCount;
                bitCount--;
                i++;
            }
            // Depending on type, call function
            switch (type) {
                case 0:
                    value = twoDifference(value);
                    break;
                case 1:
                    value = threeDifference(value);
                    break;
                case 2:
                    value = fourDifference(value);
                    break;
                case 3:
                    value = fiveDifference(value);
                    break;
            }
            razlikeData.push_back(value);
        }
        // Packet type 01
        if (!bitVector[i] && bitVector[i + 1]) {
            i += 2;

            int zeroCount = 0;
            zeroCount += bitVector[i] << 2;
            zeroCount += bitVector[i + 1] << 1;
            zeroCount += bitVector[i + 2];

            i += 3;
            while (zeroCount >= 0) {
                razlikeData.push_back(0);
                zeroCount--;
            }

        }
        if (bitVector[i] && !bitVector[i + 1]) {
            i += 2;
            bool sign = bitVector[i];
            i++;
            int number = 0;

            for (int j = 0; j < 8; j++) {
                number += bitVector[i+j] << 7 - j;
            }

            razlikeData.push_back((-1 * sign)* number);
            i += 8;
        }
    }

    std::vector<uint8_t> calculatedVector;
    calculatedVector.push_back(razlikeData[0]);

    for (int i = 1; i < razlikeData.size(); i++) {
        calculatedVector.push_back(calculatedVector[i-1] + razlikeData[i]);
    }

    return calculatedVector;
}

