#include "AllHeader.h"

int main(void)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	/*定义IMAGE类型的变量，数组，指针数组来存储.jpg/.png文件(图片帧)*/
	IMAGE imgBg;//表示背景图片
	IMAGE imgBar;//表示植物栏背景图片
	IMAGE imgEnd;//挑战失败背景图片
	IMAGE imgWin;//挑战成功背景图片
	IMAGE imgCards[ZHI_WU_COUNT];//植物卡牌图片
	IMAGE* imgZhiWu[ZHI_WU_COUNT][20];//各种植物种植后的帧图片 
	IMAGE imgsunshineBall[29];//阳光球的帧图片 
	//普通僵尸
	IMAGE imgZMNormal[22];//普通僵尸行走时的帧图片
	IMAGE imgZMSnow[22];//普通僵尸被寒冰射手击中减速时的帧图片
	IMAGE imgZMDead[20];//僵尸死亡时的帧图片
	IMAGE imgZMEat[21];//普通僵尸吃植物时的帧图片
	IMAGE imgZmStand[11];//片头巡场画面中僵尸的帧图片
	//旗子僵尸(死亡状态与普通僵尸的图片一致)
	IMAGE imgZMFlag[12];//旗子僵尸行走时的帧图片
	IMAGE imgZMFlagSnow[12];//旗子僵尸被寒冰射手击中减速时的帧图片
	IMAGE imgZMEatFlag[11];//旗子僵尸吃植物时的帧图片
	//路障僵尸(死亡状态与普通僵尸的图片一致) 
	IMAGE imgZMConehead[21];//路障僵尸行走时的帧图片
	IMAGE imgZMConeheadSnow[21];//路障僵尸被寒冰射手击中减速时的帧图片 
	IMAGE imgZMEatConehead[11];//路障僵尸吃植物时的帧图片 
	//铁桶僵尸(死亡状态与普通僵尸的图片一致)
	IMAGE imgZMBuckethead[15];//铁桶僵尸行走时的帧图片
	IMAGE imgZMBucketheadSnow[15];//铁桶僵尸被寒冰射手击中减速时的帧图片
	IMAGE imgZMEatBuckethead[11];//铁桶僵尸吃植物时的帧图片
	//普通豌豆(含碰撞后的爆炸效果)
	IMAGE imgBulletNormal;//普通豌豆子弹的图片
	IMAGE imgBulletBlast[4];//普通豌豆子弹碰撞后爆炸的帧图片
	//寒冰豌豆
	IMAGE imgBulletSnow;//寒冰豌豆子弹的图片
	//辣椒燃烧状态
	IMAGE imgJalapenoExplode[35];//辣椒燃烧时火焰的帧图片
	
	/*定义结构体类型的数组*/
	struct zhiwu map[5][9];
	//10个阳光球
	struct sunshineBalls  balls[10];
	//10个普通僵尸
	struct zm zms[10];
	//5个旗子僵尸
	struct zmFlag zmFlags[5];
	//5个路障僵尸
	struct zmConehead zmConeheads[5];
	//5个铁桶僵尸
	struct zmBuckethead zmBucketheads[5];
	//100个普通豌豆
	struct bullet bullets[100];
	//30个寒冰豌豆
	struct bulletsnow bullet_snows[30];
	 
	int curX, curY = 0;//当前选中植物在移动过程中的位置
	int curZhiwu = 0;//0：没有选中，1：选择了第一种植物 
	int sunshine = 0;//定义用于储存阳光值的整型变量
	ExMessage msg; 

	//游戏初始化模块
	gameInit(&imgBg, &imgBar, &imgEnd, &imgWin, imgZhiWu, imgCards, imgsunshineBall, &imgBulletNormal, imgZMNormal, imgZMFlag,
		imgZMConehead, imgZMBuckethead, imgZMSnow, imgZMFlagSnow, imgZMConeheadSnow, imgZMBucketheadSnow, imgZMEat, imgZMEatFlag,
		imgZMEatConehead, imgZMEatBuckethead, imgBulletBlast, imgJalapenoExplode, imgZMDead, imgZmStand, &imgBulletSnow,
		zms, zmFlags, zmConeheads, zmBucketheads, bullet_snows, map, balls, bullets, &curY, &curZhiwu, &sunshine);
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
	//初始化植物卡牌
	char name[64];//定义字符串数组存储文件名
	for (int i = 0; i < ZHI_WU_COUNT; i++)
	{
		//生成植物卡牌的文件名
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);

		for (int j = 0; j < 20; j++)
		{
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//先判断这个文件是否存在（打开文件）
			if (fileExist(name))
			{
				imgZhiWu[i][j] = new IMAGE;//分配内存
				loadimage(imgZhiWu[i][j], name);
			}
			else
			{
				break;
			}
		}
	}

	/*定义并初始化IMAGE类型和所定义结构体类型的指针变量(*用于传参)*/
	IMAGE* imgCardsptr = imgCards;//植物卡牌
	IMAGE* (*imgZhiWuptr)[20] = imgZhiWu;
	IMAGE* imgsunshineBallptr = imgsunshineBall;//阳光球
	//普通僵尸
	IMAGE* imgZMNormalptr = imgZMNormal;
	IMAGE* imgZMSnowptr = imgZMSnow;
	IMAGE* imgZMDeadptr = imgZMDead;
	IMAGE* imgZMEatptr = imgZMEat;
	IMAGE* imgZmStandptr = imgZmStand;
	//旗子僵尸
	IMAGE* imgZMFlagptr = imgZMFlag;
	IMAGE* imgZMFlagSnowptr = imgZMFlagSnow; 
	IMAGE* imgZMEatFlagptr = imgZMEatFlag;
	//路障僵尸
	IMAGE* imgZMConeheadptr = imgZMConehead;
	IMAGE* imgZMConeheadSnowptr = imgZMConeheadSnow; 
	IMAGE* imgZMEatConeheadptr = imgZMEatConehead;
	//铁桶僵尸
	IMAGE* imgZMBucketheadptr = imgZMBuckethead;
	IMAGE* imgZMBucketheadSnowptr = imgZMBucketheadSnow; 
	IMAGE* imgZMEatBucketheadptr = imgZMEatBuckethead;
	//普通豌豆爆炸状态
	IMAGE* imgBulletBlastptr = imgBulletBlast;
	//辣椒燃烧状态
	IMAGE* imgJalapenoExplodeptr = imgJalapenoExplode;

	struct zhiwu(*mapptr)[9] = map;
	//阳光球
	struct sunshineBalls* ballsptr = balls;
	//普通僵尸
	struct zm* zmsptr = zms;
	//旗子僵尸
	struct zmFlag* zmFlagsptr = zmFlags;
	//路障僵尸
	struct zmConehead* zmConeheadsptr = zmConeheads;
	//铁桶僵尸
	struct zmBuckethead* zmBucketheadsptr = zmBucketheads;
	//普通豌豆
	struct bullet* bulletsptr = bullets;
	//寒冰豌豆
	struct bulletsnow* bullet_snowsptr = bullet_snows;

	/*计算阳关球，寒冰豌豆子弹，普通豌豆子弹，僵尸的数量(*传参)*/
	int ballMax = sizeof(balls) / sizeof(balls[0]); //阳光球数量
	int countsnowMax = sizeof(bullet_snows) / sizeof(bullet_snows[0]);//寒冰豌豆子弹数量
	int countnormalMax = sizeof(bullets) / sizeof(bullets[0]);//普通豌豆子弹数量
	int zmCount = sizeof(zms) / sizeof(zms[0]);//普通僵尸数量
	int zmCountFlag = sizeof(zmFlags) / sizeof(zmFlags[0]);//旗子僵尸的数量
	int zmCountCone = sizeof(zmConeheads) / sizeof(zmConeheads[0]);//路障僵尸的数量
	int zmCountBucket = sizeof(zmBucketheads) / sizeof(zmBucketheads[0]);//铁桶僵尸的数量
	int dangerX = WIN_WIDTH - imgZMNormal[0].getwidth() + 50;//计算僵尸的危险距离 

	int timer = 0;
	bool flag = true;
	while (1)
	{
		//UI交互模块
		UCInteraction(&msg, &sunshine, mapptr, ballsptr, &curZhiwu, &curX, &curY, imgsunshineBallptr, ballMax);

		timer += getDelay();//优化代码的运行速度
		if (timer > 35)
		{
			flag = true;
			timer = 0;
		}
		if (flag)
		{
			flag = false;				
			//游戏渲染图像模块
			drawWindow(zmsptr, zmFlagsptr, zmConeheadsptr, zmBucketheadsptr, bulletsptr, bullet_snowsptr, mapptr, &curY, &curX,
				&curZhiwu, &sunshine, ballsptr, imgsunshineBallptr, imgZMDeadptr, imgZMEatptr, imgZMEatFlagptr, imgZMEatConeheadptr,
				imgZMEatBucketheadptr, imgZMSnowptr, imgZMFlagSnowptr, imgZMConeheadSnowptr, imgZMBucketheadSnowptr, imgZMNormalptr,
				imgZMFlagptr, imgZMConeheadptr, imgZMBucketheadptr, &imgBg, &imgBar, imgCardsptr, imgZhiWuptr, imgBulletBlastptr,
				&imgBulletNormal, &imgBulletSnow, imgJalapenoExplodeptr, imgZmStandptr, ballMax, zmCount, countnormalMax,
				countsnowMax);
			//游戏更新数据模块
			updateGame(mapptr, ballsptr, zmsptr, zmFlagsptr, zmConeheadsptr, zmBucketheadsptr, bulletsptr, bullet_snowsptr,
				&sunshine, imgZhiWuptr, &imgEnd, imgsunshineBallptr, imgZMNormalptr, ballMax, zmCount, zmCountFlag, zmCountCone,
				zmCountBucket, countnormalMax, countsnowMax, dangerX, &imgWin);
		}
	}
	system("pause");
	return 0;
}