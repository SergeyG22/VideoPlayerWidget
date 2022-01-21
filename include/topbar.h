#ifndef TOPBAR_H
#define TOPBAR_H
#include <QWidget>
#include <QPushButton>


class TopBar: public QWidget
{
public:
    explicit TopBar(QWidget *parent);
    QPushButton* remove = nullptr;
    QPushButton* insert = nullptr;
    QPushButton* selected = nullptr;
};

#endif // TOPBAR_H
