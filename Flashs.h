#pragma once
#include<graphics.h>
#include<thread>
#include <chrono>
#define FileNums 2
using namespace std;
using namespace std::chrono;

class Flashs
{
public:
	double drawX, drawY;
	int type = 0;//��Ч���ı� 0Ϊ�� 1Ϊ��,Ĭ�ϳ���
	IMAGE LeftBlackImages[FileNums];
	IMAGE LeftCoverImages[FileNums];
	IMAGE RightBlackImages[FileNums];
	IMAGE RightCoverImages[FileNums];
	void drawFlash(double x, double y, int type);
	void readImage(string name);
};

void Flashs::drawFlash(double x, double y, int type)
{
	if (type == 0)
	{
		drawX = x - LeftBlackImages[0].getwidth();
		drawY = y - LeftBlackImages[0].getheight();
		for (int i = 0; i < 500; i++)
		{
			putimage(drawX, drawY, &LeftCoverImages[0], SRCAND);//����ͼ
			putimage(drawX, drawY, &LeftBlackImages[0], SRCPAINT);//�ڵײ�ͼ
		}
		drawX = x - LeftBlackImages[1].getwidth();
		drawY = y;
		for (int i = 0; i < 500; i++)
		{
			putimage(drawX, drawY, &LeftCoverImages[1], SRCAND);//����ͼ
			putimage(drawX, drawY, &LeftBlackImages[1], SRCPAINT);//�ڵײ�ͼ
		}
	}
	else
	{
		drawX = x;
		drawY = y - RightBlackImages[0].getheight();
		for (int i = 0; i < 500; i++)
		{
			putimage(drawX, drawY, &RightCoverImages[0], SRCAND);//����ͼ
			putimage(drawX, drawY, &RightBlackImages[0], SRCPAINT);//�ڵײ�ͼ
		}
		drawX = x;
		drawY = y;
		for (int i = 0; i < 500; i++)
		{
			putimage(drawX, drawY, &RightCoverImages[1], SRCAND);//����ͼ
			putimage(drawX, drawY, &RightBlackImages[1], SRCPAINT);//�ڵײ�ͼ
		}
	}
}

/*void Flashs::startThread(double x, double y, int type)
{
	this->type = type;
	thread t(&Flashs::drawFlash, this, x, y);
	t.detach();
}*/

//��һ������
void Flashs::readImage(string name)
{
	//���ع�����Ч��ͼ
	/*for (int i = 0; i < FileNums; i++)
	{
		string LBfile = name + "��Ч��ڵײ�ͼ" + to_string(i + 1) + ".png";
		string RBfile = name + "��Ч�Һڵײ�ͼ" + to_string(i + 1) + ".png";
		loadimage(&LeftBlackImages[i], LBfile.c_str(), 0, 0, false);
		loadimage(&RightBlackImages[i], RBfile.c_str(), 0, 0, false);

		string LCfile = name + "��Ч������ͼ" + to_string(i + 1) + ".png";
		string RCfile = name + "��Ч������ͼ" + to_string(i + 1) + ".png";
		loadimage(&LeftCoverImages[i], LCfile.c_str(), 0, 0, false);
		loadimage(&RightCoverImages[i], RCfile.c_str(), 0, 0, false);
	}*/

	string file1 = name + "��Ч��ڵײ�ͼ1" + ".png";
	string file2 = name + "��Ч�Һڵײ�ͼ1" + ".png";
	if (&LeftBlackImages[0] != NULL && &RightBlackImages[0] != NULL)
	{
		loadimage(&LeftBlackImages[0], file1.c_str(), 0, 0, false);
		loadimage(&RightBlackImages[0], file2.c_str(), 0, 0, false);
	}

	file1 = name + "��Ч��ڵײ�ͼ2" + ".png";
	file2 = name + "��Ч�Һڵײ�ͼ2" + ".png";
	if (&LeftBlackImages[1] != NULL && &RightBlackImages[1] != NULL)
	{
		loadimage(&LeftBlackImages[1], file1.c_str(), 0, 0, false);
		loadimage(&RightBlackImages[1], file2.c_str(), 0, 0, false);
	}


	file1 = name + "��Ч������ͼ1" + ".png";
	file2 = name + "��Ч������ͼ1" + ".png";
	if (&LeftCoverImages[0] != NULL && &RightCoverImages[0] != NULL)
	{
		loadimage(&LeftCoverImages[0], file1.c_str(), 0, 0, false);
		loadimage(&RightCoverImages[0], file2.c_str(), 0, 0, false);
	}

	file1 = name + "��Ч������ͼ2" + ".png";
	file2 = name + "��Ч������ͼ2" + ".png";
	if (&LeftCoverImages[1] != NULL && &RightCoverImages[1] != NULL)
	{
		loadimage(&LeftCoverImages[1], file1.c_str(), 0, 0, false);
		loadimage(&RightCoverImages[1], file2.c_str(), 0, 0, false);
	}

}
