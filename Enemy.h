#pragma once
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<math.h>
#include"Player.h"
#include"Map.h"
#define EnemyNum 7//��������
double v[EnemyNum] = { 4,2,2,1 }, h[EnemyNum] = { 100,100,500,2000 }, s[EnemyNum] = { 30,30,35,40 }, scd[EnemyNum] = { 0,1.5,2,3 }, xz[EnemyNum] = { 30,30,50,50 }, xzWid[EnemyNum] = { 0,0,0,20 };//�ֱ��ʾ��ͬ���˵��ٶȣ�Ѫ������С�����cd����ͼ��ȣ���ͼ�߶ȣ���ͼ����ֵ����ͼ����������ֵ
class Enemy :public Object
{
public:
	//Enemy();
	~Enemy();
	Enemy(int enemyID, int k);//kΪ�Ѷ�ϵ��
	void MoveTo(Object* player, Map* map);//�ƶ�

	void EnemyShot(vector<Bullet*>* bullet);
	int id;//����id���������ֲ�ͬ���͵ĵ��ˣ�0 ��սС��  1 ��װǹ��  2����ǹ�֣���������ӵ��� 3����֣�����boss��
	void beatBack();//����
	int distance;//���������Ұ�ľ���
	clock_t shotRecorder;//Զ�̹�����ʱ��
	clock_t penetrateRecorder;//������ʱ��
	clock_t deadRecorder;//������Ч���ż�ʱ��
	double shotCd;
	int startSpeed;//��ʼ�ٶ�
	void StopPene(Enemy* e);
	void ifStop(Enemy* e);
	bool penetrated = false;
	static void LoadResource();
	void drawEnemy();
	void drawDeadImage();
	void EnemyDead();
	bool isDead;
	int deadTime = 0;
	//void deleteIMG();
	static IMAGE* BlackImages;//�ڵײ�ͼ
	static IMAGE* CoverImages;//����ͼ
	static IMAGE* HitImages;//�ܻ�ͼ
	static IMAGE* DeadImageBlack;//������Ч
	static IMAGE* DeadImageCover;
};

IMAGE* Enemy::BlackImages = nullptr;
IMAGE* Enemy::CoverImages = nullptr;
IMAGE* Enemy::HitImages = nullptr;
IMAGE* Enemy::DeadImageBlack = nullptr;
IMAGE* Enemy::DeadImageCover = nullptr;

Enemy::Enemy(int enemyID, int k)
{
	id = enemyID;
	hp = h[id] * k;
	startSpeed = speed = v[id];
	size = s[id];
	distance = 30;
	shotCd = scd[id];
	beHit = false;
	isLive = true;
	isDead = false;//������¼�Ƿ��������Ч
	//id = rand() % 2;
	switch (rand() % 4)//0,1,2,3�ֱ��ʾ��������
	{
	case 0:
		x = rand() % 800;
		y = -distance;
		break;
	case 1:
		x = rand() % 800;
		y = distance + 600;
		break;
	case 2:
		x = -distance;
		y = rand() % 600;
		break;
	case 3:
		x = distance + 800;
		y = rand() % 600;
		break;
	}
	//��������ɱ
}
Enemy::~Enemy()
{
	delete[] BlackImages;
	delete[] CoverImages;
	delete[] HitImages;
	delete DeadImageBlack;
	delete DeadImageCover;
}
/*Enemy::Enemy(int enemyID)
{
	Enemy();
	id = enemyID;
}*/
void Enemy::MoveTo(Object* player, Map* map)
{
	if (!beHit || speed >= 0)
	{
		cos = (player->x - x) / sqrt(pow(player->x - x, 2) + pow(player->y - y, 2));
		sin = (player->y - y) / sqrt(pow(player->x - x, 2) + pow(player->y - y, 2));
	}
	if (map->speedY == 0) player->sin = 0;
	if (map->speedX == 0) player->cos = 0;
	x += cos * speed - player->speed * player->cos;
	y += sin * speed - player->speed * player->sin;
}
void Enemy::beatBack()
{
	if (!isLive)
		return;
	if (beHit)
	{
		if (fabs(speed - startSpeed) < minN)
			beHit = false;
		else
			speed += 1;
	}
}

