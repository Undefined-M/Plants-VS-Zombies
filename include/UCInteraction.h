#pragma once
void UCInteraction(ExMessage* msg, int* sunshine, struct zhiwu(*map)[9], struct sunshineBalls* balls,
	int* curZhiwu, int* curX, int* curY, IMAGE* imgsunshineBall, int ballMax);

//实现植物的选中与放置
void UserClick(ExMessage* msg, int* sunshine, struct zhiwu(*map)[9], struct sunshineBalls* balls,
	int* curZhiwu, int* curX, int* curY, IMAGE* imgsunshineBall, int ballMax);

//实现阳光的收集
void collectSunshine(ExMessage* msg, struct sunshineBalls* balls, IMAGE* imgsunshineBall, int ballMax);

//游戏开局UI交互(用户点击后开始游戏)
void startUI();