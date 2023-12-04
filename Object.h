#pragma once
const double minN = 0.0000001;
class Object
{
public:
	double x, y;
	int size;
	int hp;
	double speed;
	bool isLive;
	double sin, cos;
	bool penetrationConfirmed = false;
	bool beHit;
	Object();
	Object(double xx, double yy);
};
Object::Object()
{
	hp = 100;
	isLive = true;
}
Object::Object(double xx, double yy)
{
	x = xx;
	y = yy;
}