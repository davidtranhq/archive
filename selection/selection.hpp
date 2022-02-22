#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <vector>

class world
{
	public:
		world(int w = 5, int h = 5);
		
		// fill world with a list of organisms pop
		void populate(const std::initializer_list<organism> &pop);
		// cause interactions between each of the organisms in the world
		void update(); // update interactions
		
	private:
		std::vector<std::vector<organism>> _m;
		int _time{0};
};

class organism
{
	public:
		organism(organism *parent = nullptr);
		// first generation won't have parents
		// predators eat
		virtual void behave(const std::vector<organism> &pop) = 0;
		// predators reproduce or die, prey reproduces
		virtual void react() = 0;
		
		int age() const;
		int gen() const;
		
	protected:
		bool alive() const;
		int strength() const;
		
	private:
		bool _alive{true};
		int _strength;
		int _age{0};
		int _gen;
		std::vector<organism *> _children;
		organism *_parent;
};

class predator : public organism
{
	public:
		predator();
		
		virtual void behave(const std::initializer_list<organism> &pop) override;
		virtual int 
		
	private:
		bool _ate{true};
};

class prey : public organism
{
	public:
		prey();
		
	private:
};

#endif