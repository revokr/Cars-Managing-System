#include "valueDTO.h"
#include <map>
#include "lst.h"
#include <memory>


using std::unique_ptr;
using std::make_unique;



class service {

	//friend class parcare;
	//friend class Masina;

private:
	parcare& p;
	file_parcare& lista;
	Validator vali;

	lst list;

	//vector<actiune_undo*> undo_actions;
	vector<actiune_undo*> undo_actions;

public:
	//explicit service(parcare& repo) :p{ repo }{};
	service(parcare& p, file_parcare& l) noexcept : p{ p }, lista{ l }, list{ p } {

	}

	/*
		adauga o masina in lista
		nr : string
		prod : string
		model : string
		tip : string
	*/
	void adauga_srv(string nr, string prod, string model, string tip);

	void adauga_ls(string nr);

	std::map<string, valueDTO> raport();

	/*
	* returneaza toate masinile din lista
	*/
	vector<Masina> get_all_srv();

	lst& get_lst() {
		return list;
	}

	/*
	* sterge o masina din lista
	* nr_inm : string
	*/
	void sterge_srv(string nr_inm);

	void gnr_rndm(unsigned long long nr);

	void goleste_lst();

	/*
	* modifica o masina din lista
	* nr_inm : string
	* prod_nou : string
	* model_nou : string
	* tip_nou : string
	*/
	void modifica_srv(string nr_inm, string prod_nou, string model_nou, string tip_nou);

	/*
	* cauta o masina in lista
	* nr_inm : string
	* returneaza masina
	*/
	Masina cauta_srv(string nr_inm);

	/*
	* filtreaza masinile dupa un producator dat
	* prod : string
	* returneaza masinile filtrate
	*/
	vector<Masina> filtreaza_p(string prod);

	/*
	  filtreaza masinile dupa un tip dat
	* prod : string
	* returneaza masinile filtrate
	*/
	vector<Masina> filtreaza_t(string tip);

	/*
		sorteaza dupa numarul de inmatriculare
	*/
	vector<Masina> sorteaza_nr_inm();

	/*
		sorteaza dupa producator si model
	*/
	vector<Masina> sorteaza_prod();

	/*
		sorteaza dupa tip
	*/
	vector<Masina> sorteaza_tip();

	/*
		teste
	*/
	vector<Masina> teste_service();

	void undo();

	vector<Masina> get_all_lst();

	void write_to_file(string nume);

	~service() {
		for (auto el : undo_actions)
			delete el;
	}
};