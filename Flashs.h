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
	int type = 0;//ÌØĞ§³¯ÄÄ±ß 0Îª×ó 1ÎªÓÒ,Ä¬ÈÏ³¯×ó
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
			putimage(drawX, drawY, &LeftCoverImages[0], SRCAND);//ÕÚÕÖÍ¼
			putimage(drawX, drawY, &LeftBlackImages[0], SRCPAINT);//ºÚµ×²ÊÍ¼
		}
		drawX = x - LeftBlackImages[1].getwidth();
		drawY = y;
		for (int i = 0; i < 500; i++)
		{
			putimage(drawX, drawY, &LeftCoverImages[1], SRCAND);//ÕÚÕÖÍ¼
			putimage(drawX, drawY, &LeftBlackImages[1], SRCPAINT);//ºÚµ×²ÊÍ¼
		}
	}
	else
	{
		drawX = x;
		drawY = y - RightBlackImages[0].getheight();
		for (int i = 0; i < 500; i++)
		{
			putimage(drawX, drawY, &RightCoverImages[0], SRCAND);//ÕÚÕÖÍ¼
			putimage(drawX, drawY, &RightBlackImages[0], SRCPAINT);//ºÚµ×²ÊÍ¼
		}
		drawX = x;
		drawY = y;
		for (int i = 0; i < 500; i++)
		{
			putimage(drawX, drawY, &RightCoverImages[1], SRCAND);//ÕÚÕÖÍ¼
			putimage(drawX, drawY, &RightBlackImages[1], SRCPAINT);//ºÚµ×²ÊÍ¼
		}
	}
}

/*void Flashs::startThread(double x, double y, int type)
{
	this->type = type;
	thread t(&Flashs::drawFlash, this, x, y);
	t.detach();
}*/

//¸ÄÒ»ÏÂÃüÃû
void Flashs::readImage(string name)
{
	//¼ÓÔØ¹¥»÷ÌØĞ§ÌùÍ¼
	/*for (int i = 0; i < FileNums; i++)
	{
		string LBfile = name + "ÌØĞ§×óºÚµ×²ÊÍ¼" + to_string(i + 1) + ".png";
		string RBfile = name + "ÌØĞ§ÓÒºÚµ×²ÊÍ¼" + to_string(i + 1) + ".png";
		loadimage(&LeftBlackImages[i], LBfile.c_str(), 0, 0, false);
		loadimage(&RightBlackImages[i], RBfile.c_str(), 0, 0, false);

		string LCfile = name + "ÌØĞ§×óÕÚÕÖÍ¼" + to_string(i + 1) + ".png";
		string RCfile = name + "ÌØĞ§ÓÒÕÚÕÖÍ¼" + to_string(i + 1) + ".png";
		loadimage(&LeftCoverImages[i], LCfile.c_str(), 0, 0, false);
		loadimage(&RightCoverImages[i], RCfile.c_str(), 0, 0, false);
	}*/

	string file1 = name + "ÌØĞ§×óºÚµ×²ÊÍ¼1" + ".png";
	string file2 = name + "ÌØĞ§ÓÒºÚµ×²ÊÍ¼1" + ".png";
	if (&LeftBlackImages[0] != NULL && &RightBlackImages[0] != NULL)
	{
		loadimage(&LeftBlackImages[0], file1.c_str(), 0, 0, false);
		loadimage(&RightBlackImages[0], file2.c_str(), 0, 0, false);
	}

	file1 = name + "ÌØĞ§×óºÚµ×²ÊÍ¼2" + ".png";
	file2 = name + "ÌØĞ§ÓÒºÚµ×²ÊÍ¼2" + ".png";
	if (&LeftBlackImages[1] != NULL && &RightBlackImages[1] != NULL)
	{
		loadimage(&LeftBlackImages[1], file1.c_str(), 0, 0, false);
		loadimage(&RightBlackImages[1], file2.c_str(), 0, 0, false);
	}


	file1 = name + "ÌØĞ§×óÕÚÕÖÍ¼1" + ".png";
	file2 = name + "ÌØĞ§ÓÒÕÚÕÖÍ¼1" + ".png";
	if (&LeftCoverImages[0] != NULL && &RightCoverImages[0] != NULL)
	{
		loadimage(&LeftCoverImages[0], file1.c_str(), 0, 0, false);
		loadimage(&RightCoverImages[0], file2.c_str(), 0, 0, false);
	}

	file1 = name + "ÌØĞ§×óÕÚÕÖÍ¼2" + ".png";
	file2 = name + "ÌØĞ§ÓÒÕÚÕÖÍ¼2" + ".png";
	if (&LeftCoverImages[1] != NULL && &RightCoverImages[1] != NULL)
	{
		loadimage(&LeftCoverImages[1], file1.c_str(), 0, 0, false);
		loadimage(&RightCoverImages[1], file2.c_str(), 0, 0, false);
	}

}
