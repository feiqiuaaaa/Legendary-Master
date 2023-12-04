#include "Enemy.h"
#include "Map.h"
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#include"Music.h"
//#pragma pack(2)
#pragma comment(lib,"winmm.lib")
#define random(a,b) (rand()%(b-a+1)+a)
#define numForVictory 2
using namespace std;
Player* player;//玩家
Enemy* deki;//敌人
Map* map;//地图
Music* music;//音乐
vector<Enemy*>enemy;//敌人集合
vector<Bullet*>bullet;//子弹集合
vector<Drop*>enemydrop, enemydropexperi;// 掉落物集合，掉落经验集合
int Time, width, height;
bool BossTime = false;
int k = 1;//难度系数，决定敌人生成快慢
int tideTime = 0;//敌人潮计时
int tideKill = 10;//敌人潮所需击杀
int bossKill = 10;//boos出现需要击杀
int bossNum = 0;//boss关出现的次数
bool ifVictory = false;
IMAGE simg1, simg2;
IMAGE fimg1, fimg2;
bool dropShowFlag = false;
IMAGE ExpimgB;
IMAGE ExpimgC;

void menu()  //加载主菜单
{
	BeginBatchDraw();
	cleardevice();
	IMAGE background;
	if (&background != NULL)
	{
		loadimage(&background, "background.png", 800, 600);
	}

	putimage(0, 0, &background);
	IMAGE start1, start2, exit1, exit2;
	if (&start1 != NULL && &start2 != NULL)
	{
		loadimage(&start1, "start1.png", 200, 80);//插入黑底彩图
		loadimage(&start2, "start2.png", 200, 80);//插入白底黑图
	}
	putimage(300, 400, &start2, SRCAND);// 插入白底黑图
	putimage(300, 400, &start1, SRCPAINT);//插入黑底彩图
	if (&exit1 != NULL && &exit2 != NULL)
	{
		loadimage(&exit1, "exit1.png", 50, 50);
		loadimage(&exit2, "exit2.png", 50, 50);
	}

	putimage(750, 0, &exit2, SRCAND);
	putimage(750, 0, &exit1, SRCPAINT);
	EndBatchDraw();
}

void choose()  //加载选择人物界面
{
	BeginBatchDraw();
	cleardevice();
	IMAGE back, man;
	if (&back != NULL)
	{
		loadimage(&back, "back.png", 800, 600);
	}

	putimage(0, 0, &back);
	IMAGE man1, man2;
	if (&man1 != NULL)
	{
		loadimage(&man1, "dashi.jpg", 200, 300);
	}

	putimage(50, 150, &man1);
	if (&man2 != NULL)
	{
		loadimage(&man2, "lzj.jpg", 200, 300);
	}

	putimage(300, 150, &man2);
	if (&man != NULL)
	{
		loadimage(&man, "man.png", 200, 300);
	}

	putimage(550, 150, &man);
	setfillcolor(GREEN);
	fillrectangle(75, 500, 225, 550);
	fillrectangle(325, 500, 475, 550);
	fillrectangle(575, 500, 725, 550);
	settextstyle(50, 0, _T("黑体"));
	setbkmode(TRANSPARENT);
	outtextxy(100, 500, "选他");
	outtextxy(350, 500, "选他");
	outtextxy(600, 500, "选他");
	IMAGE exit1, exit2;
	if (&exit1 != NULL && &exit2 != NULL)
	{
		loadimage(&exit1, "exit1.png", 50, 50);
		loadimage(&exit2, "exit2.png", 50, 50);
	}

	putimage(750, 0, &exit2, SRCAND);
	putimage(750, 0, &exit1, SRCPAINT);
	EndBatchDraw();
}


bool CHOOSE()  //选择人物操作
{
	ExMessage m;
	while (1)
	{
		m = getmessage(EM_MOUSE);
		if (m.x >= 75 && m.x <= 225 && m.y >= 500 && m.y <= 550)
		{
			if (m.message == WM_LBUTTONDOWN)
			{
				player->ChooseProfession(1);
				player->readImages();
				return true;
			}
		}
		else if (m.x >= 325 && m.x <= 475 && m.y >= 500 && m.y <= 550)
		{
			if (m.message == WM_LBUTTONDOWN)
			{
				player->ChooseProfession(2);
				player->readImages();
				return true;
			}
		}
		else if (m.x >= 575 && m.x <= 725 && m.y >= 500 && m.y <= 550)
		{
			if (m.message == WM_LBUTTONDOWN)
			{

			}
		}
		else if (m.x >= 750 && m.x <= 800 && m.y >= 0 && m.y <= 50)
		{
			if (m.message == WM_LBUTTONDOWN)
			{
				exit(0);
			}
		}
	}
}


