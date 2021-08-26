#include "topbar.h"


TopBar::TopBar(QWidget *parent): QWidget(parent){   
    remove = new QPushButton(QIcon(":/new/prefix1/icon/minus.png"), "", this);
    remove->setFixedSize(40,40);
    remove->move(10,10);
    insert = new QPushButton(QIcon(":/new/prefix1/icon/plus.png"), "", this);
    insert->setFixedSize(40,40);
    insert->move(50,10);
    selected = new QPushButton(QIcon(":/new/prefix1/icon/star.png"), "", this);
    selected->setFixedSize(40,40);
    selected->move(90,10);
    this->setStyleSheet("background-color:green;");
    this->setFixedSize(632,60);
    this->show();
}

