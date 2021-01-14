#include "infraredMode.h"
#include <QPoint>
#include <thread>
#include <QImageReader>

infraredScreen::infraredScreen(QWidget *parent) : QWidget(parent)
{

    setFixedSize(1920,1080);
    setWindowTitle("infrared");
    this->setStyleSheet("background-color:rgb(2,18,32);");

    warningArea1=new QLabel;
    warningArea1->setFixedSize(467,262);
    warningArea1->move(10,10);
    warningArea1->setParent(this);
    warningArea1->setFrameShape(QFrame::Box);
    warningArea1->setStyleSheet("border-width:2px;border-style:solid;border-color:rgb(3,52,81);");

    warningArea2=new QLabel;
    warningArea2->setFixedSize(467,262);
    warningArea2->move(484,10);
    warningArea2->setParent(this);
    warningArea2->setFrameShape(QFrame::Box);
    warningArea2->setStyleSheet("border-width:2px;border-style:solid;border-color:rgb(3,52,81);");

    warningArea3=new QLabel;
    warningArea3->setFixedSize(467,262);
    warningArea3->move(960,10);
    warningArea3->setParent(this);
    warningArea3->setFrameShape(QFrame::Box);
    warningArea3->setStyleSheet("border-width:2px;border-style:solid;border-color:rgb(3,52,81);");

    warningArea4=new QLabel;
    warningArea4->setFixedSize(467,262);
    warningArea4->move(1435,10);
    warningArea4->setParent(this);
    warningArea4->setFrameShape(QFrame::Box);
    warningArea4->setStyleSheet("border-width:2px;border-style:solid;border-color:rgb(3,52,81);");

    observeArea=new QLabel;
    observeArea->setFixedSize(1420,690);
    observeArea->move(484,282);
    observeArea->setParent(this);
    observeArea->setFrameShape(QFrame::Box);
    observeArea->setStyleSheet("border-width:2px;border-style:solid;border-color:rgb(3,52,81);");

    radarArea=new radar;
    radarArea->setFixedSize(466,690);
    radarArea->move(10,282);
    radarArea->setParent(this);
    radarArea->setStyleSheet("border:2px solid red");
//    warningArea1->setFrameShape(QFrame::Box);
//    warningArea1->setStyleSheet("border-width:2px;border-style:solid;border-color:rgb(3,52,81);");

    wholeArea=new QLabel;
    wholeArea->setFixedSize(1420,84);
    wholeArea->move(484,982);
    wholeArea->setParent(this);
    wholeArea->setFrameShape(QFrame::Box);
    wholeArea->setStyleSheet("border-width:2px;border-style:solid;border-color:rgb(3,52,81);");

}

infraredScreen::~infraredScreen()
{
    delete warningArea1;
    delete warningArea2;
    delete warningArea3;
    delete warningArea4;
    delete observeArea;
    delete radarArea;
    delete wholeArea;
}

void infraredScreen::updateImage( Control& control)
{
    //雷达区域控制
    controlRadar(control);
    //全景区域控制
    controlWhole(control);
    //观测区域下控制
    controlObserve(control);
    //警戒区控制
    controlWarn(control);
}

void infraredScreen::controlRadar( Control& control)
{
    //雷达控制全景区域
    int startX=(radarArea->showX(control.controlInfo.radarPoint)/360.0)*control.pix->width();
    QPixmap pixW=setPix(control.pix,startX,WHOLEWIDTH,WHOLEHEIGHT);
    if(control.controlInfo.whole.mode==OTHERS)
    {
        addX+=(startX-OBSERVEWIDTH/2);
    }else
    {
        addX+=(startX-WHOLEWIDTH/2);
    }
    addX1+=(startX-WHOLEWIDTH/2);
//    qDebug()<<addX;
    wholeArea->setPixmap(pixW.scaled(wholeArea->width(),wholeArea->height()));
    wholePix=pixW;
    //雷达控制观测区域
    if(control.controlInfo.FiSe==1)
        observeArea->setPixmap(pixW.copy(WHOLEWIDTH/2-OBSERVEWIDTH/2,0,OBSERVEWIDTH,OBSERVEHEIGHT).scaled(observeArea->width(),observeArea->height()));
}

