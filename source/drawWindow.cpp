#include "AllHeader.h"

void drawWindow(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], int* curY, int* curX, int* curZhiwu,
	int* sunshine, struct sunshineBalls* balls, IMAGE* imgsunshineBall, IMAGE* imgZMDead, IMAGE* imgZMEat, IMAGE* imgZMEatFlag,
	IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow,
	IMAGE* imgZMBucketheadSnow, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead, IMAGE* imgZMBuckethead, IMAGE* imgBg,
	IMAGE* imgBar, IMAGE* imgCards, IMAGE* (*imgZhiWu)[20], IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, IMAGE* imgSnowBulletNormal,
	IMAGE* imgJalapenoExplode, IMAGE* imgZmStand, int ballMax, int zmCount, int countnormalMax, int countsnowMax)
{
	BeginBatchDraw();//开始缓冲(*解决闪屏问题)

	viewScence(imgBg, imgZmStand);//片头巡场    

	/*渲染初始界面界面*/
	drawUI(imgBg, imgBar);

	/*渲染植物卡牌*/
	drawZhiWuCards(imgCards);

	/*渲染僵尸*/
	drawZMNormal(zms, imgZMDead, imgZMEat, imgZMSnow, imgZMNormal, zmCount);//渲染普通僵尸 
	drawZMFlag(zmFlags, imgZMDead, imgZMEatFlag, imgZMFlagSnow, imgZMFlag, zmCount);//渲染旗子僵尸 
	drawZMConehead(zmConeheads, imgZMDead, imgZMEatConehead, imgZMConeheadSnow, imgZMConehead, zmCount);//渲染路障僵尸 
	drawZMBuckethead(zmBucketheads, imgZMDead, imgZMEatBuckethead, imgZMBucketheadSnow, imgZMBuckethead, zmCount);//渲染铁桶僵尸  

	/*渲染拖动过程中的植物*/
	drawZhiWuMoving(imgZhiWu, curZhiwu, curY, curX);
	/*渲染放置的植物*/
	drawZhiWuSetting(map, imgZhiWu);    

	/*渲染豌豆子弹*/
	drawSingleBullets(bullets, imgBulletBlast, imgBulletNormal, countnormalMax);//渲染普通豌豆子弹   
	drawDoubleBullets(bullets, imgBulletBlast, imgBulletNormal, countnormalMax);//渲染两连发(普通)豌豆子弹  
	drawThreeBullets(bullets, imgBulletBlast, imgBulletNormal, countnormalMax);//渲染三连发(普通)豌豆子弹 
	drawSnowBullets(bullet_snows, imgSnowBulletNormal, countsnowMax);//渲染寒冰豌豆子弹  

	/*渲染阳光值*/
	drawSunshineValue(sunshine);

	/*渲染辣椒火焰*/
	drawJalapenoExplode(map, zms, imgZhiWu, imgJalapenoExplode, zmCount);

	/*渲染阳光球(随机降落，向日葵生成，收集阳光)*/
	drawSunshines(balls, imgsunshineBall, ballMax);

	EndBatchDraw();//结束双缓冲(*解决闪屏问题)
}

