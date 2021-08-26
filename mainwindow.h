#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <qlayout.h>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QDebug>
#include "frame.h"
#include "topbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void eraseFrame();
    void insertFrame();
    void setStyleMainWindow();
    void openClosePriorityFrame();
private:
    void resizeEvent(QResizeEvent*)override;
    bool priority_state = false;
    TopBar* topBar = nullptr;
    QScrollArea* scroll_bar = nullptr;
    QWidget *centralWidget;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
