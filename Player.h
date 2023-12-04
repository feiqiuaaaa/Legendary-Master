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
	double lastCos = 0;//记录上一次按键的方向
	char direction = 'a';//记录面朝的方向
	int profession = 0;//格斗大师->1	法师->2
	int bagSize = 5;//武器物品栏大小
	double skillCd = 5;//技能cd
	double unBeatAbleTime = 1;//受击无敌时间
	bool unBeatAble;//玩家是否处于无敌状态
	bool ifAttack;//判断玩家是否攻击
	bool ifShowWeapon = true;//判断是否显示武器
	int startHP;
	double defaltCos = -1;//玩家默认朝向（什么都不干的时候）开始默认朝左，后期根据上一步操作而定
	int kill = 0;//击杀数
	Drop* drops;//掉落物
	int level = 1, experiencenum, levelupneed = 25 * level;

	time_t SkillTimeRecorder = 0;//技能计时器
	clock_t AtimeRecorder = 0;//普通攻击计时器
	clock_t ShiftTimeRecorder;//shift切换武器计时器
	clock_t unBeatAbleRecorder;//受击后的无敌时间计时器
	clock_t quitWeaponRecoder;//丢武器的计时器
	clock_t coverWeaponRecoder;//隐藏武器的计时器

	vector<Weapon*> weapons;//武器背包
	Weapon* mainWeapon;//主武器

	//角色属性初始化
	Player();
	void ChooseProfession(int p);

	//角色状态显示
	void PlayerShowWeapons();
	void showCD();

	//移动和攻击功能
	void PlayerMove(int height, int width);
	void PlayerAttack();
	void PlayerGunAttack(vector<Bullet*>* bullet);
	void PlayerSkill(Map* map);
	void ifUnBeatAble();
	void PlayerBeenAttack(double harm);

	//武器物品栏管理
	bool addWeapons(Weapon* weapon);
	bool isInside(Weapon* weapon);
	Weapon* getWeapons(int index);
	void changeWeapons();
	void shiftChangeWeapons();
	void WeaponLevelUp(Weapon* weapon);

	//下面是具体各个职业的技能和属性
	//1.格斗大师
	bool isFlash = false;//判断玩家是否处于闪现状态
	bool flashSuccess = true;//判断闪现是否撞墙
	double flashLenth = 100;
	void skillOfDashi(Map* map);
	void AidFlash(Object* o);

	//2.法师
	bool isFire = false;//判断玩家是否在释放范围技能
	double fashiScope = 150;
	double fashiSkillHarm = 150;
	IMAGE* image1;
	IMAGE* image2;
	int showRecorder = 0;
	void skillOfFashi();
	bool fashiSkillAttack(Object* enemy);
	void drawFlash();

	//掉落物功能
	void pickUpDrop(Drop* drops, int x, int y);//捡武器

	//玩家贴图
	int ImageWidth, ImageHeight;
	IMAGE* LeftBlackImages;//向左黑底彩图贴图
	IMAGE* LeftCoverImages;//向左遮罩图贴图

	IMAGE* RightBlackImages;//向右黑底彩图贴图
	IMAGE* RightCoverImages;//向右遮罩图贴图

	IMAGE* standRightBlack;//向右站立黑底彩图
	IMAGE* standRightCover;//向右站立遮罩图
	IMAGE* standLeftBlack;
	IMAGE* standLeftCover;

	int LdrawIndex = 0;//绘制左向图片的下标
	int RedrawL = 0;//重复绘制计数
	int RdrawIndex = 0;//右向
	int RedrawR = 0;
	void drawPlayer();
	void readImages();
	void drawRightRun(int drawX, int drawY);
	void drawLeftRun(int drawX, int drawY);

	//武器特效
	void drawWeaponFlash();
	void drawHP();
	void checkShowTime();

	// 升级功能
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
	if (isKeyPressed(87))//键盘按下w键 注：括号内只能填大写字母对应的ascii码，可以检测大小写
	{
		move = -speed;
		if (y + move >= size && y + move <= height - size)
		{
			//y += move;
			sin = -1;
		}
	}//立马更新坐标，不然要出问题
	else if (isKeyPressed(83))//键盘按下s键
	{
		move = speed;
		if (y + move >= size && y + move <= height - size) {
			//y += move;
			sin = 1;
		}
	}
	if (isKeyPressed(65))//键盘按下a键
	{
		move = -speed;
		if (x + move >= size && x + move <= width - size) {
			//x += move;
			defaltCos = cos = -1;
		}
	}
	else if (isKeyPressed(68))//键盘按下d键
	{
		move = speed;
		if (x + move >= size && x + move <= width - size) {
			//x += move;
			defaltCos = cos = 1;
		}
	}
	if (fabs(sin) > minN && fabs(cos) > minN)//斜着移动
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
	//按下j键发动普通攻击
	if (isKeyPressed(74))
	{
		AtimeRecorder = clock();
		coverWeaponRecoder = clock();
		ifShowWeapon = false;
		//画普通攻击特效
		//solidcircle(x, y, mainWeapon->AttackScope);
		drawWeaponFlash();
		ifAttack = true;
	}
}

