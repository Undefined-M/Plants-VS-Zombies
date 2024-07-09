#pragma once
void gameInit(IMAGE* imgBg, IMAGE* imgBar, IMAGE* imgEnd, IMAGE* imgWin, IMAGE* (*imgZhiWu)[20], IMAGE* imgCards,
	IMAGE* imgsunshineBall, IMAGE* imgBulletNormal, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead,
	IMAGE* imgZMBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow, IMAGE* imgZMBucketheadSnow,
	IMAGE* imgZMEat, IMAGE* imgZMEatFlag, IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgBulletBlast,
	IMAGE* imgJalapenoExplode, IMAGE* imgZMDead, IMAGE* imgZmStand, IMAGE* imgSnowBulletNormal, struct zm* zms,
	struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads, struct bulletsnow* bullet_snows,
	struct zhiwu(*map)[9], struct sunshineBalls* balls, struct bullet* bullets, int* curY, int* curZhiwu, int* sunshine);

//������Ƭ����
void Loadimage(IMAGE* imgBg, IMAGE* imgBar, IMAGE* imgEnd, IMAGE* imgWin, IMAGE* (*imgZhiWu)[20], IMAGE* imgCards,
	IMAGE* imgsunshineBall, IMAGE* imgBulletNormal, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead,
	IMAGE* imgZMBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow, IMAGE* imgZMBucketheadSnow,
	IMAGE* imgZMEat, IMAGE* imgZMEatFlag, IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgBulletBlast,
	IMAGE* imgJalapenoExplode, IMAGE* imgZMDead, IMAGE* imgZmStand, IMAGE* imgSnowBulletNormal);

//��ʼ�����ݺ���
void InitData(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20], IMAGE* imgCards, struct sunshineBalls* balls,
	struct bullet* bullets, int* curY, int* curZhiwu, int* sunshine);

//��������ֵ���庯��
void SetSunValueFont();

//�ж��ļ��Ƿ����
bool fileExist(const char* name);