void infraredScreen::controlWhole( Control& control)
{
    //全景区域下点控制
    if(control.controlInfo.whole.mode==STATI)
    {
        //全景区域
        int startX=(control.controlInfo.whole.points.stati.x()-486)*6.095;
        addX+=(startX-OBSERVEWIDTH/2);
        if(control.controlInfo.FiSe==2)
            observeArea->setPixmap(wholePix.copy(startX-OBSERVEWIDTH/2,0,OBSERVEWIDTH,OBSERVEHEIGHT).scaled(observeArea->width(),observeArea->height()));
//        control.controlInfo.whole.points.stati=QPoint()
    }
    //全景区域下滑动控制
    else if(control.controlInfo.whole.mode==MOVE)
    {
//        qDebug()<<"start";
//        int x1=control.controlInfo.whole.points.moves.startQPoint.x()-486;
//        int x2=control.controlInfo.whole.points.moves.endQPoint.x()-486;
//        int move=x2-x1;
//        addX1+=(6.095*move);
//        addX+=(6.095*move);
//        if(6.095*move+addX1<0)
//        {
//            wholePix1=setPix(control.pix,6.095*move+addX1+control.pix->width(),WHOLEWIDTH,WHOLEHEIGHT);
//            wholeArea->setPixmap(wholePix1.scaled(wholeArea->width(),wholeArea->height()));

//            //            QPixmap pixW=setPix(control.pix,6*x2+addX+control.pix->width(),WHOLEWIDTH,WHOLEHEIGHT);
//        }else
//        {
//            wholePix1=setPix(control.pix,6.095*move+addX1,WHOLEWIDTH,WHOLEHEIGHT);
//            wholeArea->setPixmap(wholePix1.scaled(wholeArea->width(),wholeArea->height()));

//            //            QPixmap pixW=setPix(control.pix,6*x2+addX,WHOLEWIDTH,WHOLEHEIGHT);
//        }

//        observeArea->setPixmap(wholePix1.copy(WHOLEWIDTH/2-OBSERVEWIDTH/2,0,OBSERVEWIDTH,OBSERVEHEIGHT).scaled(observeArea->width(),observeArea->height()));
//        wholeArea->setPixmap(pixW.scaled(wholeArea->width(),wholeArea->height()));
    }
    addX1=0;
}

void infraredScreen::controlObserve( Control& control)
{
    //移动调整
    if(control.controlInfo.observe.mode==ADJUST)
    {

    }

    //对应警戒区
    else if(control.controlInfo.observe.mode==WARNINFO)
    {
        if(addX<0)
        {
            addX+=control.pix->width();
        }
        if(control.controlInfo.observe.observes.size()!=0)
        {
            addX2=addX;
//            qDebug()<<"addX2"<<addX2;
        }
        for(const auto &item: control.controlInfo.observe.observes)
        {
            qDebug()<<"warnX"<<item.point.x();
            qDebug()<<"warnY"<<item.point.y();
            int x=item.point.x()-233-486;
            int y=item.point.y()-131-282;
            if(x<0)
            {
                x=0;
            }else if((item.point.x()-486)>1186)
            {
                x=953;
            }
            if(y<0)
            {
                y=0;
            }else if((item.point.y()-282)>559)
            {
                y=428;
            }
            qDebug()<<"X"<<x;
            qDebug()<<"Y"<<y;
            if(item.warnId==1)
            {
                warn1X=(x*512/690)+addX2;
                warn1Y=y*512/690;
                qDebug()<<"warn1X"<<warn1X;
                qDebug()<<"warn1Y"<<warn1Y;
//                warn1=control.pix->copy(x+addX,y,WARNWIDTH,WARNHEIGHT);
            }else if(item.warnId==2)
            {
                warn2X=(x*512/690)+addX2;
                warn2Y=y*512/690;
//                warn2=control.pix->copy(x+addX,y,WARNWIDTH,WARNHEIGHT);
            }else if(item.warnId==3)
            {
                warn3X=(x*512/690)+addX2;
                warn3Y=y*512/690;
//                warn3=control.pix->copy(x+addX,y,WARNWIDTH,WARNHEIGHT);
            }else if(item.warnId==4)
            {
                warn4X=(x*512/690)+addX2;
                warn4Y=y*512/690;
//                warn4=control.pix->copy(x+addX,y,WARNWIDTH,WARNHEIGHT);
            }
        }
        control.controlInfo.observe.observes.clear();

    }
    warningArea1->setPixmap(control.pix->copy(warn1X,warn1Y,WARNWIDTH,WARNHEIGHT).scaled(WARNWIDTH,WARNHEIGHT));
    warningArea2->setPixmap(control.pix->copy(warn2X,warn2Y,WARNWIDTH,WARNHEIGHT).scaled(WARNWIDTH,WARNHEIGHT));
    warningArea3->setPixmap(control.pix->copy(warn3X,warn3Y,WARNWIDTH,WARNHEIGHT).scaled(WARNWIDTH,WARNHEIGHT));
    warningArea4->setPixmap(control.pix->copy(warn4X,warn4Y,WARNWIDTH,WARNHEIGHT).scaled(WARNWIDTH,WARNHEIGHT));
    addX=0;


}

