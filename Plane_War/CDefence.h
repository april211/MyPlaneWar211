#pragma once
#include "CGameObject.h"
class CDefence : public CGameObject
{
private:
    static CImageList dcImages; /*存储我的战机图片*/
public:
    CDefence();
    CDefence(int x, int y);
    CDefence(const CDefence&);
    virtual ~CDefence();

    BOOL drawOb(CDC*, BOOL);
    CRect& getObRect();
    void newObRect();
    static BOOL Load();


    //设置我的战机的宽度和高度
    static const int DEFENCE_WIDTH  = 80;
    static const int DEFENCE_HEIGHT = 41;
    static const int LAST = 100;

    friend class CPlaneWarView;
};

