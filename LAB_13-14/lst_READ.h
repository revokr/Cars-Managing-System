#include "lst_CRUD.h"
#include <qpaintdevice.h>
#include <qpainter.h>

class lst_read : public QWidget, public Observer
{
private:
	lst& ls;
public:
	lst_read(lst& lss) : ls{ lss } {
		ls.add_obs(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		srand(time(NULL));
		for (auto& u : ls.get()) {
			int x = rand() % 300;
			int y = rand() % 300;
			qDebug() << x << " " << y << '\n';
			int sz = u.get_producator().size();
			p.drawRect(x, y,  20, sz * 40);
		}

	}
};