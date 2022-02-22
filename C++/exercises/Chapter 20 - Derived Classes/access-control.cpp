#include <iostream>

class base
{
	protected:
		int x;
};

class derived : public base
{
	public:
		void f(base &obj) { obj.x = 5; }
};

int main()
{
	base b;
	b.x = 10;
	return 0;
}