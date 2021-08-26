#include "frame.h"

Frame::Frame(QWidget *parent): QWidget(parent){
    main_window_ptr = parent;
    lcd_timer = std::unique_ptr<LCDtimer>(new LCDtimer(this));
    lcd_clock = std::unique_ptr<LCDclock>(new LCDclock(this));
    lcd_clock->move(335,125);
    lcd_clock->showTime();
    lcd_timer->move(65,125);
    lcd_timer->showTimer();      
    priority_button = new QPushButton(QIcon(":/new/prefix1/icon/small_star.png"), "", this);
    priority_button->setFixedSize(30,30);
    priority_button->move(500,4);
    hide_button = new QPushButton(QIcon(":/new/prefix1/icon/open.png"), "", this);
    hide_button->setFixedSize(30,30);
    hide_button->move(540,4);
    this->setStyleSheet("background-color: rgba(252, 255, 0, 70%);");
    this->setFixedSize(582,350);
    this->show();
    QObject::connect(hide_button, &QPushButton::clicked, this, &Frame::hideFrame);
    QObject::connect(priority_button, &QPushButton::clicked, this, &Frame::setPriority);
}

Frame::~Frame(){

}

void Frame::hideFrame() {
    if(show_frame){
        openFrame();
    }else{
        closeFrame();
    }
}

void Frame::openFrame(){
    hide_button->setIcon(QIcon(":/new/prefix1/icon/open.png"));
    show_frame = false;
    resizeFrame(this->size().width(),350);

    int width_main_window = main_window_ptr->size().width();
    int height_main_window = main_window_ptr->size().height() + 310;
    resizeMainWindow(width_main_window,height_main_window);
    movingWidgetsFromOpenedWidget();
}

void Frame::closeFrame(){
    hide_button->setIcon(QIcon(":/new/prefix1/icon/close.png"));
    show_frame = true;
    resizeFrame(this->size().width(),40);

    int width_main_window = main_window_ptr->size().width();
    int height_main_window = main_window_ptr->size().height() - 310;
    resizeMainWindow(width_main_window,height_main_window);
    movingWidgetsToСlosedWidget();
}

void Frame::resizeMainWindow(int w,int h){
    main_window_ptr->resize(w,h);
}

void Frame::movingWidgetsToСlosedWidget(){
    QObjectList children = main_window_ptr->children();
    bool following_this_frame = false;
    foreach(QObject *child, children) {
            Frame *childWidget = dynamic_cast<Frame*> (child);
            if(childWidget == this){
               following_this_frame = true;
               continue;
            }
            if(following_this_frame){
                int posY = childWidget->pos().y() - 310;
                childWidget->move(childWidget->pos().x(),posY);
            }
        }
}

void Frame::movingWidgetsFromOpenedWidget(){
    QObjectList children = main_window_ptr->children();
    bool following_this_frame = false;
    foreach(QObject *child, children) {
            Frame *childWidget = dynamic_cast<Frame*> (child);
            if(childWidget == this){
               following_this_frame = true;
               continue;
            }
            if(following_this_frame){
                int posY = childWidget->pos().y() + 310;
                childWidget->move(childWidget->pos().x(),posY);
            }
        }
}



void Frame::resizeFrame(int w, int h){
    this->setFixedSize(w,h);
}

bool Frame::getPriority()const{
    return priority;
}

void Frame::setPriority(){
    if(priority){
        priority_button->setIcon(QIcon(":/new/prefix1/icon/small_star.png"));
        priority = false;
    }else{
        priority_button->setIcon(QIcon(":/new/prefix1/icon/blue_small_star.png"));
        priority = true;
    }
}




void Frame::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(155,155,255));
    painter.setPen(pen);
    painter.drawRoundedRect(0,2,width()-1, height()-7,3,3);
    QWidget::paintEvent(event);

}

void Frame::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if(selected_frame){
            this->setStyleSheet("background-color: rgba(252, 255, 0, 70%);");
            selected_frame = false;
        }else{
            this->setStyleSheet("background-color: rgba(13, 67, 246, 70%);");
            selected_frame = true;
        }
    }
}