//渲染普通僵尸
void drawZMNormal(struct zm* zms, IMAGE* imgZMDead, IMAGE* imgZMEat, IMAGE* imgZMSnow, IMAGE* imgZMNormal, int zmCount)
{
	for (int i = 0; i < zmCount; i++)
	{
		if (zms[i].used)
		{
			IMAGE* img = NULL;
			if (zms[i].dead)
			{
				img = imgZMDead;
			}
			else if (zms[i].eating)
			{
				img = imgZMEat;
			}
			else if (zms[i].slow)
			{
				img = imgZMSnow;
			}
			else
			{
				img = imgZMNormal;
			}

			img += zms[i].frameIndex;
			putimagePNG(zms[i].x, zms[i].y - img->getheight(), img);
		}
	}
}
//渲染旗子僵尸
void drawZMFlag(struct zmFlag* zmFlags, IMAGE* imgZMDead, IMAGE* imgZMEatFlag, IMAGE* imgZMSnow,
	IMAGE* imgZMFlag, int zmCount)
{
	int zmCountFlag = 5;
	for (int i = 0; i < zmCountFlag; i++)
	{
		if (zmFlags[i].used)
		{
			IMAGE* img = NULL;
			if (zmFlags[i].dead)
			{
				img = imgZMDead;
			}
			else if (zmFlags[i].eating)
			{
				img = imgZMEatFlag;
			}
			else if (zmFlags[i].slow)
			{
				img = imgZMSnow;
			}
			else
			{
				img = imgZMFlag;
			}

			img += zmFlags[i].frameIndex;
			putimagePNG(zmFlags[i].x, zmFlags[i].y - img->getheight(), img);
		}
	}
}
//渲染路障僵尸
void drawZMConehead(struct zmConehead* zmConeheads, IMAGE* imgZMDead, IMAGE* imgZMEatConehead,
	IMAGE* imgZMConeheadSnow, IMAGE* imgZMConehead, int zmCount)
{
	int zmCountCone = 5;
	for (int i = 0; i < zmCountCone; i++)
	{
		if (zmConeheads[i].used)
		{
			IMAGE* img = NULL;
			if (zmConeheads[i].dead)
			{
				img = imgZMDead;
			}
			else if (zmConeheads[i].eating)
			{
				img = imgZMEatConehead;
			}
			else if (zmConeheads[i].slow)
			{
				img = imgZMConeheadSnow;
			}
			else
			{
				img = imgZMConehead;
			}

			img += zmConeheads[i].frameIndex;
			putimagePNG(zmConeheads[i].x, zmConeheads[i].y - img->getheight(), img);
		}
	}
}
//渲染铁桶僵尸
void drawZMBuckethead(struct zmBuckethead* zmBucketheads, IMAGE* imgZMDead,
	IMAGE* imgZMEatBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMBuckethead, int zmCount)
{
	int zmCountBucket = 5;
	for (int i = 0; i < zmCountBucket; i++)
	{
		if (zmBucketheads[i].used)
		{
			IMAGE* img = NULL;
			if (zmBucketheads[i].dead)
			{
				img = imgZMDead;
			}
			else if (zmBucketheads[i].eating)
			{
				img = imgZMEatBuckethead;
			}
			else if (zmBucketheads[i].slow)
			{
				img = imgZMSnow;
			}
			else
			{
				img = imgZMBuckethead;
			}
			img += zmBucketheads[i].frameIndex;
			putimagePNG(zmBucketheads[i].x, zmBucketheads[i].y - img->getheight(), img);
		}
	}
}

//渲染普通豌豆射手豌豆子弹
void drawSingleBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax)
{
	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used && bullets[i].single)
		{
			if (bullets[i].blast)
			{
				IMAGE* img = NULL;
				img = &imgBulletBlast[bullets[i].frameIndex];
				putimagePNG(bullets[i].pCur.x, bullets[i].pCur.y, img);
			}
			else
			{
				putimagePNG(bullets[i].pCur.x, bullets[i].pCur.y, imgBulletNormal);
			}
		}
	}
}
//渲染双重豌豆射手豌豆子弹
void drawDoubleBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax)
{
	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used && bullets[i].repeater)
		{
			if (bullets[i].blast)
			{
				IMAGE* img = NULL;
				img = &imgBulletBlast[bullets[i].frameIndex];
				putimagePNG(bullets[i].pCur.x, bullets[i].pCur.y, img);
			}
			else
			{
				putimagePNG(bullets[i].pCur.x, bullets[i].pCur.y, imgBulletNormal);
			}
		}
	}
}
//渲染三重豌豆射手豌豆子弹
void drawThreeBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax)
{
	for (int i = 0; i < countnormalMax; i++)
	{
		//渲染斜射时的子弹
		if (bullets[i].used && bullets[i].triple && bullets[i].oblique)
		{
			if (bullets[i].blast)
			{
				IMAGE* img;
				img = &imgBulletBlast[bullets[i].frameIndex];
				putimagePNG(bullets[i].pCur.x, bullets[i].pCur.y, img);
			}
			else
			{
				putimagePNG(bullets[i].pCur.x, bullets[i].pCur.y, imgBulletNormal);
			}
		}
		//渲染直射时的子弹
		if (bullets[i].used && bullets[i].triple && bullets[i].straight)
		{
			if (bullets[i].blast)
			{
				IMAGE* img;
				img = &imgBulletBlast[bullets[i].frameIndex];
				putimagePNG(bullets[i].pCur.x, bullets[i].pCur.y, img);
			}
			else
			{
				putimagePNG(bullets[i].pCur.x, bullets[i].pCur.y, imgBulletNormal);
			}
		}
	}
}
//渲染寒冰豌豆射手豌豆子弹
void drawSnowBullets(struct bulletsnow* bullet_snows, IMAGE* imgSnowBulletNormal, int countsnowMax)
{
	for (int i = 0; i < countsnowMax; i++)
	{
		if (bullet_snows[i].used)
		{
			putimagePNG(bullet_snows[i].pCur.x, bullet_snows[i].pCur.y, imgSnowBulletNormal);
		}
	}
}

