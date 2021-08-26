#include "mainwindow.h"
#include "frame.h"
#include "topbar.h"
#include "clock.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(632,16000);
    setStyleMainWindow();
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    topBar = new TopBar(this);
    this->setCentralWidget(topBar);
    this->resize(topBar->size().width(),topBar->size().height());
    QObject::connect(topBar->insert, &QPushButton::clicked, this, &MainWindow::insertFrame);
    QObject::connect(topBar->remove, &QPushButton::clicked, this, &MainWindow::eraseFrame);
    QObject::connect(topBar->selected ,&QPushButton::clicked, this, &MainWindow::openClosePriorityFrame);
    scroll_bar = new QScrollArea();
    scroll_bar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_bar->setFixedSize(632,800);
    scroll_bar->show();
    scroll_bar->setWidget(this);
}

void MainWindow::eraseFrame() {
    int height_remove_widget;
    bool following_this_frame = false;

    int number_selected_frames = 0;                  //общее число выделенных элементов
    QObjectList children_ = this->children();
    foreach(QObject *child, children_) {
            Frame *childWidget = dynamic_cast<Frame*> (child);
            if(childWidget){
                if(childWidget->isFrameSelected()){
                    number_selected_frames++;
                }

            }
    }

 bool only_one_pass = true;
 for(int index = 0; index < number_selected_frames; ++index) {  // за каждую итерацию удаляет по одному элементу
    following_this_frame = false;
    only_one_pass = true;
    QObjectList children = this->children();
    foreach(QObject *child, children) {
            Frame *childWidget = dynamic_cast<Frame*> (child);
            if(childWidget){
                if(childWidget->isFrameSelected() && only_one_pass) {
                  only_one_pass = false;              //находит первый выделенный элемент
                  height_remove_widget = childWidget->size().height();
                  following_this_frame = true;       //и разрешает сместить остальные
                  delete childWidget;

                  int window_height = topBar->size().height();
                  QObjectList children_ = this->children();
                  foreach(QObject *child, children_) {
                          Frame *childWidget = dynamic_cast<Frame*> (child);
                          if(childWidget){
                              window_height += childWidget->size().height();
                          }

                  }
                  this->resize(this->size().width(),window_height);
                  continue;
            }
             if(following_this_frame){           //moving frames after removing selected frame
                 childWidget->move(25,childWidget->pos().y() - height_remove_widget);
             }
        }
    }
    }

}


void MainWindow::insertFrame() {
  Frame* frame = new Frame(this);
  frame->closeFrame();
  int topBarHeight = topBar->size().height();
  int pos = -frame->size().height();       //notice: here is minus //размер первого виджета не учитывается
   QObjectList children = this->children();
      foreach(QObject *child, children) {
           Frame *childWidget = dynamic_cast<Frame*> (child);
                 if(childWidget){
                           pos+=childWidget->size().height();
                          }
                    }
      pos+=topBarHeight;
      frame->move(25,pos);
      this->resize(this->size().width(),pos+=350);
}


void MainWindow::openClosePriorityFrame() {
    QObjectList children = this->children();
       foreach(QObject *child, children) {
            Frame *childWidget = dynamic_cast<Frame*> (child);
                  if(childWidget){
                         if(!childWidget->getPriority() && childWidget->currentStateFrame()) {
                             childWidget->openFrame();
                             continue;
                          }
                         if(!childWidget->getPriority() && !childWidget->currentStateFrame()) {
                             childWidget->closeFrame();
                             continue;
                          }
                     }
       }

}

void MainWindow::setStyleMainWindow(){
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(252, 255, 0));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(153, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
}


void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow() {
    delete ui;
}







