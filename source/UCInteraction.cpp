#include "AllHeader.h"

void UCInteraction(ExMessage* msg, int* sunshine, struct zhiwu(*map)[9], struct sunshineBalls* balls,
	int* curZhiwu, int* curX, int* curY, IMAGE* imgsunshineBall, int ballMax)
{
	//游戏开局UI交互(用户点击后开始游戏)
	startUI();
	//植物的选中与放置,阳光的收集
	UserClick(msg, sunshine, map, balls, curZhiwu, curX, curY, imgsunshineBall, ballMax);
}

//实现植物的选中与放置
void UserClick(ExMessage* msg, int* sunshine, struct zhiwu(*map)[9], struct sunshineBalls* balls,
	int* curZhiwu, int* curX, int* curY, IMAGE* imgsunshineBall, int ballMax)
{
	static int status = 0;
	if (peekmessage(msg))//判断有没有消息
	{
		if (msg->message == WM_LBUTTONDOWN)
		{
			if (msg->x > 336 && msg->x < 336 + 65 * ZHI_WU_COUNT && msg->y < 96)
			{
				int index = (msg->x - 336) / 65;

				*curZhiwu = index + 1;
				if (*curZhiwu == 1 && *sunshine >= 100)
				{
					status = 1;
				}
				else if (*curZhiwu == 2 && *sunshine >= 50)
				{
					status = 1;
				}
				else if (*curZhiwu == 3 && *sunshine >= 175)
				{
					status = 1;
				}
				else if (*curZhiwu == 4 && *sunshine >= 200)
				{
					status = 1;
				}
				else if (*curZhiwu == 5 && *sunshine >= 125)
				{
					status = 1;
				}
				else if (*curZhiwu == 6 && *sunshine >= 325)
				{
					status = 1;
				}
			}
			else
			{
				collectSunshine(msg, balls, imgsunshineBall, ballMax);
			}
		}
		else if (msg->message == WM_MOUSEMOVE)
		{
			*curX = msg->x;
			*curY = msg->y;
		}
		else if (msg->message == WM_LBUTTONUP)
		{
			if (msg->x > 256 - 112 && msg->y > 88 && msg->y < 580)
			{
				int row = (msg->y - 88) / 102;//计算鼠标的行坐标
				int col = (msg->x - (256 - 112)) / 81;//计算鼠标的列坐标

				if (map[row][col].type == 0)
				{
					if (status == 1)
					{
						map[row][col].type = *curZhiwu;
						map[row][col].frameIndex = 0;
						if (*curZhiwu == 1)
						{
							PlaySound("res/plant1.wav", NULL, SND_FILENAME | SND_ASYNC);
							(*sunshine) -= 100;
							if (*sunshine < 0)
							{
								*sunshine = 0;
							}
						}
						else if (*curZhiwu == 2)
						{
							PlaySound("res/plant1.wav", NULL, SND_FILENAME | SND_ASYNC);
							(*sunshine) -= 50;
							if (*sunshine < 0)
							{
								*sunshine = 0;
							}
						}
						else if (*curZhiwu == 3)
						{
							PlaySound("res/plant1.wav", NULL, SND_FILENAME | SND_ASYNC);
							(*sunshine) -= 175;
							if (*sunshine < 0)
							{
								*sunshine = 0;
							}
						}
						else if (*curZhiwu == 4)
						{
							PlaySound("res/plant1.wav", NULL, SND_FILENAME | SND_ASYNC);
							(*sunshine) -= 200;
							if (*sunshine < 0)
							{
								*sunshine = 0;
							}
						}
						else if (*curZhiwu == 5)
						{
							PlaySound("res/jalapeno.wav", NULL, SND_FILENAME | SND_ASYNC);
							(*sunshine) -= 125;
							if (*sunshine < 0)
							{
								*sunshine = 0;
							}
						}
						else if (*curZhiwu == 6)
						{
							PlaySound("res/plant1.wav", NULL, SND_FILENAME | SND_ASYNC);
							(*sunshine) -= 325;
							if (*sunshine < 0)
							{
								*sunshine = 0;
							}
						}
					}
					map[row][col].x = 256 - 112 + col * 81;
					map[row][col].y = 77 + row * 102 + 10;
				}
			}
			*curZhiwu = 0;
			status = 0;
		}
	}
}

//实现阳光的收集
void collectSunshine(ExMessage* msg, struct sunshineBalls* balls, IMAGE* imgsunshineBall, int ballMax)
{
	int w = imgsunshineBall[0].getwidth();
	int h = imgsunshineBall[0].getheight();
	for (int i = 0; i < ballMax; i++)
	{
		if (balls[i].used)
		{
			int x = balls[i].pCur.x;
			int y = balls[i].pCur.y;

			if (msg->x > x && msg->x<x + w && msg->y>y && msg->y < y + h)
			{
				balls[i].status = SUNSHINE_COLLECT;

				PlaySound("res/sunshine.wav", NULL, SND_FILENAME | SND_ASYNC);

				balls[i].p1 = balls[i].pCur;
				balls[i].p4 = vector2(262, 0);
				balls[i].t = 0;
				float distance = dis(balls[i].p1 - balls[i].p4);
				float off = 10;
				balls[i].speed = 1.0 / (distance / off);
				break;
			}
		}
	}
}

//游戏开局UI交互(用户点击后开始游戏)
void startUI()
{   
	static int times = 0;
	if (times == 0) 
	{
		times++;
		IMAGE imgBg, imgMenu1, imgMenu2;
		loadimage(&imgBg, "res/menu.png");
		loadimage(&imgMenu1, "res/menu1.png");
		loadimage(&imgMenu2, "res/menu2.png");
		int flag = 0;
		while (1)
		{
			BeginBatchDraw();
			putimage(0, 0, &imgBg);
			putimagePNG(474, 75, flag ? &imgMenu2 : &imgMenu1);

			ExMessage msg;
			if (peekmessage(&msg))
			{
				if (msg.message == WM_LBUTTONDOWN
					&& msg.x > 474 && msg.x < 474 + 300
					&& msg.y>75 && msg.y < 75 + 140)
				{
					flag = 1;
				}
				else if (msg.message == WM_LBUTTONUP && flag)
				{
					EndBatchDraw();
					break;
				}
			}
			EndBatchDraw();
		}
	}
}