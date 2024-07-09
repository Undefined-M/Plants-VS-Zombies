// 在 Struct.h 头文件中声明结构体
#ifndef STRUCT_H
#define STRUCT_H

//普通僵尸的数据类型
struct zm
{
	int x, y;
	int row;
	int frameIndex;
	bool used;
	int speed;
	int blood;
	bool dead;
	bool eating;
	bool slow;
	int slowtimer;
};
//旗子僵尸的数据类型
struct zmFlag
{
	int x, y;
	int row;
	int frameIndex;
	bool used;
	int speed;
	int blood;
	bool dead;
	bool eating;
	bool slow;
	int slowtimer;
};
//路障僵尸的数据类型
struct zmConehead
{
	int x, y;
	int row;
	int frameIndex;
	bool used;
	int speed;
	int blood;
	bool dead;
	bool eating;
	bool slow;
	int slowtimer;
};
//铁桶僵尸的数据类型
struct zmBuckethead
{
	int x, y;
	int row;
	int frameIndex;
	bool used;
	int speed;
	int blood;
	bool dead;
	bool eating;
	bool slow;
	int slowtimer;
};

//普通豌豆子弹的数据类型(普通豌豆射手，双重射手，三重射手的子弹库)
struct bullet
{
	int row;
	bool used;
	int speed;
	bool blast;//子弹是否发生爆炸
	int frameIndex;

	bool single;//子弹是否单发(*普通豌豆射手)
	bool repeater;//子弹是否两连发(*双重射手)
	bool triple;//子弹是否三连发(*三重射手)

	float t;//贝塞尔曲线的时间点0...1(*三重射手)
	vector2 p1, p4;//斜射时的起始位置

	vector2 pCur;//当前时刻子弹的位置

	bool oblique;//子弹斜射状态(*三重射手)
	bool straight;//子弹直射状态(*三重射手)

	float speedoblique;//斜射状态的速度(*三重射手)
	float speedstraight;//直射状态的速度(*三重射手)
};

//寒冰豌豆子弹的数据类型(寒冰射手的子弹库)
struct bulletsnow
{
	vector2 pCur;//当前时刻子弹的位置
	int row;
	bool used;
	int speed;
	bool contant;//子弹是否与僵尸接触
	int frameIndex;
};

struct zhiwu
{
	int type;		//0:没有植物 1：选择了第一种植物
	int frameIndex;	//植物抖动状态的序列帧序号
	bool catched;//是否被僵尸捕获
	int deadTime;//死亡计数器

	int timer;
	int x, y;

	bool JalapenoExplode;//辣椒是否燃烧
	int JalapenoframeIndex;//辣椒燃烧状态的序列帧序号
};

//阳光球的数据类型
struct sunshineBalls
{
	int x, y;
	int frameIndex;//当前显示的图片帧的序号
	int destY;//阳光房飘落的目标位置的y坐标
	bool used;//是否在使用
	int timer;//定时器


	float t;//贝塞尔曲线的时间点0...1
	vector2 p1, p2, p3, p4;

	vector2 pCur;//当前时刻阳光球的位置
	float speed;
	int status;
};

enum { SUNSHINE_DOWN, SUNSHINE_GROUND, SUNSHINE_COLLECT, SUNSHINE_PRODUCT };
enum { WAN_DOU_1, XIANG_RI_KUI, WAN_DOU_2, WAN_DOU_3, JALAPENO, WAN_DOU_4,ZHI_WU_COUNT };

#endif

