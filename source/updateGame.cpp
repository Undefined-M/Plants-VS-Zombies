#include "AllHeader.h"

void updateGame(struct zhiwu(*map)[9], struct sunshineBalls* balls, struct zm* zms, struct zmFlag* zmFlags,
	struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads, struct bullet* bullets, struct bulletsnow* bullet_snows,
	int* sunshine, IMAGE* (*imgZhiWu)[20], IMAGE* imgEnd, IMAGE* imgsunshineBall, IMAGE* imgZMNormal, int ballMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int countnormalMax, int countsnowMax, int dangerX, IMAGE* imgWin)
{
	upodateZhiWuState(map, imgZhiWu);////更新植物种植后的状态

	/*阳光球*/
	createSunshine(balls, map, imgZhiWu, imgsunshineBall, ballMax);//创建阳光球
	updateSunshine(balls, sunshine, ballMax);//更新阳光球状态

	/*普通僵尸*/
	createZMNormal(zms, zmCount);//创建普通僵尸 
	updateZMNormal(zms, imgEnd, zmCount);//更新普通僵尸的状态 
	/*旗子僵尸*/
	createZMFlag(zmFlags, zmCount);//创建旗子僵尸   
	updateZMFlag(zmFlags, imgEnd, zmCount);//更新旗子僵尸的状态  
	/*路障僵尸*/
	createZMConehead(zmConeheads, zmCount);//创建路障僵尸    
	updateZMConehead(zmConeheads, imgEnd, zmCount);//更新路障僵尸的状态   
	/*铁桶僵尸*/
	createZMBuckethead(zmBucketheads, zmCount);//创建铁通僵尸 
	updateZMBuckethead(zmBucketheads, imgEnd, zmCount);//更新铁桶僵尸的状态  

	/*普通豌豆射手*/
	shoot_single(zms, zmFlags, zmConeheads, zmBucketheads, bullets, map, imgZMNormal, imgZhiWu, countnormalMax,
		zmCount, zmCountFlag, zmCountCone, zmCountBucket, dangerX);//发射普通豌豆子弹 
	updateSingleBullets(bullets, countnormalMax);//更新普通豌豆子弹
	/*双重豌豆射手*/
	shoot_double(zms, zmFlags, zmConeheads, zmBucketheads, bullets, map, imgZMNormal, imgZhiWu,
		countnormalMax, zmCount, zmCountFlag, zmCountCone, zmCountBucket, dangerX);//发射两连发(普通)豌豆子弹 
	updateDoubleBullets(bullets, countnormalMax);//更新两连发(普通)豌豆子弹 
	/*三重豌豆射手*/
	shoot_three(zms, zmFlags, zmConeheads, zmBucketheads, bullets, map, imgZMNormal, imgZhiWu, countnormalMax,
		zmCount, zmCountFlag, zmCountCone, zmCountBucket, dangerX);//发射三连发(普通)豌豆子弹 
	updateThreeBullets(bullets, countnormalMax);//更新三连发(普通)豌豆子弹 
	/*寒冰豌豆射手*/
	shoot_snow(zms, zmFlags, zmConeheads, zmBucketheads, bullet_snows, map, imgZMNormal, imgZhiWu, countsnowMax,
		zmCount, zmCountFlag, zmCountCone, zmCountBucket, dangerX);//发射寒冰豌豆子弹
	updateSnowBullets(bullet_snows, countsnowMax);//更新寒冰豌豆子弹

	/*辣椒*/
	updateJalapeno(map);//更新辣椒

	checkNormalBullet2Zm(bullets, zms, zmFlags, zmConeheads, zmBucketheads, countnormalMax, zmCount, zmCountFlag,
		zmCountCone, zmCountBucket);//普通子弹对僵尸的碰撞检测	

	checkSnowBullet2Zm(bullet_snows, zms, zmFlags, zmConeheads, zmBucketheads, countnormalMax, zmCount, zmCountFlag,
		zmCountCone, zmCountBucket);//实现寒冰子弹对僵尸的碰撞检测

	checkFlame2Zm(map, zms, zmFlags, zmConeheads, zmBucketheads, zmCount, zmCountFlag,
		zmCountCone, zmCountBucket, dangerX);//实现辣椒火焰与僵尸的接触检测

	checkZm2ZhiWu(zms, zmFlags, zmConeheads, zmBucketheads, map, zmCount, zmCountFlag, zmCountCone, zmCountBucket);//实现僵尸对植物的碰撞检测

	checksuccess(zms, zmFlags, zmConeheads, zmBucketheads, zmCount, zmCountFlag, zmCountCone, zmCountBucket, imgWin);//判断是否挑战成功
}

//创建阳光球
void createSunshine(struct sunshineBalls* balls, struct zhiwu(*map)[9],
	IMAGE* (*imgZhiWu)[20], IMAGE* imgsunshineBall, int ballMax)
{
	static int count = 0;
	static int fre = 450;
	count++;
	if (count >= fre)
	{
		fre = 300 + rand() % 150;
		count = 0;
		//从阳光池中取一个可以使用的
		int i;
		for (i = 0; i < ballMax && balls[i].used; i++);
		if (i >= ballMax)return;

		balls[i].used = true;
		balls[i].frameIndex = 0;
		balls[i].timer = 0;
		balls[i].status = SUNSHINE_DOWN;
		balls[i].t = 0;
		balls[i].p1 = vector2(260 - 112 + rand() % (900 - (260 - 140)), 60);
		balls[i].p4 = vector2(balls[i].p1.x, 200 + (rand() % 4) * 90);
		float off = 2;
		float distance = balls[i].p4.y - balls[i].p1.y;
		balls[i].speed = 1.0 / (distance / off);
	}
	//向日葵生产阳光
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type == XIANG_RI_KUI + 1)
			{
				map[i][j].timer++;
				if (map[i][j].timer > 300)
				{
					map[i][j].timer = 0;

					int k;
					for (k = 0; k < ballMax && balls[k].used; k++);
					if (k >= ballMax)return;

					balls[k].used = true;
					balls[k].p1 = vector2(map[i][j].x, map[i][j].y);
					int w = (100 + rand() % 50) * (rand() % 2 ? 1 : -1);
					balls[k].p4 = vector2(map[i][j].x + w,
						map[i][j].y + imgZhiWu[XIANG_RI_KUI][0]->getheight() - imgsunshineBall[0].getheight());
					balls[k].p2 = vector2(balls[k].p1.x + w * 0.3, balls[k].p1.y - 100);
					balls[k].p3 = vector2(balls[k].p1.x + w * 0.7, balls[k].p1.y - 100);
					balls[k].status = SUNSHINE_PRODUCT;
					balls[k].speed = 0.05;
					balls[k].t = 0;
				}
			}
		}
	}
}
//更新阳光球
void updateSunshine(struct sunshineBalls* balls, int* sunshine, int ballMax)
{
	for (int i = 0; i < ballMax; i++)
	{
		if (balls[i].used)
		{
			balls[i].frameIndex = (balls[i].frameIndex + 1) % 29;
			if (balls[i].status == SUNSHINE_DOWN)
			{
				struct sunshineBalls* sun = &balls[i];
				sun->t += sun->speed;
				sun->pCur = sun->p1 + sun->t * (sun->p4 - sun->p1);
				if (sun->t >= 1)
				{
					sun->status = SUNSHINE_GROUND;
					sun->timer = 0;
				}
			}
			else if (balls[i].status == SUNSHINE_GROUND)
			{
				balls[i].timer++;
				if (balls[i].timer > 100)
				{
					balls[i].used = false;
					balls[i].timer = 0;
				}
			}
			else if (balls[i].status == SUNSHINE_COLLECT)
			{
				struct sunshineBalls* sun = &balls[i];
				sun->t += sun->speed;
				sun->pCur = sun->p1 + sun->t * (sun->p4 - sun->p1);
				if (sun->t >= 1)
				{
					sun->used = false;
					(*sunshine) += 25;
				}
			}
			else if (balls[i].status == SUNSHINE_PRODUCT)
			{
				struct sunshineBalls* sun = &balls[i];
				sun->t += sun->speed;
				sun->pCur = calcBezierPoint(sun->t, sun->p1, sun->p2, sun->p3, sun->p4);//计算贝塞尔曲线上点的位置
				if (sun->t >= 1)
				{
					sun->status = SUNSHINE_GROUND;
					sun->timer = 0;
				}
			}
		}
	}
}

