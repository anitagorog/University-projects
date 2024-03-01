#pragma once
#include <vector>

class Observer
{
public:
	virtual void update() = 0;
};

class Subject
{
private:
	std::vector<Observer*> obs;
public:
	void add_obs(Observer* o) { obs.push_back(o); }
	void notify() {
		for (auto o : obs)
			o->update();
	}
};

