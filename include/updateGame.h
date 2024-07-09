#pragma once
void updateGame(struct zhiwu(*map)[9], struct sunshineBalls* balls, struct zm* zms, struct zmFlag* zmFlags,
	struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads, struct bullet* bullets, struct bulletsnow* bullet_snows,
	int* sunshine, IMAGE* (*imgZhiWu)[20], IMAGE* imgEnd, IMAGE* imgsunshineBall, IMAGE* imgZMNormal, int ballMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int countnormalMax, int countsnowMax, int dangerX, IMAGE* imgWin);

//更新植物种植后的状态
void upodateZhiWuState(struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20]);

//实现普通子弹对僵尸的碰撞检测
void checkNormalBullet2Zm(struct bullet* bullets, struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int countnormalMax, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket);

//实现寒冰子弹对僵尸的碰撞检测
void checkSnowBullet2Zm(struct bulletsnow* bullet_snows, struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int countnormalMax, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket);

//实现辣椒火焰与僵尸的接触检测
void checkFlame2Zm(struct zhiwu(*map)[9], struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);

//实现僵尸对植物的碰撞检测
void checkZm2ZhiWu(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct zhiwu(*map)[9], int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket);

//判断是否挑战成功
void checksuccess(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, IMAGE* imgWin);

//实现普通豌豆射手的发射
void shoot_single(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);
//实现双重豌豆射手的发射
void shoot_double(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);
//实现三重豌豆射手的发射
void shoot_three(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);
//实现寒冰豌豆射手的发射
void shoot_snow(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countsnowMax,
	int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);

//更新普通豌豆射手的发射
void updateSingleBullets(struct bullet* bullets, int countnormalMax);
//更新双重豌豆射手的发射
void updateDoubleBullets(struct bullet* bullets, int countnormalMax);
//更新三重豌豆射手的发射
void updateThreeBullets(struct bullet* bullets, int countnormalMax);
//更新寒冰豌豆射手的发射
void updateSnowBullets(struct bulletsnow* bullet_snows, int countsnowMax);

//创建普通僵尸
void createZMNormal(struct zm* zms, int zmCount);
//创建旗子僵尸
void createZMFlag(struct zmFlag* zmFlags, int zmCount);
//创建路障僵尸
void createZMConehead(struct zmConehead* zmConeheads, int zmCount);
//创建铁桶僵尸
void createZMBuckethead(struct zmBuckethead* zmBucketheads, int zmCount);

//更新普通僵尸
void updateZMNormal(struct zm* zms, IMAGE* imgEnd, int zmCount);
//更新旗子僵尸
void updateZMFlag(struct zmFlag* zmFlags, IMAGE* imgEnd, int zmCount);
//更新路障僵尸
void updateZMConehead(struct zmConehead* zmConeheads, IMAGE* imgEnd, int zmCount);
//更新铁桶僵尸
void updateZMBuckethead(struct zmBuckethead* zmBucketheads, IMAGE* imgEnd, int zmCount);

//创建阳光球
void createSunshine(struct sunshineBalls* balls, struct zhiwu(*map)[9],
	IMAGE* (*imgZhiWu)[20], IMAGE* imgsunshineBall, int ballMax);
//更新阳光球
void updateSunshine(struct sunshineBalls* balls, int* sunshine, int ballMax);

//更新辣椒
void updateJalapeno(struct zhiwu(*map)[9]);