//渲染阳光球(随机降落，向日葵生成，收集阳光)
void drawSunshines(struct sunshineBalls* balls, IMAGE* imgsunshineBall, int ballMax)
{
	for (int i = 0; i < ballMax; i++)
	{
		if (balls[i].used)
		{
			IMAGE* img = NULL;
			img = &imgsunshineBall[balls[i].frameIndex];
			putimagePNG(balls[i].pCur.x, balls[i].pCur.y, img);
		}
	}
}

//渲染拖动过程中的植物
void drawZhiWuMoving(IMAGE* (*imgZhiWu)[20], int* curZhiwu, int* curY, int* curX)
{
	if (*curZhiwu > 0)
	{
		IMAGE* img = NULL;
		img = imgZhiWu[*curZhiwu - 1][0];
		putimagePNG(*curX - img->getwidth() / 2, *curY - img->getheight() / 2, img);//将光标调整到植物中间 
	}
}
//渲染放置的植物
void drawZhiWuSetting(struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type > 0)
			{
				int zhiWuType = map[i][j].type - 1;
				int index = map[i][j].frameIndex;
				putimagePNG(map[i][j].x, map[i][j].y, imgZhiWu[zhiWuType][index]); 
			}
		}
	}
}

//渲染阳光值
void drawSunshineValue(int* sunshine)
{
	char scoreText[80];
	sprintf_s(scoreText, sizeof(scoreText), "%d", *sunshine);
	outtextxy(278, 67, scoreText);
}

//渲染植物卡牌
void drawZhiWuCards(IMAGE* imgCards)
{
	for (int i = 0; i < ZHI_WU_COUNT; i++)
	{
		int x = 336 + i * 65;
		int y = 6;
		putimage(x, y, &imgCards[i]);
	}
}

//渲染UI界面
void drawUI(IMAGE* imgBg, IMAGE* imgBar)
{
	putimage(-112, 0, imgBg);
	putimagePNG(250, 0, imgBar);
}

//渲染辣椒火焰
void drawJalapenoExplode(struct zhiwu(*map)[9], struct zm* zms, IMAGE* (*imgZhiWu)[20], IMAGE* imgJalapenoExplode, int zmCount)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].JalapenoExplode)
			{
				map[i][j].JalapenoframeIndex++;
				if (map[i][j].JalapenoframeIndex > 35)
				{
					map[i][j].JalapenoframeIndex = -1;
					map[i][j].JalapenoExplode = false;
				}

				int JalapenoY = map[i][j].y;

				IMAGE* img;
				img = imgJalapenoExplode;
				img += map[i][j].JalapenoframeIndex;
				putimagePNG(245 - 112, JalapenoY - 47, img);
			}
		}
	}
}

//片头巡场
void viewScence(IMAGE* imgBg, IMAGE* imgZmStand)
{
	static int times = 0;
	if (times == 0)
	{
		times++;
		int WIN_WIDTH = 900;
		int WIN_HIGHTH = 600;

		int xMin = WIN_WIDTH - imgBg->getwidth();
		vector2 point[9] =
		{
			{550,80},{530,160},{630,170},{530,200},{515,270},
			{565,370},{605,340},{705,280},{690,340}
		};
		int index[9];
		for (int i = 0; i < 9; i++)
		{
			index[i] = rand() % 11;
		}

		int count = 0;
		for (int x = 0; x >= xMin; x -= 2)
		{
			BeginBatchDraw();

			putimage(x, 0, imgBg);

			count++;
			for (int k = 0; k < 9; k++)
			{
				putimagePNG(point[k].x - xMin + x, point[k].y, &imgZmStand[index[k]]);
				if (count >= 10)
				{
					index[k] = (index[k] + 1) % 11;
				}
			}
			if (count >= 10) count = 0;

			EndBatchDraw();
			Sleep(20);
		}

		//停留1s左右
		for (int i = 0; i < 100; i++)
		{
			BeginBatchDraw();

			putimage(xMin, 0, imgBg);
			for (int k = 0; k < 9; k++)
			{
				putimagePNG(point[k].x, point[k].y, &imgZmStand[index[k]]);
				index[k] = (index[k] + 1) % 11;
			}
			EndBatchDraw();
			Sleep(30);
		}

		for (int x = xMin; x <= -112; x += 2)
		{
			BeginBatchDraw();

			putimage(x, 0, imgBg);
			count++;
			for (int k = 0; k < 9; k++)
			{
				putimagePNG(point[k].x - xMin + x, point[k].y, &imgZmStand[index[k]]);
				if (count >= 10)
				{
					index[k] = (index[k] + 1) % 11;
				}
				if (count >= 10) count = 0;
			}
			EndBatchDraw();
			Sleep(5);
		}
	}
}