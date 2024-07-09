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

	//������Ϸ��ͼ�δ���	
	initgraph(WIN_WIDTH, WIN_HIGHTH, 1);

	//������Ƭ
	Loadimage(imgBg, imgBar, imgEnd, imgWin, imgZhiWu, imgCards, imgsunshineBall, imgBulletNormal, imgZMNormal, imgZMFlag,
		imgZMConehead, imgZMBuckethead, imgZMSnow, imgZMFlagSnow, imgZMConeheadSnow, imgZMBucketheadSnow, imgZMEat, imgZMEatFlag,
		imgZMEatConehead, imgZMEatBuckethead, imgBulletBlast, imgJalapenoExplode, imgZMDead, imgZmStand, imgBulletSnow); 

	//��ʼ������
	InitData(zms, zmFlags, zmConeheads, zmBucketheads, bullet_snows, map, imgZhiWu, imgCards, balls, bullets, curY, curZhiwu, sunshine);

	//��������ֵ����
	SetSunValueFont();

	//�����������
	srand(time(NULL));
}

//������Ƭ����
void Loadimage(IMAGE* imgBg, IMAGE* imgBar, IMAGE* imgEnd, IMAGE* imgWin, IMAGE* (*imgZhiWu)[20], IMAGE* imgCards,
	IMAGE* imgsunshineBall, IMAGE* imgBulletNormal, IMAGE* imgZMNormal, IMAGE* imgZMFlag, IMAGE* imgZMConehead,
	IMAGE* imgZMBuckethead, IMAGE* imgZMSnow, IMAGE* imgZMFlagSnow, IMAGE* imgZMConeheadSnow, IMAGE* imgZMBucketheadSnow,
	IMAGE* imgZMEat, IMAGE* imgZMEatFlag, IMAGE* imgZMEatConehead, IMAGE* imgZMEatBuckethead, IMAGE* imgBulletBlast,
	IMAGE* imgJalapenoExplode, IMAGE* imgZMDead, IMAGE* imgZmStand, IMAGE* imgSnowBulletNormal)
{
	//���ر���ͼƬ
	loadimage(imgBg, "res/map0.jpg");//��ͼͼƬ
	loadimage(imgBar, "res/bar5.png");//ֲ����ͼƬ
	loadimage(imgEnd, "res/fail2.png");//��Ϸ��������
	loadimage(imgWin, "res/gameWin.png");//��Ϸʤ������

	char name[64];//�����ַ�������洢��Ƭ�����ļ�·��

	//������������ʱ��֡ͼƬ
	for (int i = 0; i < 35; i++)
	{
		sprintf_s(name, sizeof(name), "res/JalapenoExplode/%d.png", i);
		loadimage(&imgJalapenoExplode[i], name);
	}

	//������ײ���㶹�ӵ���֡ͼƬ(ͨ��һ����Ƭ���ϷŴ������ɢЧ��)
	loadimage(&imgBulletBlast[3], "res/bullets/bullet_blast.png");
	for (int i = 0; i < 3; i++)
	{
		float k = (i + 1) * 0.4;
		loadimage(&imgBulletBlast[i], "res/bullets/bullet_blast.png",
			imgBulletBlast[3].getwidth() * k,
			imgBulletBlast[3].getheight() * k,
			true);
	}

	//���ؽ�ʬ����״̬��ͼƬ
	/*����״̬*/
	for (int i = 0; i < 22; i++)//��ͨ��ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_normal/%d.png", i + 1);
		loadimage(&imgZMNormal[i], name);
	}
	for (int i = 0; i < 12; i++)//���ӽ�ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_flag/%d.png", i + 1);
		loadimage(&imgZMFlag[i], name);
	}
	for (int i = 0; i < 21; i++)//·�Ͻ�ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_conehead/%d.png", i + 1);
		loadimage(&imgZMConehead[i], name);
	}
	for (int i = 0; i < 15; i++)//��Ͱ��ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_buckethead/%d.png", i + 1);
		loadimage(&imgZMBuckethead[i], name);
	}
	/*����״̬(�����㶹���ֻ��к�)*/
	for (int i = 0; i < 22; i++)//��ͨ��ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_snow/%d.png", i + 1);
		loadimage(&imgZMSnow[i], name);
	}
	for (int i = 0; i < 12; i++)//���ӽ�ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_snow_flag/%d.png", i + 1);
		loadimage(&imgZMFlagSnow[i], name);
	}
	for (int i = 0; i < 21; i++)//·�Ͻ�ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_snow_conehead/%d.png", i + 1);
		loadimage(&imgZMConeheadSnow[i], name);
	}
	for (int i = 0; i < 15; i++)//��Ͱ��ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_snow_buckethead/%d.png", i + 1);
		loadimage(&imgZMBucketheadSnow[i], name);
	}
	/*��ֲ��״̬*/
	for (int i = 0; i < 21; i++)//��ͨ��ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_eat/%d.png", i + 1);
		loadimage(&imgZMEat[i], name);
	}
	for (int i = 0; i < 11; i++)//���ӽ�ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_eat_flag/%d.png", i + 1);
		loadimage(&imgZMEatFlag[i], name);
	}
	for (int i = 0; i < 11; i++)//·�Ͻ�ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_eat_conehead/%d.png", i + 1);
		loadimage(&imgZMEatConehead[i], name);
	}
	for (int i = 0; i < 11; i++)//��Ͱ��ʬ
	{
		sprintf_s(name, sizeof(name), "res/zm_eat_buckethead/%d.png", i + 1);
		loadimage(&imgZMEatBuckethead[i], name);
	}
	/*����״̬*/
	for (int i = 0; i < 20; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm_dead/%d.png", i + 1);
		loadimage(&imgZMDead[i], name);
	}
	/*ƬͷѲ����ʬ״̬*/
	for (int i = 0; i < 11; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm_stand/%d.png", i + 1);
		loadimage(&imgZmStand[i], name);
	}

	//�����������֡ͼƬ
	for (int i = 0; i < 29; i++)
	{
		sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
		loadimage(&imgsunshineBall[i], name);
	}

	//������ͨ�㶹�ӵ���ͼƬ
	loadimage(imgBulletNormal, "res/bullets/bullet_normal.png");
	//���غ����㶹�ӵ���ͼƬ
	loadimage(imgSnowBulletNormal, "res/bullets/bullet_snownormal.png");
}

