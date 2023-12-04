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
Player* player;//���
Enemy* deki;//����
Map* map;//��ͼ
Music* music;//����
vector<Enemy*>enemy;//���˼���
vector<Bullet*>bullet;//�ӵ�����
vector<Drop*>enemydrop, enemydropexperi;// �����Ｏ�ϣ����侭�鼯��
int Time, width, height;
bool BossTime = false;
int k = 1;//�Ѷ�ϵ���������������ɿ���
int tideTime = 0;//���˳���ʱ
int tideKill = 10;//���˳������ɱ
int bossKill = 10;//boos������Ҫ��ɱ
int bossNum = 0;//boss�س��ֵĴ���
bool ifVictory = false;
IMAGE simg1, simg2;
IMAGE fimg1, fimg2;
bool dropShowFlag = false;
IMAGE ExpimgB;
IMAGE ExpimgC;

void menu()  //�������˵�
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
		loadimage(&start1, "start1.png", 200, 80);//����ڵײ�ͼ
		loadimage(&start2, "start2.png", 200, 80);//����׵׺�ͼ
	}
	putimage(300, 400, &start2, SRCAND);// ����׵׺�ͼ
	putimage(300, 400, &start1, SRCPAINT);//����ڵײ�ͼ
	if (&exit1 != NULL && &exit2 != NULL)
	{
		loadimage(&exit1, "exit1.png", 50, 50);
		loadimage(&exit2, "exit2.png", 50, 50);
	}

	putimage(750, 0, &exit2, SRCAND);
	putimage(750, 0, &exit1, SRCPAINT);
	EndBatchDraw();
}

void choose()  //����ѡ���������
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
	settextstyle(50, 0, _T("����"));
	setbkmode(TRANSPARENT);
	outtextxy(100, 500, "ѡ��");
	outtextxy(350, 500, "ѡ��");
	outtextxy(600, 500, "ѡ��");
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


bool CHOOSE()  //ѡ���������
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
	loadimage(&ExpimgB, "����ڵײ�ͼ.png");
	loadimage(&ExpimgC, "����׵׺�ͼ.png");
	music->playIniMusic();
	Time = 0;
	srand((unsigned int)time(NULL));//���
	width = 800;//������
	height = 600;//����߶�
	player = new Player;//�������
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
	initgraph(width, height);//������
	map->createMap(player);
	Weapon* weapon4 = new Weapon("��", player->x, player->y, player->sin, player->cos, 1);//����4
	if (weapon4 != NULL)
		player->addWeapons(weapon4);
}//��ʼ��

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
}//��ͣ

bool isCollide(Object* e, Object* p)
{
	if (pow(e->x - p->x, 2) + pow(e->y - p->y, 2) <= pow(e->size + p->size, 2))
		return true;
	return false;
}//��ײ

bool attack(Player* a, Enemy* b)
{
	//�ж�����Ƿ��ܹ���ս����������,��Բ��Բ��λ�ù�ϵ
	double s = a->sin, c = a->cos;
	double px = a->x, py = a->y, ps = a->mainWeapon->AttackScope;
	double ex = b->x, ey = b->y, es = b->size;

	double ds = sqrt(pow(ex - px, 2) + pow(ey - py, 2));

	if (ds > ps + es)	return false;
	if (c < -minN || a->lastCos < -minN)
	{
		//����
		return ex <= px;
	}
	else if (c > minN || a->lastCos > minN)
	{
		//����
		return ex >= px;
	}
}

