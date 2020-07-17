#pragma once
#include "CGameObject.h"

//CPlane.h

class CPlane : public CGameObject
{
protected:
    int speed$;	          /*战机的速度*/
    int score$;	          /*战机的得分*/
    int hp$;		      /*战机的生命值*/
    int twait$;           /*战机填装空隙*/
public:
//构造函数
    CPlane();
    CPlane(int speed, int score, int hp);
    CPlane(const CPlane& tt);
    virtual ~CPlane();       //构造函数的的声明
//方法声明
    void setHp(int);
    void setSpeed(int);
    void setScore(int);
    int  getHp();
    int  getSpeed();
    int  getScore();
    
    bool ifFire();//检测战机近期是否开过炮，避免炮弹的重叠
};