//更新植物种植后的状态
void upodateZhiWuState(struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type > 0)
			{
				map[i][j].frameIndex++;
				int zhiWuType = map[i][j].type - 1;
				int index = map[i][j].frameIndex;
				if (imgZhiWu[zhiWuType][index] == NULL)
				{
					map[i][j].frameIndex = 0;
					map[i][j].JalapenoframeIndex = 0;
				}
			}
		}
	}
}

//实现普通子弹对僵尸的碰撞检测
void checkNormalBullet2Zm(struct bullet* bullets, struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int countnormalMax, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket)
{
	/*单发豌豆射手豌豆子弹的碰撞检测*/
	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used == false || bullets[i].single == false || bullets[i].blast) continue;

		//与普通僵尸的碰撞检测
		for (int k = 0; k < zmCount; k++)
		{
			if (zms[k].used == false) continue;

			int x = bullets[i].pCur.x;
			int x1 = zms[k].x + 80;
			int x2 = zms[k].x + 110;

			if (zms[k].dead == false && bullets[i].row == zms[k].row && x > x1 && x < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zms[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speed = 0;

				if (zms[k].blood <= 0)
				{
					zms[k].speed = 0;
					zms[k].dead = true;
					zms[k].frameIndex = 0;
				}
			}
		}
		//与旗子僵尸的碰撞检测
		for (int k = 0; k < zmCountFlag; k++)
		{
			if (zmFlags[k].used == false) continue;

			int x = bullets[i].pCur.x;
			int x1 = zmFlags[k].x + 80;
			int x2 = zmFlags[k].x + 110;

			if (zmFlags[k].dead == false && bullets[i].row == zmFlags[k].row && x > x1 && x < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmFlags[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speed = 0;

				if (zmFlags[k].blood <= 0)
				{
					zmFlags[k].speed = 0;
					zmFlags[k].dead = true;
					zmFlags[k].frameIndex = 0;
				}
			}
		}
		//与路障僵尸的碰撞检测
		for (int k = 0; k < zmCountCone; k++)
		{
			if (zmConeheads[k].used == false) continue;

			int x = bullets[i].pCur.x;
			int x1 = zmConeheads[k].x + 80;
			int x2 = zmConeheads[k].x + 110;

			if (zmConeheads[k].dead == false && bullets[i].row == zmConeheads[k].row && x > x1 && x < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmConeheads[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speed = 0;

				if (zmConeheads[k].blood <= 0)
				{
					zmConeheads[k].speed = 0;
					zmConeheads[k].dead = true;
					zmConeheads[k].frameIndex = 0;
				}
			}
		}
		//与铁桶僵尸的碰撞检测
		for (int k = 0; k < zmCountBucket; k++)
		{
			if (zmBucketheads[k].used == false) continue;

			int x = bullets[i].pCur.x;
			int x1 = zmBucketheads[k].x + 80;
			int x2 = zmBucketheads[k].x + 110;

			if (zmBucketheads[k].dead == false && bullets[i].row == zmBucketheads[k].row && x > x1 && x < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmBucketheads[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speed = 0;

				if (zmBucketheads[k].blood <= 0)
				{
					zmBucketheads[k].speed = 0;
					zmBucketheads[k].dead = true;
					zmBucketheads[k].frameIndex = 0;
				}
			}
		}

	}
	/*双重豌豆射手豌豆子弹的碰撞检测*/
	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used == false || bullets[i].repeater == false || bullets[i].blast)continue;

		//与普通僵尸的碰撞检测
		for (int k = 0; k < zmCount; k++)
		{
			if (zms[k].used == false) continue;

			int x = bullets[i].pCur.x;
			int x1 = zms[k].x + 80;
			int x2 = zms[k].x + 110;

			if (zms[k].dead == false && bullets[i].row == zms[k].row && x > x1 && x < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zms[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speed = 0;

				if (zms[k].blood <= 0)
				{
					zms[k].speed = 0;
					zms[k].dead = true;
					zms[k].frameIndex = 0;
				}
			}
		}
		//与旗子僵尸的碰撞检测
		for (int k = 0; k < zmCountFlag; k++)
		{
			if (zmFlags[k].used == false) continue;

			int x = bullets[i].pCur.x;
			int x1 = zmFlags[k].x + 80;
			int x2 = zmFlags[k].x + 110;

			if (zmFlags[k].dead == false && bullets[i].row == zmFlags[k].row && x > x1 && x < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmFlags[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speed = 0;

				if (zmFlags[k].blood <= 0)
				{
					zmFlags[k].speed = 0;
					zmFlags[k].dead = true;
					zmFlags[k].frameIndex = 0;
				}
			}
		}
		//与路障僵尸的碰撞检测
		for (int k = 0; k < zmCountCone; k++)
		{
			if (zmConeheads[k].used == false) continue;

			int x = bullets[i].pCur.x;
			int x1 = zmConeheads[k].x + 80;
			int x2 = zmConeheads[k].x + 110;

			if (zmConeheads[k].dead == false && bullets[i].row == zmConeheads[k].row && x > x1 && x < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmConeheads[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speed = 0;

				if (zmConeheads[k].blood <= 0)
				{
					zmConeheads[k].speed = 0;
					zmConeheads[k].dead = true;
					zmConeheads[k].frameIndex = 0;
				}
			}
		}
		//与铁桶僵尸的碰撞检测
		for (int k = 0; k < zmCountBucket; k++)
		{
			if (zmBucketheads[k].used == false) continue;

			int x = bullets[i].pCur.x;
			int x1 = zmBucketheads[k].x + 80;
			int x2 = zmBucketheads[k].x + 110;

			if (zmBucketheads[k].dead == false && bullets[i].row == zmBucketheads[k].row && x > x1 && x < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmBucketheads[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speed = 0;

				if (zmBucketheads[k].blood <= 0)
				{
					zmBucketheads[k].speed = 0;
					zmBucketheads[k].dead = true;
					zmBucketheads[k].frameIndex = 0;
				}
			}

		}
	}
	/*三重射手豌豆子弹的碰撞检测*/
	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used == false || bullets[i].triple == false || bullets[i].blast)continue;

		//与普通僵尸的碰撞检测
		for (int k = 0; k < zmCount; k++)
		{
			if (zms[k].used == false) continue;

			int x3 = bullets[i].pCur.x;
			int y3 = bullets[i].pCur.y;

			int x1 = zms[k].x + 80;
			int x2 = zms[k].x + 110;

			int y1 = zms[k].y + 40;
			int y2 = zms[k].y + 120;

			//子弹斜射状态
			if (zms[k].dead == false && bullets[i].row == zms[k].row && bullets[i].oblique &&
				x3 > x1 && x3 < x2 && y3 > y1 && y3 < y2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zms[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speedoblique = 0;

				if (zms[k].blood <= 0)
				{
					zms[k].dead = true;
					zms[k].speed = 0;
					zms[k].frameIndex = 0;
				}
			}
			//子弹直射状态
			if (zms[k].dead == false && bullets[i].row == zms[k].row && bullets[i].straight && x3 > x1 && x3 < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zms[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speedstraight = 0;

				if (zms[k].blood <= 0)
				{
					zms[k].dead = true;
					zms[k].speed = 0;
					zms[k].frameIndex = 0;
				}
			}
		}
		//与旗子僵尸的碰撞检测
		for (int k = 0; k < zmCountFlag; k++)
		{
			if (zmFlags[k].used == false) continue;

			int x3 = bullets[i].pCur.x;
			int y3 = bullets[i].pCur.y;

			int x1 = zmFlags[k].x + 80;
			int x2 = zmFlags[k].x + 110;

			int y1 = zmFlags[k].y + 40;
			int y2 = zmFlags[k].y + 120;

			//子弹斜射状态
			if (zmFlags[k].dead == false && bullets[i].row == zmFlags[k].row && bullets[i].oblique &&
				x3 > x1 && x3 < x2 && y3>y1 && y3 < y2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmFlags[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speedoblique = 0;

				if (zmFlags[k].blood <= 0)
				{
					zmFlags[k].dead = true;
					zmFlags[k].speed = 0;
					zmFlags[k].frameIndex = 0;
				}
			}
			//子弹直射状态
			if (zmFlags[k].dead == false && bullets[i].row == zmFlags[k].row && bullets[i].straight && x3 > x1 && x3 < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmFlags[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speedstraight = 0;

				if (zmFlags[k].blood <= 0)
				{
					zmFlags[k].dead = true;
					zmFlags[k].speed = 0;
					zmFlags[k].frameIndex = 0;
				}
			}
		}
		//与路障僵尸的碰撞检测
		for (int k = 0; k < zmCountCone; k++)
		{
			if (zmConeheads[k].used == false) continue;

			int x3 = bullets[i].pCur.x;
			int y3 = bullets[i].pCur.y;

			int x1 = zmConeheads[k].x + 80;
			int x2 = zmConeheads[k].x + 110;

			int y1 = zmConeheads[k].y + 40;
			int y2 = zmConeheads[k].y + 120;

			//子弹斜射状态
			if (zmConeheads[k].dead == false && bullets[i].row == zmConeheads[k].row && bullets[i].oblique &&
				x3 > x1 && x3 < x2 && y3>y1 && y3 < y2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmConeheads[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speedoblique = 0;

				if (zmConeheads[k].blood <= 0)
				{
					zmConeheads[k].dead = true;
					zmConeheads[k].speed = 0;
					zmConeheads[k].frameIndex = 0;
				}
			}
			//子弹直射状态
			if (zmConeheads[k].dead == false && bullets[i].row == zmConeheads[k].row && bullets[i].straight && x3 > x1 && x3 < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmConeheads[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speedstraight = 0;

				if (zmConeheads[k].blood <= 0)
				{
					zmConeheads[k].dead = true;
					zmConeheads[k].speed = 0;
					zmConeheads[k].frameIndex = 0;
				}
			}
		}
		//与铁桶僵尸的碰撞检测
		for (int k = 0; k < zmCountBucket; k++)
		{
			if (zmBucketheads[k].used == false) continue;

			int x3 = bullets[i].pCur.x;
			int y3 = bullets[i].pCur.y;

			int x1 = zmBucketheads[k].x + 80;
			int x2 = zmBucketheads[k].x + 110;

			int y1 = zmBucketheads[k].y + 40;
			int y2 = zmBucketheads[k].y + 120;

			//子弹斜射状态
			if (zmBucketheads[k].dead == false && bullets[i].row == zmBucketheads[k].row && bullets[i].oblique &&
				x3 > x1 && x3 < x2 && y3>y1 && y3 < y2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmBucketheads[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speedoblique = 0;

				if (zmBucketheads[k].blood <= 0)
				{
					zmBucketheads[k].dead = true;
					zmBucketheads[k].speed = 0;
					zmBucketheads[k].frameIndex = 0;
				}
			}
			//子弹直射状态
			if (zmBucketheads[k].dead == false && bullets[i].row == zmBucketheads[k].row && bullets[i].straight && x3 > x1 && x3 < x2)
			{
				//PlaySound("res/splat1.wav", NULL, SND_FILENAME | SND_ASYNC);
				zmBucketheads[k].blood -= 10;
				bullets[i].blast = true;
				bullets[i].speedstraight = 0;

				if (zmBucketheads[k].blood <= 0)
				{
					zmBucketheads[k].dead = true;
					zmBucketheads[k].speed = 0;
					zmBucketheads[k].frameIndex = 0;
				}
			}
		}
	}
}
//实现寒冰子弹对僵尸的碰撞检测
void checkSnowBullet2Zm(struct bulletsnow* bullet_snows, struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int countnormalMax, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket)
{
	//static int countnormal = 0;
	//static int countflag = 0;
	//static int countcone = 0;
	//static int countbucket = 0;

	for (int i = 0; i < countnormalMax; i++)
	{
		int x = bullet_snows[i].pCur.x;

		if (bullet_snows[i].used == false || bullet_snows[i].contant) continue;

		//普通僵尸的碰撞检测
		for (int k = 0; k < zmCount; k++)
		{
			if (zms[k].used == false) continue;
			int x1 = zms[k].x + 40;
			int x2 = zms[k].x + 110;

			if (zms[k].dead == false && bullet_snows[i].row == zms[k].row && x > x1 && x < x2)
			{
				zms[k].blood -= 10;
				//countnormal++;
				bullet_snows[i].contant = true;
				zms[k].slow = true;
				zms[k].speed = 1;
				//if (countnormal > 3)
				//{
				//	countnormal = 0;
				//	zms[k].slow = false;
				//	zms[k].speed = 2.5;
				//}
				if (zms[k].slowtimer > 10)
				{
					zms[k].slowtimer = 0;
				}
				bullet_snows[i].speed = 0;

				if (zms[k].blood <= 0)
				{
					zms[k].dead = true;
					zms[k].speed = 0;
					zms[k].frameIndex = 0;
				}
			}
		}
		//旗子僵尸的碰撞检测
		for (int k = 0; k < zmCountFlag; k++)
		{
			if (zmFlags[k].used == false) continue;
			int x1 = zmFlags[k].x + 40;
			int x2 = zmFlags[k].x + 110;

			if (zmFlags[k].dead == false && bullet_snows[i].row == zmFlags[k].row && x > x1 && x < x2)
			{
				zmFlags[k].blood -= 10;
				//countflag++;
				bullet_snows[i].contant = true;
				zmFlags[k].slow = true;
				zmFlags[k].speed = 1;
				//if (countflag > 3)
				//{
				//	countflag = 0;
				//	zmFlags[k].slow = false;
				//	zmFlags[k].speed = 2.5;
				//}
				if (zmFlags[k].slowtimer > 10)
				{
					zmFlags[k].slowtimer = 0;
				}
				bullet_snows[i].speed = 0;
				if (zmFlags[k].blood <= 0)
				{
					zmFlags[k].dead = true;
					zmFlags[k].speed = 0;
					zmFlags[k].frameIndex = 0;
				}
			}
		}
		//路障僵尸的碰撞检测
		for (int k = 0; k < zmCountCone; k++)
		{
			if (zmConeheads[k].used == false) continue;
			int x1 = zmConeheads[k].x + 40;
			int x2 = zmConeheads[k].x + 110;

			if (zmConeheads[k].dead == false && bullet_snows[i].row == zmConeheads[k].row && x > x1 && x < x2)
			{
				zmConeheads[k].blood -= 10;
				//countcone++;
				bullet_snows[i].contant = true;
				zmConeheads[k].slow = true;
				zmConeheads[k].speed = 1;
				//if (countcone > 3)
				//{
				//	countcone = 0;
				//	zmConeheads[k].slow = false;
				//	zmConeheads[k].speed = 2.5;
				//}
				if (zmConeheads[k].slowtimer > 10)
				{
					zmConeheads[k].slowtimer = 0;
				}
				bullet_snows[i].speed = 0;

				if (zmConeheads[k].blood <= 0)
				{
					zmConeheads[k].dead = true;
					zmConeheads[k].speed = 0;
					zmConeheads[k].frameIndex = 0;
				}
			}
		}
		//铁桶僵尸的碰撞检测
		for (int k = 0; k < zmCountBucket; k++)
		{
			if (zmBucketheads[k].used == false) continue;
			int x1 = zmBucketheads[k].x + 40;
			int x2 = zmBucketheads[k].x + 110;

			if (zmBucketheads[k].dead == false && bullet_snows[i].row == zmBucketheads[k].row && x > x1 && x < x2)
			{
				zmBucketheads[k].blood -= 10;
				//countbucket++;
				bullet_snows[i].contant = true;
				zmBucketheads[k].slow = true;
				zmBucketheads[k].speed = 1;
				//if (countbucket > 3)
				//{
				//	countbucket = 0;
				//	zmBucketheads[k].slow = false;
				//	zmBucketheads[k].speed = 2.5;
				//}
				if (zmBucketheads[k].slowtimer > 10)
				{
					zmBucketheads[k].slowtimer = 0;
				}
				bullet_snows[i].speed = 0;

				if (zmBucketheads[k].blood <= 0)
				{
					zmBucketheads[k].dead = true;
					zmBucketheads[k].speed = 0;
					zmBucketheads[k].frameIndex = 0;
				}
			}
		}
	}
}
//实现辣椒火焰与僵尸的接触检测
void checkFlame2Zm(struct zhiwu(*map)[9], struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX)
{
	int zmRow = -1;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].JalapenoExplode)
			{
				zmRow = i;

				//普通僵尸的接触检测
				for (int k = 0; k < zmCount; k++)
				{
					if (zms[k].row == zmRow && zms[k].used && zms[k].x <= dangerX)
					{
						if (zms[k].dead == false)//注*:如果没有此条件会让死亡进行时(僵尸死亡帧图片未加载完成)的僵尸再重新死亡一遍
						{
							zms[k].frameIndex = 0;
							zms[k].dead = true;
							zms[k].blood = 0;
							zms[k].speed = 0;
						}
					}
				}
				//旗子僵尸的接触检测
				for (int k = 0; k < zmCountFlag; k++)
				{
					if (zmFlags[k].row == zmRow && zmFlags[k].used && zmFlags[k].x <= dangerX)
					{
						if (zmFlags[k].dead == false)//注*:如果没有此条件会让死亡进行时(僵尸死亡帧图片未加载完成)的僵尸再重新死亡一遍
						{
							zmFlags[k].frameIndex = 0;
							zmFlags[k].dead = true;
							zmFlags[k].blood = 0;
							zmFlags[k].speed = 0;
						}
					}
				}
				//路障僵尸的接触检测
				for (int k = 0; k < zmCountCone; k++)
				{
					if (zmConeheads[k].row == zmRow && zmConeheads[k].used && zmConeheads[k].x <= dangerX)
					{
						if (zmConeheads[k].dead == false)//注*:如果没有此条件会让死亡进行时(僵尸死亡帧图片未加载完成)的僵尸再重新死亡一遍
						{
							zmConeheads[k].frameIndex = 0;
							zmConeheads[k].dead = true;
							zmConeheads[k].blood = 0;
							zmConeheads[k].speed = 0;
						}
					}
				}
				//铁桶僵尸的接触检测
				for (int k = 0; k < zmCountBucket; k++)
				{
					if (zmBucketheads[k].row == zmRow && zmBucketheads[k].used && zmBucketheads[k].x <= dangerX)
					{
						if (zmBucketheads[k].dead == false)//注*:如果没有此条件会让死亡进行时(僵尸死亡帧图片未加载完成)的僵尸再重新死亡一遍
						{
							zmBucketheads[k].frameIndex = 0;
							zmBucketheads[k].dead = true;
							zmBucketheads[k].blood = 0;
							zmBucketheads[k].speed = 0;
						}
					}
				}
			}
		}
	}
}
//实现僵尸对植物的碰撞检测
void checkZm2ZhiWu(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct zhiwu(*map)[9], int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket)
{
	//普通僵尸检测
	for (int i = 0; i < zmCount; i++)
	{
		if (zms[i].dead) continue;
		int row = zms[i].row;
		for (int k = 0; k < 9; k++)
		{
			if (map[row][k].type == 0) continue;

			//      x1   x2
			//		[     ]植物
			//			[	  ]僵尸
			//			x3

			int ZhiWuX = 256 - 112 + k * 81;
			int x1 = ZhiWuX + 10;
			int x2 = ZhiWuX + 60;
			int x3 = zms[i].x + 80;
			if (x1 < x3 && x3 < x2)
			{
				if (map[row][k].catched)
				{
					zms[i].eating = true;
					zms[i].speed = 0;
					map[row][k].deadTime++;
					if (map[row][k].deadTime > 120)
					{
						map[row][k].deadTime = 0;
						map[row][k].type = 0;
					}

					for (int i = 0; i < zmCount; i++)
					{
						if (map[row][k].type == 0 && zms[i].eating)
						{
							zms[i].eating = false;
							zms[i].speed = 2.5;
							zms[i].frameIndex = 0;
						}
					}
				}
				else
				{
					map[row][k].catched = true;
					map[row][k].deadTime = 0;
				}
			}
		}
	}
	//旗子僵尸检测
	for (int i = 0; i < zmCountFlag; i++)
	{
		if (zmFlags[i].dead) continue;
		int row = zmFlags[i].row;
		for (int k = 0; k < 9; k++)
		{
			if (map[row][k].type == 0) continue;

			//      x1   x2
			//		[     ]植物
			//			[	  ]僵尸
			//			x3

			int ZhiWuX = 256 - 112 + k * 81;
			int x1 = ZhiWuX + 10;
			int x2 = ZhiWuX + 60;
			int x3 = zmFlags[i].x + 80;
			if (x1 < x3 && x3 < x2)
			{
				if (map[row][k].catched)
				{
					zmFlags[i].eating = true;
					zmFlags[i].speed = 0;
					map[row][k].deadTime++;
					if (map[row][k].deadTime > 120)
					{
						map[row][k].deadTime = 0;
						map[row][k].type = 0;
					}

					for (int i = 0; i < zmCountFlag; i++)
					{
						if (map[row][k].type == 0 && zmFlags[i].eating)
						{
							zmFlags[i].eating = false;
							zmFlags[i].speed = 2.5;
							zmFlags[i].frameIndex = 0;
						}
					}
				}
				else
				{
					map[row][k].catched = true;
					map[row][k].deadTime = 0;
				}
			}
		}
	}
	//路障僵尸检测
	for (int i = 0; i < zmCountCone; i++)
	{
		if (zmConeheads[i].dead) continue;
		int row = zmConeheads[i].row;
		for (int k = 0; k < 9; k++)
		{
			if (map[row][k].type == 0) continue;

			//      x1   x2
			//		[     ]植物
			//			[	  ]僵尸
			//			x3

			int ZhiWuX = 256 - 112 + k * 81;
			int x1 = ZhiWuX + 10;
			int x2 = ZhiWuX + 60;
			int x3 = zmConeheads[i].x + 80;
			if (x1 < x3 && x3 < x2)
			{
				if (map[row][k].catched)
				{
					zmConeheads[i].eating = true;
					zmConeheads[i].speed = 0;
					map[row][k].deadTime++;
					if (map[row][k].deadTime > 120)
					{
						map[row][k].deadTime = 0;
						map[row][k].type = 0;
					}

					for (int i = 0; i < zmCountCone; i++)
					{
						if (map[row][k].type == 0 && zmConeheads[i].eating)
						{
							zmConeheads[i].eating = false;
							zmConeheads[i].speed = 2.5;
							zmConeheads[i].frameIndex = 0;
						}
					}
				}
				else
				{
					map[row][k].catched = true;
					map[row][k].deadTime = 0;
				}
			}
		}
	}
	//铁桶僵尸检测
	for (int i = 0; i < zmCountBucket; i++)
	{
		if (zmBucketheads[i].dead) continue;
		int row = zmBucketheads[i].row;
		for (int k = 0; k < 9; k++)
		{
			if (map[row][k].type == 0) continue;

			//      x1   x2
			//		[     ]植物
			//			[	  ]僵尸
			//			x3

			int ZhiWuX = 256 - 112 + k * 81;
			int x1 = ZhiWuX + 10;
			int x2 = ZhiWuX + 60;
			int x3 = zmBucketheads[i].x + 80;
			if (x1 < x3 && x3 < x2)
			{
				if (map[row][k].catched)
				{
					zmBucketheads[i].eating = true;
					zmBucketheads[i].speed = 0;
					map[row][k].deadTime++;
					if (map[row][k].deadTime > 120)
					{
						map[row][k].deadTime = 0;
						map[row][k].type = 0;
					}

					for (int i = 0; i < zmCountBucket; i++)
					{
						if (map[row][k].type == 0 && zmBucketheads[i].eating)
						{
							zmBucketheads[i].eating = false;
							zmBucketheads[i].speed = 2.5;
							zmBucketheads[i].frameIndex = 0;
						}
					}
				}
				else
				{
					map[row][k].catched = true;
					map[row][k].deadTime = 0;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//实现普通豌豆射手的发射
void shoot_single(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX)
{
	int lines[5] = { 0 };

	//普通僵尸的发射检测
	for (int i = 0; i < zmCount; i++)
	{
		if (zms[i].used && zms[i].x < dangerX && zms[i].dead == false)
		{
			lines[zms[i].row] = 1;
		}
	}
	//旗子僵尸的发射检测
	for (int i = 0; i < zmCountFlag; i++)
	{
		if (zmFlags[i].used && zmFlags[i].x < dangerX && zmFlags[i].dead == false)
		{
			lines[zmFlags[i].row] = 1;
		}
	}
	//路障僵尸的发射检测
	for (int i = 0; i < zmCountCone; i++)
	{
		if (zmConeheads[i].used && zmConeheads[i].x < dangerX && zmConeheads[i].dead == false)
		{
			lines[zmConeheads[i].row] = 1;
		}
	}
	//铁桶僵尸的发射检测
	for (int i = 0; i < zmCountBucket; i++)
	{
		if (zmBucketheads[i].used && zmBucketheads[i].x < dangerX && zmBucketheads[i].dead == false)
		{
			lines[zmBucketheads[i].row] = 1;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((map[i][j].type == WAN_DOU_1 + 1) && lines[i])
			{
				int zwX = 256 - 112 + j * 81;
				int zwY = 77 + i * 102 + 14;

				static int count = 0;
				count++;
				if (count > 30)
				{
					//PlaySound("res/shoop.wav", NULL, SND_FILENAME | SND_ASYNC);
					count = 0;

					int k;
					for (k = 0; k < countnormalMax && bullets[k].used; k++);
					if (k < countnormalMax)
					{
						bullets[k].used = true;
						bullets[k].single = true;
						bullets[k].row = i;
						bullets[k].speed = 11;

						bullets[k].blast = false;
						bullets[k].frameIndex = 0;

						bullets[k].pCur.x = zwX + imgZhiWu[map[i][j].type - 1][0]->getwidth() - 10;
						bullets[k].pCur.y = zwY + 5;
					}
				}
			}
		}
	}
}
//实现双重豌豆射手的发射
void shoot_double(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX)
{
	int lines[5] = { 0 };

	//普通僵尸的发射检测
	for (int i = 0; i < zmCount; i++)
	{
		if (zms[i].used && zms[i].x < dangerX && zms[i].dead == false)
		{
			lines[zms[i].row] = 1;
		}
	}
	//旗子僵尸的发射检测
	for (int i = 0; i < zmCountFlag; i++)
	{
		if (zmFlags[i].used && zmFlags[i].x < dangerX && zmFlags[i].dead == false)
		{
			lines[zmFlags[i].row] = 1;
		}
	}
	//路障僵尸的发射检测
	for (int i = 0; i < zmCountCone; i++)
	{
		if (zmConeheads[i].used && zmConeheads[i].x < dangerX && zmConeheads[i].dead == false)
		{
			lines[zmConeheads[i].row] = 1;
		}
	}
	//铁桶僵尸的发射检测
	for (int i = 0; i < zmCountBucket; i++)
	{
		if (zmBucketheads[i].used && zmBucketheads[i].x < dangerX && zmBucketheads[i].dead == false)
		{
			lines[zmBucketheads[i].row] = 1;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((map[i][j].type == WAN_DOU_3 + 1) && lines[i])
			{
				//确定双重射手的x,y坐标
				int zwX = 256 - 112 + j * 81;
				int zwY = 88 + i * 102 + 14;

				static int count = 0;
				count++;
				if (count > 30)
				{
					//PlaySound("res/shoop.wav", NULL, SND_FILENAME | SND_ASYNC);
					count = 0;

					int k;
					//第一发子弹
					for (k = 0; k < countnormalMax && bullets[k].used || bullets[k].repeater; k++);
					if (k < countnormalMax)
					{
						bullets[k].used = true;
						bullets[k].repeater = true;
						bullets[k].row = i;
						bullets[k].speed = 9;

						bullets[k].blast = false;
						bullets[k].frameIndex = 0;

						bullets[k].pCur.x = zwX + imgZhiWu[map[i][j].type - 1][0]->getwidth() - 10;
						bullets[k].pCur.y = zwY + 5;
					}
					//第二发子弹
					for (k = 0; k < countnormalMax && bullets[k].used || bullets[k].repeater; k++);
					if (k < countnormalMax)
					{
						bullets[k].used = true;
						bullets[k].repeater = true;
						bullets[k].row = i;
						bullets[k].speed = 9;

						bullets[k].blast = false;
						bullets[k].frameIndex = 0;

						bullets[k].pCur.x = zwX + 2 * (imgZhiWu[map[i][j].type - 1][0]->getwidth()) - 10;
						bullets[k].pCur.y = zwY + 5;
					}
				}
			}
		}
	}
}
//实现三重豌豆射手的发射
void shoot_three(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX)
{
	int flag = 0;//判断地图中是否有僵尸

	//普通僵尸的发射检测
	for (int i = 0; i < zmCount; i++)
	{
		if (zms[i].used && zms[i].x < dangerX && zms[i].dead == false)
		{
			flag = 1;
		}
	}
	//旗子僵尸的发射检测
	for (int i = 0; i < zmCountFlag; i++)
	{
		if (zmFlags[i].used && zmFlags[i].x < dangerX && zmFlags[i].dead == false)
		{
			flag = 1;
		}
	}
	//路障僵尸的发射检测
	for (int i = 0; i < zmCountCone; i++)
	{
		if (zmConeheads[i].used && zmConeheads[i].x < dangerX && zmConeheads[i].dead == false)
		{
			flag = 1;
		}
	}
	//铁桶僵尸的发射检测
	for (int i = 0; i < zmCountBucket; i++)
	{
		if (zmBucketheads[i].used && zmBucketheads[i].x < dangerX && zmBucketheads[i].dead == false)
		{
			flag = 1;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((map[i][j].type == WAN_DOU_4 + 1) && flag)
			{
				//确定三重射手的x,y坐标
				float zwX = 256 - 112 + j * 81;
				float zwY = 77 + i * 102 + 14;

				static int count = 0;
				count++;
				if (count > 30)
				{
					//PlaySound("res/shoop.wav", NULL, SND_FILENAME | SND_ASYNC);
					count = 0;
					int k;
					if (i != 0)
					{
						//第一发子弹(上弹道)
						for (k = 0; k < countnormalMax && bullets[k].used; k++);
						if (k < countnormalMax)
						{
							bullets[k].used = true;
							bullets[k].triple = true;
							bullets[k].oblique = true;
							bullets[k].straight = false;

							bullets[k].speedstraight = 9;//设置直射状态时的速度

							bullets[k].frameIndex = 0;

							bullets[k].t = 0;

							/*子弹的起始位置p1-->p4*/
							bullets[k].p1.x = zwX + imgZhiWu[map[i][j].type - 1][0]->getwidth() - 10;
							bullets[k].p1.y = zwY + 5;

							//注*;及时更新pCur(豌豆当前位置),否则发射的豌豆一开始会渲染在上个豌豆碰撞的位置
							bullets[k].pCur = bullets[k].p1;

							bullets[k].p4.x = bullets[k].p1.x + 81 + 10;
							bullets[k].p4.y = bullets[k].p1.y - 102;

							//计算起始位置之间的距离,并设置移动速度
							float distance = dis(bullets[k].p4 - bullets[k].p1);
							float off = 12;
							bullets[k].speedoblique = 1.0 / (distance / off);
						}
					}
					//第二发子弹(中弹道)
					for (k = 0; k < countnormalMax && bullets[k].used; k++);
					if (k < countnormalMax)
					{
						bullets[k].used = true;
						bullets[k].triple = true;
						bullets[k].oblique = false;
						bullets[k].straight = true;//发射时直接更新为直射状态

						bullets[k].speedstraight = 9;

						bullets[k].frameIndex = 0;

						bullets[k].t = 0;

						/*子弹的初始位置p1*/
						bullets[k].p1.x = zwX + imgZhiWu[map[i][j].type - 1][0]->getwidth() - 10;
						bullets[k].p1.y = zwY + 5;

						bullets[k].pCur = bullets[k].p1;
					}
					if (i != 4)
					{
						//第三发子弹(下弹道)
						for (k = 0; k < countnormalMax && bullets[k].used; k++);
						if (k < countnormalMax)
						{
							bullets[k].used = true;
							bullets[k].triple = true;
							bullets[k].oblique = true;
							bullets[k].straight = false;

							bullets[k].speedstraight = 9;

							bullets[k].frameIndex = 0;

							bullets[k].t = 0;

							/*子弹的起始位置p1-->p4*/
							bullets[k].p1.x = zwX + imgZhiWu[map[i][j].type - 1][0]->getwidth() - 10;
							bullets[k].p1.y = zwY + 5;

							//注*;及时更新pCur(豌豆当前位置),否则发射的豌豆一开始会渲染在上个豌豆碰撞的位置
							bullets[k].pCur = bullets[k].p1;

							bullets[k].p4.x = bullets[k].p1.x + 81 + 10;
							bullets[k].p4.y = bullets[k].p1.y + 102;

							//计算起始位置之间的距离,并设置移动速度
							float distance = dis(bullets[k].p4 - bullets[k].p1);
							float off = 12;
							bullets[k].speedoblique = 1.0 / (distance / off);
						}
					}
				}
			}
		}
	}
}
//实现寒冰豌豆射手的发射
void shoot_snow(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countsnowMax,
	int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX)
{
	int lines[5] = { 0 };

	//普通僵尸的发射检测
	for (int i = 0; i < zmCount; i++)
	{
		if (zms[i].used && zms[i].x < dangerX && zms[i].dead == false)
		{
			lines[zms[i].row] = 1;
		}
	}
	//旗子僵尸的发射检测
	for (int i = 0; i < zmCountFlag; i++)
	{
		if (zmFlags[i].used && zmFlags[i].x < dangerX && zmFlags[i].dead == false)
		{
			lines[zmFlags[i].row] = 1;
		}
	}
	//路障僵尸的发射检测
	for (int i = 0; i < zmCountCone; i++)
	{
		if (zmConeheads[i].used && zmConeheads[i].x < dangerX && zmConeheads[i].dead == false)
		{
			lines[zmConeheads[i].row] = 1;
		}
	}
	//铁桶僵尸的发射检测
	for (int i = 0; i < zmCountBucket; i++)
	{
		if (zmBucketheads[i].used && zmBucketheads[i].x < dangerX && zmBucketheads[i].dead == false)
		{
			lines[zmBucketheads[i].row] = 1;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((map[i][j].type == WAN_DOU_2 + 1) && lines[i])
			{
				int zwX = 256 - 112 + j * 81;
				int zwY = 77 + i * 102 + 14;
				static int count = 0;
				count++;
				if (count > 30)
				{
					//PlaySound("res/shoop.wav", NULL, SND_FILENAME | SND_ASYNC);
					count = 0;

					int k;
					for (k = 0; k < countsnowMax && bullet_snows[k].used; k++);
					if (k < countsnowMax)
					{
						bullet_snows[k].used = true;
						bullet_snows[k].row = i;
						bullet_snows[k].speed = 11;

						bullet_snows[k].contant = false;

						bullet_snows[k].pCur.x = zwX + imgZhiWu[map[i][j].type - 1][0]->getwidth() - 10;
						bullet_snows[k].pCur.y = zwY + 5;
					}
				}
			}
		}
	}
}

//更新普通豌豆射手的发射
void updateSingleBullets(struct bullet* bullets, int countnormalMax)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used == false || bullets[i].single == false)continue;

		bullets[i].pCur.x += bullets[i].speed;
		if (bullets[i].pCur.x > WIN_WIDTH)
		{
			bullets[i].used = false;
			bullets[i].single = false;
		}
		if (bullets[i].blast)
		{
			bullets[i].frameIndex++;
			if (bullets[i].frameIndex > 3)
			{
				bullets[i].used = false;
				bullets[i].single = false;
				bullets[i].blast = false;
				bullets[i].frameIndex = 0;
			}
		}
	}
}
//更新双重豌豆射手的发射
void updateDoubleBullets(struct bullet* bullets, int countnormalMax)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used == false || bullets[i].repeater == false)continue;

		bullets[i].pCur.x += bullets[i].speed;
		if (bullets[i].pCur.x > WIN_WIDTH)
		{
			bullets[i].used = false;
			bullets[i].repeater = false;
		}
		if (bullets[i].blast)
		{
			bullets[i].frameIndex++;
			if (bullets[i].frameIndex > 3)
			{
				bullets[i].used = false;
				bullets[i].repeater = false;
				bullets[i].blast = false;
				bullets[i].frameIndex = 0;
			}
		}
	}
}
//更新三重豌豆射手的发射
void updateThreeBullets(struct bullet* bullets, int countnormalMax)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	//更新豌豆斜射(oblique)时的状态
	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used == false || bullets[i].triple == false || bullets[i].oblique == false)continue;
		bullets[i].t += bullets[i].speedoblique;
		bullets[i].pCur = bullets[i].p1 + bullets[i].t * (bullets[i].p4 - bullets[i].p1);

		//更新斜射状态下豌豆的行数
		bullets[i].row = (bullets[i].pCur.y - 77) / 102;

		if (bullets[i].pCur.x > WIN_WIDTH)
		{
			bullets[i].used = false;
			bullets[i].triple = false;
			bullets[i].oblique = false;
			bullets[i].straight = false;
		}

		if (bullets[i].blast)
		{
			bullets[i].frameIndex++;
			if (bullets[i].frameIndex > 3)
			{
				bullets[i].used = false;
				bullets[i].triple = false;
				bullets[i].oblique = false;
				bullets[i].straight = false;
				bullets[i].blast = false;
				bullets[i].frameIndex = 0;
			}
		}

		if (bullets[i].t >= 1)
		{
			bullets[i].straight = true;
			bullets[i].oblique = false;
			bullets[i].t = 0;
		}
	}
	//更新豌豆直射(straight)时的状态
	for (int i = 0; i < countnormalMax; i++)
	{
		if (bullets[i].used == false || bullets[i].triple == false || bullets[i].straight == false)continue;

		bullets[i].pCur.x += bullets[i].speedstraight;
		//bullets[i].pCur.y = bullets[i].p4.y; 

		//更新直射状态下豌豆的行数
		bullets[i].row = (bullets[i].pCur.y - 77) / 102;

		if (bullets[i].pCur.x > WIN_WIDTH)
		{
			bullets[i].used = false;
			bullets[i].triple = false;
			bullets[i].straight = false;
		}
		if (bullets[i].blast)
		{
			bullets[i].frameIndex++;
			if (bullets[i].frameIndex > 3)
			{
				bullets[i].used = false;
				bullets[i].triple = false;
				bullets[i].straight = false;
				bullets[i].blast = false;
				bullets[i].frameIndex = 0;
			}
		}
	}
}
//更新寒冰豌豆射手的发射
void updateSnowBullets(struct bulletsnow* bullet_snows, int countsnowMax)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	for (int i = 0; i < countsnowMax; i++)
	{
		if (bullet_snows[i].used)
		{
			bullet_snows[i].pCur.x += bullet_snows[i].speed;
			if (bullet_snows[i].pCur.x > WIN_WIDTH)
			{
				bullet_snows[i].used = false;
			}
			if (bullet_snows[i].contant)
			{
				bullet_snows[i].used = false;
			}
		}
	}
}

