#pragma once
#include<iostream>
#include<cstdlib>
#include <ctime>
#include <string>
#include <graphics.h>
#include <chrono>
#include <random>

#include "Bullet.h"
#include "Object.h"
#include "Weapon.h"
#include "Map.h"

#define isKeyPressed(nVirtKey)	(GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0
// #define random(a,b) (rand()%(b-a+1)+a)

using namespace std;

class Drop :public Object
{
public:
	int type;
	string weaponName;
	static IMAGE* DropBlackImages;//µôÂäÎïºÚµ×²ÊÍ¼
	static IMAGE* DropCoverImages;//µôÂäÎïÕÚÕÖÍ¼
	// µôÂäÎï×ö³É¶ÔÏó,typeÎªµôÂäÎïµÄÀàÐÍ
	static IMAGE* ExperienceBlack;
	static IMAGE* ExperienceCover;

	Drop();
	~Drop();
	void trigger();
	void drawDrop();
	void ExperiencePickUp();
	void drawExperience();
	static void LoadResource();
};

IMAGE* Drop::DropBlackImages = nullptr;
IMAGE* Drop::DropCoverImages = nullptr;
IMAGE* Drop::ExperienceBlack = nullptr;
IMAGE* Drop::ExperienceCover = nullptr;

void Drop::LoadResource() {
	static string str1[12] = {
		"½£ºÚµ×²ÊÍ¼1.png", "´¸×ÓºÚµ×²ÊÍ¼1.png", "Ç¹ºÚµ×²ÊÍ¼8.png", "ÑªÆ¿ºÚ²Ê.png", "ÒÆËÙ¼Ó³ÉºÚ²Ê.png", "¹¥ËÙ¼Ó³ÉºÚ²Ê.png",
		"ÉËº¦¼Ó³ÉºÚ²Ê.png", "¸«Í·ºÚµ×²ÊÍ¼1.png", "¼¤¹âÇ¹ºÚµ×²ÊÍ¼8.png"
	};

	static string str2[12] = {
		"½£ÕÚÕÖÍ¼1.png", "´¸×ÓÕÚÕÖÍ¼1.png", "Ç¹ÕÚÕÖÍ¼8.png", "ÑªÆ¿°×ÕÚÕÖ.png", "ÒÆËÙ¼Ó³É°×ÕÚÕÖ.png",
		"¹¥ËÙ¼Ó³É°×ÕÚÕÖ.png", "ÉËº¦¼Ó³É°×ÕÚÕÖ.png", "¸«Í·ÕÚÕÖÍ¼1.png", "¼¤¹âÇ¹ÕÚÕÖÍ¼8.png"
	};

	DropBlackImages = new IMAGE[12];
	DropCoverImages = new IMAGE[12];

	for (int i = 0; i < 9; ++i) {
		loadimage(&DropBlackImages[i], str1[i].c_str());
		loadimage(&DropCoverImages[i], str2[i].c_str());
	}

	ExperienceBlack = new IMAGE;
	ExperienceCover = new IMAGE;
	loadimage(ExperienceBlack, "¾­ÑéºÚµ×²ÊÍ¼.png", 12, 12, true);
	loadimage(ExperienceCover, "¾­Ñé°×µ×ºÚÍ¼.png", 12, 12, true);
}

Drop::Drop()
{
	type = -1;
}

Drop::~Drop() {}

void Drop::trigger()
{
	type = rand() % 9;
	if (type == 0) {
		weaponName = "½£";
	}
	else if (type == 1) {
		weaponName = "´¸×Ó";
	}
	else if (type == 2) {
		weaponName = "Ç¹";
	}
	else if (type == 7) {
		weaponName = "¸«Í·";
	}
	else if (type == 8) {
		weaponName = "¼¤¹âÇ¹";
	}
}

void Drop::drawDrop() {
	putimage(x, y, &DropCoverImages[type], SRCAND);//ÕÚÕÖÍ¼
	putimage(x, y, &DropBlackImages[type], SRCPAINT);//ºÚµ×²ÊÍ¼
}

void Drop::drawExperience()
{
	putimage(x, y, ExperienceCover, SRCAND);//ÕÚÕÖÍ¼
	putimage(x, y, ExperienceBlack, SRCPAINT);//ºÚµ×²ÊÍ¼
}