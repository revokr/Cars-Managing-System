#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qlistwidget.h>
#include <QStringList>
#include <string>
#include "lst_READ.h"
#include "table_model.h"

class parcare_gui : public QWidget {
private:
	service& srv;

	TableModel* table_parcare;
	QTableView* tblV = new QTableView;

	QLabel* lbl_nr = new QLabel{ "Numar inmatriculare: " };
	QLabel* lbl_prod = new QLabel{ "Producator: " };
	QLabel* lbl_model = new QLabel{ "Model: " };
	QLabel* lbl_tip = new QLabel{ "Tip: " };
	
	QLineEdit* edit_nr;
	QLineEdit* edit_prod;
	QLineEdit* edit_model;
	QLineEdit* edit_tip;
	QPushButton* btn_add;
	QPushButton* btn_del;
	QPushButton* btn_mod;
	QPushButton* btn_srch;
	
	QPushButton* raport;
	QGroupBox* grp_box = new QGroupBox(tr("Tip sortare: "));
	QRadioButton* radio_sort_nr = new QRadioButton(QString::fromStdString("Numar inmatriculare"));
	QRadioButton* radio_sort_prod = new QRadioButton(QString::fromStdString("Producator"));
	QRadioButton* radio_sort_tip = new QRadioButton(QString::fromStdString("Tip"));
	QPushButton* btn_sort;
	
	QLabel* lbl_filter_crt2 = new QLabel{ "Producatorul dupa care se filtreaza: " };
	QLineEdit* edit_filter_prod;
	QPushButton* btn_flt_prod;
	QLabel* lbl_filter_crt3 = new QLabel{ "Tipul dupa care se filtreaza: " };
	QLineEdit* edit_filter_tip;
	QPushButton* btn_flt_tip;
	QPushButton* btn_reload;
	QPushButton* btn_undo;
	
	
	QListWidget* parcare_lista;
	QLineEdit* nr_inmatriculare;
	QLineEdit* nr_masini;
	QLineEdit* xprt;
	QLineEdit* edit_rndm;
	QPushButton* btn_lista;
	QPushButton* btn_lista_read;
	QPushButton* add_lst;
	QPushButton* empty_lst;
	QPushButton* grndm_lst;
	QPushButton* btn1;
	QPushButton* btn2;
	QPushButton* btn3;
	QTableWidget* lst_lista;
	QPushButton* export_lst;
	QLabel* lbl_rndm = new QLabel{ "Numar masini random:" };
	QLabel* lbl_export = new QLabel{ "Nume fisier:" };
	
	QPushButton* t_br; // break
	int br;
	QPushButton* t_sdn; // sedan
	int sdn;
	QPushButton* t_suv; // suv
	int suv;
	QPushButton* t_sprt; // sport
	int sprt;
	QPushButton* altele;
	int alt;


	
	void init_components();
	void connect_sig_slots();
	void reload_parcare(std::vector<Masina> parc);
	void reload_lst(std::vector<Masina> lst);

public:

	parcare_gui(service& srv) : srv{ srv } {
		init_components();
		table_parcare = new TableModel{ srv.get_all_srv()};
		tblV->setModel(table_parcare);
		connect_sig_slots();
		vector<Masina> v = srv.get_all_srv();
		reload_parcare(v);
	}

	void gui_add();
	void gui_del();
	void gui_mod();

};