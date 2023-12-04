#pragma once
#include<string>
#include<graphics.h>
#include"Flashs.h"
#define CFileNums 2
#define TFileNums 2
#define LFileNums 8
using namespace std;

/*
	��ս��ͼֻ�����ţ�����������ͼҲ������������
	Զ�̶�Ӧ8��������8����ͼ
	��˳ʱ�뷽���������
	wa--8	w--1	wd--2
	a --7			d --3
	sa--6   s--5	sd--4
*/

class Weapon
{
public:
	string name;
	double startX, startY;//��������ʼλ��
	double GunX, GunY;//��λԶ������ǹ��λ��
	int type;//1 Ϊ��ս������2 ΪԶ������
	int level;//������Ӧ�ȼ���������
	double sin, cos;
	double harm;//�������˺�
	double Aspeed;//�����ٶ�
	double AttackScope;//������Χ
	double RepulseSpeed;//������ֵ
	double tempCos;//����ʱ�����ҷ���ʵ������������������
	int temp = 7;//����Զ��ʱ���ص�ͼƬ
	Flashs flashs;

	bool ifEqual(Weapon*);
	//������ͼ
	IMAGE* CBlackImages;//��ս�����ڵײ�ͼ  0Ϊ��1Ϊ��
	IMAGE* CCoverImages;//��ս��������ͼ

	IMAGE* LBlackImages;//Զ�������ڵײ�ͼ
	IMAGE* LCoverImages;//Զ����������ͼ

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
	//����ͼƬ
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

	//�������ֽ��������ķ���,���ò�ͬ����������
	if (n == "��")
	{
		name = "��";
		type = 1;
		harm = 100;
		Aspeed = 0.25;
		AttackScope = 70;
		RepulseSpeed = 5;
	}
	if (n == "����")
	{
		name = "����";
		type = 1;
		harm = 150;
		Aspeed = 0.5;
		AttackScope = 100;
		RepulseSpeed = 10;
	}
	if (n == "��ͷ")
	{
		name = "��ͷ";
		type = 1;
		harm = 120;
		Aspeed = 0.4;
		AttackScope = 70;
		RepulseSpeed = 7;
	}
	if (n == "ǹ")
	{
		name = "ǹ";
		type = 2;
		Aspeed = 0.5;
		RepulseSpeed = 4;
	}
	if (n == "����ǹ")
	{
		name = "����ǹ";
		type = 2;
		Aspeed = 0;
		RepulseSpeed = 2;
	}
	this->sin = sin;
	this->cos = cos;
	this->level = level;
	/*
		ͼƬ��ʽ��name+���.png
	*/
	//���ļ��м���ͼƬ
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
		//����������ͼ
		for (int i = 0; i < CFileNums; i++)
		{
			//�ֱ����ڵײ�ͼ������ͼ
			string filepath1 = name + "�ڵײ�ͼ" + to_string(i + 1) + ".png";
			string filepath2 = name + "����ͼ" + to_string(i + 1) + ".png";
			loadimage(&CBlackImages[i], filepath1.c_str(), 0, 0, false);
			loadimage(&CCoverImages[i], filepath2.c_str(), 0, 0, false);
		}
		//���ع�����Ч
		flashs.readImage(name);
	}
	else
	{
		for (int i = 0; i < LFileNums; i++)
		{
			string filepath1 = name + "�ڵײ�ͼ" + to_string(i + 1) + ".png";
			string filepath2 = name + "����ͼ" + to_string(i + 1) + ".png";
			loadimage(&LBlackImages[i], filepath1.c_str(), 0, 0, false);
			loadimage(&LCoverImages[i], filepath2.c_str(), 0, 0, false);
		}
	}
	string sfileC1 = "����-�׵׺�ͼ-1.png";
	string sfileB1 = "����-�ڵײ�ͼ-1.png";
	string sfileC2 = "����-�׵׺�ͼ-2.png";
	string sfileB2 = "����-�ڵײ�ͼ-2.png";
	string sfileC3 = "����-�׵׺�ͼ-3.png";
	string sfileB3 = "����-�ڵײ�ͼ-3.png";
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


//bug:�������������Ĭ��������������
void Weapon::changeCloseWeaponXY(double x, double y, double sin, double cos)
{
	if (cos < 0)//ͼƬ1 --> a
	{
		startX = x - CBlackImages[0].getwidth();
		startY = y - (CBlackImages[0].getheight() / 2);
		tempCos = cos;
	}
	else if (cos > 0)//ͼƬ2 --> d
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
	if (cos < 0) //����
	{
		putimage(startX, startY, &CCoverImages[0], SRCAND);//����ͼ
		putimage(startX, startY, &CBlackImages[0], SRCPAINT);//�ڵײ�ͼ
	}
	else if (cos > 0)//����
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


