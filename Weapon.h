#pragma once
#include<string>
#include<graphics.h>
#include"Flashs.h"
#define CFileNums 2
#define TFileNums 2
#define LFileNums 8
using namespace std;

/*
	近战贴图只有两张，我们人物贴图也就先做两张了
	远程对应8个方向，有8张贴图
	按顺时针方向命名序号
	wa--8	w--1	wd--2
	a --7			d --3
	sa--6   s--5	sd--4
*/

class Weapon
{
public:
	string name;
	double startX, startY;//武器的起始位置
	double GunX, GunY;//定位远程武器枪口位置
	int type;//1 为近战武器，2 为远程武器
	int level;//武器对应等级（星数）
	double sin, cos;
	double harm;//武器的伤害
	double Aspeed;//攻击速度
	double AttackScope;//攻击范围
	double RepulseSpeed;//击退数值
	double tempCos;//存暂时的左右方向，实现上下行走武器方向
	int temp = 7;//绘制远程时加载的图片
	Flashs flashs;

	bool ifEqual(Weapon*);
	//武器贴图
	IMAGE* CBlackImages;//近战武器黑底彩图  0为左，1为右
	IMAGE* CCoverImages;//近战武器遮罩图

	IMAGE* LBlackImages;//远程武器黑底彩图
	IMAGE* LCoverImages;//远程武器遮罩图

	IMAGE* star1Black;
	IMAGE* star1Cover;
	IMAGE* star2Black;
	IMAGE* star2Cover;
	IMAGE* star3Black;
	IMAGE* star3Cover;

	Weapon(string n, double x, double y, double sin, double cos, int level);
	~Weapon();
	void readImage();

	void changeCloseWeaponXY(double x, double y, double sin, double cos);
	void drawCloseWeapon();

	void changeLongWeaponXY(double x, double y, double sin, double cos);
	void drawLongWeapon();

	void showStars(double x, double y);
};


bool Weapon::ifEqual(Weapon* w1)
{
	if (&(w1->name) == &name)
	{
		return true;
	}
	return false;
}

Weapon::Weapon(string n, double x, double y, double sin, double cos, int level)
{
	//加载图片
	CBlackImages = new IMAGE[CFileNums];
	CCoverImages = new IMAGE[CFileNums];
	LBlackImages = new IMAGE[LFileNums];
	LCoverImages = new IMAGE[LFileNums];

	star1Black = new IMAGE;
	star1Cover = new IMAGE;
	star2Black = new IMAGE;
	star2Cover = new IMAGE;
	star3Black = new IMAGE;
	star3Cover = new IMAGE;

	//传入名字进行武器的分类,设置不同武器的属性
	if (n == "剑")
	{
		name = "剑";
		type = 1;
		harm = 100;
		Aspeed = 0.25;
		AttackScope = 70;
		RepulseSpeed = 5;
	}
	if (n == "锤子")
	{
		name = "锤子";
		type = 1;
		harm = 150;
		Aspeed = 0.5;
		AttackScope = 100;
		RepulseSpeed = 10;
	}
	if (n == "斧头")
	{
		name = "斧头";
		type = 1;
		harm = 120;
		Aspeed = 0.4;
		AttackScope = 70;
		RepulseSpeed = 7;
	}
	if (n == "枪")
	{
		name = "枪";
		type = 2;
		Aspeed = 0.5;
		RepulseSpeed = 4;
	}
	if (n == "激光枪")
	{
		name = "激光枪";
		type = 2;
		Aspeed = 0;
		RepulseSpeed = 2;
	}
	this->sin = sin;
	this->cos = cos;
	this->level = level;
	/*
		图片格式：name+序号.png
	*/
	//从文件中加载图片
	readImage();
	if (type == 1)
	{
		changeCloseWeaponXY(x, y, sin, cos);
		drawCloseWeapon();
	}
	else
	{
		changeLongWeaponXY(x, y, sin, cos);
		drawLongWeapon();
	}
}

Weapon::~Weapon()
{
	if (type == 1)
	{
		delete[] CBlackImages;
		delete[] CCoverImages;
	}
	else
	{
		delete[] LBlackImages;
		delete[] LCoverImages;
	}


	delete star1Black;
	delete star1Cover;
	delete star2Black;
	delete star2Cover;
	delete star3Black;
	delete star3Cover;
}

void Weapon::readImage()
{
	if (type == 1)
	{
		//加载武器贴图
		for (int i = 0; i < CFileNums; i++)
		{
			//分别读入黑底彩图和遮罩图
			string filepath1 = name + "黑底彩图" + to_string(i + 1) + ".png";
			string filepath2 = name + "遮罩图" + to_string(i + 1) + ".png";
			loadimage(&CBlackImages[i], filepath1.c_str(), 0, 0, false);
			loadimage(&CCoverImages[i], filepath2.c_str(), 0, 0, false);
		}
		//加载攻击特效
		flashs.readImage(name);
	}
	else
	{
		for (int i = 0; i < LFileNums; i++)
		{
			string filepath1 = name + "黑底彩图" + to_string(i + 1) + ".png";
			string filepath2 = name + "遮罩图" + to_string(i + 1) + ".png";
			loadimage(&LBlackImages[i], filepath1.c_str(), 0, 0, false);
			loadimage(&LCoverImages[i], filepath2.c_str(), 0, 0, false);
		}
	}
	string sfileC1 = "星星-白底黑图-1.png";
	string sfileB1 = "星星-黑底彩图-1.png";
	string sfileC2 = "星星-白底黑图-2.png";
	string sfileB2 = "星星-黑底彩图-2.png";
	string sfileC3 = "星星-白底黑图-3.png";
	string sfileB3 = "星星-黑底彩图-3.png";
	loadimage(star1Black, sfileC1.c_str(), 0, 0, false);
	loadimage(star1Cover, sfileB1.c_str(), 0, 0, false);
	loadimage(star2Black, sfileC2.c_str(), 0, 0, false);
	loadimage(star2Cover, sfileB2.c_str(), 0, 0, false);
	loadimage(star3Black, sfileC3.c_str(), 0, 0, false);
	loadimage(star3Cover, sfileB3.c_str(), 0, 0, false);

}

