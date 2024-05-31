#include "domain.h"
#include <assert.h>

Masina::Masina(string nr, string prod, string mod, string t) {
	nrInmatriculare = nr;
	producator = prod;
	model = mod;
	tip = t;
}

string Masina::get_nr() {
	return nrInmatriculare;
}

string Masina::get_producator() {
	return producator;
}

string Masina::get_model() {
	return model;
}

string Masina::get_tip() {
	return tip;
}

void Masina::set_nr(string nr) {
	nrInmatriculare = nr;
}
void Masina::set_producator(string prod) {
	producator = prod;
}
void Masina::set_model(string mod) {
	model = mod;
}
void Masina::set_tip(string t) {
	tip = t;
}

int Masina::valideaza() noexcept {
	if (tip == "" || nrInmatriculare == "" || model == "" || producator == "")
		return 0;
	return 1;
}