void drawPointer()
{
	if (tideTime)
	{
		string s = "�������ˣ�";
		outtextxy(500, 50, s.c_str());
	}
	if (BossTime)
	{
		string s = "���Ҫ���ˣ�";
		outtextxy(500, 100, s.c_str());
	}
}
void draw()
{
	BeginBatchDraw();//��ʼ��ͼ������������⣩
	//����wasd��������ƶ�
	player->PlayerMove(height, width);
	player->changeWeapons();
	player->shiftChangeWeapons();
	player->PlayerSkill(map);
	cleardevice();//��ջ���
	map->createMap(player);
	if (player->isFire)
	{
		player->drawFlash();
	}
	player->drawPlayer();
	if (player->mainWeapon->type == 1)//��ս����
	{
		player->mainWeapon->changeCloseWeaponXY(player->x, player->y, player->sin, player->cos);
		player->checkShowTime();
		if (player->ifShowWeapon)
		{
			player->mainWeapon->drawCloseWeapon();//������
		}
		player->PlayerAttack();
	}
	else//Զ�̹���
	{
		player->mainWeapon->changeLongWeaponXY(player->x, player->y, player->sin, player->cos);
		player->mainWeapon->drawLongWeapon();//������
		player->PlayerGunAttack(&bullet);
	}
	vector<Enemy*>::iterator it;
	vector<Bullet*>::iterator bu;
	for (it = enemy.begin(); it != enemy.end(); it++)
	{
		(*it)->MoveTo(player, map);//�����ƶ������λ��
		player->AidFlash(*it);
		if (((*it)->x + (*it)->size >= 0 && (*it)->x - (*it)->size <= width) && ((*it)->y + (*it)->size >= 0 && (*it)->y - (*it)->size <= height))//�����������Ұ��Χ�ڣ�������
		{
			(*it)->drawEnemy();
		}
	}
	for (bu = bullet.begin(); bu != bullet.end(); bu++)
	{
		if ((*bu)->id == 0 || (*bu)->id == 1 || (*bu)->id == 4)
		{
			(*bu)->Move();//�ӵ��ƶ�
			(*bu)->x -= player->speed * player->cos, (*bu)->y -= player->speed * player->sin;//�ֶ�������ͼƫ�ƣ�û�취��bullet������û�����õ�ͼ
		}
		else
		{
			if ((*bu)->belong == 1)
				(*bu)->MoveTo(player);
		}
		player->AidFlash(*bu);
		(*bu)->drawBullet();
	}
}//��ͼ

