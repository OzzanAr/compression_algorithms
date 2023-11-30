#include "Compression.hpp"
#include <cstdlib>
#include <bitset>


void Compression::predict(std::vector<int>& E, std::vector<std::vector<int>> P, int width, int height)
{
    E[0] = P[0][0];

    for (int i = 1; i < width; i++) {
        E[i] = P[0][i - 1] - P[0][i]; 
    }

    for (int i = 1; i < height; i++) {
        E[i * width] = P[i - 1][0] - P[i][0];
    }

    for (int y = 1; y < height; y++) {
        for (int x = 1; x < width; x++) {
            if (P[y - 1][x - 1] >= std::max(P[y][x - 1], P[y - 1][x])) {
                E[y * width + x] = std::min(P[y][x - 1], P[y - 1][x]) - P[y][x];
            }
            else if (P[y - 1][x - 1] <= std::min(P[y][x - 1], P[y - 1][x])) {
                E[y * width + x] = std::max(P[y][x - 1], P[y - 1][x]) - P[y][x];
            }
            else {
                E[y * width + x] = P[y][x - 1] + P[y - 1][x] - P[y - 1][x - 1] - P[y][x];
            }
        }
    }
}

void Compression::IC(std::vector<int> C, int L, int H)
{   
    int m, g;

    if (H - L > 1)  {
        if (C[H] != C[L]) {
            m = (H + L) / 2;
            g = std::ceil(log2(C[H] - C[L] + 1));
            encode(g, C[m] - C[L]);
            if (L < m) {
                IC(C, L, m);
            }

            if (m < H) {
                IC(C, m, H);
            }
        }
    }
}

void Compression::encode(int g, int diff)
{
    for (int i = 0; i < g; ++i) {
        bool bit = (diff >> i) & 1;
        bitWriter.writeBit(bit);
    }
}



void Compression::compress(std::vector<std::vector<int>> P, int width, int height)
{
    int n = height * width;
    std::vector<int> E(n, 0);
    std::vector<int> N(n, 0);
    std::vector<int> C(n, 0);

    predict(E, P, width, height);

    // Calculating N
    N[0] = E[0];

    for (size_t i = 1; i < n; i++) {
        if (E[i] >= 0) {
            N[i] = 2 * E[i];
        }
        else {
            N[i] = 2 * std::abs(E[i]) - 1;
        }
    }

    C[0] = N[0];

    for (size_t i = 1; i < n; i++) {
        C[i] = C[i - 1] + N[i];
    }

    // 88 bits -> 11 bytes/zlog
    // Writing the header
    bitWriter.writeTwoByte(height);
    bitWriter.writeByte(C[0]);
    bitWriter.writeInt(C.back());
    bitWriter.writeInt(C.size());

    IC(C, 0, n - 1);

    bitWriter.finish();
}