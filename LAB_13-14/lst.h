#pragma once
#include "Undo.h"
#include "observer.h"

class lst : public Observable {
private:
	std::vector<Masina> masini;
	parcare& prc;
public:
	lst(parcare& pr) : prc{ pr } {};

	void add_lst(string nr) {
		Masina m = prc.cautaa(nr);
		masini.push_back(m);
		notify();
	}

	void gnr_rndm(int nr) {
		std::vector<Masina> v = prc.get_all();
		std::shuffle(v.begin(), v.end(), std::default_random_engine(std::random_device{}()));
		unsigned long long i = 1;
		if (nr > v.size()) {
			while (masini.size() < nr) {
				for (auto car : v)
					if (masini.size() < nr) {
						masini.push_back(car);
					}
					else
						break;
			}
		}
		else {
			for (auto el : v) {
				masini.push_back(el);
				if (i == nr)
					break;
				i++;
			}
		}
		notify();
	}

	void empty() {
		masini.clear();
		notify();
	}

	std::vector<Masina> get() {
		return masini;
	}

	/*std::vector<Masina> get_org() {
		return prc;
	}*/
};