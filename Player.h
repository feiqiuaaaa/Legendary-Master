#pragma once
#include<graphics.h>
#include<conio.h>
#include<vector>
#include<time.h>
#include"Weapon.h"
#include"Bullet.h"
#include"Object.h"
#include"Drop.h"
#include"Map.h"
#define isKeyPressed(nVirtKey) (GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0
#define ImageNum 6
#define hpLong 150

using namespace std;

class Player :public Object
{
public:
	double lastSin = 0;
	double lastCos = 0;//��¼��һ�ΰ����ķ���
	char direction = 'a';//��¼�泯�ķ���
	int profession = 0;//�񶷴�ʦ->1	��ʦ->2
	int bagSize = 5;//������Ʒ����С
	double skillCd = 5;//����cd
	double unBeatAbleTime = 1;//�ܻ��޵�ʱ��
	bool unBeatAble;//����Ƿ����޵�״̬
	bool ifAttack;//�ж�����Ƿ񹥻�
	bool ifShowWeapon = true;//�ж��Ƿ���ʾ����
	int startHP;
	double defaltCos = -1;//���Ĭ�ϳ���ʲô�����ɵ�ʱ�򣩿�ʼĬ�ϳ��󣬺��ڸ�����һ����������
	int kill = 0;//��ɱ��
	Drop* drops;//������
	int level = 1, experiencenum, levelupneed = 25 * level;

	time_t SkillTimeRecorder = 0;//���ܼ�ʱ��
	clock_t AtimeRecorder = 0;//��ͨ������ʱ��
	clock_t ShiftTimeRecorder;//shift�л�������ʱ��
	clock_t unBeatAbleRecorder;//�ܻ�����޵�ʱ���ʱ��
	clock_t quitWeaponRecoder;//�������ļ�ʱ��
	clock_t coverWeaponRecoder;//���������ļ�ʱ��

	vector<Weapon*> weapons;//��������
	Weapon* mainWeapon;//������

	//��ɫ���Գ�ʼ��
	Player();
	void ChooseProfession(int p);

	//��ɫ״̬��ʾ
	void PlayerShowWeapons();
	void showCD();

	//�ƶ��͹�������
	void PlayerMove(int height, int width);
	void PlayerAttack();
	void PlayerGunAttack(vector<Bullet*>* bullet);
	void PlayerSkill(Map* map);
	void ifUnBeatAble();
	void PlayerBeenAttack(double harm);

	//������Ʒ������
	bool addWeapons(Weapon* weapon);
	bool isInside(Weapon* weapon);
	Weapon* getWeapons(int index);
	void changeWeapons();
	void shiftChangeWeapons();
	void WeaponLevelUp(Weapon* weapon);

	//�����Ǿ������ְҵ�ļ��ܺ�����
	//1.�񶷴�ʦ
	bool isFlash = false;//�ж�����Ƿ�������״̬
	bool flashSuccess = true;//�ж������Ƿ�ײǽ
	double flashLenth = 100;
	void skillOfDashi(Map* map);
	void AidFlash(Object* o);

	//2.��ʦ
	bool isFire = false;//�ж�����Ƿ����ͷŷ�Χ����
	double fashiScope = 150;
	double fashiSkillHarm = 150;
	IMAGE* image1;
	IMAGE* image2;
	int showRecorder = 0;
	void skillOfFashi();
	bool fashiSkillAttack(Object* enemy);
	void drawFlash();

	//�����﹦��
	void pickUpDrop(Drop* drops, int x, int y);//������

	//�����ͼ
	int ImageWidth, ImageHeight;
	IMAGE* LeftBlackImages;//����ڵײ�ͼ��ͼ
	IMAGE* LeftCoverImages;//��������ͼ��ͼ

	IMAGE* RightBlackImages;//���Һڵײ�ͼ��ͼ
	IMAGE* RightCoverImages;//��������ͼ��ͼ

	IMAGE* standRightBlack;//����վ���ڵײ�ͼ
	IMAGE* standRightCover;//����վ������ͼ
	IMAGE* standLeftBlack;
	IMAGE* standLeftCover;

	int LdrawIndex = 0;//��������ͼƬ���±�
	int RedrawL = 0;//�ظ����Ƽ���
	int RdrawIndex = 0;//����
	int RedrawR = 0;
	void drawPlayer();
	void readImages();
	void drawRightRun(int drawX, int drawY);
	void drawLeftRun(int drawX, int drawY);

