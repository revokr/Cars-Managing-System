#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include <vector>
#include <qdebug.h>

using namespace std;

class TableModel : public QAbstractTableModel {
private:
	std::vector<Masina> lst;
public:
	TableModel(std::vector<Masina> oferte) : lst{ oferte } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return lst.size() + 1;
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		//qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::DisplayRole && index.row() < lst.size()) {
			Masina p = lst[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.get_nr());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.get_producator());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.get_model());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(p.get_tip());
			}
			//return QString("Row%1, Column%2").arg(index.row()).arg(index.column());
		}

		return QVariant{};
	}

	void setMasini(vector<Masina> oferte) {
		oferte.push_back(Masina{ "", "", "", "" });
		this->lst = oferte;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};