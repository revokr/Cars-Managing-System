#include "GUI.h"

void parcare_gui::init_components() {

	QHBoxLayout* ly_main = new QHBoxLayout;

	this->setLayout(ly_main);

	// partea stanga
	QWidget* left = new QWidget;
	QVBoxLayout* ly_left = new QVBoxLayout;
	left->setLayout(ly_left);

	QWidget* form = new QWidget;
	QFormLayout* ly_form = new QFormLayout;
	form->setLayout(ly_form);
	edit_nr = new QLineEdit;
	edit_prod = new QLineEdit;
	edit_model = new QLineEdit;
	edit_tip = new QLineEdit;

	ly_form->addRow(lbl_nr, edit_nr);
	ly_form->addRow(lbl_prod, edit_prod);
	ly_form->addRow(lbl_model, edit_model);
	ly_form->addRow(lbl_tip, edit_tip);

	btn_add = new QPushButton{ "Adauga masina" };
	ly_form->addWidget(btn_add);

	btn_del = new QPushButton{ "Sterge masina" };
	ly_form->addWidget(btn_del);

	btn_mod = new QPushButton{ "Modifica masina" };
	ly_form->addWidget(btn_mod);



	QVBoxLayout* ly_sortare = new QVBoxLayout;
	this->grp_box->setLayout(ly_sortare);

	ly_sortare->addWidget(grp_box);
	ly_sortare->addWidget(radio_sort_nr);
	ly_sortare->addWidget(radio_sort_prod);
	ly_sortare->addWidget(radio_sort_tip);

	btn_sort = new QPushButton{ "Sorteaza" };
	ly_sortare->addWidget(btn_sort);


	ly_left->addWidget(form);
	ly_left->addWidget(grp_box);

	// pt filtrari
	QWidget* flt_form = new QWidget;
	QFormLayout* ly_form_flt = new QFormLayout;
	flt_form->setLayout(ly_form_flt);
	edit_filter_prod = new QLineEdit;
	edit_filter_tip = new QLineEdit;


	btn_flt_prod = new QPushButton{ "Flt dupa prod" };
	ly_form_flt->addRow(lbl_filter_crt2, edit_filter_prod);
	ly_form_flt->addWidget(btn_flt_prod);

	btn_flt_tip = new QPushButton{ "Flt dupa tip" };
	ly_form_flt->addRow(lbl_filter_crt3, edit_filter_tip);
	ly_form_flt->addWidget(btn_flt_tip);

	ly_left->addWidget(flt_form);


	// tabelul
	QWidget* right = new QWidget;
	QVBoxLayout* tab = new QVBoxLayout;
	right->setLayout(tab);

	//int nr_lines = 20;
	//int nr_col = 4;
	//this->table_parcare = new TableModel{ srv.get_all_srv()};
	//QStringList tab_header;
	//tab_header << "   Numar Inmatriculare    " << "    Producator   " << "    Model    " << "Tip";
	//
	///*this->table_parcare->horizontalHeader()->setStretchLastSection(true);
	//this->table_parcare->setHorizontalHeaderLabels(tab_header);*/
	//// optiune pt a se redimensiona celulele
	//this->table_parcare->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//tab->addWidget(table_parcare);
	tab->addWidget(tblV);


	// lista init
	/*lst_lista = new QTableWidget{ 20, 4 };
	QStringList tab_header1;
	tab_header1 << "   Numar Inmatriculare    " << "    Producator   " << "    Model    " << "Tip";
	this->lst_lista->horizontalHeader()->setStretchLastSection(true);
	this->lst_lista->setHorizontalHeaderLabels(tab_header1);*/
	btn1 = new QPushButton{ "Adauga Lista" };
	btn2 = new QPushButton{ "Genereaza random Lista" };
	btn3 = new QPushButton{ "Goleste Lista" };
	edit_rndm = new QLineEdit;
	tab->addWidget(btn1);
	tab->addWidget(edit_rndm);
	tab->addWidget(btn2);
	tab->addWidget(btn3);
	

	btn_undo = new QPushButton{ "Undo" };
	tab->addWidget(btn_undo);

	btn_reload = new QPushButton{ "Reload" };
	tab->addWidget(btn_reload);

	btn_lista = new QPushButton{ "Lista" };
	tab->addWidget(btn_lista);

	btn_lista_read = new QPushButton{ "Lista Read" };
	tab->addWidget(btn_lista_read);

	raport = new QPushButton{ "Raport" };
	tab->addWidget(raport);


	QWidget* rright = new QWidget;
	QVBoxLayout* ly_rr = new QVBoxLayout;
	rright->setLayout(ly_rr);

	parcare_lista = new QListWidget;
	t_br = new QPushButton{ "Break" };
	t_sdn = new QPushButton{ "Sedan" };
	t_suv = new QPushButton{ "SUV" };
	t_sprt = new QPushButton{ "Sport" };
	altele = new QPushButton{ "Altele" };
	ly_rr->addWidget(parcare_lista);

	vector<string> srt;
	for (auto m : srv.get_all_srv()) {
		srt.push_back(m.get_tip());
	}

	std::sort(srt.begin(), srt.end());
	srt.erase(unique(srt.begin(), srt.end()), srt.end());


	std::map<QString, QPushButton*> flt_btn;

	for (auto t : srt) {
		QPushButton* btn = new QPushButton(QString::fromStdString(t), this);

		connect(btn, &QPushButton::clicked, [this, t]() {
			vector<Masina> v = srv.filtreaza_t(t);
			this->reload_parcare(v);
			});

		ly_rr->addWidget(btn);
	}

	ly_main->addWidget(left);
	ly_main->addWidget(right);
	ly_main->addWidget(rright);

}