void Enemy::EnemyShot(vector<Bullet*>* bullet)
{
	clock_t now = clock();
	if ((double)(now - shotRecorder) / CLOCKS_PER_SEC < shotCd)
	{
		return;
	}
	if (!beHit)//�������û�����ˣ�������Ӳֱ�޷������ӵ���
	{
		if (id == 1)
		{
			shotRecorder = clock();
			Bullet* b = new Bullet(x + cos * size, y + sin * size, sin, cos, 7, 3, 50, 0, 1, 1);
			if (b == NULL) return;
			b->Move();
			(*bullet).push_back(b);
		}
		else if (id == 2)
		{
			shotRecorder = clock();
			Bullet* b = new Bullet(x + cos * size, y + sin * size, sin, cos, 7, 22, 100, 0, 2, 1);
			if (b == NULL) return;
			b->Move();
			(*bullet).push_back(b);
		}
		else if (id == 3)
		{
			shotRecorder = clock();
			Bullet* b = new Bullet(x + cos * size, y + sin * size, sin, cos, 7, 24, 200, 0, 3, 1);
			if (b == NULL) return;
			b->Move();
			(*bullet).push_back(b);
		}
	}
}
void Enemy::LoadResource()
{
	DeadImageBlack = new IMAGE;
	DeadImageCover = new IMAGE;
	loadimage(DeadImageBlack, "������Ч�ڵײ�ͼ.png", 0, 0, false);
	loadimage(DeadImageCover, "������Ч����ͼ.png", 0, 0, false);

	BlackImages = new IMAGE[5];
	CoverImages = new IMAGE[5];
	HitImages = new IMAGE[5];
	/*for (int i = 0; i <= 1; i++)
	{
		string filepath1 = "���˺ڵײ�ͼ" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//ͼƬ��-1Ϊ���� -2Ϊ����
		string filepath2 = "��������ͼ" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//ͼƬ��-1Ϊ���� -2Ϊ����
		string filepath3 = "�����ܻ�ͼ" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//ͼƬ��-1Ϊ���� -2Ϊ����
		loadimage(&BlackImages[i], filepath1.c_str(), 0, 0, false);
		loadimage(&CoverImages[i], filepath2.c_str(), 0, 0, false);
		loadimage(&HitImages[i], filepath3.c_str(), 0, 0, false);
	}*/

	for (int i = 0; i <= 1; i++)
	{
		string filepath1 = "���˺ڵײ�ͼ" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//ͼƬ��-1Ϊ���� -2Ϊ����
		string filepath2 = "��������ͼ" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//ͼƬ��-1Ϊ���� -2Ϊ����
		string filepath3 = "�����ܻ�ͼ" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//ͼƬ��-1Ϊ���� -2Ϊ����
		loadimage(&BlackImages[i], filepath1.c_str(), 0, 0, false);
		loadimage(&CoverImages[i], filepath2.c_str(), 0, 0, false);
		loadimage(&HitImages[i], filepath3.c_str(), 0, 0, false);
	}
}

void Enemy::drawEnemy()
{
	if (!isLive)
		return;
	if (cos > minN)//����
	{
		putimage(x - xz[id] - xzWid[id], y - xz[id], &CoverImages[1], SRCAND);//���Ƴ��ҵ���ͼ
		if (beHit)
		{
			putimage(x - xz[id] - xzWid[id], y - xz[id], &HitImages[1], SRCPAINT);//���Ƴ��ҵ���ͼ
		}
		else
		{
			putimage(x - xz[id] - xzWid[id], y - xz[id], &BlackImages[1], SRCPAINT);
		}
	}
	else
	{
		putimage(x - xz[id] - xzWid[id], y - xz[id], &CoverImages[0], SRCAND);//���Ƴ������ͼ
		if (beHit)
		{
			putimage(x - xz[id] - xzWid[id], y - xz[id], &HitImages[0], SRCPAINT);//���Ƴ��ҵ���ͼ
		}
		else
		{
			putimage(x - xz[id] - xzWid[id], y - xz[id], &BlackImages[0], SRCPAINT);
		}
	}
}

void Enemy::StopPene(Enemy* e)
{
	if (e->penetrated)
	{
		ifStop(e);
	}
}
//��ʱһ����������״̬

void Enemy::ifStop(Enemy* e)
{     
	clock_t now = clock();
	if ((double)(now - penetrateRecorder) / CLOCKS_PER_SEC < 1)
		e->penetrated = true;
	else
	{
		e->penetrated = false;
	}
}

void Enemy::EnemyDead()
{
	isLive = false;
	speed = 0;
	if (deadTime < 10)
	{
		drawDeadImage();
		deadTime++;             
	}
	else
	{
		isDead = true;
	}
}
void Enemy::drawDeadImage()
{
	y -= 5;
	putimage(x, y, DeadImageCover, SRCAND);//����������Ч
	putimage(x, y, DeadImageBlack, SRCPAINT);
}
/*void Enemy::deleteIMG()
{
	delete(&BlackImages);
	delete(&CoverImages);
}*/