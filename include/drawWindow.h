#pragma once
void drawWindow(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], int* curY, int* curX, int* curZhiwu,
	int* sunshine, struct sunshineBalls* balls, IMAGE* imgsunshineBall, IMAGE* imgZMDead, IMAGE* imgZMEat, IMAGE* imgZMEatFlag,
	IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow,
	IMAGE* imgZMBucketheadSnow, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead, IMAGE* imgZMBuckethead, IMAGE* imgBg,
	IMAGE* imgBar, IMAGE* imgCards, IMAGE* (*imgZhiWu)[20], IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, IMAGE* imgSnowBulletNormal,
	IMAGE* imgJalapenoExplode, IMAGE* imgZmStand, int ballMax, int zmCount, int countnormalMax, int countsnowMax);

//��Ⱦ��ͨ��ʬ
void drawZMNormal(struct zm* zms, IMAGE* imgZMDead, IMAGE* imgZMEat, IMAGE* imgZMSnow, IMAGE* imgZMNormal,
	int zmCount);
//��Ⱦ���ӽ�ʬ
void drawZMFlag(struct zmFlag* zmFlags, IMAGE* imgZMDead, IMAGE* imgZMEatFlag, IMAGE* imgZMSnow,
	IMAGE* imgZMFlag, int zmCount);
//��Ⱦ·�Ͻ�ʬ
void drawZMConehead(struct zmConehead* zmConeheads, IMAGE* imgZMDead, IMAGE* imgZMEatConehead,
	IMAGE* imgZMConeheadSnow, IMAGE* imgZMConehead, int zmCount);
//��Ⱦ��Ͱ��ʬ
void drawZMBuckethead(struct zmBuckethead* zmBucketheads, IMAGE* imgZMDead,
	IMAGE* imgZMEatBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMBuckethead, int zmCount);

//��Ⱦ��ͨ�㶹�����㶹�ӵ�
void drawSingleBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax);
//��Ⱦ˫���㶹�����㶹�ӵ�
void drawDoubleBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax);
//��Ⱦ�����㶹�����㶹�ӵ�
void drawThreeBullets(struct bullet* bullets, IMAGE* imgBulletBlast, IMAGE* imgBulletNormal, int countnormalMax);
//��Ⱦ���������㶹�ӵ�
void drawSnowBullets(struct bulletsnow* bullet_snows, IMAGE* imgSnowBulletNormal, int countsnowMax);

//��Ⱦ������(������䣬���տ����ɣ��ռ�����)
void drawSunshines(struct sunshineBalls* balls, IMAGE* imgsunshineBall, int ballMax);

//��Ⱦ�϶������е�ֲ��
void drawZhiWuMoving(IMAGE* (*imgZhiWu)[20], int* curZhiwu, int* curY, int* curX);

//��Ⱦ���õ�ֲ��
void drawZhiWuSetting(struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20]);

//��Ⱦ����ֵ
void drawSunshineValue(int* sunshine);

//��Ⱦֲ�￨��
void drawZhiWuCards(IMAGE* imgCards);

//��ȾUI����
void drawUI(IMAGE* imgBg, IMAGE* imgBar);

//��Ⱦ��������
void drawJalapenoExplode(struct zhiwu(*map)[9], struct zm* zms, IMAGE* (*imgZhiWu)[20], IMAGE* imgJalapenoExplode, int zmCount);

//ƬͷѲ��
void viewScence(IMAGE* imgBg, IMAGE* imgZmStand);