//创建普通僵尸
void createZMNormal(struct zm* zms, int zmCount)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	//创建普通僵尸
	static int zmFre = 400;
	static int count = 0;
	count++;
	if (count > zmFre)
	{
		count = 0;
		zmFre = rand() % 250 + 100;
		int i;
		for (i = 0; i < zmCount && zms[i].used; i++);
		if (i < zmCount)
		{
			memset(&zms[i], 0, sizeof(zms[i]));
			zms[i].used = true;
			zms[i].dead = false;
			zms[i].x = WIN_WIDTH;
			zms[i].row = rand() % 5;//0...4
			zms[i].y = 77 + (1 + zms[i].row) * 100;
			zms[i].speed = 2.5;
			zms[i].blood = 100;
		}
	}
}
//创建旗子僵尸
void createZMFlag(struct zmFlag* zmFlags, int zmCount)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	//创建旗子僵尸
	int zmCountFlag = 5;
	static int zmFlagFre = 500;
	static int countFlag = 0;
	countFlag++;
	if (countFlag > zmFlagFre)
	{
		countFlag = 0;
		zmFlagFre = rand() % 300 + 200;
		int i;
		for (i = 0; i < zmCountFlag && zmFlags[i].used; i++);
		if (i < zmCountFlag)
		{
			memset(&zmFlags[i], 0, sizeof(zmFlags[i]));
			zmFlags[i].used = true;
			zmFlags[i].dead = false;
			zmFlags[i].x = WIN_WIDTH;
			zmFlags[i].row = rand() % 4;//0...5
			zmFlags[i].y = 77 + (1 + zmFlags[i].row) * 100;
			zmFlags[i].speed = 2.5;
			zmFlags[i].blood = 150;
		}
	}
}
//创建路障僵尸
void createZMConehead(struct zmConehead* zmConeheads, int zmCount)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	//创建路障僵尸
	int zmCountCone = 5;
	static int zmConeFre = 600;
	static int countCone = 0;
	countCone++;
	if (countCone > zmConeFre)
	{
		countCone = 0;
		zmConeFre = rand() % 300 + 300;
		int i;
		for (i = 0; i < zmCountCone && zmConeheads[i].used; i++);
		if (i < zmCountCone)
		{
			memset(&zmConeheads[i], 0, sizeof(zmConeheads[i]));
			zmConeheads[i].used = true;
			zmConeheads[i].dead = false;
			zmConeheads[i].x = WIN_WIDTH;
			zmConeheads[i].row = rand() % 5;//0...4
			zmConeheads[i].y = 77 + (1 + zmConeheads[i].row) * 100;
			zmConeheads[i].speed = 2.5;
			zmConeheads[i].blood = 200;
		}
	}

}
//创建铁桶僵尸
void createZMBuckethead(struct zmBuckethead* zmBucketheads, int zmCount)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	//创建铁桶僵尸
	int zmCountBucket = 5;
	static int zmBucketFre = 300;
	static int countBucket = 0;
	countBucket++;
	if (countBucket > zmBucketFre)
	{
		countBucket = 0;
		zmBucketFre = rand() % 200 + 100;
		int i;
		for (i = 0; i < zmCountBucket && zmBucketheads[i].used; i++);
		if (i < zmCountBucket)
		{
			memset(&zmBucketheads[i], 0, sizeof(zmBucketheads[i]));
			zmBucketheads[i].used = true;
			zmBucketheads[i].dead = false;
			zmBucketheads[i].x = WIN_WIDTH;
			zmBucketheads[i].row = rand() % 5;//0...4
			zmBucketheads[i].y = 77 + (1 + zmBucketheads[i].row) * 100;
			zmBucketheads[i].speed = 2.5;
			zmBucketheads[i].blood = 250;

		}
	}
}

