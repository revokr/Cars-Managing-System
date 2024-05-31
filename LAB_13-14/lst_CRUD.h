#pragma once
#include "service.h"
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




class lst_crud : public Observer, public QWidget {
private:
	lst& lstt;
	QTableWidget* lst_lista;
	QLineEdit* nr_inm;
	QLineEdit* nr_mas;
	QPushButton* add_lst;
	QPushButton* empty_lst;
	QPushButton* grndm_lst;

	void init() {
		QHBoxLayout* ly = new QHBoxLayout;
		lst_lista = new QTableWidget{ 20, 4 };
		ly->addWidget(lst_lista);

		nr_inm = new QLineEdit;
		nr_mas = new QLineEdit;
		add_lst = new QPushButton{ "Adauga" };
		empty_lst = new QPushButton{ "Goleste" };
		grndm_lst = new QPushButton{ "Genereaza random" };

		QVBoxLayout* lyy = new QVBoxLayout;
		lyy->addWidget(nr_inm);
		lyy->addWidget(add_lst);

		lyy->addWidget(nr_mas);
		lyy->addWidget(grndm_lst);

		lyy->addWidget(empty_lst);
		ly->insertLayout(1, lyy);
		setLayout(ly);

	}

	void conn() {
		lstt.add_obs(this);
		QObject::connect(add_lst, &QPushButton::clicked, [&]() {
			try {
				string nr = nr_inm->text().toStdString();
				nr_inm->clear();
				lstt.add_lst(nr);

				this->reload_lstt(lstt.get());
			}
			catch (parcare_exception& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
			}
			});

		QObject::connect(empty_lst, &QPushButton::clicked, [&]() {
			this->lstt.empty();
			this->reload_lstt(lstt.get());
			});

		QObject::connect(grndm_lst, &QPushButton::clicked, [&]() {
			int nr = nr_mas->text().toInt();
			this->lstt.empty();
			this->lstt.gnr_rndm(nr);

			this->reload_lstt(lstt.get());
			});
	}
public:
	lst_crud(lst& ap) : lstt{ ap } {
		init();
		conn();
	}

	void update() override {
		reload_lstt(lstt.get());
	}

	~lst_crud() {
		lstt.remove_obs(this);
	}

	void reload_lstt(std::vector<Masina> lst) {
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
};