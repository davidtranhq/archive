#ifndef PERCEPTRON_H
#define PERCEPTRON _H

#include <vector>

namespace neural_net
{
    class Perceptron;
    template <typename T> int sign(T val);
    template <typename T> T real_rand(T a, T b);
}

class Perceptron
{
    public:
        // constructor that takes number of weights
        Perceptron(int n);
        
        int guess(std::vector<float> inp);
    
    private:
        std::vector<float> weights {};
};

#endif