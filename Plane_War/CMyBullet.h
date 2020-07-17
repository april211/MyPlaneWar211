#pragma once
#include "CBullet.h"
class CMyBullet :
    public CBullet
{
protected:

public:
    CMyBullet();
    CMyBullet(int x, int y, int speed, int atk);
    virtual ~CMyBullet();
};

