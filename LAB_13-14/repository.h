#include <vector>
#include <iostream>
#include <fstream>
#include "exceptie.h"
#include <random>

using std::vector;


class parcare_abstract {
public:
	/*
		Default constructor
	*/
	parcare_abstract() = default;

	/*
		Returneaza elementul de pe pozitia i
	*/
	virtual Masina curent(int i) = 0;

	/*
		Adauga masina in lista
	*/
	virtual void adauga(Masina car) = 0;

	/*
		Adauga masina in lista (forta bruta)
	*/
	virtual void add(Masina car) = 0;

	/*
		Sterge o masina din lista
	*/
	virtual void sterge(string nr_inm) = 0;

	/*
		Sterge o masina din lista (forta bruta)
	*/
	virtual void erase_(string nr) = 0;

	/*
		Modifica o masina din lista (forta bruta)
	*/
	virtual void modify(string nr_inm, string producator_nou, string model_nou, string tip_nou) = 0;

	/*
		Modifica o masina din lista
	*/
	virtual void modifica(string nr_inm, string producator_nou, string model_nou, string tip_nou) = 0;

	/*
		Returneaza pozitia elementului cautat, -1 daca nu exista
	*/
	virtual int cauta(string nr_inm) = 0;

	/*
		Returneaza o lista cu toate elemntele
	*/
	virtual vector<Masina> get_all() = 0;

	/*
		Returneaza adevarat daca exista elemntul in lista
	*/
	virtual bool cauta_(string nr_inm) = 0;

	/*
		Destructor
	*/
	virtual ~parcare_abstract() {};
};


class parcare_lab : public parcare_abstract {
private:
	vector<Masina> lista;

	double prb;


public:
	void random() const {
		double random = rand() % 100;
		if (random > prb * 100) {
			throw (parcare_exception("Nu se poate executa aceasta functie!!!\n"));
		}
	}

	parcare_lab(double prb) noexcept : prb{ prb } {}

	double get_prb() {
		return prb;
	}

	Masina curent(int i) override {
		Masina m1 = lista.at(i);
		return m1;
	}

	void adauga(Masina car) override {
		random();
		lista.push_back(car);
	}

	void sterge(string nr_inm) override {
		random();
		int i;
		for (i = 0; i < lista.size(); i++) {
			if (lista.at(i).get_nr() == nr_inm)
				break;
		}
		lista.erase(lista.begin() + i);
	}

	void erase_(string nr) override {
		lista.erase(lista.begin() + cauta(nr));
	}

	void modify(string nr_inm, string producator_nou, string model_nou, string tip_nou) override {
		int i;
		for (i = 0; i < lista.size(); i++) {
			if (lista.at(i).get_nr() == nr_inm)
				break;
		}
		lista.at(i).set_producator(producator_nou);
		lista.at(i).set_model(model_nou);
		lista.at(i).set_tip(tip_nou);
	}

	void add(Masina car) override {
		lista.push_back(car);
	}



	int cauta(string nr_inm) override {
		random();
		int i = 0;
		for (auto car : lista) {
			if (car.get_nr() == nr_inm) {
				return i;
			}
			i++;
		}
		return -1;
	}

	void modifica(string nr_inm, string producator_nou, string model_nou, string tip_nou) override {
		random();
		int i;
		for (i = 0; i < lista.size(); i++) {
			if (lista.at(i).get_nr() == nr_inm)
				break;
		}
		lista.at(i).set_producator(producator_nou);
		lista.at(i).set_model(model_nou);
		lista.at(i).set_tip(tip_nou);
	}

	vector<Masina> get_all() override {
		vector<Masina> all;
		for (auto car : lista) {
			all.push_back(car);
		}
		return all;
	}

	bool cauta_(string nr_inm) override {
		for (auto car : lista) {
			if (car.get_nr() == nr_inm)
				return true;
		}
		return false;
	}

	~parcare_lab() = default;
};

class parcare : public parcare_abstract {
private:
	vector<Masina> lista;
public:
	/*
		Constructor implicit
	*/
	parcare() = default;

	Masina curent(int i) override {
		Masina m1 = lista.at(i);
		return m1;
	}

	/*
		Adauga o masina in lista
		Parametru : car - obiect masina
	*/
	void adauga(Masina car)override;

	void add(Masina car)override;

	void erase_(string nr) override {
		lista.erase(lista.begin() + cauta(nr));
	}

	void modify(string nr_inm, string producator_nou, string model_nou, string tip_nou) override {
		lista.at(cauta(nr_inm)).set_producator(producator_nou);
		lista.at(cauta(nr_inm)).set_model(model_nou);
		lista.at(cauta(nr_inm)).set_tip(tip_nou);
	}
	/*
		Sterge o masina din lista dupa pozitia in lista
		Parametru : pos - int
	*/
	void sterge(string nr_inm)override;

	/*
		modifica o masina din lista
	*/
	void modifica(string nr_inm, string producator_nou, string model_nou, string tip_nou)override;

	/*
		Returneaza dimensiunea listei
	*/

	int cauta(string nr_inm)override;

	Masina cautaa(string nr) {
		for (auto m : get_all()) {
			if (m.get_nr() == nr)
				return m;
		}
	}

	bool cauta_(string nr_inm)override;

	/*
		Creeaza o lista cu toate masinile din parcare
	*/
	vector<Masina> get_all()override;

	/*
		Destructor
	*/
	~parcare() = default;


};


class file_parcare : public parcare_abstract {
private:
	vector<Masina> lista;
public:
	file_parcare() = default;

	Masina curent(int i) override {
		Masina m1 = lista.at(i);
		return m1;
	}

	void adauga(Masina car) override {
		lista.push_back(car);

	}

	void sterge(string nr_inm) override {
		lista.erase(lista.begin() + cauta(nr_inm));
	}

	void add(Masina car) override {
		lista.push_back(car);
	}

	void erase_(string nr) override {
		lista.erase(lista.begin() + cauta(nr));
	}

	void modify(string nr_inm, string producator_nou, string model_nou, string tip_nou) override {
		lista.at(cauta(nr_inm)).set_producator(producator_nou);
		lista.at(cauta(nr_inm)).set_model(model_nou);
		lista.at(cauta(nr_inm)).set_tip(tip_nou);
	}

	int cauta(string nr_inm) override {
		int i = 0;
		for (auto car : lista) {
			if (car.get_nr() == nr_inm) {
				return i;
			}
			i++;
		}
		return -1;
	}

	void modifica(string nr_inm, string producator_nou, string model_nou, string tip_nou) override {
		lista.at(cauta(nr_inm)).set_producator(producator_nou);
		lista.at(cauta(nr_inm)).set_model(model_nou);
		lista.at(cauta(nr_inm)).set_tip(tip_nou);
	}

	vector<Masina> get_all() override {
		vector<Masina> all;
		for (auto car : lista) {
			all.push_back(car);
		}
		return all;
	}

	bool cauta_(string nr_inm) override {
		auto f = std::find_if(lista.begin(), lista.end(), [=](Masina& c) {
			return (c.get_nr() == nr_inm);
			});
		if (f != lista.end())
			return true;
		else
			return false;
	}

	void write_to_file(string nume) {
		std::ofstream fout(nume);
		for (auto car : get_all()) {
			fout << car.get_nr() << " " << car.get_producator() << " " << car.get_model() << " " << car.get_tip();
			fout << std::endl;
		}
	}


	~file_parcare() = default;
};