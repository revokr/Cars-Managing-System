#include "repository.h"


vector<Masina> parcare::get_all() {
	vector<Masina> all;
	for (auto car : lista) {
		all.push_back(car);
	}
	return all;
}

int parcare::cauta(string nr_inm) {
	int i = 0;
	for (auto car : lista) {
		if (car.get_nr() == nr_inm) {
			return i;
		}
		i++;
	}
	return -1;
}

bool parcare::cauta_(string nr_inm) {
	auto f = std::find_if(lista.begin(), lista.end(), [=](Masina& c) {
		return (c.get_nr() == nr_inm);
		});
	if (f != lista.end())
		return true;
	else
		return false;
}


void parcare::modifica(string nr_inm, string producator_nou, string model_nou, string tip_nou) {
	lista.at(cauta(nr_inm)).set_producator(producator_nou);
	lista.at(cauta(nr_inm)).set_model(model_nou);
	lista.at(cauta(nr_inm)).set_tip(tip_nou);
}

void parcare::sterge(string nr_inm) {
	lista.erase(lista.begin() + cauta(nr_inm));
}

void parcare::adauga(Masina car) {

	lista.push_back(car);
}

void parcare::add(Masina car) {
	lista.push_back(car);
}