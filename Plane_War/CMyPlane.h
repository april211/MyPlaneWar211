#pragma once
#include "CPlane.h"
#include "resource.h"

//CMyPlane.h
class CMyPlane : public CPlane
{
protected:
    BOOL isdefence$;              /*我的战机是否拥有激光炮*/
    int  horizenm$;             /*战机的水平移动标识。左-1、静止0、右+1*/
    int  verticalm$;            /*战机的垂直移动标识。下+1、静止0、上-1*/
    int  maxtwait$;             //随关卡变化的最大发射间隔
    enum pD { UP = 0, DOWN, LEFT, RIGHT};
private:
    static CImageList mpImages; /*存储我的战机图片*/
public:
    CMyPlane();
    CMyPlane(const CMyPlane&);
    virtual ~CMyPlane();
    void setDefence(bool);
    bool getDefence();
    BOOL drawOb(CDC*, BOOL);
    CRect& getObRect();
    void newObRect();
    static BOOL Load();
     

    //设置我的战机的宽度和高度
    static const int MYPLANE_WIDTH = 64;    
    static const int MYPLANE_HEIGHT = 48;

    friend class CPlaneWarView;
};

