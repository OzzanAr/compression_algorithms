#include "Decompression.hpp"



void Decompression::decodeHeader(int& height, int& n, int& cFirst, int& cLast)
{
    height = reader.readTwoBytes();
    cFirst = reader.readByte();
    cLast = reader.readFourBytes();
    n = reader.readFourBytes();
}

int Decompression::getBits(int g)
{
    int value = 0;
    for (int i = 0; i < g; i++)
    {
        bool bit = reader.readBit();
        value |= bit << i;
    }
    return value;
}


void Decompression::DeIC(std::vector<int>& C , int L, int H) {
    int m, g;
    
    if ((H - L) > 1) {
        if (C[L] == C[H]) {
            for (int i = L + 1; i < H - 1; i++) {
                C[i] = C[L];
            }
        }
        else {
            m = (H + L) / 2;
            g = std::ceil(log2(C[H] - C[L] + 1));
            C[m] = C[L] + getBits(g);

            if (L < m) {
                DeIC(C, L, m);
            }

            if (m < H) {
                DeIC(C, m, H);
            }
        }
    }
}

std::vector<std::vector<int>> Decompression::predictInverse(std::vector<int> E, int width, int height) {
    std::vector<std::vector<int>> P(height, std::vector<int>(width, 0));

    P[0][0] = E[0];

    for (int x = 1; x < width; x++) {
        P[0][x] = P[0][x - 1] - E[x];
    }

    for (int y = 1; y < height; y++) {
        P[y][0] = P[y - 1][0] - E[y * width];
    }

    for (int y = 1; y < height; y++) {
        for (int x = 1; x < width; x++) {
            if (P[y - 1][x - 1] >= std::max(P[y][x - 1], P[y - 1][x])) {
                P[y][x] = std::min(P[y][x - 1], P[y - 1][x]) - E[y * width + x];
            }
            else if (P[y - 1][x - 1] <= std::min(P[y][x - 1], P[y - 1][x])) {
                P[y][x] = std::max(P[y][x - 1], P[y - 1][x]) - E[y * width + x];
            }
            else {
                P[y][x] = P[y][x - 1] + P[y - 1][x] - P[y - 1][x - 1] - E[y * width + x];
            }
        }
    }

    return P;
}


std::vector<std::vector<int>> Decompression::decompress()
{
    int height, cFirst, cLast, n, width;
    decodeHeader(height, n, cFirst, cLast);

    width = n / height;

    // InitialiseC
    std::vector<int> C(n, 0);
    C[0] = cFirst;
    C[n - 1] = cLast;

    DeIC(C, 0, n - 1);

    std::vector<int> N(n, 0);
    N[0] = C[0];

    for (int i = 1; i < n - 1; i++) {
        N[i] = C[i] - C[i - 1];
    }

    std::vector<int> E(n, 0);
    E[0] = N[0];
    for (int i = 1; i < n - 1; i++) {
        if (N[i] % 2 == 0) {
            E[i] = N[i] / 2;
        }
        else {
            E[i] = -((N[i] + 1) / 2);
        }
    }

    return predictInverse(E, width, height);
}


