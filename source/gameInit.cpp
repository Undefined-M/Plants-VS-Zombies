#include "AllHeader.h"

void gameInit(IMAGE* imgBg, IMAGE* imgBar, IMAGE* imgEnd, IMAGE* imgWin, IMAGE* (*imgZhiWu)[20], IMAGE* imgCards,
	IMAGE* imgsunshineBall, IMAGE* imgBulletNormal, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead,
	IMAGE* imgZMBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow, IMAGE* imgZMBucketheadSnow,
	IMAGE* imgZMEat, IMAGE* imgZMEatFlag, IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgBulletBlast,
	IMAGE* imgJalapenoExplode, IMAGE* imgZMDead, IMAGE* imgZmStand, IMAGE* imgBulletSnow, struct zm* zms,
	struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads, struct bulletsnow* bullet_snows,
	struct zhiwu(*map)[9], struct sunshineBalls* balls, struct bullet* bullets, int* curY, int* curZhiwu, int* sunshine)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	//创建游戏的图形窗口	
	initgraph(WIN_WIDTH, WIN_HIGHTH, 1);

	//加载照片
	Loadimage(imgBg, imgBar, imgEnd, imgWin, imgZhiWu, imgCards, imgsunshineBall, imgBulletNormal, imgZMNormal, imgZMFlag,
		imgZMConehead, imgZMBuckethead, imgZMSnow, imgZMFlagSnow, imgZMConeheadSnow, imgZMBucketheadSnow, imgZMEat, imgZMEatFlag,
		imgZMEatConehead, imgZMEatBuckethead, imgBulletBlast, imgJalapenoExplode, imgZMDead, imgZmStand, imgBulletSnow); 

	//初始化数据
	InitData(zms, zmFlags, zmConeheads, zmBucketheads, bullet_snows, map, imgZhiWu, imgCards, balls, bullets, curY, curZhiwu, sunshine);

	//设置阳光值字体
	SetSunValueFont();

	//配置随机种子
	srand(time(NULL));
}

//加载照片函数
void Loadimage(IMAGE* imgBg, IMAGE* imgBar, IMAGE* imgEnd, IMAGE* imgWin, IMAGE* (*imgZhiWu)[20], IMAGE* imgCards,
	IMAGE* imgsunshineBall, IMAGE* imgBulletNormal, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead,
	IMAGE* imgZMBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow, IMAGE* imgZMBucketheadSnow,
	IMAGE* imgZMEat, IMAGE* imgZMEatFlag, IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgBulletBlast,
	IMAGE* imgJalapenoExplode, IMAGE* imgZMDead, IMAGE* imgZmStand, IMAGE* imgSnowBulletNormal)
{
	//加载背景图片
	loadimage(imgBg, "res/map0.jpg");//地图图片
	loadimage(imgBar, "res/bar5.png");//植物栏图片
	loadimage(imgEnd, "res/fail2.png");//游戏结束界面
	loadimage(imgWin, "res/gameWin.png");//游戏胜利界面

	char name[64];//定义字符串数组存储照片所在文件路径

	//加载辣椒攻击时的帧图片
	for (int i = 0; i < 35; i++)
	{
		sprintf_s(name, sizeof(name), "res/JalapenoExplode/%d.png", i);
		loadimage(&imgJalapenoExplode[i], name);
	}

	//加载碰撞后豌豆子弹的帧图片(通过一张照片不断放大产生发散效果)
	loadimage(&imgBulletBlast[3], "res/bullets/bullet_blast.png");
	for (int i = 0; i < 3; i++)
	{
		float k = (i + 1) * 0.4;
		loadimage(&imgBulletBlast[i], "res/bullets/bullet_blast.png",
			imgBulletBlast[3].getwidth() * k,
			imgBulletBlast[3].getheight() * k,
			true);
	}

	//加载僵尸各种状态的图片
	/*行走状态*/
	for (int i = 0; i < 22; i++)//普通僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_normal/%d.png", i + 1);
		loadimage(&imgZMNormal[i], name);
	}
	for (int i = 0; i < 12; i++)//旗子僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_flag/%d.png", i + 1);
		loadimage(&imgZMFlag[i], name);
	}
	for (int i = 0; i < 21; i++)//路障僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_conehead/%d.png", i + 1);
		loadimage(&imgZMConehead[i], name);
	}
	for (int i = 0; i < 15; i++)//铁桶僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_buckethead/%d.png", i + 1);
		loadimage(&imgZMBuckethead[i], name);
	}
	/*减速状态(寒冰豌豆射手击中后)*/
	for (int i = 0; i < 22; i++)//普通僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_snow/%d.png", i + 1);
		loadimage(&imgZMSnow[i], name);
	}
	for (int i = 0; i < 12; i++)//旗子僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_snow_flag/%d.png", i + 1);
		loadimage(&imgZMFlagSnow[i], name);
	}
	for (int i = 0; i < 21; i++)//路障僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_snow_conehead/%d.png", i + 1);
		loadimage(&imgZMConeheadSnow[i], name);
	}
	for (int i = 0; i < 15; i++)//铁桶僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_snow_buckethead/%d.png", i + 1);
		loadimage(&imgZMBucketheadSnow[i], name);
	}
	/*吃植物状态*/
	for (int i = 0; i < 21; i++)//普通僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_eat/%d.png", i + 1);
		loadimage(&imgZMEat[i], name);
	}
	for (int i = 0; i < 11; i++)//旗子僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_eat_flag/%d.png", i + 1);
		loadimage(&imgZMEatFlag[i], name);
	}
	for (int i = 0; i < 11; i++)//路障僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_eat_conehead/%d.png", i + 1);
		loadimage(&imgZMEatConehead[i], name);
	}
	for (int i = 0; i < 11; i++)//铁桶僵尸
	{
		sprintf_s(name, sizeof(name), "res/zm_eat_buckethead/%d.png", i + 1);
		loadimage(&imgZMEatBuckethead[i], name);
	}
	/*死亡状态*/
	for (int i = 0; i < 20; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm_dead/%d.png", i + 1);
		loadimage(&imgZMDead[i], name);
	}
	/*片头巡场僵尸状态*/
	for (int i = 0; i < 11; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm_stand/%d.png", i + 1);
		loadimage(&imgZmStand[i], name);
	}

	//加载阳光球的帧图片
	for (int i = 0; i < 29; i++)
	{
		sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
		loadimage(&imgsunshineBall[i], name);
	}

	//加载普通豌豆子弹的图片
	loadimage(imgBulletNormal, "res/bullets/bullet_normal.png");
	//加载寒冰豌豆子弹的图片
	loadimage(imgSnowBulletNormal, "res/bullets/bullet_snownormal.png");
}

