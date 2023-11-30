#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <vector>
#include <math.h>
#include "Compression.hpp"
#include "Decompression.hpp"
#include "BitWriter.hpp"
#include "BitReader.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


int main()
{
    const char* filename = "Cameraman.bmp"; // Change this to your image file name

    int width, height, channels;
    uint8_t* image_data = stbi_load(filename, &width, &height, &channels, STBI_grey);

    if (!image_data) {
        std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
        return 1;
    }

    // Convert 1D vector to 2D vector of type int
    std::vector<std::vector<int>> image_2d_vector(height, std::vector<int>(width));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image_2d_vector[i][j] = static_cast<int>(image_data[i * width + j]);
        }
    }

    stbi_image_free(image_data);
    
    Compression compressor;
    compressor.compress(image_2d_vector, width, height);

    Decompression decompressor;

    std::vector<std::vector<int>> P = decompressor.decompress();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (image_2d_vector[i][j] != P[i][j]) {
                std::cout << image_2d_vector[i][j] << "\n";
                std::cout << P[i][j] << "\n";
                return 1;
            }
        }
    }
    
    std::vector<uint8_t> flattened_data;
    for (const auto& row : P) {
        for (int value : row) {
            flattened_data.push_back(static_cast<uint8_t>(value));
        }
    }

    // Save the decompressed image using stbi_write_bmp
    stbi_write_bmp("out.bmp", static_cast<int>(P[0].size()), static_cast<int>(P.size()), 1, flattened_data.data());

	return 0;
}