//��ʼ�����ݺ���
void InitData(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20], IMAGE* imgCards, struct sunshineBalls* balls,
	struct bullet* bullets, int* curY, int* curZhiwu, int* sunshine)
{
	//ָ�������ʼ������ 
	memset(imgZhiWu, 0, sizeof(imgZhiWu)); 
	//��ʼ��ֲ���״̬ 
	memset(map, 0, sizeof(map)); 
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++) 
		{
			map[i][j].catched = false; 
			map[i][j].JalapenoExplode = false; 
		}
	}

	//��ʼ������������
	memset(balls, 0, sizeof(balls));
	for (int i = 0; i < 10; i++)
	{
		balls[i].used = false;//���е��������Ƿ���ʹ��
	}

	//��ʼ����ͨ��ʬ����
	memset(zms, 0, sizeof(zms));
	for (int i = 0; i < 10; i++)
	{
		zms[i].used = false;
		zms[i].eating = false;
		zms[i].slow = false;
		zms[i].blood = 100;//��ͨ��ʬ��ʼ����ֵ
	}
	//��ʼ�����ӽ�ʬ����
	memset(zmFlags, 0, sizeof(zmFlags));
	for (int i = 0; i < 10; i++)
	{
		zmFlags[i].used = false;
		zmFlags[i].eating = false;
		zmFlags[i].slow = false;
		zmFlags[i].blood = 150;//���ӽ�ʬ��ʼ����ֵ
	}
	//��ʼ��·�Ͻ�ʬ����
	memset(zmConeheads, 0, sizeof(zmConeheads));
	for (int i = 0; i < 10; i++)
	{
		zmConeheads[i].used = false;
		zmConeheads[i].eating = false;
		zmConeheads[i].slow = false;
		zmConeheads[i].blood = 200;//·�Ͻ�ʬ��ʼ����ֵ
	}
	//��ʼ����Ͱ��ʬ����
	memset(zmBucketheads, 0, sizeof(zmBucketheads));
	for (int i = 0; i < 10; i++)
	{
		zmBucketheads[i].used = false;
		zmBucketheads[i].eating = false;
		zmBucketheads[i].slow = false;
		zmBucketheads[i].blood = 250;//��Ͱ��ʬ��ʼ����ֵ
	}

	//��ʼ����ͨ�ӵ�����
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

	//��ʼ�������ӵ�����
	memset(bullet_snows, 0, sizeof(bullet_snows));
	for (int i = 0; i < 30; i++)
	{
		bullet_snows[i].contant = false;
		bullet_snows[i].used = false;
	}

	//��ʼ������ֵ�ĳ�ֵ��ֲ�￨�Ƶ�ѡ�����(0/1)
	*curZhiwu = 0;
	*sunshine = 1000;
}

//��������ֵ���庯��
void SetSunValueFont()
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 15;
	strcpy(f.lfFaceName, "Segoe UI Black");
	f.lfQuality = ANTIALIASED_QUALITY;//�����Ч��
	settextstyle(&f);
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	setcolor(BLACK);
}

//�ж��ļ��Ƿ����
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