void infraredScreen::controlWarn(Control& control)
{

    switch (control.controlInfo.warn.warning)
    {
    case 1:
    {
        if(control.controlInfo.warn.warn1%2==1)
            observeArea->setPixmap(control.pix->copy(warn1X,warn1Y,WARNWIDTH,WARNHEIGHT).scaled(observeArea->width(),observeArea->height()));
        break;
    }
    case 2:
    {
        if(control.controlInfo.warn.warn2%2==1)
            observeArea->setPixmap(control.pix->copy(warn2X,warn2Y,WARNWIDTH,WARNHEIGHT).scaled(observeArea->width(),observeArea->height()));
        break;
    }
    case 3:
    {
        if(control.controlInfo.warn.warn3%2==1)
            observeArea->setPixmap(control.pix->copy(warn3X,warn3Y,WARNWIDTH,WARNHEIGHT).scaled(observeArea->width(),observeArea->height()));
        break;
    }
    case 4:
    {
        if(control.controlInfo.warn.warn4%2==1)
            observeArea->setPixmap(control.pix->copy(warn4X,warn4Y,WARNWIDTH,WARNHEIGHT).scaled(observeArea->width(),observeArea->height()));
        break;
    }
    }


}

QPixmap infraredScreen::stitchPixmap(QPixmap pix1,QPixmap pix2)
{
    QPixmap stitchPix(pix1.width()+pix2.width(),pix1.height());
    QPainter p(&stitchPix);

    p.drawPixmap(0,0,pix1.width(),pix1.height(),pix1);
    p.drawPixmap(pix1.width(),0,pix2.width(),pix2.height(),pix2);
    return stitchPix;
}

QPixmap infraredScreen::setPix(const QPixmap* pix,int x,int targetWidth,int targetHeight)
{
    if(x<targetWidth/2)
    {
        QPixmap pix1=pix->copy(pix->width()+x-targetWidth/2,0,targetWidth/2-x,pix->height());
        QPixmap pix2=pix->copy(0,0,targetWidth/2+x,pix->height());
        QPixmap pix3=stitchPixmap(pix1,pix2);
        return pix3;
    }else if(pix->width()-x<targetWidth/2)
    {
        QPixmap pix1=pix->copy(x-targetWidth/2,0,pix->width()-x-targetWidth/2,pix->height());
        QPixmap pix2=pix->copy(0,0,targetWidth-(pix->width()-x-targetWidth/2),pix->height());
        QPixmap pix3=stitchPixmap(pix1,pix2);
        return pix3;
    }else
    {

        return pix->copy(x-targetWidth/2,0,targetWidth,targetHeight);
    }

}