//初始化数据函数
void InitData(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20], IMAGE* imgCards, struct sunshineBalls* balls,
	struct bullet* bullets, int* curY, int* curZhiwu, int* sunshine)
{
	//指针数组初始化置零 
	memset(imgZhiWu, 0, sizeof(imgZhiWu)); 
	//初始化植物的状态 
	memset(map, 0, sizeof(map)); 
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++) 
		{
			map[i][j].catched = false; 
			map[i][j].JalapenoExplode = false; 
		}
	}

	//初始化阳光球数据
	memset(balls, 0, sizeof(balls));
	for (int i = 0; i < 10; i++)
	{
		balls[i].used = false;//池中的阳光球是否在使用
	}

	//初始化普通僵尸数据
	memset(zms, 0, sizeof(zms));
	for (int i = 0; i < 10; i++)
	{
		zms[i].used = false;
		zms[i].eating = false;
		zms[i].slow = false;
		zms[i].blood = 100;//普通僵尸初始生命值
	}
	//初始化旗子僵尸数据
	memset(zmFlags, 0, sizeof(zmFlags));
	for (int i = 0; i < 10; i++)
	{
		zmFlags[i].used = false;
		zmFlags[i].eating = false;
		zmFlags[i].slow = false;
		zmFlags[i].blood = 150;//旗子僵尸初始生命值
	}
	//初始化路障僵尸数据
	memset(zmConeheads, 0, sizeof(zmConeheads));
	for (int i = 0; i < 10; i++)
	{
		zmConeheads[i].used = false;
		zmConeheads[i].eating = false;
		zmConeheads[i].slow = false;
		zmConeheads[i].blood = 200;//路障僵尸初始生命值
	}
	//初始化铁桶僵尸数据
	memset(zmBucketheads, 0, sizeof(zmBucketheads));
	for (int i = 0; i < 10; i++)
	{
		zmBucketheads[i].used = false;
		zmBucketheads[i].eating = false;
		zmBucketheads[i].slow = false;
		zmBucketheads[i].blood = 250;//铁桶僵尸初始生命值
	}

	//初始化普通子弹数据
	memset(bullets, 0, sizeof(bullets));
	for (int i = 0; i < 100; i++)
	{
		bullets[i].used = false;
		bullets[i].blast = false;
		bullets[i].repeater = false;
		bullets[i].triple = false;
		bullets[i].oblique = false;
		bullets[i].straight = false;
		bullets[i].single = false;
	}

	//初始化寒冰子弹数据
	memset(bullet_snows, 0, sizeof(bullet_snows));
	for (int i = 0; i < 30; i++)
	{
		bullet_snows[i].contant = false;
		bullet_snows[i].used = false;
	}

	//初始化阳光值的初值和植物卡牌的选中情况(0/1)
	*curZhiwu = 0;
	*sunshine = 1000;
}

//设置阳光值字体函数
void SetSunValueFont()
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 15;
	strcpy(f.lfFaceName, "Segoe UI Black");
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿效果
	settextstyle(&f);
	setbkmode(TRANSPARENT);//设置背景模式
	setcolor(BLACK);
}

//判断文件是否存在
bool fileExist(const char* name)
{
	FILE* fp = fopen(name, "r");
	if (fp == NULL)
	{
		return false;
	}
	else
	{
		fclose(fp);
		return true;
	}
}