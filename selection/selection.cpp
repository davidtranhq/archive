#include "selection.hpp"
#include <random>
#include <algorithm>

world::world(int w, int h)
	: _m(w*h),
{
}

void world::populate(std::intializer_list<organism> pop)
{
	for (organism o : pop)
		_m[rand() % (_m.capacity()+1)].push_back(o);
}

void world::update()
{
	for (std::vector<organism> v : _m)
	{
		// sort animals based on highest strength to lowest
		std::sort(v.begin(), v.end(), [](const organism &i, const organism &j)
		{
			return i.strength() < j.strength();
		});
		for (organism o : v)
		{
			o.behave();
			o.react();
		}
	}
	_time++;
}

organism::organism(organism *parent = nullptr, int strength)
	: _parent{parent}, _strength{strength}
{
	if (_parent)
	{
		_gen = _parent->gen() + 1;
	}
	else
	{
		_gen = 0;
	}
}

predator::predator(int acuity)
	: organism(), _acuity{acuity}
{
}

void predator::behave(const std::vector<organism> &pop)
{
	// the weakest prey will be eaten first, iterate in reverse
	for (std::vector<organism>::reverse_iterator prey = v.rbegin(); 
		 prey != v.rend(); 
		 ++prey)
	{
		// eat if the organism is weaker and lower on the food chain
		if (prey->trophic() < _trophic
		    && prey->strength() < _strength)
			
	}
}