void Weapon::changeLongWeaponXY(double x, double y, double sin, double cos)
{
	if (sin == -1 && cos == 0)//w
	{
		startX = x - LBlackImages[0].getwidth() / 2;
		startY = y - LBlackImages[0].getheight();
	}
	else if (sin < 0 && cos > 0)//wd
	{
		startX = x;
		startY = y - LBlackImages[1].getheight();
	}
	else if (sin == 0 && cos == 1)//d
	{
		startX = x;
		startY = y - LBlackImages[2].getheight() / 2;
	}
	else if (sin > 0 && cos > 0)//sd
	{
		startX = x;
		startY = y;
	}
	else if (sin == 1 && cos == 0)//s
	{
		startX = x - LBlackImages[4].getwidth() / 2;
		startY = y;
	}
	else if (sin > 0 && cos < 0)//sa
	{
		startX = x - LBlackImages[5].getwidth();
		startY = y;
	}
	else if (sin == 0 && cos == -1)//a
	{
		startX = x - LBlackImages[6].getwidth();
		startY = y - LBlackImages[6].getheight() / 2;
	}
	else if (sin < 0 && cos < 0)//wa
	{
		startX = x - LBlackImages[7].getwidth();
		startY = y - LBlackImages[7].getheight();
	}
	this->sin = sin;
	this->cos = cos;
}

void Weapon::drawLongWeapon()
{
	if (sin == -1 && cos == 0)//w
		temp = 0;
	else if (sin < 0 && cos > 0)//wd
		temp = 1;
	else if (sin == 0 && cos == 1)//d
		temp = 2;
	else if (sin > 0 && cos > 0)//sd
		temp = 3;
	else if (sin == 1 && cos == 0)//s
		temp = 4;
	else if (sin > 0 && cos < 0)//sa
		temp = 5;
	else if (sin == 0 && cos == -1)//a
		temp = 6;
	else if (sin < 0 && cos < 0)//wa
		temp = 7;
	putimage(startX, startY, &LCoverImages[temp], SRCAND);
	putimage(startX, startY, &LBlackImages[temp], SRCPAINT);
}


//bug:如果向上下行走默认武器方向向左
void Weapon::changeCloseWeaponXY(double x, double y, double sin, double cos)
{
	if (cos < 0)//图片1 --> a
	{
		startX = x - CBlackImages[0].getwidth();
		startY = y - (CBlackImages[0].getheight() / 2);
		tempCos = cos;
	}
	else if (cos > 0)//图片2 --> d
	{
		startX = x;
		startY = y - (CBlackImages[1].getheight() / 2);
		tempCos = cos;
	}
	else if (cos == 0)
	{
		if (tempCos < 0)
		{
			startX = x - CBlackImages[0].getwidth();
			startY = y - (CBlackImages[0].getheight() / 2);
		}
		else if (tempCos > 0)
		{
			startX = x;
			startY = y - (CBlackImages[1].getheight() / 2);
		}
	}
	this->sin = sin;
	this->cos = cos;
}

void Weapon::drawCloseWeapon()
{
	if (cos < 0) //往左
	{
		putimage(startX, startY, &CCoverImages[0], SRCAND);//遮罩图
		putimage(startX, startY, &CBlackImages[0], SRCPAINT);//黑底彩图
	}
	else if (cos > 0)//往右
	{
		putimage(startX, startY, &CCoverImages[1], SRCAND);
		putimage(startX, startY, &CBlackImages[1], SRCPAINT);
	}
	else if (cos == 0)
	{
		if (tempCos < 0) {
			putimage(startX, startY, &CCoverImages[0], SRCAND);
			putimage(startX, startY, &CBlackImages[0], SRCPAINT);
		}
		else if (tempCos > 0) {
			putimage(startX, startY, &CCoverImages[1], SRCAND);
			putimage(startX, startY, &CBlackImages[1], SRCPAINT);
		}
	}
}

void Weapon::showStars(double x, double y)
{
	if (level == 1)
	{
		putimage(x, y, star1Cover, SRCAND);
		putimage(x, y, star1Black, SRCPAINT);
	}
	else if (level == 2)
	{
		putimage(x, y, star2Cover, SRCAND);
		putimage(x, y, star2Black, SRCPAINT);
	}
	else if (level == 3)
	{
		putimage(x, y, star3Cover, SRCAND);
		putimage(x, y, star3Black, SRCPAINT);
	}
}


