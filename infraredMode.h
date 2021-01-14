#ifndef INFRAREDSCREEN_H
#define INFRAREDSCREEN_H

#include <QWidget>
#include<QKeyEvent>
#include<QLabel>
#include<QPixmap>
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<QTime>
#include<vector>
#include"radar.h"
#define WHOLEWIDTH 8655
#define WHOLEHEIGHT 512
#define OBSERVEWIDTH 1054
#define OBSERVEHEIGHT 512
#define WARNWIDTH 467
#define WARNHEIGHT 262

//雷达区
//QPoint radarPoint;
//全景区
struct MoveQPoints
{
    QPoint startQPoint;
    QPoint endQPoint;
};

enum WholeMode
{
    STATI,
    MOVE,
    OTHERS
};

struct WholePoints
{
   QPoint stati;
   MoveQPoints moves;
};
struct WInfo
{
    WholeMode mode=OTHERS;
    WholePoints points;
};

//观察区
struct OInfo{
    int warnId;
    QPoint point;
};
enum observeMode{
    ADJUST,
    WARNINFO,
    OTHER
};
struct ObserveInfo{
    observeMode mode=OTHER;
    std::vector<OInfo> observes;
//    ={{1,QPoint(300,200)},
//                                 {2,QPoint(300,200)},
//                                 {3,QPoint(300,200)},
//                                 {4,QPoint(300,200)}};
    MoveQPoints move;
};
struct warnInfo
{
    int warning=-1;
    int warn1=0;
    int warn2=0;
    int warn3=0;
    int warn4=0;
};

struct Info
{
    QPoint radarPoint=QPoint(233+10,355+282);
    WInfo whole;
    ObserveInfo observe;
    warnInfo warn;
    int FiSe=0;
};


//enum ControlMode{
//    RADAR,
//    WHOLE,
//    OBSERVE,
//    WARN
//};

struct Control
{
    QPixmap *pix;
//    ControlMode mode;
    Info controlInfo;
};



enum Area
{
    warningArea1,
    warningArea2,
    warningArea3,
    warningArea4,
    observeArea,
    radarArea,
    wholeArea
};



class infraredScreen : public QWidget
{
    Q_OBJECT
public:
    explicit infraredScreen(QWidget *parent = nullptr);

    ~infraredScreen();

    void updateImage(Control& control);

private:

    QLabel * warningArea1;
    QLabel * warningArea2;
    QLabel * warningArea3;
    QLabel * warningArea4;
    QLabel * observeArea;
    radar * radarArea;
    QLabel * wholeArea;

    QPixmap wholePix;
    QPixmap wholePix1;
    QPixmap observePix;

    int warn1X=720,warn1Y=345;
    int warn2X=720,warn2Y=345;
    int warn3X=720,warn3Y=345;
    int warn4X=720,warn4Y=345;

//    QPixmap warn1;
//    QPixmap warn2;
//    QPixmap warn3;
//    QPixmap warn4;

    int tMove1=0,tMove=0;

    int addX=0,addX1=0,addX2=0;

    void controlRadar(Control& control);

    void controlWhole(Control& control);

    void controlObserve(Control& control);

    void controlWarn(Control& control);

    QPixmap stitchPixmap(QPixmap pix1,QPixmap pix2);

    QPixmap setPix(const QPixmap* pix,int x,int targetWidth,int targetHeight);

};

#endif // INFRAREDSCREEN_H
