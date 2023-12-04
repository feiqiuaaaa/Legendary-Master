#pragma once
#include"Object.h"
#include<math.h>
int bulletXZ[7] = { 4,4,27,23,30 };//贴图修正
class Bullet : public Object
{
public:
	Bullet();
	~Bullet();
	Bullet(double xx, double yy, double dsin, double dcos, double bulletSpeed, int bulletSize, int bulletDamage, int RepulseSpeed, int iid, int bulletBelong);
	int damage;
	int belong;//0表示属于玩家，1表示属于敌人
	int id;//0表示玩家子弹，1表示一般子弹，2表示跟踪子弹，3表示大型跟踪子弹,4表示激光枪子弹
	int bulletBeat;//击退数值
	bool penetrate;
	double startSin, startCos, maxAngle = 3.1415926 / 3;//初始方向，最大偏离角度60度（用于跟踪子弹
	IMAGE* img1;
	IMAGE* img2;
	IMAGE* Blackimgs;
	IMAGE* Coverimgs;
	Object* des;
	void Move();
	void MoveTo(Object* a);
	void readImage();
	void drawBullet();
};
Bullet::Bullet(double xx, double yy, double dsin, double dcos, double bulletSpeed, int bulletSize, int bulletDamage, int RepulseSpeed, int iid, int bulletBelong)
{
	x = xx;
	y = yy;
	startSin = sin = dsin;
	startCos = cos = dcos;
	damage = bulletDamage;
	speed = bulletSpeed;
	size = bulletSize;
	belong = bulletBelong;
	bulletBeat = RepulseSpeed;
	id = iid;
	readImage();
}
Bullet::~Bullet()
{
	if (id == 4)
	{
		delete[] Blackimgs;
		delete[] Coverimgs;
	}
	else
	{
		delete img1;
		delete img2;
	}
}
void Bullet::Move()
{
	x += speed * cos;
	y += speed * sin;
}
void Bullet::MoveTo(Object* a)
{
	if (fabs(acos(cos) - acos(startCos)) < maxAngle)
	{
		cos = (a->x - x) / sqrt(pow(a->x - x, 2) + pow(a->y - y, 2));
		sin = (a->y - y) / sqrt(pow(a->x - x, 2) + pow(a->y - y, 2));
	}
	x += speed * cos - a->speed * a->cos;
	y += speed * sin - a->speed * a->sin;
}
void Bullet::readImage()
{
	if (id == 4)
	{
		Blackimgs = new IMAGE[9];
		Coverimgs = new IMAGE[9];
		for (int i = 0; i < 8; i++)
		{
			string file1 = "子弹黑底彩图5-" + to_string(i + 1) + ".png";
			string file2 = "子弹遮罩图5-" + to_string(i + 1) + ".png";
			if (&Blackimgs[i] != NULL && &Coverimgs[i] != NULL)
			{
				loadimage(&Blackimgs[i], file1.c_str(), 0, 0, false);
				loadimage(&Coverimgs[i], file2.c_str(), 0, 0, false);
			}

		}
	}
	else
	{
		img1 = new IMAGE;
		img2 = new IMAGE;
		string filepath1 = "子弹遮罩图" + to_string(id + 1) + ".png";//图片名-1为朝左 -2为朝右
		string filepath2 = "子弹黑底彩图" + to_string(id + 1) + ".png";//图片名-1为朝左 -2为朝右
		loadimage(img1, filepath1.c_str(), 0, 0, false);
		loadimage(img2, filepath2.c_str(), 0, 0, false);
	}
}

void Bullet::drawBullet()
{
	if (id == 4)
	{
		if (sin == -1 && cos == 0)//w
		{
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Coverimgs[0], SRCAND);//绘制子弹贴图
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Blackimgs[0], SRCPAINT);
		}
		else if (sin < 0 && cos > 0)//wd
		{
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Coverimgs[1], SRCAND);//绘制子弹贴图
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Blackimgs[1], SRCPAINT);
		}
		else if (sin == 0 && cos == 1)//d
		{
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Coverimgs[2], SRCAND);//绘制子弹贴图
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Blackimgs[2], SRCPAINT);
		}
		else if (sin > 0 && cos > 0)//sd
		{
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Coverimgs[3], SRCAND);//绘制子弹贴图
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Blackimgs[3], SRCPAINT);
		}
		else if (sin == 1 && cos == 0)//s
		{
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Coverimgs[4], SRCAND);//绘制子弹贴图
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Blackimgs[4], SRCPAINT);
		}
		else if (sin > 0 && cos < 0)//sa
		{
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Coverimgs[5], SRCAND);//绘制子弹贴图
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Blackimgs[5], SRCPAINT);
		}
		else if (sin == 0 && cos == -1)//a
		{
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Coverimgs[6], SRCAND);//绘制子弹贴图
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Blackimgs[6], SRCPAINT);
		}
		else if (sin < 0 && cos < 0)//wa
		{
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Coverimgs[7], SRCAND);//绘制子弹贴图
			putimage(x - bulletXZ[id], y - bulletXZ[id], &Blackimgs[7], SRCPAINT);
		}
	}
	else
	{
		putimage(x - bulletXZ[id], y - bulletXZ[id], img1, SRCAND);//绘制子弹贴图
		putimage(x - bulletXZ[id], y - bulletXZ[id], img2, SRCPAINT);
	}
}