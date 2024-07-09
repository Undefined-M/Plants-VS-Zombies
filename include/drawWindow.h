#pragma once
void drawWindow(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], int* curY, int* curX, int* curZhiwu,
	int* sunshine, struct sunshineBalls* balls, IMAGE* imgsunshineBall, IMAGE* imgZMDead, IMAGE* imgZMEat, IMAGE* imgZMEatFlag,
	IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow,
	IMAGE* imgZMBucketheadSnow, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead, IMAGE* imgZMBuckethead, IMAGE* imgBg,
	IMAGE* imgBar, IMAGE* imgCards, IMAGE* (*imgZhiWu)[20], IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, IMAGE* imgSnowBulletNormal,
	IMAGE* imgJalapenoExplode, IMAGE* imgZmStand, int ballMax, int zmCount, int countnormalMax, int countsnowMax);

//渲染普通僵尸
void drawZMNormal(struct zm* zms, IMAGE* imgZMDead, IMAGE* imgZMEat, IMAGE* imgZMSnow, IMAGE* imgZMNormal,
	int zmCount);
//渲染旗子僵尸
void drawZMFlag(struct zmFlag* zmFlags, IMAGE* imgZMDead, IMAGE* imgZMEatFlag, IMAGE* imgZMSnow,
	IMAGE* imgZMFlag, int zmCount);
//渲染路障僵尸
void drawZMConehead(struct zmConehead* zmConeheads, IMAGE* imgZMDead, IMAGE* imgZMEatConehead,
	IMAGE* imgZMConeheadSnow, IMAGE* imgZMConehead, int zmCount);
//渲染铁桶僵尸
void drawZMBuckethead(struct zmBuckethead* zmBucketheads, IMAGE* imgZMDead,
	IMAGE* imgZMEatBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMBuckethead, int zmCount);

//渲染普通豌豆射手豌豆子弹
void drawSingleBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax);
//渲染双重豌豆射手豌豆子弹
void drawDoubleBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax);
//渲染三重豌豆射手豌豆子弹
void drawThreeBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax);
//渲染寒冰射手豌豆子弹
void drawSnowBullets(struct bulletsnow* bullet_snows, IMAGE* imgSnowBulletNormal, int countsnowMax);

//渲染阳光球(随机降落，向日葵生成，收集阳光)
void drawSunshines(struct sunshineBalls* balls, IMAGE* imgsunshineBall, int ballMax);

//渲染拖动过程中的植物
void drawZhiWuMoving(IMAGE* (*imgZhiWu)[20], int* curZhiwu, int* curY, int* curX);

//渲染放置的植物
void drawZhiWuSetting(struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20]);

//渲染阳光值
void drawSunshineValue(int* sunshine);

//渲染植物卡牌
void drawZhiWuCards(IMAGE* imgCards);

//渲染UI界面
void drawUI(IMAGE* imgBg, IMAGE* imgBar);

//渲染辣椒火焰
void drawJalapenoExplode(struct zhiwu(*map)[9], struct zm* zms, IMAGE* (*imgZhiWu)[20], IMAGE* imgJalapenoExplode, int zmCount);

//片头巡场
void viewScence(IMAGE* imgBg, IMAGE* imgZmStand);