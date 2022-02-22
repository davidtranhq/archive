#include <iostream>
#include <string>

// structs use public inheritance; all the members of Employee are also
// in Manager
struct Employee
{
	std::string first_name, family_name;
	char middle_initial;
	int hiring_date;
	short department;
};

struct Manager : public Employee
{
	std::list<Employee *> group;
	short level;
};

// Manager can now be used wherever an Employee is expected
void f(Manager m1, Employee e1)
{
	std::list<Employee *> elist{&m1, &e1};
	// ...
}

// but an Employee isn't necessarily a manager
void g(Manager m, Employee e)
{
	Manager *p = &e // error: not every Employee is a Manager
}