	//������Ч
	void drawWeaponFlash();
	void drawHP();
	void checkShowTime();

	// ��������
	void levelup();
	void drawEXP();
};

Player::Player() {
	x = 400;
	y = 300;
	lastSin = 0;
	lastCos = 0;

	speed = 10;
	isLive = true;
	ifAttack = false;
	unBeatAble = false;
	beHit = false;

	LeftBlackImages = new IMAGE[ImageNum];
	LeftCoverImages = new IMAGE[ImageNum];
	RightBlackImages = new IMAGE[ImageNum];
	RightCoverImages = new IMAGE[ImageNum];
	standRightBlack = new IMAGE;
	standRightCover = new IMAGE;
	standLeftBlack = new IMAGE;
	standLeftCover = new IMAGE;
	image1 = new IMAGE;
	image2 = new IMAGE;
}

void Player::ChooseProfession(int p)
{
	if (p == 1)
	{
		profession = 1;
		startHP = hp = 3000;
		size = 30;
	}
	else if (p == 2)
	{
		profession = 2;
		startHP = hp = 2000;
		size = 30;
	}
}

void Player::PlayerShowWeapons()
{
	for (int i = 0; i < weapons.size(); i++)
	{
		outtextxy(200 + i * 50, 50, weapons[i]->name.c_str());
	}
}

void Player::PlayerMove(int height, int width)
{
	double move;
	sin = 0, cos = 0;
	if (isKeyPressed(87))//���̰���w�� ע��������ֻ�����д��ĸ��Ӧ��ascii�룬���Լ���Сд
	{
		move = -speed;
		if (y + move >= size && y + move <= height - size)
		{
			//y += move;
			sin = -1;
		}
	}//����������꣬��ȻҪ������
	else if (isKeyPressed(83))//���̰���s��
	{
		move = speed;
		if (y + move >= size && y + move <= height - size) {
			//y += move;
			sin = 1;
		}
	}
	if (isKeyPressed(65))//���̰���a��
	{
		move = -speed;
		if (x + move >= size && x + move <= width - size) {
			//x += move;
			defaltCos = cos = -1;
		}
	}
	else if (isKeyPressed(68))//���̰���d��
	{
		move = speed;
		if (x + move >= size && x + move <= width - size) {
			//x += move;
			defaltCos = cos = 1;
		}
	}
	if (fabs(sin) > minN && fabs(cos) > minN)//б���ƶ�
	{
		sin /= sqrt(2);
		cos /= sqrt(2);
	}
	if (!(sin == 0 && cos == 0))
	{
		lastSin = sin;
		lastCos = cos;
	}
}

void Player::PlayerAttack()
{
	clock_t now = clock();
	if ((double)(now - AtimeRecorder) / CLOCKS_PER_SEC < mainWeapon->Aspeed)
	{
		ifAttack = false;
		return;
	}
	//����j��������ͨ����
	if (isKeyPressed(74))
	{
		AtimeRecorder = clock();
		coverWeaponRecoder = clock();
		ifShowWeapon = false;
		//����ͨ������Ч
		//solidcircle(x, y, mainWeapon->AttackScope);
		drawWeaponFlash();
		ifAttack = true;
	}
}

