#pragma once
#include <vector>

class Observer {
public:

	virtual void update() = 0;

};

class Observable {
private:
	std::vector<Observer*> observers;
public:
	void add_obs(Observer* obs) {
		observers.push_back(obs);
	}

	void remove_obs(Observer* obs) {
		observers.erase(std::remove(begin(observers), end(observers), obs), observers.end());
	}

protected:	
	void notify() {
		for (auto obs : observers) {
			obs->update();
		}
	}
};