#pragma once
void updateGame(struct zhiwu(*map)[9], struct sunshineBalls* balls, struct zm* zms, struct zmFlag* zmFlags,
	struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads, struct bullet* bullets, struct bulletsnow* bullet_snows,
	int* sunshine, IMAGE* (*imgZhiWu)[20], IMAGE* imgEnd, IMAGE* imgsunshineBall, IMAGE* imgZMNormal, int ballMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int countnormalMax, int countsnowMax, int dangerX, IMAGE* imgWin);

//����ֲ����ֲ���״̬
void upodateZhiWuState(struct zhiwu(*map)[9], IMAGE* (*imgZhiWu)[20]);

//ʵ����ͨ�ӵ��Խ�ʬ����ײ���
void checkNormalBullet2Zm(struct bullet* bullets, struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int countnormalMax, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket);

//ʵ�ֺ����ӵ��Խ�ʬ����ײ���
void checkSnowBullet2Zm(struct bulletsnow* bullet_snows, struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int countnormalMax, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket);

//ʵ�����������뽩ʬ�ĽӴ����
void checkFlame2Zm(struct zhiwu(*map)[9], struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads,
	struct zmBuckethead* zmBucketheads, int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);

//ʵ�ֽ�ʬ��ֲ�����ײ���
void checkZm2ZhiWu(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct zhiwu(*map)[9], int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket);

//�ж��Ƿ���ս�ɹ�
void checksuccess(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, IMAGE* imgWin);

//ʵ����ͨ�㶹���ֵķ���
void shoot_single(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);
//ʵ��˫���㶹���ֵķ���
void shoot_double(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);
//ʵ�������㶹���ֵķ���
void shoot_three(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bullet* bullets, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countnormalMax, int zmCount,
	int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);
//ʵ�ֺ����㶹���ֵķ���
void shoot_snow(struct zm* zms, struct zmFlag* zmFlags, struct zmConehead* zmConeheads, struct zmBuckethead* zmBucketheads,
	struct bulletsnow* bullet_snows, struct zhiwu(*map)[9], IMAGE* imgZMNormal, IMAGE* (*imgZhiWu)[20], int countsnowMax,
	int zmCount, int zmCountFlag, int zmCountCone, int zmCountBucket, int dangerX);

//������ͨ�㶹���ֵķ���
void updateSingleBullets(struct bullet* bullets, int countnormalMax);
//����˫���㶹���ֵķ���
void updateDoubleBullets(struct bullet* bullets, int countnormalMax);
//���������㶹���ֵķ���
void updateThreeBullets(struct bullet* bullets, int countnormalMax);
//���º����㶹���ֵķ���
void updateSnowBullets(struct bulletsnow* bullet_snows, int countsnowMax);

//������ͨ��ʬ
void createZMNormal(struct zm* zms, int zmCount);
//�������ӽ�ʬ
void createZMFlag(struct zmFlag* zmFlags, int zmCount);
//����·�Ͻ�ʬ
void createZMConehead(struct zmConehead* zmConeheads, int zmCount);
//������Ͱ��ʬ
void createZMBuckethead(struct zmBuckethead* zmBucketheads, int zmCount);

//������ͨ��ʬ
void updateZMNormal(struct zm* zms, IMAGE* imgEnd, int zmCount);
//�������ӽ�ʬ
void updateZMFlag(struct zmFlag* zmFlags, IMAGE* imgEnd, int zmCount);
//����·�Ͻ�ʬ
void updateZMConehead(struct zmConehead* zmConeheads, IMAGE* imgEnd, int zmCount);
//������Ͱ��ʬ
void updateZMBuckethead(struct zmBuckethead* zmBucketheads, IMAGE* imgEnd, int zmCount);

//����������
void createSunshine(struct sunshineBalls* balls, struct zhiwu(*map)[9],
	IMAGE* (*imgZhiWu)[20], IMAGE* imgsunshineBall, int ballMax);
//����������
void updateSunshine(struct sunshineBalls* balls, int* sunshine, int ballMax);

//��������
void updateJalapeno(struct zhiwu(*map)[9]);