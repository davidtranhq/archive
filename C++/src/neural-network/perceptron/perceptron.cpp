#include <random>
#include <iostream>
#include <chrono>

#include "perceptron.h"

Perceptron::Perceptron(int n)
{
    for (int i = 0; i < n; i++)
        weights.push_back(neural_net::real_rand<float>(-1, 1));
}

Perceptron::guess(std::vector<float> inp)
{
    float sum {0.0};
    for (float i : inp)
        sum += i*weights[i];
    return neural_net::sign(sum);
}

// activation function
template <typename T>
int neural_net::sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

// RNG function
template <typename T>
T neural_net::real_rand(T a, T b)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed); // mersenne-twister engine
    std::uniform_real_distribution<float> dist(a,b);
    return dist(gen);
}