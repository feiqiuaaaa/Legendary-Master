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
	static IMAGE* DropBlackImages;//������ڵײ�ͼ
	static IMAGE* DropCoverImages;//����������ͼ
	// ���������ɶ���,typeΪ�����������
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
		"���ڵײ�ͼ1.png", "���Ӻڵײ�ͼ1.png", "ǹ�ڵײ�ͼ8.png", "Ѫƿ�ڲ�.png", "���ټӳɺڲ�.png", "���ټӳɺڲ�.png",
		"�˺��ӳɺڲ�.png", "��ͷ�ڵײ�ͼ1.png", "����ǹ�ڵײ�ͼ8.png"
	};

	static string str2[12] = {
		"������ͼ1.png", "��������ͼ1.png", "ǹ����ͼ8.png", "Ѫƿ������.png", "���ټӳɰ�����.png",
		"���ټӳɰ�����.png", "�˺��ӳɰ�����.png", "��ͷ����ͼ1.png", "����ǹ����ͼ8.png"
	};

	DropBlackImages = new IMAGE[12];
	DropCoverImages = new IMAGE[12];

	for (int i = 0; i < 9; ++i) {
		loadimage(&DropBlackImages[i], str1[i].c_str());
		loadimage(&DropCoverImages[i], str2[i].c_str());
	}

	ExperienceBlack = new IMAGE;
	ExperienceCover = new IMAGE;
	loadimage(ExperienceBlack, "����ڵײ�ͼ.png", 12, 12, true);
	loadimage(ExperienceCover, "����׵׺�ͼ.png", 12, 12, true);
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
		weaponName = "��";
	}
	else if (type == 1) {
		weaponName = "����";
	}
	else if (type == 2) {
		weaponName = "ǹ";
	}
	else if (type == 7) {
		weaponName = "��ͷ";
	}
	else if (type == 8) {
		weaponName = "����ǹ";
	}
}

void Drop::drawDrop() {
	putimage(x, y, &DropCoverImages[type], SRCAND);//����ͼ
	putimage(x, y, &DropBlackImages[type], SRCPAINT);//�ڵײ�ͼ
}

void Drop::drawExperience()
{
	putimage(x, y, ExperienceCover, SRCAND);//����ͼ
	putimage(x, y, ExperienceBlack, SRCPAINT);//�ڵײ�ͼ
}