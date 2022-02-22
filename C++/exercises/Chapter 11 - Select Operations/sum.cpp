#include <iostream>
#include <vector>
#include <algorithm>

int sum_for(std::vector<int> &v)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++)
        sum += v[i];
    return sum;
}

int sum_range(std::vector<int> &v)
{
    int sum = 0;
    for (auto x : v)
        sum += x;
    return sum;
}

int sum_each(std::vector<int> &v)
{
    int sum = 0;
    auto add = [&sum](int x) {sum += x;};
    std::for_each(v.begin(), v.end(), add);
    return sum;
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << sum_for(v) << '\n'
              << sum_range(v) << '\n'
              << sum_each(v) << '\n';
    return 0;
}