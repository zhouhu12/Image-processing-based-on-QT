#include "radar.h"

radar::radar(QWidget *parent) : QWidget(parent)
{

}


void radar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.drawEllipse(18,130,430,430);
    painter.drawPixmap(6,112,454,454,QPixmap("/home/hz/Ray/ImageProcess/Radar.png"));
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(3,52,81));
    painter.setPen(pen);
    painter.drawRect(0,0,465,689);
}

float radar::showX(const QPoint& point)
{
    float x=(point.x()-233-10);
    float y=(point.y()-345-282);
    if(x>=0&&y<0)
    {
        float result=atan(x/(-y))*180/3.1415926;
        return result;
    }else if(x>=0&&y>0)
    {
        float result=atan(x/(-y))*180/3.1415926+180;
        return result;
    }else if(x<0&&y<0)
    {
        float result=atan(x/(-y))*180/3.1415926+360;
        return result;
    }else if(x<0 && y>0)
    {
        float result=atan(x/(-y))*180/3.1415926+180;
        return result;
    }else if(y==0 && x>0)
    {
        return 90.0;
    }else if(y==0&&x<=0)
    {
        return 270.0;
    }
}