void Player::PlayerGunAttack(vector<Bullet*>* bullet)
{
	//����j�����ӵ�
	if (isKeyPressed(74))
	{
		Bullet* bu;
		clock_t now = clock();
		if ((double)(now - AtimeRecorder) / CLOCKS_PER_SEC < mainWeapon->Aspeed)
		{
			return;
		}
		AtimeRecorder = clock();
		if (fabs(sin) < minN && fabs(cos) < minN)//���ûָ��
		{
			if (mainWeapon->name == "����ǹ")
				bu = new Bullet(x + lastCos * size, y + lastSin * size, lastSin, lastCos, 40, 30, 25, mainWeapon->RepulseSpeed, 4, 0);
			else
				bu = new Bullet(x + lastCos * size, y + lastSin * size, lastSin, lastCos, 15, 10, 50, mainWeapon->RepulseSpeed, 0, 0);//ʹ��Ĭ��ָ��
		}
		else
		{
			if (mainWeapon->name == "����ǹ")
				bu = new Bullet(x + cos * size, y + sin * size, sin, cos, 40, 30, 25, mainWeapon->RepulseSpeed, 4, 0);
			else
				bu = new Bullet(x + cos * size, y + sin * size, sin, cos, 15, 10, 50, mainWeapon->RepulseSpeed, 0, 0);
		}
		bu->Move();
		(*bullet).push_back(bu);
	}
	if (isKeyPressed(80) || penetrationConfirmed) {//��������||���߼�Ӧ����&&����������Ʒ�������
		Bullet* bu;
		clock_t now = clock();
		if ((double)(now - AtimeRecorder) / CLOCKS_PER_SEC < mainWeapon->Aspeed)
		{
			return;
		}
		AtimeRecorder = clock();
		if (fabs(sin) < minN && fabs(cos) < minN)//���ûָ��
		{
			bu = new Bullet(x + defaltCos * size, y, 0, defaltCos, 15, 10, 50, mainWeapon->RepulseSpeed, 0, 0);//ʹ��Ĭ��ָ��
		}
		else
		{
			bu = new Bullet(x + cos * size, y + sin * size, sin, cos, 15, 10, 50, mainWeapon->RepulseSpeed, 0, 0);
		}
		bu->speed *= 2;
		bu->damage *= 4;//���Ը���
		bu->penetrate = true;
		bu->Move();
		(*bullet).push_back(bu);
		penetrationConfirmed = false;//���˻��������Ƕ�����Ƶģ��������Ƿ���ԭ�еģ�������ͼ����
	}
}


void Player::PlayerSkill(Map* map)
{
	//�м���cd
	if (difftime(time(NULL), SkillTimeRecorder) < skillCd)
	{
		//��ʾ������cd
		/*char c = (int)(skillCd - difftime(time(NULL), SkillTimeRecorder)) + '0';
		outtextxy(500, 300, c);*/
		return;
	}
	//���̰���k�����ͷż���
	if (isKeyPressed(75)) {

		//�ѵ�ǰʱ���¼����ʱ����
		SkillTimeRecorder = time(NULL);
		if (profession == 1)//�񶷴�ʦ�ļ���
		{
			skillOfDashi(map);
		}
		if (profession == 2)//��ʦ�ļ���
		{
			skillOfFashi();
		}
		//...
	}
}

void Player::ifUnBeatAble()
{
	clock_t now = clock();
	if ((double)(now - unBeatAbleRecorder) / CLOCKS_PER_SEC < unBeatAbleTime)
		unBeatAble = true;
	else
		unBeatAble = false;
}

void Player::PlayerBeenAttack(double harm)
{
	if (!unBeatAble)
	{
		hp -= harm;
		beHit = true;
		unBeatAble = true;
		unBeatAbleRecorder = clock();
	}
}

void Player::skillOfDashi(Map* map)
{
	isFlash = true;
	if (map->creY - flashLenth >= 0 && map->creY + map->width + flashLenth <= mapImgWid)   //��ͼ������Զ�߽��ж�
	{
		map->creY += flashLenth * lastSin;
	}
	if (map->creX - flashLenth >= 0 && map->creX + map->length + flashLenth <= mapImgLen)
	{
		if (lastSin == 0 && lastCos == 0)
		{
			map->creX += flashLenth * defaltCos;
		}
		else
		{
			map->creX += flashLenth * lastCos;
		}
	}
	flashSuccess = map->creY - flashLenth >= 0 && map->creY + map->width + flashLenth <= mapImgWid
		&& map->creX - flashLenth >= 0 && map->creX + map->length + flashLenth <= mapImgLen;
}

void Player::AidFlash(Object* o)
{
	if (isFlash && flashSuccess)
	{
		o->x -= flashLenth * lastCos;
		o->y -= flashLenth * lastSin;
	}
}

//��ʦ����
void Player::skillOfFashi()
{
	isFire = true;
	showRecorder = 0;
}

