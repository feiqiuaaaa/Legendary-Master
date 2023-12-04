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
#define mapImgWid 6144    //地图图片总像素5631*6144
#define mapFile "Map.png"    //地图文件地址

class Map
{
public:
	int length;             //地图绘制长
	int width;				//地图绘制宽
	IMAGE mapFoundation;    //存放读入的图片
	int creX = 3000;
	int creY = 3000;			//地图绘制左上角坐标
	int speedX = 0;
	int speedY = 0;
	int circus[4] = { 1,2,3,4 };
	bool shakeStart = false;
	int i = 0;

	//设置地图在绘制窗口的大小
	Map(int m_len, int m_wid)
	{
		length = m_len;
		width = m_wid;
		if (&mapFoundation != NULL)
		{
			loadimage(&mapFoundation, mapFile, 0, 0, false);
		}
	}

	//设置地图绘制坐标
	void setCreCoo(int crX, int crY)
	{
		creX = crX;
		creY = crY;
	}

	//创造可移动地图
	void createMap(Object* player)
	{
		putimage(0, 0, length, width, &mapFoundation, creX, creY);
		if (isKeyPressed(87))//键盘按下w键
		{
			if (creY - player->speed >= 0)   //地图绘制最远边界判定
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
		else if (isKeyPressed(83))//键盘按下s键
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
		if (isKeyPressed(65))//键盘按下a键
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
		else if (isKeyPressed(68) && player->cos > 0)//键盘按下d键
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