void Player::PlayerGunAttack(vector<Bullet*>* bullet)
{
	//按下j键射子弹
	if (isKeyPressed(74))
	{
		Bullet* bu;
		clock_t now = clock();
		if ((double)(now - AtimeRecorder) / CLOCKS_PER_SEC < mainWeapon->Aspeed)
		{
			return;
		}
		AtimeRecorder = clock();
		if (fabs(sin) < minN && fabs(cos) < minN)//玩家没指向
		{
			if (mainWeapon->name == "激光枪")
				bu = new Bullet(x + lastCos * size, y + lastSin * size, lastSin, lastCos, 40, 30, 25, mainWeapon->RepulseSpeed, 4, 0);
			else
				bu = new Bullet(x + lastCos * size, y + lastSin * size, lastSin, lastCos, 15, 10, 50, mainWeapon->RepulseSpeed, 0, 0);//使用默认指向
		}
		else
		{
			if (mainWeapon->name == "激光枪")
				bu = new Bullet(x + cos * size, y + sin * size, sin, cos, 40, 30, 25, mainWeapon->RepulseSpeed, 4, 0);
			else
				bu = new Bullet(x + cos * size, y + sin * size, sin, cos, 15, 10, 50, mainWeapon->RepulseSpeed, 0, 0);
		}
		bu->Move();
		(*bullet).push_back(bu);
	}
	if (isKeyPressed(80) || penetrationConfirmed) {//测试用了||，逻辑应该是&&这样捡到消耗品才能射出
		Bullet* bu;
		clock_t now = clock();
		if ((double)(now - AtimeRecorder) / CLOCKS_PER_SEC < mainWeapon->Aspeed)
		{
			return;
		}
		AtimeRecorder = clock();
		if (fabs(sin) < minN && fabs(cos) < minN)//玩家没指向
		{
			bu = new Bullet(x + defaltCos * size, y, 0, defaltCos, 15, 10, 50, mainWeapon->RepulseSpeed, 0, 0);//使用默认指向
		}
		else
		{
			bu = new Bullet(x + cos * size, y + sin * size, sin, cos, 15, 10, 50, mainWeapon->RepulseSpeed, 0, 0);
		}
		bu->speed *= 2;
		bu->damage *= 4;//属性更好
		bu->penetrate = true;
		bu->Move();
		(*bullet).push_back(bu);
		penetrationConfirmed = false;//除了击穿属性是额外设计的，其他都是仿照原有的，包括贴图……
	}
}


void Player::PlayerSkill(Map* map)
{
	//有技能cd
	if (difftime(time(NULL), SkillTimeRecorder) < skillCd)
	{
		//显示出技能cd
		/*char c = (int)(skillCd - difftime(time(NULL), SkillTimeRecorder)) + '0';
		outtextxy(500, 300, c);*/
		return;
	}
	//键盘按下k键则释放技能
	if (isKeyPressed(75)) {

		//把当前时间记录到计时器中
		SkillTimeRecorder = time(NULL);
		if (profession == 1)//格斗大师的技能
		{
			skillOfDashi(map);
		}
		if (profession == 2)//法师的技能
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
	if (map->creY - flashLenth >= 0 && map->creY + map->width + flashLenth <= mapImgWid)   //地图绘制最远边界判定
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

//法师技能
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
		//加范围技能贴图
		putimage(x - (image2->getwidth() / 2), y - (image2->getheight() / 2), image2, SRCAND);//遮罩图
		putimage(x - (image2->getwidth() / 2), y - (image2->getheight() / 2), image1, SRCPAINT);//黑底彩图
		showRecorder++;
	}
	else
	{
		isFire = false;
	}
}

//武器物品栏管理
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
	//循环遍历武器物品栏，判断要添加的武器是否已经添加过
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

