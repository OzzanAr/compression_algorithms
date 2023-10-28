#include <iostream>
#include <random>
#include <vector> 

using namespace std;

int main()
{
    // Amount of values
    vector<int> N = { 5, 50 };
    
    // Difference vector for the values
    vector<int> M = { 5, 10, 15, 30 };

    random_device rd;
    mt19937 gen(rd());
       
    int max = 255;
    int min = 0;
    uniform_int_distribution<int> dist_1(min, max);

    uniform_int_distribution<int> fuck(-100, 2);
    cout << fuck(gen) << endl;
   
    vector<int> input = {};

    for (int i = 0; i < M.size(); i++) {
        cout << endl;

        for(int j = 0; j < N.size(); j++) {
            input.clear();
            input.push_back(dist_1(gen));

            cout << endl;
            for (int counter = 0; counter < N[j]; counter++) {
                int max_range = M[i];
                int min_range = M[i] * -1;
                uniform_int_distribution<int> dist(min_range, max_range);

                int rng = dist(gen);
                int newBoy = input.back() + rng;

                if (newBoy > max || newBoy < min) {
                    int newBoy = input.back() - rng;
                    input.push_back(newBoy);
                }
                else
                    input.push_back(newBoy);
            }

            for (int k = 0; k < input.size(); k++)
                cout << (int)input.at(k) << ' ';
            cout << endl;
        }

    }
    
   

}