//更新普通僵尸
void updateZMNormal(struct zm* zms, IMAGE* imgEnd, int zmCount)
{
	//更新普通僵尸
	static int count = 0;
	count++;
	if (count > 2)
	{
		count = 0;
		//更新普通僵尸的位置
		for (int i = 0; i < zmCount; i++)
		{
			if (zms[i].used)
			{
				zms[i].x -= zms[i].speed;
				if (zms[i].x < 170 - 130)
				{
					PlaySound("res/lose.wav", NULL, SND_FILENAME | SND_ASYNC);
					printf("GAME OVER\n");
					putimage(0, 0, imgEnd);
					MessageBox(NULL, "over", "over", 0);//待优化
					exit(0);//待优化
				}
			}
		}
	}

	static int count2 = 0;
	count2++;
	if (count2 > 5)
	{
		count2 = 0;
		for (int i = 0; i < zmCount; i++)
		{
			if (zms[i].used)
			{
				if (zms[i].dead)
				{
					zms[i].frameIndex++;
					if (zms[i].frameIndex >= 20)
					{
						zms[i].used = false;
						zms[i].dead = false;
					}
				}
				else if (zms[i].eating)
				{
					zms[i].frameIndex = (zms[i].frameIndex + 1) % 21;
				}
				else if (zms[i].slow)
				{
					zms[i].slowtimer++;
					zms[i].frameIndex = (zms[i].frameIndex + 1) % 22;
					if (zms[i].slowtimer > 10)
					{
						zms[i].slow = false;
						zms[i].speed = 2.5;
					}								
				}
				else
				{
					zms[i].frameIndex = (zms[i].frameIndex + 1) % 22;
				}
			}
		}
	}
}
//更新旗子僵尸
void updateZMFlag(struct zmFlag* zmFlags, IMAGE* imgEnd, int zmCount)
{
	//更新旗子僵尸
	int zmCountFlag = 5;
	static int countFlag = 0;
	countFlag++;
	if (countFlag > 2)
	{
		countFlag = 0;
		//更新旗子僵尸的位置
		for (int i = 0; i < zmCountFlag; i++)
		{
			if (zmFlags[i].used)
			{
				zmFlags[i].x -= zmFlags[i].speed;
				if (zmFlags[i].x < 170 - 112)
				{
					PlaySound("res/lose.wav", NULL, SND_FILENAME | SND_ASYNC);
					printf("GAME OVER\n");
					putimage(0, 0, imgEnd);
					MessageBox(NULL, "over", "over", 0);//待优化
					exit(0);//待优化
				}
			}
		}
	}

	static int countFlag2 = 0;
	countFlag2++;
	if (countFlag2 > 5)
	{
		countFlag2 = 0;
		for (int i = 0; i < zmCountFlag; i++)
		{
			if (zmFlags[i].used)
			{
				if (zmFlags[i].dead)
				{
					zmFlags[i].frameIndex++;
					if (zmFlags[i].frameIndex >= 20)
					{
						zmFlags[i].used = false;
						zmFlags[i].dead = false;
					}
				}
				else if (zmFlags[i].eating)
				{
					zmFlags[i].frameIndex = (zmFlags[i].frameIndex + 1) % 11;
				}
				else if (zmFlags[i].slow)
				{
					zmFlags[i].slowtimer++;
					zmFlags[i].frameIndex = (zmFlags[i].frameIndex + 1) % 12;
					if (zmFlags[i].slowtimer > 10)
					{
						zmFlags[i].slow = false;
						zmFlags[i].speed = 2.5;
					}
				}
				else
				{
					zmFlags[i].frameIndex = (zmFlags[i].frameIndex + 1) % 12;
				}
			}
		}
	}
}
//更新路障僵尸
void updateZMConehead(struct zmConehead* zmConeheads, IMAGE* imgEnd, int zmCount)
{
	//更新路障僵尸
	int zmCountCone = 5;
	static int countCone = 0;
	countCone++;
	if (countCone > 2)
	{
		countCone = 0;
		//更新路障僵尸的位置
		for (int i = 0; i < zmCountCone; i++)
		{
			if (zmConeheads[i].used)
			{
				zmConeheads[i].x -= zmConeheads[i].speed;
				if (zmConeheads[i].x < 170 - 112)
				{
					PlaySound("res/lose.wav", NULL, SND_FILENAME | SND_ASYNC);
					printf("GAME OVER\n");
					putimage(0, 0, imgEnd);
					MessageBox(NULL, "over", "over", 0);//待优化
					exit(0);//待优化
				}
			}
		}
	}

	static int count2Cone = 0;
	count2Cone++;
	if (count2Cone > 5)
	{
		count2Cone = 0;
		for (int i = 0; i < zmCountCone; i++)
		{
			if (zmConeheads[i].used)
			{
				if (zmConeheads[i].dead)
				{
					zmConeheads[i].frameIndex++;
					if (zmConeheads[i].frameIndex >= 20)
					{
						zmConeheads[i].used = false;
						zmConeheads[i].dead = false;
					}
				}
				else if (zmConeheads[i].eating)
				{
					zmConeheads[i].frameIndex = (zmConeheads[i].frameIndex + 1) % 11;
				}
				else if (zmConeheads[i].slow)
				{
					zmConeheads[i].slowtimer++;
					zmConeheads[i].frameIndex = (zmConeheads[i].frameIndex + 1) % 21;
					if (zmConeheads[i].slowtimer > 10)
					{
						zmConeheads[i].slow = false;
						zmConeheads[i].speed = 2.5;
					}
				}
				else
				{
					zmConeheads[i].frameIndex = (zmConeheads[i].frameIndex + 1) % 21;
				}
			}
		}
	}
}
//更新铁桶僵尸
void updateZMBuckethead(struct zmBuckethead* zmBucketheads, IMAGE* imgEnd, int zmCount)
{
	//更新铁桶僵尸
	int zmCountBucket = 5;
	static int countBucket = 0;
	countBucket++;
	if (countBucket > 2)
	{
		countBucket = 0;
		//更新铁桶僵尸的位置
		for (int i = 0; i < zmCountBucket; i++)
		{
			if (zmBucketheads[i].used)
			{
				zmBucketheads[i].x -= zmBucketheads[i].speed;
				if (zmBucketheads[i].x < 170 - 112)
				{
					PlaySound("res/lose.wav", NULL, SND_FILENAME | SND_ASYNC);
					printf("GAME OVER\n");
					putimage(0, 0, imgEnd);
					MessageBox(NULL, "over", "over", 0);//待优化
					exit(0);//待优化
				}
			}
		}
	}

	static int count2Bucket = 0;
	count2Bucket++;
	if (count2Bucket > 5)
	{
		count2Bucket = 0;
		for (int i = 0; i < zmCountBucket; i++)
		{
			if (zmBucketheads[i].used)
			{
				if (zmBucketheads[i].dead)
				{
					zmBucketheads[i].frameIndex++;
					if (zmBucketheads[i].frameIndex >= 20)
					{
						zmBucketheads[i].used = false;
						zmBucketheads[i].dead = false;
					}
				}
				else if (zmBucketheads[i].eating)
				{
					zmBucketheads[i].frameIndex = (zmBucketheads[i].frameIndex + 1) % 11;
				}
				else if (zmBucketheads[i].slow)
				{
					zmBucketheads[i].slowtimer++;
					zmBucketheads[i].frameIndex = (zmBucketheads[i].frameIndex + 1) % 15;
					if (zmBucketheads[i].slowtimer > 10)
					{
						zmBucketheads[i].slow = false;
						zmBucketheads[i].speed = 2.5;
					}
				}
				else
				{
					zmBucketheads[i].frameIndex = (zmBucketheads[i].frameIndex + 1) % 15;
				}
			}
		}
	}
}