bool Player::fashiSkillAttack(Object* enemy)
{
	double distance = sqrt(pow(enemy->x - this->x, 2) + pow(enemy->y - this->y, 2));
	double length = fashiScope + enemy->size;
	if (distance > length)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Player::drawFlash()
{
	if (showRecorder <= 25)
	{
		//�ӷ�Χ������ͼ
		putimage(x - (image2->getwidth() / 2), y - (image2->getheight() / 2), image2, SRCAND);//����ͼ
		putimage(x - (image2->getwidth() / 2), y - (image2->getheight() / 2), image1, SRCPAINT);//�ڵײ�ͼ
		showRecorder++;
	}
	else
	{
		isFire = false;
	}
}

//������Ʒ������
bool Player::addWeapons(Weapon* weapon)
{
	if (!isInside(weapon))
	{
		if (weapons.size() == 0) {
			this->mainWeapon = weapon;
		}
		if (weapons.size() <= bagSize)
		{
			this->weapons.push_back(weapon);
			return true;
		}
	}
	else
	{
		WeaponLevelUp(weapon);
		return false;
	}
}

bool Player::isInside(Weapon* weapon)
{
	//ѭ������������Ʒ�����ж�Ҫ��ӵ������Ƿ��Ѿ���ӹ�
	for (auto iter = weapons.begin(); iter != weapons.end(); iter++)
	{
		if ((*iter)->name == weapon->name)
		{
			return true;
		}
	}
	return false;
}

Weapon* Player::getWeapons(int index)
{
	return weapons.at(index - 1);
}

void Player::changeWeapons()//12345��������shift�����л�
{
	if (isKeyPressed(49) && weapons.size() >= 1)//������ϵ�1
	{
		this->mainWeapon = weapons.at(0);
	}

	if (isKeyPressed(50) && weapons.size() >= 2)//������ϵ�2
	{
		this->mainWeapon = weapons.at(1);
	}

	if (isKeyPressed(51) && weapons.size() >= 3)//������ϵ�3
	{
		this->mainWeapon = weapons.at(2);
	}

	if (isKeyPressed(52) && weapons.size() >= 4)//������ϵ�4
	{
		this->mainWeapon = weapons.at(3);
	}

	if (isKeyPressed(53) && weapons.size() == 5)//������ϵ�5
	{
		this->mainWeapon = weapons.at(4);
	}

}

void Player::shiftChangeWeapons()
{
	clock_t now = clock();
	if ((double)(now - ShiftTimeRecorder) / CLOCKS_PER_SEC < 0.25)
	{
		return;
	}
	//��shift�����л�����
	if (isKeyPressed(VK_SHIFT))
	{
		ShiftTimeRecorder = clock();
		Weapon* temp = NULL;
		//ѭ������������Ʒ�����ҵ�����������ͬ��ַ������,��ȡ��ǰ����������һ������
		for (auto iter = weapons.begin(); iter != weapons.end(); iter++)
		{
			if (*iter == mainWeapon)
			{
				if (iter + 1 != weapons.end())
				{
					iter++;
					temp = *iter;
					iter--;
				}
				else
				{  //��������vector���һ������,����Ϊ��Ʒ����һ������
					temp = weapons[0];
				}
			}
		}
		mainWeapon = temp;
	}

}

/*void Player::quitWeapon()
{
	if (weapons.size() == 0 || weapons.size() == 1)
	{
		return;
	}
	clock_t now = clock();
	if ((double)(now - quitWeaponRecoder) / CLOCKS_PER_SEC < 1)
	{
		return;
	}
	if (isKeyPressed(81))	//��q������
	{
		//ѭ������������Ʒ�����ҵ�����������ͬ��ַ������������ɾ��
		/*for (auto iter = weapons.begin() + 1; iter != weapons.end();)
		{
			iter = weapons.erase(iter);
		}
		quitWeaponRecoder = clock();
		if (weapons.size() > 1)
		{
			weapons.pop_back();
		}
	}
}*/

void Player::WeaponLevelUp(Weapon* weapon)
{
	for (auto iter = weapons.begin(); iter != weapons.end(); iter++)
	{
		if ((*iter)->name == weapon->name)
		{
			if ((*iter)->level < 3)
			{
				(*iter)->level++;
				(*iter)->harm += 100;
				(*iter)->AttackScope += 30;
			}
			else
			{
				(*iter)->level = 3;
			}
		}
	}
}



void Player::pickUpDrop(Drop* drops, int x, int y)
{
	if (drops->type == 0)
	{
		// ��
		Weapon* wp = new Weapon("��", x, y, -1, 0, 1);
		if (!addWeapons(wp))
		{
			delete(wp);
		}
	}
	else if (drops->type == 1)
	{
		// �޴�
		Weapon* wp = new Weapon("����", x, y, -1, 0, 1);
		if (!addWeapons(wp))
		{
			delete(wp);
		}
	}
	else if (drops->type == 2)
	{
		// ǹ
		Weapon* wp = new Weapon("ǹ", x, y, -1, 0, 1);
		if (!addWeapons(wp))
		{
			delete(wp);
		}
	}
	else if (drops->type == 3)
	{
		// Ѫƿ
		hp += 500;
		if (hp > 3000)	hp = 3000;
	}
	else if (drops->type == 4)
	{
		// ����
		if (speed <= 20)
		{
			speed += 0.5;
		}
	}
	else if (drops->type == 5)
	{
		// ����
		mainWeapon->Aspeed /= 1.08;
	}
	else if (drops->type == 6)
	{
		// �����˺�
		mainWeapon->harm *= 1.1;
	}
	else if (drops->type == 7)
	{
		// ��ͷ
		Weapon* wp = new Weapon("��ͷ", x, y, -1, 0, 1);
		addWeapons(wp);
	}
	else if (drops->type == 8)
	{
		// ����ǹ
		Weapon* wp = new Weapon("����ǹ", x, y, -1, 0, 1);
		addWeapons(wp);
	}
}
void Player::readImages()
{
	int width;
	int height;
	if (profession == 1)
	{
		width = 100;
		height = 74;
	}
	if (profession == 2)
	{
		width = 0;
		height = 0;
	}
	for (int i = 0; i < ImageNum; i++)
	{
		string lfilepath1 = to_string(profession) + " l" + to_string(i + 1) + " b.png";//����ڵײ�ͼ
		string lfilepath2 = to_string(profession) + " l" + to_string(i + 1) + " w.png";//��������ͼ

		loadimage(&LeftBlackImages[i], lfilepath1.c_str(), width, height, true);
		loadimage(&LeftCoverImages[i], lfilepath2.c_str(), width, height, true);

		string rfilepath1 = to_string(profession) + " r" + to_string(i + 1) + " b.png";//����ڵײ�ͼ
		string rfilepath2 = to_string(profession) + " r" + to_string(i + 1) + " w.png";//��������ͼ

		loadimage(&RightBlackImages[i], rfilepath1.c_str(), width, height, true);
		loadimage(&RightCoverImages[i], rfilepath2.c_str(), width, height, true);

	}
	string slfilepath1 = to_string(profession) + " ls b.png";
	string slfilepath2 = to_string(profession) + " ls w.png";
	string srfilepath1 = to_string(profession) + " rs b.png";
	string srfilepath2 = to_string(profession) + " rs w.png";

	loadimage(standLeftBlack, slfilepath1.c_str(), width, height, true);
	loadimage(standLeftCover, slfilepath2.c_str(), width, height, true);
	loadimage(standRightBlack, srfilepath1.c_str(), width, height, true);
	loadimage(standRightCover, srfilepath2.c_str(), width, height, true);

	string file1 = "2 ���� �ڵ�.png";
	string file2 = "2 ���� �׵�.png";

	loadimage(image1, file1.c_str(), 150, 150, true);
	loadimage(image2, file2.c_str(), 150, 150, true);
}

void Player::drawPlayer()
{
	double drawX = x - (LeftBlackImages[0].getwidth() / 2);
	double drawY = y - (LeftBlackImages[0].getheight() / 2);
	if (cos > 0)//����ʱ���Ŷ�ͼ
	{
		drawRightRun(drawX, drawY);
	}
	else if (cos < 0)
	{
		drawLeftRun(drawX, drawY);
	}
	else if (cos == 0)
	{
		if (sin == 0)
		{
			if (defaltCos <= 0)//֮ǰ����Ĭ��Ϊ��
			{
				putimage(drawX, drawY, standLeftCover, SRCAND);//����ͼ
				putimage(drawX, drawY, standLeftBlack, SRCPAINT);//�ڵײ�ͼ
			}
			else
			{
				putimage(drawX, drawY, standRightCover, SRCAND);//����ͼ
				putimage(drawX, drawY, standRightBlack, SRCPAINT);//�ڵײ�ͼ
			}
		}
		else
		{
			if (defaltCos > 0)
			{
				drawRightRun(drawX, drawY);
			}
			else if (defaltCos < 0)
			{
				drawLeftRun(drawX, drawY);
			}
		}
	}
}

void Player::drawRightRun(int drawX, int drawY)
{
	LdrawIndex = 0;
	putimage(drawX, drawY, &RightCoverImages[RdrawIndex], SRCAND);//����ͼ
	putimage(drawX, drawY, &RightBlackImages[RdrawIndex], SRCPAINT);//�ڵײ�ͼ
	RedrawR++;
	if (RedrawR > 3)
		RedrawR = 0;
	else
		return;
	if (RdrawIndex == 5)
	{
		RdrawIndex = 0;
	}
	else
	{
		RdrawIndex++;
	}
}

void Player::drawLeftRun(int drawX, int drawY)
{
	RdrawIndex = 0;
	putimage(drawX, drawY, &LeftCoverImages[LdrawIndex], SRCAND);//����ͼ
	putimage(drawX, drawY, &LeftBlackImages[LdrawIndex], SRCPAINT);//�ڵײ�ͼ
	RedrawL++;
	if (RedrawL > 3)
		RedrawL = 0;
	else
		return;
	if (LdrawIndex == 5)
	{
		LdrawIndex = 0;
	}
	else
	{
		LdrawIndex++;
	}
}

void Player::drawWeaponFlash()
{
	double drawX, drawY;
	if (defaltCos <= 0)//���󹥻�
	{
		mainWeapon->flashs.drawFlash(x, y, 0);
	}
	else//���ҹ���
	{
		mainWeapon->flashs.drawFlash(x, y, 1);
	}
}

void Player::drawHP()
{
	/*setfillcolor(RGB(255, 0, 0));
	fillrectangle(0, 50, (hp - startHP) * hpLong / startHP + hpLong, 75);*/
	setfillcolor(DARKGRAY);
	solidrectangle(70, 35, 300, 65);
	setfillcolor(RED);
	solidrectangle(70, 35, 70 + 210 * hp / startHP, 65);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("����"));
	outtextxy(75, 35, "HP");
}

