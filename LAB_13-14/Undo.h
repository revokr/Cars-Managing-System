#include "repository.h"

class actiune_undo {
public:
	virtual void do_undo() = 0;
	virtual ~actiune_undo() = default;
};



class adauga_undo : public actiune_undo {
private:
	Masina last;
	parcare_abstract& p;
public:
	adauga_undo(Masina& m, parcare_abstract& p) : last{ m }, p{ p } {}

	void do_undo() override {
		string nr = last.get_nr();
		p.erase_(nr);//trebuie facute functiile astea pt ca iti pusca-silentios cand dai undo... PROSTULE
	}

};


class sterge_undo : public actiune_undo {
private:
	Masina last;
	parcare_abstract& p;
public:
	sterge_undo(Masina& m, parcare_abstract& p) : last{ m }, p{ p } {}

	void do_undo() override {
		p.add(last);
	}

};

class modifica_undo : public actiune_undo {
private:
	Masina last;
	parcare_abstract& p;
public:
	modifica_undo(Masina& m, parcare_abstract& p) : last{ m }, p{ p } {}

	void do_undo() override {
		p.modify(last.get_nr(), last.get_producator(), last.get_model(), last.get_tip());
	}

};