//更新辣椒
void updateJalapeno(struct zhiwu(*map)[9])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type == 5)
			{
				if (map[i][j].frameIndex == 7)
				{
					map[i][j].type = 0;
					map[i][j].frameIndex = 0;
					map[i][j].JalapenoExplode = true;
				}
			}
		}
	}
}

//判断是否挑战成功
void checksuccess(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, IMAGE* imgWin)
{
	static int deadtimesNormal = 0;//普通僵尸死亡次数
	static int deadtimesFlag = 0;//旗子僵尸死亡次数
	static int deadtimesCone = 0;//路障僵尸死亡次数
	static int deadtimesBucket = 0;//铁桶僵尸死亡次数

	static int deadsumtimes = 0;//僵尸死亡总次数

	//普通僵尸死亡次数计数
	for (int i = 0; i < zmCount; i++)
	{
		if (zms[i].used == false)continue;

		if (zms[i].blood <= 0 && zms[i].speed == 0 && zms[i].frameIndex == 1 && zms[i].dead)
		{
			deadtimesNormal++;
		}
	}
	//旗子僵尸死亡次数计数
	for (int i = 0; i < zmCountFlag; i++)
	{
		if (zmFlags[i].used == false)continue;

		if (zmFlags[i].blood < 0 && zmFlags[i].speed == 0 && zmFlags[i].frameIndex == 1 && zmFlags[i].dead)
		{
			deadtimesFlag++;
		}
	}
	//路障僵尸死亡次数计数
	for (int i = 0; i < zmCountCone; i++)
	{
		if (zmConeheads[i].used == false)continue;

		if (zmConeheads[i].blood <= 0 && zmConeheads[i].speed == 0 && zmConeheads[i].frameIndex == 1 && zmConeheads[i].dead)
		{
			deadtimesCone++;
		}
	}
	//铁桶僵尸死亡次数计数
	for (int i = 0; i < zmCountBucket; i++)
	{
		if (zmBucketheads[i].used == false)continue;

		if (zmBucketheads[i].blood <= 0 && zmBucketheads[i].speed == 0 && zmBucketheads[i].frameIndex == 1 && zmBucketheads[i].dead)
		{
			deadtimesBucket++;
		}
	}

	deadsumtimes = deadtimesNormal + deadtimesFlag + deadtimesCone + deadtimesBucket;

	if (deadsumtimes > 126)//*要求死亡僵尸数*6*
	{
		PlaySound("res/win.wav", NULL, SND_FILENAME | SND_ASYNC);
		printf("SUCCESS!\n");
		putimage(0, 0, imgWin);
		MessageBox(NULL, "over", "over", 0);//待优化
		exit(0);//待优化
	}
}
