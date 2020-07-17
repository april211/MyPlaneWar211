#include "pch.h"
#include "CBullet.h"
//CBullet.cpp

//构造
CBullet::CBullet() : CGameObject(0, 0), atk$(0), speed$(0) {}
CBullet::CBullet(int atk, int speed) : CGameObject(0, 0), atk$(atk), speed$(speed) {}
CBullet::CBullet(int x, int y, int atk, int speed): CGameObject(x, y), atk$(atk), speed$(speed) {}
CBullet::CBullet(const CBullet& tt) : atk$(tt.atk$), speed$(tt.speed$) 
{ 
	setObPoint(tt.obposition$.x, tt.obposition$.y);
}
CBullet::~CBullet() {}

//方法
void CBullet::setSpeed(int speed) { speed$ = speed; }
void CBullet::setAtk(int atk) { atk$ = atk; }
int CBullet::getSpeed() { return speed$; }
int CBullet::getAtk() { return atk$; }

