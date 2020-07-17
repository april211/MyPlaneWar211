#pragma once
#include "CPlane.h"
#include "resource.h"


class CEnemyPlane : public CPlane
{
protected:
    int  verticalm$;            //敌人机的垂直移动标识。一般为下，+1
    enum pD { UP = 0, DOWN, LEFT, RIGHT };
private:
    static CImageList epImages; //存储敌机图片
public:
    CEnemyPlane();
    CEnemyPlane(int hp);
    CEnemyPlane(const CEnemyPlane&);
    virtual ~CEnemyPlane();
    BOOL drawOb(CDC*, BOOL);
    CRect& getObRect();
    void newObRect();
    static BOOL Load();

    //设置我的战机的宽度和高度
    static const int ENEMYPLANE_WIDTH = 64;
    static const int ENEMYPLANE_HEIGHT = 47;

    friend class CPlaneWarView;
};

