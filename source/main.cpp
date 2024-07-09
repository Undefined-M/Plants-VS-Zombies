#include "AllHeader.h"

int main(void)
{
	int WIN_WIDTH = 900;
	int WIN_HIGHTH = 600;

	/*����IMAGE���͵ı��������飬ָ���������洢.jpg/.png�ļ�(ͼƬ֡)*/
	IMAGE imgBg;//��ʾ����ͼƬ
	IMAGE imgBar;//��ʾֲ��������ͼƬ
	IMAGE imgEnd;//��սʧ�ܱ���ͼƬ
	IMAGE imgWin;//��ս�ɹ�����ͼƬ
	IMAGE imgCards[ZHI_WU_COUNT];//ֲ�￨��ͼƬ
	IMAGE* imgZhiWu[ZHI_WU_COUNT][20];//����ֲ����ֲ���֡ͼƬ 
	IMAGE imgsunshineBall[29];//�������֡ͼƬ 
	//��ͨ��ʬ
	IMAGE imgZMNormal[22];//��ͨ��ʬ����ʱ��֡ͼƬ
	IMAGE imgZMSnow[22];//��ͨ��ʬ���������ֻ��м���ʱ��֡ͼƬ
	IMAGE imgZMDead[20];//��ʬ����ʱ��֡ͼƬ
	IMAGE imgZMEat[21];//��ͨ��ʬ��ֲ��ʱ��֡ͼƬ
	IMAGE imgZmStand[11];//ƬͷѲ�������н�ʬ��֡ͼƬ
	//���ӽ�ʬ(����״̬����ͨ��ʬ��ͼƬһ��)
	IMAGE imgZMFlag[12];//���ӽ�ʬ����ʱ��֡ͼƬ
	IMAGE imgZMFlagSnow[12];//���ӽ�ʬ���������ֻ��м���ʱ��֡ͼƬ
	IMAGE imgZMEatFlag[11];//���ӽ�ʬ��ֲ��ʱ��֡ͼƬ
	//·�Ͻ�ʬ(����״̬����ͨ��ʬ��ͼƬһ��) 
	IMAGE imgZMConehead[21];//·�Ͻ�ʬ����ʱ��֡ͼƬ
	IMAGE imgZMConeheadSnow[21];//·�Ͻ�ʬ���������ֻ��м���ʱ��֡ͼƬ 
	IMAGE imgZMEatConehead[11];//·�Ͻ�ʬ��ֲ��ʱ��֡ͼƬ 
	//��Ͱ��ʬ(����״̬����ͨ��ʬ��ͼƬһ��)
	IMAGE imgZMBuckethead[15];//��Ͱ��ʬ����ʱ��֡ͼƬ
	IMAGE imgZMBucketheadSnow[15];//��Ͱ��ʬ���������ֻ��м���ʱ��֡ͼƬ
	IMAGE imgZMEatBuckethead[11];//��Ͱ��ʬ��ֲ��ʱ��֡ͼƬ
	//��ͨ�㶹(����ײ��ı�ըЧ��)
	IMAGE imgBulletNormal;//��ͨ�㶹�ӵ���ͼƬ
	IMAGE imgBulletBlast[4];//��ͨ�㶹�ӵ���ײ��ը��֡ͼƬ
	//�����㶹
	IMAGE imgBulletSnow;//�����㶹�ӵ���ͼƬ
	//����ȼ��״̬
	IMAGE imgJalapenoExplode[35];//����ȼ��ʱ�����֡ͼƬ
	
	/*����ṹ�����͵�����*/
	struct zhiwu map[5][9];
	//10��������
	struct sunshineBalls  balls[10];
	//10����ͨ��ʬ
	struct zm zms[10];
	//5�����ӽ�ʬ
	struct zmFlag zmFlags[5];
	//5��·�Ͻ�ʬ
	struct zmConehead zmConeheads[5];
	//5����Ͱ��ʬ
	struct zmBuckethead zmBucketheads[5];
	//100����ͨ�㶹
	struct bullet bullets[100];
	//30�������㶹
	struct bulletsnow bullet_snows[30];
	 
	int curX, curY = 0;//��ǰѡ��ֲ�����ƶ������е�λ��
	int curZhiwu = 0;//0��û��ѡ�У�1��ѡ���˵�һ��ֲ�� 
	int sunshine = 0;//�������ڴ�������ֵ�����ͱ���
	ExMessage msg; 

	//��Ϸ��ʼ��ģ��
	gameInit(&imgBg, &imgBar, &imgEnd, &imgWin, imgZhiWu, imgCards, imgsunshineBall, &imgBulletNormal, imgZMNormal, imgZMFlag,
		imgZMConehead, imgZMBuckethead, imgZMSnow, imgZMFlagSnow, imgZMConeheadSnow, imgZMBucketheadSnow, imgZMEat, imgZMEatFlag,
		imgZMEatConehead, imgZMEatBuckethead, imgBulletBlast, imgJalapenoExplode, imgZMDead, imgZmStand, &imgBulletSnow,
		zms, zmFlags, zmConeheads, zmBucketheads, bullet_snows, map, balls, bullets, &curY, &curZhiwu, &sunshine);
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
	//��ʼ��ֲ�￨��
	char name[64];//�����ַ�������洢�ļ���
	for (int i = 0; i < ZHI_WU_COUNT; i++)
	{
		//����ֲ�￨�Ƶ��ļ���
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);

		for (int j = 0; j < 20; j++)
		{
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//���ж�����ļ��Ƿ���ڣ����ļ���
			if (fileExist(name))
			{
				imgZhiWu[i][j] = new IMAGE;//�����ڴ�
				loadimage(imgZhiWu[i][j], name);
			}
			else
			{
				break;
			}
		}
	}

	/*���岢��ʼ��IMAGE���ͺ�������ṹ�����͵�ָ�����(*���ڴ���)*/
	IMAGE* imgCardsptr = imgCards;//ֲ�￨��
	IMAGE* (*imgZhiWuptr)[20] = imgZhiWu;
	IMAGE* imgsunshineBallptr = imgsunshineBall;//������
	//��ͨ��ʬ
	IMAGE* imgZMNormalptr = imgZMNormal;
	IMAGE* imgZMSnowptr = imgZMSnow;
	IMAGE* imgZMDeadptr = imgZMDead;
	IMAGE* imgZMEatptr = imgZMEat;
	IMAGE* imgZmStandptr = imgZmStand;
	//���ӽ�ʬ
	IMAGE* imgZMFlagptr = imgZMFlag;
	IMAGE* imgZMFlagSnowptr = imgZMFlagSnow; 
	IMAGE* imgZMEatFlagptr = imgZMEatFlag;
	//·�Ͻ�ʬ
	IMAGE* imgZMConeheadptr = imgZMConehead;
	IMAGE* imgZMConeheadSnowptr = imgZMConeheadSnow; 
	IMAGE* imgZMEatConeheadptr = imgZMEatConehead;
	//��Ͱ��ʬ
	IMAGE* imgZMBucketheadptr = imgZMBuckethead;
	IMAGE* imgZMBucketheadSnowptr = imgZMBucketheadSnow; 
	IMAGE* imgZMEatBucketheadptr = imgZMEatBuckethead;
	//��ͨ�㶹��ը״̬
	IMAGE* imgBulletBlastptr = imgBulletBlast;
	//����ȼ��״̬
	IMAGE* imgJalapenoExplodeptr = imgJalapenoExplode;

	struct zhiwu(*mapptr)[9] = map;
	//������
	struct sunshineBalls* ballsptr = balls;
	//��ͨ��ʬ
	struct zm* zmsptr = zms;
	//���ӽ�ʬ
	struct zmFlag* zmFlagsptr = zmFlags;
	//·�Ͻ�ʬ
	struct zmConehead* zmConeheadsptr = zmConeheads;
	//��Ͱ��ʬ
	struct zmBuckethead* zmBucketheadsptr = zmBucketheads;
	//��ͨ�㶹
	struct bullet* bulletsptr = bullets;
	//�����㶹
	struct bulletsnow* bullet_snowsptr = bullet_snows;

	/*���������򣬺����㶹�ӵ�����ͨ�㶹�ӵ�����ʬ������(*����)*/
	int ballMax = sizeof(balls) / sizeof(balls[0]); //����������
	int countsnowMax = sizeof(bullet_snows) / sizeof(bullet_snows[0]);//�����㶹�ӵ�����
	int countnormalMax = sizeof(bullets) / sizeof(bullets[0]);//��ͨ�㶹�ӵ�����
	int zmCount = sizeof(zms) / sizeof(zms[0]);//��ͨ��ʬ����
	int zmCountFlag = sizeof(zmFlags) / sizeof(zmFlags[0]);//���ӽ�ʬ������
	int zmCountCone = sizeof(zmConeheads) / sizeof(zmConeheads[0]);//·�Ͻ�ʬ������
	int zmCountBucket = sizeof(zmBucketheads) / sizeof(zmBucketheads[0]);//��Ͱ��ʬ������
	int dangerX = WIN_WIDTH - imgZMNormal[0].getwidth() + 50;//���㽩ʬ��Σ�վ��� 

	int timer = 0;
	bool flag = true;
	while (1)
	{
		//UI����ģ��
		UCInteraction(&msg, &sunshine, mapptr, ballsptr, &curZhiwu, &curX, &curY, imgsunshineBallptr, ballMax);

		timer += getDelay();//�Ż�����������ٶ�
		if (timer > 35)
		{
			flag = true;
			timer = 0;
		}
		if (flag)
		{
			flag = false;				
			//��Ϸ��Ⱦͼ��ģ��
			drawWindow(zmsptr, zmFlagsptr, zmConeheadsptr, zmBucketheadsptr, bulletsptr, bullet_snowsptr, mapptr, &curY, &curX,
				&curZhiwu, &sunshine, ballsptr, imgsunshineBallptr, imgZMDeadptr, imgZMEatptr, imgZMEatFlagptr, imgZMEatConeheadptr,
				imgZMEatBucketheadptr, imgZMSnowptr, imgZMFlagSnowptr, imgZMConeheadSnowptr, imgZMBucketheadSnowptr, imgZMNormalptr,
				imgZMFlagptr, imgZMConeheadptr, imgZMBucketheadptr, &imgBg, &imgBar, imgCardsptr, imgZhiWuptr, imgBulletBlastptr,
				&imgBulletNormal, &imgBulletSnow, imgJalapenoExplodeptr, imgZmStandptr, ballMax, zmCount, countnormalMax,
				countsnowMax);
			//��Ϸ��������ģ��
			updateGame(mapptr, ballsptr, zmsptr, zmFlagsptr, zmConeheadsptr, zmBucketheadsptr, bulletsptr, bullet_snowsptr,
				&sunshine, imgZhiWuptr, &imgEnd, imgsunshineBallptr, imgZMNormalptr, ballMax, zmCount, zmCountFlag, zmCountCone,
				zmCountBucket, countnormalMax, countsnowMax, dangerX, &imgWin);
		}
	}
	system("pause");
	return 0;
}