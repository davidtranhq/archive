#include <string>

class A
{
	public:
	A(const std::string &s) : s_ {s.c_str()} {}
	
	A(A &rhs) : s_ {s} {}
	
	
	private:
	char *s_;
};