#include <iostream>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "BitWriter.hpp"
#include "BitReader.hpp"
#include "Compression.hpp"
#include "Decompression.hpp"
#include <random>

void randomNumberGenerator(int N, int M, std::vector<uint8_t>& vec)
{
	N--;
	random_device rd;
	mt19937 gen(rd());

	int const max = 255;
	int const min = 0;


	uniform_int_distribution<int> dist_1(min, max);
	vec.push_back(dist_1(gen));

	for (int counter = 0; counter < N; counter++) {
		int max_range = M;
		int min_range = M * -1;
		uniform_int_distribution<int> dist(min_range, max_range);

		int rng = dist(gen);
		int newBoy = vec.back() + rng;

		if (newBoy > max || newBoy < min) {
			int newBoy = vec.back() - rng;
			vec.push_back(newBoy);
		}
		else
			vec.push_back(newBoy);
	}
	
}


int main() {
	// Amount of numbers to generate
	std::vector<int> N = { 5, 50, 500, 5000 };
	// The difference between the generated values
	std::vector<int> M = { 5, 10, 15, 30 };

    auto start = std::chrono::system_clock::now();
    printf("N, \t M, \t Compress time, \tDecompress time, \t Input size, \t Output size, \t Compression ratio, \n");

    for (int i = 0; i < N.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            std::vector<uint8_t> input_vector;
            std::vector<uint8_t> output_vector;
            randomNumberGenerator(N[i], M[j], input_vector);

            Compression compress;

            // Calling the compression algorithm and saving the start and end times
            auto compression_begin = std::chrono::system_clock::now();
            compress.compressInput(input_vector);
            auto compression_end = std::chrono::system_clock::now();

            Decompression decompress;

			auto decompression_start = std::chrono::system_clock::now();
            output_vector = decompress.decompress();
			auto decompression_end = std::chrono::system_clock::now();

            for (size_t k = 0; k < input_vector.size(); k++)
            {
                if ((int)input_vector.at(k) != (int)output_vector.at(k))
                {
                    printf("Error\n");
                    return 0;
                }
            }

			std::chrono::duration<double> compressionTime = compression_end - compression_begin;
			std::chrono::duration<double> decompressionTime = decompression_end - decompression_start;

            printf("%d,\t %d,\t ", N[i], M[j]);
            printf("%f,\t\t", compressionTime.count());
            printf("%f,\t\t ", decompressionTime.count());
            uint64_t input_size = N[i] * sizeof(uint8_t);
            printf("%ld,\t\t ", input_size);


        }
    }

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> decTime = end - start;
	printf("Total time: %f\n", decTime.count());


	return 0;
}