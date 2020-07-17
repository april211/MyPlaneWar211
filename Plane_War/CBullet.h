#pragma once
#include "CGameObject.h"
class CBullet :
    public CGameObject
{
protected:
    int atk$;             /*弹药的攻击力*/
    int speed$;           /*弹药的飞行速度*/
public:
//构造函数
    CBullet();
    CBullet(int atk, int speed);
    CBullet(int x, int y, int atk, int speed);
    CBullet(const CBullet& tt);
    virtual ~CBullet();       
//方法声明
    void setSpeed(int);
    void setAtk(int);
    int  getSpeed();
    int  getAtk();
};