void parcare_gui::connect_sig_slots() {
	QObject::connect(btn_add, &QPushButton::clicked, this, &parcare_gui::gui_add);
	QObject::connect(btn_del, &QPushButton::clicked, this, &parcare_gui::gui_del);
	QObject::connect(btn_mod, &QPushButton::clicked, this, &parcare_gui::gui_mod);

	
	//QObject::connect(add_lst, &QPushButton::clicked, [&]() {
	//	this->srv.goleste_lst();
	//});

	//QObject::connect(grndm_lst, &QPushButton::clicked, [&]() {
	//	int nr = edit_rndm->text().toInt();
	//	this->srv.goleste_lst();
	//	this->srv.gnr_rndm(nr);
	//	//this->reload_lst(srv.get_all_lst());
	//});

	//QObject::connect(empty_lst, &QPushButton::clicked, [&]() {
	//	this->srv.goleste_lst();
	//});
	
	
	
	QObject::connect(btn_undo, &QPushButton::clicked, [&]() {
		try {
			this->srv.undo();
			vector<Masina> v = srv.get_all_srv();
			this->reload_parcare(v);
			QMessageBox::information(this, "INFO", QString::fromStdString("Undo realizat."));
		}
		catch (parcare_exception& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		});

	QObject::connect(btn_reload, &QPushButton::clicked, [&]() {
		try {
			vector<Masina> v = srv.get_all_srv();
			this->reload_parcare(v);
			QMessageBox::information(this, "INFO", QString::fromStdString("Reload realizat."));
		}
		catch (parcare_exception& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		});

	QObject::connect(btn_sort, &QPushButton::clicked, [&]() {
		if (this->radio_sort_nr->isChecked()) { 
			vector<Masina> v = srv.sorteaza_nr_inm();
			this->reload_parcare(v);
		}
		if (this->radio_sort_prod->isChecked()) {
			vector<Masina> v = srv.sorteaza_prod();
			this->reload_parcare(v);
		}
		if (this->radio_sort_tip->isChecked()) {
			vector<Masina> v = srv.sorteaza_tip();
			this->reload_parcare(v);
		}
	});

	QObject::connect(btn_flt_prod, &QPushButton::clicked, [&]() {
		try {
			string prod = edit_filter_prod->text().toStdString();
			vector<Masina> v = srv.filtreaza_p(prod);
			this->reload_parcare(v);

			QMessageBox::information(this, "INFO", QString::fromStdString("Filtrare efectuata."));
		}
		catch (parcare_exception& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
	});

	QObject::connect(btn_flt_tip, &QPushButton::clicked, [&]() {
		try {
			string tip = edit_filter_tip->text().toStdString();
			vector<Masina> v = srv.filtreaza_t(tip);
			this->reload_parcare(v);

			QMessageBox::information(this, "Warning", QString::fromStdString("Filtrare efectuata."));
		}
		catch (parcare_exception& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		});

	QObject::connect(btn_lista, &QPushButton::clicked, [&]() {

		auto fer_lst = new lst_crud{ srv.get_lst() };
		fer_lst->show();
		});

	QObject::connect(btn_lista_read, &QPushButton::clicked, [&]() {
		auto fer_lst = new lst_read{ srv.get_lst() };
		fer_lst->show();
		});

	QObject::connect(btn1, &QPushButton::clicked, [&]() {
			string nr = nr_inmatriculare->text().toStdString();
			nr_inmatriculare->clear();
			this->srv.adauga_ls(nr);

			//this->reload_lst(srv.get_all_lst());
		});

	QObject::connect(btn3, &QPushButton::clicked, [&]() {
		this->srv.goleste_lst();
		//this->reload_lst(srv.get_all_lst());
		});

	QObject::connect(btn2, &QPushButton::clicked, [&]() {
		int nr = edit_rndm->text().toInt();

		this->srv.gnr_rndm(nr);

		//this->reload_lst(srv.get_all_lst());
		});

	/*QObject::connect(export_lst, &QPushButton::clicked, [&]() {
		string nume = xprt->text().toStdString();
		xprt->clear();

		this->srv.write_to_file(nume);
		QMessageBox::information(this, "INFO", "Lista salvata!");
		});*/

	QObject::connect(raport, &QPushButton::clicked, [&]() {
		QWidget* rprt = new QWidget;
		QFormLayout* ly = new QFormLayout;
		rprt->setLayout(ly);

		QTableWidget* tbl_raport = new QTableWidget{ 20, 2 };
		QStringList tab_header1;
		tab_header1 << "   Numar Inmatriculare    " << "    Producator   " << "    Model    " << "Tip";
		tbl_raport->horizontalHeader()->setStretchLastSection(true);
		tbl_raport->setHorizontalHeaderLabels(tab_header1);

		ly->addWidget(tbl_raport);
		std::map<string, valueDTO> mp = srv.raport();
		int nr_linie = 0;
		for (auto& str : mp) {
			string ss = str.first;
			int ii = str.second.get_value();
			string g = std::to_string(ii);
			tbl_raport->setItem(nr_linie, 0, new QTableWidgetItem(QString::fromStdString(ss)));
			tbl_raport->setItem(nr_linie, 1, new QTableWidgetItem(QString::fromStdString(g)));
			nr_linie++;
		}
		rprt->show();
		});


}

void parcare_gui::reload_parcare(std::vector<Masina> parc) {

	this->parcare_lista->clear();
	int nr_linie = 0;
	for (auto& masina : parc) {
		string bam_bam = masina.get_nr() + " | " + masina.get_producator() + " | " + masina.get_model() + " | " + masina.get_tip();
		this->parcare_lista->addItem(QString::fromStdString(bam_bam));

		nr_linie++;
	}
	table_parcare->setMasini(parc);
}

void parcare_gui::reload_lst(std::vector<Masina> lst) {
	this->lst_lista->clearContents();
	this->lst_lista->setRowCount(lst.size());

	int nr_linie = 0;
	for (auto& masina : lst) {
		this->lst_lista->setItem(nr_linie, 0, new QTableWidgetItem(QString::fromStdString(masina.get_nr())));
		this->lst_lista->setItem(nr_linie, 1, new QTableWidgetItem(QString::fromStdString(masina.get_producator())));
		this->lst_lista->setItem(nr_linie, 2, new QTableWidgetItem(QString::fromStdString(masina.get_model())));
		this->lst_lista->setItem(nr_linie, 3, new QTableWidgetItem(QString::fromStdString(masina.get_tip())));
		nr_linie++;
	}
}

void parcare_gui::gui_add() {
	try {
		string nr = edit_nr->text().toStdString();
		string prod = edit_prod->text().toStdString();
		string model = edit_model->text().toStdString();
		string tip = edit_tip->text().toStdString();

		edit_nr->clear();
		edit_prod->clear();
		edit_tip->clear();
		edit_model->clear();

		this->srv.adauga_srv(nr, prod, model, tip);
		vector<Masina> v = srv.get_all_srv();
		this->reload_parcare(v);

		QMessageBox::information(this, "INFO", QString::fromStdString("Masina adaugata."));
	}
	catch (parcare_exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}

}

void parcare_gui::gui_del() {
	try {
		string nr = edit_nr->text().toStdString();
		string prod = edit_prod->text().toStdString();
		string model = edit_model->text().toStdString();
		string tip = edit_tip->text().toStdString();

		edit_nr->clear();
		edit_prod->clear();
		edit_tip->clear();
		edit_model->clear();

		this->srv.sterge_srv(nr);
		vector<Masina> v = srv.get_all_srv();
		this->reload_parcare(v);

		QMessageBox::information(this, "INFO", QString::fromStdString("Masina stearsa."));
	}
	catch (parcare_exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}

}

void parcare_gui::gui_mod() {
	try {
		string nr = edit_nr->text().toStdString();
		string prod = edit_prod->text().toStdString();
		string model = edit_model->text().toStdString();
		string tip = edit_tip->text().toStdString();

		edit_nr->clear();
		edit_prod->clear();
		edit_tip->clear();
		edit_model->clear();

		this->srv.modifica_srv(nr, prod, model, tip);
		vector<Masina> v = srv.get_all_srv();
		this->reload_parcare(v);

		QMessageBox::information(this, "INFO", QString::fromStdString("Masina modificata."));
	}
	catch (parcare_exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}
}