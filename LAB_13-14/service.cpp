#include "service.h"
#include <iostream>
#include <algorithm>


using std::cout;

void service::undo() {
	if (undo_actions.empty())
		throw parcare_exception("Nu mai exista operatii anterioare!!\n");
	else {
		actiune_undo* act = undo_actions.back();
		act->do_undo();
		undo_actions.pop_back();
		delete act;
	}
}

void service::adauga_srv(string nr, string prod, string model, string tip) {
	Masina car{ nr, prod, model, tip };
	string va = vali.valideaza(car);
	if (va.size() == 0) {
		if (p.cauta_(nr) == true)
			throw parcare_exception("Numar de inmatriculare existent!!\n");
		else {
			p.adauga(car);
			actiune_undo* act = new adauga_undo(car, p);
			undo_actions.push_back(act);

		}
	}
}

void service::adauga_ls(string nr) {
	Masina car = cauta_srv(nr);
	list.add_lst(nr);
}

void service::goleste_lst() {
	/*for (auto masina : lista.get_all()) {
		lista.sterge(masina.get_nr());
	}*/
	list.empty();
}

void service::gnr_rndm(unsigned long long nr) {
	goleste_lst();
	list.gnr_rndm(nr);
}


void service::sterge_srv(string nr_inm) {
	if (p.cauta_(nr_inm) == false)
		throw parcare_exception("Masina nu exista!!\n");
	else {
		Masina car = cauta_srv(nr_inm);
		p.sterge(nr_inm);
		undo_actions.push_back(new sterge_undo(car, p));
	}
}

void service::modifica_srv(string nr_inm, string prod_nou, string model_nou, string tip_nou) {
	Masina c(nr_inm, prod_nou, model_nou, tip_nou);
	string va = vali.valideaza(c);
	if (va.size() == 0) {
		if (p.cauta_(nr_inm) == false)
			throw parcare_exception("Masina nu exista!!\n");
		else {
			Masina car = cauta_srv(nr_inm);
			p.modifica(nr_inm, prod_nou, model_nou, tip_nou);
			undo_actions.push_back(new modifica_undo(car, p));

		}
	}
}


Masina service::cauta_srv(string nr_inm) {
	bool gasit = false;
	for (auto car : p.get_all()) {
		if (car.get_nr() == nr_inm) {
			gasit = true;
			return car;
		}

	}
	throw parcare_exception("Masina nu exista!\n");
}

std::map<string, valueDTO> service::raport() {
	std::map<string, valueDTO> mp;
	vector<Masina> masini = sorteaza_tip();
	for (auto car : masini) {
		if (mp.find(car.get_tip()) == mp.end()) {
			valueDTO v{ car.get_tip(), 1 };
			mp[car.get_tip()] = v;
		}
		else {
			mp[car.get_tip()].inc_value();
		}
	}
	return mp;
}

void service::write_to_file(string nume) {
	lista.write_to_file(nume);
}

vector<Masina> service::filtreaza_p(string prod) {
	vector<Masina> masini = p.get_all();
	vector<Masina> masini_filtrate;
	for (auto car : masini) {
		if (car.get_producator() == prod) {
			masini_filtrate.push_back(car);
		}
	}
	return masini_filtrate;
}

vector<Masina> service::filtreaza_t(string tip) {
	vector<Masina> masini = p.get_all();
	vector<Masina> masini_filtrate;
	for (auto car : masini) {
		if (car.get_tip() == tip) {
			masini_filtrate.push_back(car);
		}
	}
	return masini_filtrate;
}

vector<Masina> service::sorteaza_nr_inm() {
	vector<Masina> masini = p.get_all();
	std::sort(masini.begin(), masini.end(), [](Masina a, Masina b) {return a.get_nr() < b.get_nr(); });
	return masini;
}

vector<Masina> service::sorteaza_prod() {
	vector<Masina> masini = p.get_all();
	std::sort(masini.begin(), masini.end(), [](Masina a, Masina b)
		{return (a.get_producator() < b.get_producator() ||
			(a.get_producator() == b.get_producator() && a.get_model() < b.get_model())); });
	return masini;
}

vector<Masina> service::sorteaza_tip() {
	vector<Masina> masini = p.get_all();
	std::sort(masini.begin(), masini.end(), [](Masina a, Masina b) {return a.get_tip() < b.get_tip(); });
	return masini;
}

vector<Masina> service::get_all_srv() {
	return p.get_all();
}

vector<Masina> service::get_all_lst() {
	return list.get();
}