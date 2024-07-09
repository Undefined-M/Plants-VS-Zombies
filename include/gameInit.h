#pragma once
void gameInit(IMAGE* imgBg, IMAGE* imgBar, IMAGE* imgEnd, IMAGE* imgWin, IMAGE* (*imgZhiWu)[20], IMAGE* imgCards,
	IMAGE* imgsunshineBall, IMAGE* imgBulletNormal, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead,
	IMAGE* imgZMBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow, IMAGE* imgZMBucketheadSnow,
	IMAGE* imgZMEat, IMAGE* imgZMEatFlag, IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgBulletBlast,
	IMAGE* imgJalapenoExplode, IMAGE* imgZMDead, IMAGE* imgZmStand, IMAGE* imgSnowBulletNormal, struct zm* zms,
	struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads, struct bulletsnow* bullet_snows,
	struct zhiwu(*map)[9], struct sunshineBalls* balls, struct bullet* bullets, int* curY, int* curZhiwu, int* sunshine);

//加载照片函数
void Loadimage(IMAGE* imgBg, IMAGE* imgBar, IMAGE* imgEnd, IMAGE* imgWin, IMAGE* (*imgZhiWu)[20], IMAGE* imgCards,
	IMAGE* imgsunshineBall, IMAGE* imgBulletNormal, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead,
	IMAGE* imgZMBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow, IMAGE* imgZMBucketheadSnow,
	IMAGE* imgZMEat, IMAGE* imgZMEatFlag, IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgBulletBlast,
	IMAGE* imgJalapenoExplode, IMAGE* imgZMDead, IMAGE* imgZmStand, IMAGE* imgSnowBulletNormal);

//初始化数据函数
void InitData(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20], IMAGE* imgCards, struct sunshineBalls* balls,
	struct bullet* bullets, int* curY, int* curZhiwu, int* sunshine);

//设置阳光值字体函数
void SetSunValueFont();

//判断文件是否存在
bool fileExist(const char* name);