void initialization()
{

	loadimage(&simg1, "success1.png", 600, 400);
	loadimage(&simg2, "success2.png", 600, 400);
	loadimage(&fimg1, "fail1.png", 600, 400);
	loadimage(&fimg2, "fail2.png", 600, 400);
	loadimage(&ExpimgB, "经验黑底彩图.png");
	loadimage(&ExpimgC, "经验白底黑图.png");
	music->playIniMusic();
	Time = 0;
	srand((unsigned int)time(NULL));//随机
	width = 800;//画面宽度
	height = 600;//画面高度
	player = new Player;//创建玩家
	map = new Map(width, height);
	initgraph(800, 600);
	menu();
	ExMessage m;
	while (1)
	{
		m = getmessage(EM_MOUSE);
		if (m.x >= 300 && m.x <= 500 && m.y >= 400 && m.y <= 480)
		{
			if (m.message == WM_LBUTTONDOWN)
			{
				choose();
				if (CHOOSE())
				{
					break;
				}
			}
		}
		else if (m.x >= 750 && m.x <= 800 && m.y >= 0 && m.y <= 50)
		{
			if (m.message == WM_LBUTTONDOWN)
			{
				exit(0);
			}
		}
	}
	initgraph(width, height);//画窗口
	map->createMap(player);
	Weapon* weapon4 = new Weapon("剑", player->x, player->y, player->sin, player->cos, 1);//武器4
	if (weapon4 != NULL)
		player->addWeapons(weapon4);
}//初始化

void ifPause()
{
	if (isKeyPressed(27))
	{
		IMAGE img1, img2;
		if (&img1 != NULL && &img2 != NULL)
		{
			loadimage(&img1, "pause1.png", 400, 300);
			loadimage(&img2, "pause2.png", 400, 300);
		}

		putimage(200, 150, &img2, SRCAND);
		putimage(200, 150, &img1, SRCPAINT);
		system("pause");
		for (int i = 3; i >= 1; i--)
		{
			char s[10];
			sprintf_s(s, "%d", i);
			outtextxy(600 - i * 50, 100, s);
			Sleep(1000);
		}
	}
}//暂停

bool isCollide(Object* e, Object* p)
{
	if (pow(e->x - p->x, 2) + pow(e->y - p->y, 2) <= pow(e->size + p->size, 2))
		return true;
	return false;
}//碰撞

bool attack(Player* a, Enemy* b)
{
	//判定玩家是否能够近战攻击到敌人,半圆和圆的位置关系
	double s = a->sin, c = a->cos;
	double px = a->x, py = a->y, ps = a->mainWeapon->AttackScope;
	double ex = b->x, ey = b->y, es = b->size;

	double ds = sqrt(pow(ex - px, 2) + pow(ey - py, 2));

	if (ds > ps + es)	return false;
	if (c < -minN || a->lastCos < -minN)
	{
		//朝左
		return ex <= px;
	}
	else if (c > minN || a->lastCos > minN)
	{
		//朝右
		return ex >= px;
	}
}