void Player::changeWeapons()//12345切武器，shift快速切换
{
	if (isKeyPressed(49) && weapons.size() >= 1)//大键盘上的1
	{
		this->mainWeapon = weapons.at(0);
	}

	if (isKeyPressed(50) && weapons.size() >= 2)//大键盘上的2
	{
		this->mainWeapon = weapons.at(1);
	}

	if (isKeyPressed(51) && weapons.size() >= 3)//大键盘上的3
	{
		this->mainWeapon = weapons.at(2);
	}

	if (isKeyPressed(52) && weapons.size() >= 4)//大键盘上的4
	{
		this->mainWeapon = weapons.at(3);
	}

	if (isKeyPressed(53) && weapons.size() == 5)//大键盘上的5
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
	//按shift快速切换武器
	if (isKeyPressed(VK_SHIFT))
	{
		ShiftTimeRecorder = clock();
		Weapon* temp = NULL;
		//循环遍历武器物品栏，找到和主武器相同地址的武器,获取当前主武器的下一把武器
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
				{  //主武器在vector最后一格的情况,设置为物品栏第一把武器
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
	if (isKeyPressed(81))	//按q丢武器
	{
		//循环遍历武器物品栏，找到和主武器相同地址的武器并把它删掉
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
		// 剑
		Weapon* wp = new Weapon("剑", x, y, -1, 0, 1);
		if (!addWeapons(wp))
		{
			delete(wp);
		}
	}
	else if (drops->type == 1)
	{
		// 巨锤
		Weapon* wp = new Weapon("锤子", x, y, -1, 0, 1);
		if (!addWeapons(wp))
		{
			delete(wp);
		}
	}
	else if (drops->type == 2)
	{
		// 枪
		Weapon* wp = new Weapon("枪", x, y, -1, 0, 1);
		if (!addWeapons(wp))
		{
			delete(wp);
		}
	}
	else if (drops->type == 3)
	{
		// 血瓶
		hp += 500;
		if (hp > 3000)	hp = 3000;
	}
	else if (drops->type == 4)
	{
		// 移速
		if (speed <= 20)
		{
			speed += 0.5;
		}
	}
	else if (drops->type == 5)
	{
		// 攻速
		mainWeapon->Aspeed /= 1.08;
	}
	else if (drops->type == 6)
	{
		// 增加伤害
		mainWeapon->harm *= 1.1;
	}
	else if (drops->type == 7)
	{
		// 斧头
		Weapon* wp = new Weapon("斧头", x, y, -1, 0, 1);
		addWeapons(wp);
	}
	else if (drops->type == 8)
	{
		// 激光枪
		Weapon* wp = new Weapon("激光枪", x, y, -1, 0, 1);
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
		string lfilepath1 = to_string(profession) + " l" + to_string(i + 1) + " b.png";//左向黑底彩图
		string lfilepath2 = to_string(profession) + " l" + to_string(i + 1) + " w.png";//左向遮罩图

		loadimage(&LeftBlackImages[i], lfilepath1.c_str(), width, height, true);
		loadimage(&LeftCoverImages[i], lfilepath2.c_str(), width, height, true);

		string rfilepath1 = to_string(profession) + " r" + to_string(i + 1) + " b.png";//右向黑底彩图
		string rfilepath2 = to_string(profession) + " r" + to_string(i + 1) + " w.png";//右向遮罩图

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

	string file1 = "2 技能 黑底.png";
	string file2 = "2 技能 白底.png";

	loadimage(image1, file1.c_str(), 150, 150, true);
	loadimage(image2, file2.c_str(), 150, 150, true);
}

void Player::drawPlayer()
{
	double drawX = x - (LeftBlackImages[0].getwidth() / 2);
	double drawY = y - (LeftBlackImages[0].getheight() / 2);
	if (cos > 0)//向右时播放动图
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
			if (defaltCos <= 0)//之前朝左，默认为左
			{
				putimage(drawX, drawY, standLeftCover, SRCAND);//遮罩图
				putimage(drawX, drawY, standLeftBlack, SRCPAINT);//黑底彩图
			}
			else
			{
				putimage(drawX, drawY, standRightCover, SRCAND);//遮罩图
				putimage(drawX, drawY, standRightBlack, SRCPAINT);//黑底彩图
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
	putimage(drawX, drawY, &RightCoverImages[RdrawIndex], SRCAND);//遮罩图
	putimage(drawX, drawY, &RightBlackImages[RdrawIndex], SRCPAINT);//黑底彩图
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
	putimage(drawX, drawY, &LeftCoverImages[LdrawIndex], SRCAND);//遮罩图
	putimage(drawX, drawY, &LeftBlackImages[LdrawIndex], SRCPAINT);//黑底彩图
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
	if (defaltCos <= 0)//向左攻击
	{
		mainWeapon->flashs.drawFlash(x, y, 0);
	}
	else//向右攻击
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
	settextstyle(30, 0, _T("黑体"));
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
	settextstyle(30, 0, _T("黑体"));
	outtextxy(45, 165, "CD");
}

void Player::levelup()
{
	// 升级功能
	if (experiencenum >= levelupneed)
	{
		experiencenum = 0;
		level++;
		levelupneed = 25 * level;

		// 升级属性加成
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
	settextstyle(30, 0, _T("黑体"));
	outtextxy(75, 90, "EXP");
	setfillcolor(WHITE);
	solidcircle(40, 105, 20);
	string le = to_string(level);
	outtextxy(35, 90, le.c_str());
}
//捡武器升级 1星 2星 3星
//丢武器bug
//武器特效-
//多加一个角色 设计角色技能（范围伤害）-
