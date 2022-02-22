#include <iostream>
#include <array>

void f(int a)
{
	static_assert(a == 1, "a is not 1!");
}

int main()
{
	int a = 1;
	return 0;
}