void drawPointer()
{
	if (tideTime)
	{
		string s = "他们来了！";
		outtextxy(500, 50, s.c_str());
	}
	if (BossTime)
	{
		string s = "大的要来了！";
		outtextxy(500, 100, s.c_str());
	}
}
void draw()
{
	BeginBatchDraw();//开始作图（解决闪屏问题）
	//按下wasd控制玩家移动
	player->PlayerMove(height, width);
	player->changeWeapons();
	player->shiftChangeWeapons();
	player->PlayerSkill(map);
	cleardevice();//清空画面
	map->createMap(player);
	if (player->isFire)
	{
		player->drawFlash();
	}
	player->drawPlayer();
	if (player->mainWeapon->type == 1)//近战攻击
	{
		player->mainWeapon->changeCloseWeaponXY(player->x, player->y, player->sin, player->cos);
		player->checkShowTime();
		if (player->ifShowWeapon)
		{
			player->mainWeapon->drawCloseWeapon();//画武器
		}
		player->PlayerAttack();
	}
	else//远程攻击
	{
		player->mainWeapon->changeLongWeaponXY(player->x, player->y, player->sin, player->cos);
		player->mainWeapon->drawLongWeapon();//画武器
		player->PlayerGunAttack(&bullet);
	}
	vector<Enemy*>::iterator it;
	vector<Bullet*>::iterator bu;
	for (it = enemy.begin(); it != enemy.end(); it++)
	{
		(*it)->MoveTo(player, map);//敌人移动至玩家位置
		player->AidFlash(*it);
		if (((*it)->x + (*it)->size >= 0 && (*it)->x - (*it)->size <= width) && ((*it)->y + (*it)->size >= 0 && (*it)->y - (*it)->size <= height))//敌人在玩家视野范围内，画出来
		{
			(*it)->drawEnemy();
		}
	}
	for (bu = bullet.begin(); bu != bullet.end(); bu++)
	{
		if ((*bu)->id == 0 || (*bu)->id == 1 || (*bu)->id == 4)
		{
			(*bu)->Move();//子弹移动
			(*bu)->x -= player->speed * player->cos, (*bu)->y -= player->speed * player->sin;//手动修正地图偏移，没办法，bullet类里面没法调用地图
		}
		else
		{
			if ((*bu)->belong == 1)
				(*bu)->MoveTo(player);
		}
		player->AidFlash(*bu);
		(*bu)->drawBullet();
	}
}//绘图