void Player::checkShowTime()
{
	clock_t now = clock();
	if ((double)(now - coverWeaponRecoder) / CLOCKS_PER_SEC < 0.4)
	{
		ifShowWeapon = false;
	}
	else
	{
		ifShowWeapon = true;
	}
}

void Player::showCD()
{
	double tangle;
	setfillcolor(BLUE);
	solidcircle(60, 180, 40);
	if (difftime(time(NULL), SkillTimeRecorder) < skillCd) {
		for (int y = 140; y <= 220; y++) {
			for (int x = 20; x <= 100; x++) {
				if (pow(x - 60, 2) + pow(y - 180, 2) <= 1600) {
					if (y == 180) {
						tangle = x >= 60 ? 0 : 3.14;
					}
					else if (x == 60) {
						tangle = y > 180 ? 1.57 : 3.14 + 1.57;
					}
					else {
						tangle = atan((double)(y - 180) / (double)(x - 60));
						if (x < 60)
							tangle += 3.14;
						else if (y < 180)
							tangle = 6.28 + tangle;
					}
					if (tangle < 6.28 * (double)((skillCd - difftime(time(NULL), SkillTimeRecorder)) / skillCd)) {
						putpixel(60 - y + 180, 180 - x + 60, WHITE);
					}

				}
			}
		}
	}
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("����"));
	outtextxy(45, 165, "CD");
}

void Player::levelup()
{
	// ��������
	if (experiencenum >= levelupneed)
	{
		experiencenum = 0;
		level++;
		levelupneed = 25 * level;

		// �������Լӳ�
		hp = startHP;
		if (speed <= 20)
		{
			speed += 0.5;
		}
		mainWeapon->Aspeed /= 1.08;
		mainWeapon->harm *= 1.1;
	}
}


void Player::drawEXP()
{
	setfillcolor(DARKGRAY);
	solidrectangle(70, 90, 300, 120);
	setfillcolor(GREEN);
	solidrectangle(70, 90, 70 + 230 * experiencenum / levelupneed, 120);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("����"));
	outtextxy(75, 90, "EXP");
	setfillcolor(WHITE);
	solidcircle(40, 105, 20);
	string le = to_string(level);
	outtextxy(35, 90, le.c_str());
}
//���������� 1�� 2�� 3��
//������bug
//������Ч-
//���һ����ɫ ��ƽ�ɫ���ܣ���Χ�˺���-