void update()
{
	vector<Enemy*>::iterator it;
	vector<Bullet*>::iterator bu;
	for (bu = bullet.begin(); bu != bullet.end();)//����/����Ƿ�ײ���ӵ� �����ӵ�����
	{
		//fillcircle((*bu)->x, (*bu)->y, (*bu)->size);
		if ((*bu)->x + (*bu)->size < 0 || (*bu)->x - (*bu)->size > width
			|| (*bu)->y + (*bu)->size < 0 || (*bu)->y - (*bu)->size > width)//�ӵ����磬ɾ��
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
			bool ifHit = false;//�ӵ��Ƿ����
			if (isCollide(player, *bu) && (*bu)->belong == 1)//���ײ�����˷�����ӵ�
			{
				ifHit = true;//�ӵ�����
				//Bullet* b = *bu;
				player->PlayerBeenAttack((*bu)->damage);
				delete(*bu);
				bu = bullet.erase(bu);//ɾ����ǰԪ�أ�����Ҫʹ����������
				//delete(b);
				//b = NULL;
			}
			if (!ifHit)
			{
				for (it = enemy.begin(); it != enemy.end(); it++)
				{
					if (isCollide(*it, *bu) && (*bu)->belong == 0 && !(*it)->penetrated)//����ײ����ҷ�����ӵ�
					{
						ifHit = true;//�ӵ�����
						//Bullet* b = *bu;

						(*it)->hp -= (*bu)->damage;
						(*it)->beHit = true;//������
						(*it)->speed = -(*bu)->bulletBeat;//�ӵ��Ļ�����ֵ
						if (!(*bu)->penetrate) {
							delete(*bu);
							bu = bullet.erase(bu);//ɾ����ǰԪ�أ�����Ҫʹ����������
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
			if (!ifHit) bu++;//����ӵ�û�л��У���������
		}
	}
	for (it = enemy.begin(); it != enemy.end(); it++) {
		if ((*it)->penetrated == true) {

			(*it)->StopPene(*it);

		}
	}
	for (it = enemy.begin(); it != enemy.end();)//�������˼���
	{
		//fillcircle((*it)->x, (*it)->y, (*it)->size);
		(*it)->beatBack();//�ж��Ƿ�Ϊ����״̬
		if (player->ifAttack && attack(player, *it))
		{
			(*it)->hp -= player->mainWeapon->harm;
			(*it)->beHit = true;//������
			(*it)->speed = -player->mainWeapon->RepulseSpeed;//�����Ļ�����ֵ
		}
		if (player->isFire && player->fashiSkillAttack(*it))
		{
			(*it)->hp -= player->fashiSkillHarm;
			(*it)->beHit = true;//������
		}
		if ((*it)->hp <= 0)//������ƨ
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
					// ������
					// dropexpei->ExperiencePickUp();
					if (dropShowFlag == false)
					{
						string filepath1 = "����ڵײ�ͼ.png", filepath2 = "����׵׺�ͼ.png";
						//loadimage(&ExpimgB, filepath1.c_str(), 12, 12, true);
						//loadimage(&ExpimgC, filepath2.c_str(), 12, 12, true);
						dropShowFlag = true;
					}
					dropexpei->type = -1;
					dropexpei->x = (*it)->x;
					dropexpei->y = (*it)->y;
					enemydropexperi.push_back(dropexpei);
				}
				// ��װ��


				player->kill++;
				//Enemy* p = *it;
				delete(*it);
				it = enemy.erase(it);
				//delete(p);//�ͷ��ڴ�
				//p = NULL;
			}

		}
		else if (isCollide(*it, player))//����ײ�����
		{
			player->PlayerBeenAttack(25);
			it++;
		}
		else//����������
		{
			(*it)->EnemyShot(&bullet);
			it++;
		}
	}
	if (enemy.empty()) //���û������
	{
		BossTime = false;
		if (bossNum == numForVictory) ifVictory = true;//���ͨ�������boss�أ�ʤ��
	}
	for (auto dp = enemydrop.begin(); dp != enemydrop.end(); )	//���������Ｏ��
	{
		player->AidFlash(*dp);
		(*dp)->x -= player->speed * player->cos, (*dp)->y -= player->speed * player->sin;
		(*dp)->drawDrop();
		// ʰȡ
		int d = ((*dp)->x - player->x) * ((*dp)->x - player->x) + ((*dp)->y - player->y) * ((*dp)->y - player->y);
		if (d <= 10000 && isKeyPressed(69))
		{
			player->pickUpDrop((*dp), (*dp)->x, (*dp)->y);
			//Drop* st = *dp;
			delete(*dp);
			dp = enemydrop.erase(dp);
			//delete(st);//�ͷ��ڴ�
			//st = NULL;
		}
		else
		{
			dp++;
		}
	}
	for (auto dp = enemydropexperi.begin(); dp != enemydropexperi.end(); )	//���������Ｏ��
	{
		player->AidFlash(*dp);
		(*dp)->x -= player->speed * player->cos, (*dp)->y -= player->speed * player->sin;
		(*dp)->drawExperience();
		// ʰȡ
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
			//putimage((*dp)->x, (*dp)->y, &ExpimgC, SRCAND);//����ͼ
			//putimage((*dp)->x, (*dp)->y, &ExpimgB, SRCPAINT);//�ڵײ�ͼ
			//delete(st);//�ͷ��ڴ�
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
	if (player->hp <= 0)//�����ƨ
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
		if (tideTime)//���˳���ʱ
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
			tideKill = 10 + 40 * log(k);//��̬�������˳������ɱ
		}
		if (Time % max(1, 50 / k) == 0)//ÿ��һ��ʱ�����ɵ���
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
		settextstyle(20, 0, _T("����"));
		settextcolor(BLACK);
		outtextxy(570, 510, "������");
		IMAGE img1, img2;
		for (int i = 0; i < player->weapons.size(); i++)
		{
			/*string filepath1 = player->weapons[i]->name + "�ڵײ�ͼ1" + ".png";
			string filepath2 = player->weapons[i]->name + "����ͼ1" + ".png";
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
		EndBatchDraw();//������ͼ
		Sleep(20);//����20ms
		if (ifVictory)
		{
			music->closeMusic();
			music->playSuccessMusic();
			putimage(100, 100, &simg2, SRCAND);
			putimage(100, 100, &simg1, SRCPAINT);
			Sleep(5000);
			break;//���Ӯ�˾��˳�
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