void update()
{
	vector<Enemy*>::iterator it;
	vector<Bullet*>::iterator bu;
	for (bu = bullet.begin(); bu != bullet.end();)//敌人/玩家是否撞到子弹 遍历子弹集合
	{
		//fillcircle((*bu)->x, (*bu)->y, (*bu)->size);
		if ((*bu)->x + (*bu)->size < 0 || (*bu)->x - (*bu)->size > width
			|| (*bu)->y + (*bu)->size < 0 || (*bu)->y - (*bu)->size > width)//子弹出界，删除
		{
			/*Bullet* b = *bu;
			bu = bullet.erase(bu);
			delete(b);
			b = NULL;*/
			delete(*bu);
			bu = bullet.erase(bu);
		}
		else
		{
			bool ifHit = false;//子弹是否击中
			if (isCollide(player, *bu) && (*bu)->belong == 1)//玩家撞到敌人发射的子弹
			{
				ifHit = true;//子弹击中
				//Bullet* b = *bu;
				player->PlayerBeenAttack((*bu)->damage);
				delete(*bu);
				bu = bullet.erase(bu);//删除当前元素，不需要使迭代器增加
				//delete(b);
				//b = NULL;
			}
			if (!ifHit)
			{
				for (it = enemy.begin(); it != enemy.end(); it++)
				{
					if (isCollide(*it, *bu) && (*bu)->belong == 0 && !(*it)->penetrated)//敌人撞到玩家发射的子弹
					{
						ifHit = true;//子弹击中
						//Bullet* b = *bu;

						(*it)->hp -= (*bu)->damage;
						(*it)->beHit = true;//被击中
						(*it)->speed = -(*bu)->bulletBeat;//子弹的击退数值
						if (!(*bu)->penetrate) {
							delete(*bu);
							bu = bullet.erase(bu);//删除当前元素，不需要使迭代器增加
							//delete(b);
							//b = NULL;
						}
						else if ((*bu)->penetrate) {
							(*it)->penetrated = true;
							(*it)->penetrateRecorder = clock();
						}
						break;
					}
				}
			}
			if (!ifHit) bu++;//如果子弹没有击中，继续迭代
		}
	}
	for (it = enemy.begin(); it != enemy.end(); it++) {
		if ((*it)->penetrated == true) {

			(*it)->StopPene(*it);

		}
	}
	for (it = enemy.begin(); it != enemy.end();)//遍历敌人集合
	{
		//fillcircle((*it)->x, (*it)->y, (*it)->size);
		(*it)->beatBack();//判断是否为击退状态
		if (player->ifAttack && attack(player, *it))
		{
			(*it)->hp -= player->mainWeapon->harm;
			(*it)->beHit = true;//被击中
			(*it)->speed = -player->mainWeapon->RepulseSpeed;//武器的击退数值
		}
		if (player->isFire && player->fashiSkillAttack(*it))
		{
			(*it)->hp -= player->fashiSkillHarm;
			(*it)->beHit = true;//被击中
		}
		if ((*it)->hp <= 0)//敌人嗝屁
		{
			if (!(*it)->isDead)
			{
				(*it)->EnemyDead();
				it++;
			}
			else
			{
				Drop* dropthing = new Drop();
				Drop* dropexpei = new Drop();
				if (dropthing != NULL && dropexpei != NULL)
				{
					if (random(1, 100) < 30)
					{
						dropthing->trigger();
						dropthing->x = (*it)->x;
						dropthing->y = (*it)->y;
						enemydrop.push_back(dropthing);
					}
					// 爆经验
					// dropexpei->ExperiencePickUp();
					if (dropShowFlag == false)
					{
						string filepath1 = "经验黑底彩图.png", filepath2 = "经验白底黑图.png";
						//loadimage(&ExpimgB, filepath1.c_str(), 12, 12, true);
						//loadimage(&ExpimgC, filepath2.c_str(), 12, 12, true);
						dropShowFlag = true;
					}
					dropexpei->type = -1;
					dropexpei->x = (*it)->x;
					dropexpei->y = (*it)->y;
					enemydropexperi.push_back(dropexpei);
				}
				// 爆装备


				player->kill++;
				//Enemy* p = *it;
				delete(*it);
				it = enemy.erase(it);
				//delete(p);//释放内存
				//p = NULL;
			}

		}
		else if (isCollide(*it, player))//敌人撞到玩家
		{
			player->PlayerBeenAttack(25);
			it++;
		}
		else//敌人完好无恙
		{
			(*it)->EnemyShot(&bullet);
			it++;
		}
	}
	if (enemy.empty()) //如果没敌人了
	{
		BossTime = false;
		if (bossNum == numForVictory) ifVictory = true;//如果通过第五次boss关，胜利
	}
	for (auto dp = enemydrop.begin(); dp != enemydrop.end(); )	//遍历掉落物集合
	{
		player->AidFlash(*dp);
		(*dp)->x -= player->speed * player->cos, (*dp)->y -= player->speed * player->sin;
		(*dp)->drawDrop();
		// 拾取
		int d = ((*dp)->x - player->x) * ((*dp)->x - player->x) + ((*dp)->y - player->y) * ((*dp)->y - player->y);
		if (d <= 10000 && isKeyPressed(69))
		{
			player->pickUpDrop((*dp), (*dp)->x, (*dp)->y);
			//Drop* st = *dp;
			delete(*dp);
			dp = enemydrop.erase(dp);
			//delete(st);//释放内存
			//st = NULL;
		}
		else
		{
			dp++;
		}
	}
	for (auto dp = enemydropexperi.begin(); dp != enemydropexperi.end(); )	//遍历掉落物集合
	{
		player->AidFlash(*dp);
		(*dp)->x -= player->speed * player->cos, (*dp)->y -= player->speed * player->sin;
		(*dp)->drawExperience();
		// 拾取
		int d = ((*dp)->x - player->x) * ((*dp)->x - player->x) + ((*dp)->y - player->y) * ((*dp)->y - player->y);
		if (d <= 10000)
		{
			player->pickUpDrop((*dp), (*dp)->x, (*dp)->y);
			player->experiencenum += 5;
			//Drop* st = *dp;
			delete(*dp);
			dp = enemydropexperi.erase(dp);
			player->levelup();
			// player->drawEXP();
			//putimage((*dp)->x, (*dp)->y, &ExpimgC, SRCAND);//遮罩图
			//putimage((*dp)->x, (*dp)->y, &ExpimgB, SRCPAINT);//黑底彩图
			//delete(st);//释放内存
			//st = NULL;
		}
		else
		{
			//player->levelup();
			dp++;
		}
	}
	player->isFlash = false;
	//player->isFire = false;
	vector<Bullet*>(bullet).swap(bullet);
	vector<Enemy*>(enemy).swap(enemy);
	vector<Drop*>(enemydrop).swap(enemydrop);
	vector<Drop*>(enemydropexperi).swap(enemydropexperi);
	if (player->hp <= 0)//玩家嗝屁
	{
		music->closeMusic();
		music->playFailMusic();
		putimage(100, 100, &fimg2, SRCAND);
		putimage(100, 100, &fimg1, SRCPAINT);
		Time = -1;
	}
}

