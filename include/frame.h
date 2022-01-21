#ifndef FRAME_H
#define FRAME_H
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QMainWindow>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPainter>
#include <QTimer>
#include <memory>
#include "clock.h"


class Frame: public QWidget
{
    QWidget* main_window_ptr = nullptr;
    QPushButton* hide_button = nullptr;
    QPushButton* priority_button = nullptr;   
    bool priority = false;
    bool show_frame = false;   
    bool selected_frame = false;   
    std::unique_ptr<LCDtimer>lcd_timer;
    std::unique_ptr<LCDclock>lcd_clock;
public:
    explicit Frame(QWidget *parent);
    void openFrame();
    void closeFrame();
    void resizeFrame(int,int);
    void movingWidgetsToClosedWidget();
    void movingWidgetsFromOpenedWidget();
    void resizeMainWindow(int,int);
    bool getPriority()const;
    bool isFrameSelected()const{ return selected_frame; };
    bool currentStateFrame()const{ return show_frame; };
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*)override;
    ~Frame();
private slots:
   void hideFrame();
   void setPriority();
};

#endif // FRAME_H
