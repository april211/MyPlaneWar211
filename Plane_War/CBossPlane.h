#pragma once
#include "CEnemyPlane.h"
#include "resource.h"
class CBossPlane : public CPlane
{
private:
    static CImageList bp1Images; //存储BOSS1图片
    static CImageList bp2Images; //存储BOSS2图片
    static CImageList bp3Images; //存储BOSS3图片
    static CImageList bp4Images; //存储BOSS4图片
public:
    CBossPlane(int id, int hp);
    CBossPlane(const CBossPlane&);
    virtual ~CBossPlane();
    BOOL drawOb(CDC*, BOOL);
    CRect& getObRect();
    void newObRect();
    static BOOL Load();
    enum BossId
    {
        enfirst = 0,
        ensecond,
        enthird,
        enforth
    };
protected:
    int id$;        //确定BOSS型号
    int verticalm$;



    //设置BOSS的战机的宽度和高度
    static const int BOSSPLANE1_WIDTH  = 122;
    static const int BOSSPLANE1_HEIGHT = 114;

    static const int BOSSPLANE2_WIDTH  = 119;
    static const int BOSSPLANE2_HEIGHT = 110;

    static const int BOSSPLANE3_WIDTH  = 131;
    static const int BOSSPLANE3_HEIGHT = 92;

    static const int BOSSPLANE4_WIDTH  = 125;
    static const int BOSSPLANE4_HEIGHT = 84;

    friend class CPlaneWarView;

};



