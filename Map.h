#pragma once
#include <iostream>
#include <io.h>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include "Object.h"
#define isKeyPressed(nVirtKey)	(GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0
#define mapImgLen 5631
#define mapImgWid 6144    //��ͼͼƬ������5631*6144
#define mapFile "Map.png"    //��ͼ�ļ���ַ

class Map
{
public:
	int length;             //��ͼ���Ƴ�
	int width;				//��ͼ���ƿ�
	IMAGE mapFoundation;    //��Ŷ����ͼƬ
	int creX = 3000;
	int creY = 3000;			//��ͼ�������Ͻ�����
	int speedX = 0;
	int speedY = 0;
	int circus[4] = { 1,2,3,4 };
	bool shakeStart = false;
	int i = 0;

	//���õ�ͼ�ڻ��ƴ��ڵĴ�С
	Map(int m_len, int m_wid)
	{
		length = m_len;
		width = m_wid;
		if (&mapFoundation != NULL)
		{
			loadimage(&mapFoundation, mapFile, 0, 0, false);
		}
	}

	//���õ�ͼ��������
	void setCreCoo(int crX, int crY)
	{
		creX = crX;
		creY = crY;
	}

	//������ƶ���ͼ
	void createMap(Object* player)
	{
		putimage(0, 0, length, width, &mapFoundation, creX, creY);
		if (isKeyPressed(87))//���̰���w��
		{
			if (creY - player->speed >= 0)   //��ͼ������Զ�߽��ж�
			{
				speedY = player->speed * player->sin;
				creY += speedY;
				putimage(0, 0, length, width, &mapFoundation, creX, creY);
			}
			else
			{
				speedY = 0;
			}
		}
		else if (isKeyPressed(83))//���̰���s��
		{
			if (creY + width < mapImgWid - 10)
			{
				speedY = player->speed * player->sin;
				creY += speedY;
				putimage(0, 0, length, width, &mapFoundation, creX, creY);
			}
			else
			{
				speedY = 0;
			}
		}
		if (isKeyPressed(65))//���̰���a��
		{
			if (creX - player->speed >= 0)
			{
				speedX = player->speed * player->cos;
				creX += speedX;
				putimage(0, 0, length, width, &mapFoundation, creX, creY);
			}
			else
			{
				speedX = 0;
			}
		}
		else if (isKeyPressed(68) && player->cos > 0)//���̰���d��
		{
			if (creX + length < mapImgLen - 10)
			{
				speedX = player->speed * player->cos;
				creX += speedX;
				putimage(0, 0, length, width, &mapFoundation, creX, creY);
			}
			else
			{
				speedX = 0;
			}
		}
	}

	void mapShake(Object* player) {
		if (i < 3) {
			i++;
			shakeStart = true;
		}
		else {
			i -= 3;
			shakeStart = false;
		}
		switch (circus[i]) {
		case 1:
			putimage(0, 0, length, width, &mapFoundation, creX + 10, creY + 10);
			break;
		case 2:
			putimage(0, 0, length, width, &mapFoundation, creX - 10, creY + 10);
			break;
		case 3:
			putimage(0, 0, length, width, &mapFoundation, creX - 10, creY - 10);
			break;
		case 4:
			putimage(0, 0, length, width, &mapFoundation, creX + 10, creY - 10);
			break;
		}
	}
};
