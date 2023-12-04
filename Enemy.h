#pragma once
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<math.h>
#include"Player.h"
#include"Map.h"
#define EnemyNum 7//敌人数量
double v[EnemyNum] = { 4,2,2,1 }, h[EnemyNum] = { 100,100,500,2000 }, s[EnemyNum] = { 30,30,35,40 }, scd[EnemyNum] = { 0,1.5,2,3 }, xz[EnemyNum] = { 30,30,50,50 }, xzWid[EnemyNum] = { 0,0,0,20 };//分别表示不同敌人的速度，血量，大小，射击cd，贴图宽度，贴图高度，贴图修正值，贴图横坐标修正值
class Enemy :public Object
{
public:
	//Enemy();
	~Enemy();
	Enemy(int enemyID, int k);//k为难度系数
	void MoveTo(Object* player, Map* map);//移动

	void EnemyShot(vector<Bullet*>* bullet);
	int id;//敌人id（用来区分不同类型的敌人）0 近战小兵  1 重装枪手  2智能枪手（发射跟踪子弹） 3大肉怪（初级boss）
	void beatBack();//击退
	int distance;//距离玩家视野的距离
	clock_t shotRecorder;//远程攻击计时器
	clock_t penetrateRecorder;//击穿计时器
	clock_t deadRecorder;//死亡特效播放计时器
	double shotCd;
	int startSpeed;//初始速度
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
	static IMAGE* BlackImages;//黑底彩图
	static IMAGE* CoverImages;//遮罩图
	static IMAGE* HitImages;//受击图
	static IMAGE* DeadImageBlack;//死亡特效
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
	isDead = false;//用来记录是否出死亡特效
	//id = rand() % 2;
	switch (rand() % 4)//0,1,2,3分别表示上下左右
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
	//避免贴脸杀
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
	if (!beHit)//如果敌人没被击退（击退有硬直无法发射子弹）
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
	loadimage(DeadImageBlack, "死亡特效黑底彩图.png", 0, 0, false);
	loadimage(DeadImageCover, "死亡特效遮罩图.png", 0, 0, false);

	BlackImages = new IMAGE[5];
	CoverImages = new IMAGE[5];
	HitImages = new IMAGE[5];
	/*for (int i = 0; i <= 1; i++)
	{
		string filepath1 = "敌人黑底彩图" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//图片名-1为朝左 -2为朝右
		string filepath2 = "敌人遮罩图" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//图片名-1为朝左 -2为朝右
		string filepath3 = "敌人受击图" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//图片名-1为朝左 -2为朝右
		loadimage(&BlackImages[i], filepath1.c_str(), 0, 0, false);
		loadimage(&CoverImages[i], filepath2.c_str(), 0, 0, false);
		loadimage(&HitImages[i], filepath3.c_str(), 0, 0, false);
	}*/

	for (int i = 0; i <= 1; i++)
	{
		string filepath1 = "敌人黑底彩图" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//图片名-1为朝左 -2为朝右
		string filepath2 = "敌人遮罩图" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//图片名-1为朝左 -2为朝右
		string filepath3 = "敌人受击图" + to_string(id + 1) + "-" + to_string(i + 1) + ".png";//图片名-1为朝左 -2为朝右
		loadimage(&BlackImages[i], filepath1.c_str(), 0, 0, false);
		loadimage(&CoverImages[i], filepath2.c_str(), 0, 0, false);
		loadimage(&HitImages[i], filepath3.c_str(), 0, 0, false);
	}
}

void Enemy::drawEnemy()
{
	if (!isLive)
		return;
	if (cos > minN)//朝右
	{
		putimage(x - xz[id] - xzWid[id], y - xz[id], &CoverImages[1], SRCAND);//绘制朝右的贴图
		if (beHit)
		{
			putimage(x - xz[id] - xzWid[id], y - xz[id], &HitImages[1], SRCPAINT);//绘制朝右的贴图
		}
		else
		{
			putimage(x - xz[id] - xzWid[id], y - xz[id], &BlackImages[1], SRCPAINT);
		}
	}
	else
	{
		putimage(x - xz[id] - xzWid[id], y - xz[id], &CoverImages[0], SRCAND);//绘制朝左的贴图
		if (beHit)
		{
			putimage(x - xz[id] - xzWid[id], y - xz[id], &HitImages[0], SRCPAINT);//绘制朝右的贴图
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
//计时一秒后结束击穿状态

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
	putimage(x, y, DeadImageCover, SRCAND);//绘制死亡特效
	putimage(x, y, DeadImageBlack, SRCPAINT);
}
/*void Enemy::deleteIMG()
{
	delete(&BlackImages);
	delete(&CoverImages);
}*/