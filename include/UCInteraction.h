#pragma once
void UCInteraction(ExMessage* msg, int* sunshine, struct zhiwu(*map)[9], struct sunshineBalls* balls,
	int* curZhiwu, int* curX, int* curY, IMAGE* imgsunshineBall, int ballMax);

//ʵ��ֲ���ѡ�������
void UserClick(ExMessage* msg, int* sunshine, struct zhiwu(*map)[9], struct sunshineBalls* balls,
	int* curZhiwu, int* curX, int* curY, IMAGE* imgsunshineBall, int ballMax);

//ʵ��������ռ�
void collectSunshine(ExMessage* msg, struct sunshineBalls* balls, IMAGE* imgsunshineBall, int ballMax);

//��Ϸ����UI����(�û������ʼ��Ϸ)
void startUI();