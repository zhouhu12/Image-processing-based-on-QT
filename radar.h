#ifndef RADAR_H
#define RADAR_H

#include <QWidget>
#include<QPainter>
#include<cmath>

class radar : public QWidget
{
    Q_OBJECT
public:
    explicit radar(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    float showX(const QPoint& point);


};

#endif // RADAR_H
