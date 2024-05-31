#pragma once
#include <string>
#include <iostream>
#include <assert.h>

using std::string;



class Masina {
private:
	string nrInmatriculare;
	string producator;
	string model;
	string tip;
public:
	/*
		Construnctor implicit
		Parametrii : nr, producator, model, tip - string
	*/
	Masina(const string nr, const string prod, const string mod, const string tip);


	// copy constructor
	//Masina(const Masina& m) : nrInmatriculare{ m.nrInmatriculare }, producator{ m.producator }, model{ m.model }, tip{ m.tip } {
		//std::cout << "*\n";
	//}
	/*
		Validator
		Returneaza 1 daca Masina e valida 0 in caz contrer
	*/
	int valideaza() noexcept;

	/*
		Getters
	*/
	string get_nr();
	string get_producator();
	string get_model();
	string get_tip();


	/*
		Setters
	*/
	void set_nr(string nr);
	void set_producator(string prod);
	void set_model(string mod);
	void set_tip(string t);



};