#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>

int main()
{
	std::vector<int> v(10);
	std::iota(v.begin(), v.end(), 0);
	for (std::vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit)
		std::cout << v[*rit] << ' ';
	return 0;
}