void createEnemy()
{
	if (player->kill >= bossKill)
	{
		if (!BossTime)
		{
			bossNum++;
			for (int i = 1; i <= bossNum; i++)
			{
				deki = new Enemy(3, k);
				if (deki != NULL)
					enemy.push_back(deki);
			}
			bossKill *= 2;
		}
		BossTime = true;
	}
	if (!BossTime)
	{
		if (tideTime)//敌人潮计时
		{
			tideTime--;
		}
		else
		{
			k = player->kill / tideKill + 1;
		}
		if ((player->kill % tideKill) == 0 && player->kill != 0 && tideTime == 0)
		{
			tideTime = 200;
			k = k + k / 3;
			tideKill = 10 + 40 * log(k);//动态调整敌人潮所需击杀
		}
		if (Time % max(1, 50 / k) == 0)//每隔一段时间生成敌人
		{
			deki = new Enemy(0, k);
			if (deki != NULL)
				enemy.push_back(deki);
		}
		if (Time > 200 && Time % max(1, (200 / k)) == 0)
		{
			deki = new Enemy(1, k);
			if (deki != NULL)
				enemy.push_back(deki);
		}
		if (Time > 1000 && Time % max(1, (500 / k)) == 0)
		{
			deki = new Enemy(2, k);
			if (deki != NULL)
				enemy.push_back(deki);
		}
	}
}


void gaming()
{
	char ifQuit;
	music->closeMusic();
	music->playFightMusic();
	while (++Time)
	{
		createEnemy();
		ifPause();
		draw();
		player->ifUnBeatAble();
		update();
		setfillcolor(WHITE);
		solidrectangle(450, 510, 800, 600);
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, _T("黑体"));
		settextcolor(BLACK);
		outtextxy(570, 510, "武器栏");
		IMAGE img1, img2;
		for (int i = 0; i < player->weapons.size(); i++)
		{
			/*string filepath1 = player->weapons[i]->name + "黑底彩图1" + ".png";
			string filepath2 = player->weapons[i]->name + "遮罩图1" + ".png";
			if (&img1 != NULL && &img2 != NULL)
			{
				loadimage(&img1, filepath1.c_str(), 70, 70);
				loadimage(&img2, filepath2.c_str(), 70, 70);
			}*/
			if (player->weapons[i]->type == 1)
			{
				putimage(450 + 70 * i, 530, &player->weapons[i]->CBlackImages[0], SRCAND);
				putimage(450 + 70 * i, 530, &player->weapons[i]->CCoverImages[0], SRCPAINT);
			}
			else if (player->weapons[i]->type == 2)
			{
				putimage(450 + 70 * i, 530, &player->weapons[i]->LBlackImages[0], SRCAND);
				putimage(450 + 70 * i, 530, &player->weapons[i]->LCoverImages[0], SRCPAINT);
			}

		}
		for (int i = 0; i < player->weapons.size(); i++)
		{
			player->weapons[i]->showStars(460 + 70 * i, 580);
		}
		player->drawEXP();
		player->drawHP();
		player->showCD();
		drawPointer();
		EndBatchDraw();//结束作图
		Sleep(20);//休眠20ms
		if (ifVictory)
		{
			music->closeMusic();
			music->playSuccessMusic();
			putimage(100, 100, &simg2, SRCAND);
			putimage(100, 100, &simg1, SRCPAINT);
			Sleep(5000);
			break;//如果赢了就退出
		}
		Sleep(4);
	}

}

int main()
{
	Drop::LoadResource();
	Enemy::LoadResource();
	srand((int)time(0));
	initialization();
	gaming();
	//cleardevice();
	getchar();
}