#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>

bool havel_hakimi(std::vector<int> v)
{
	// remove all zeros
	v.erase(std::remove(v.begin(), v.end(), 0), v.end());
	if (v.empty())
		return true;
	// descending order
	std::sort(v.begin(), v.end(), std::greater<int>());
	int n {v[0]};
	v.erase(v.begin());
	if (n > v.size())
		return false;
	for (int &x : v)
		--x;
	return havel_hakimi(v);
	
}

int main()
{
	std::vector<int> v;
	std::string in;
	int x;
	std::getline(std::cin, in);
	std::istringstream iss {in};
	while (iss >> x)
		v.push_back(x);
	std::cout << std::boolalpha << havel_hakimi(v);
	return 0;
}