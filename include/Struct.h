// �� Struct.h ͷ�ļ��������ṹ��
#ifndef STRUCT_H
#define STRUCT_H

//��ͨ��ʬ����������
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
//���ӽ�ʬ����������
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
//·�Ͻ�ʬ����������
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
//��Ͱ��ʬ����������
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

//��ͨ�㶹�ӵ�����������(��ͨ�㶹���֣�˫�����֣��������ֵ��ӵ���)
struct bullet
{
	int row;
	bool used;
	int speed;
	bool blast;//�ӵ��Ƿ�����ը
	int frameIndex;

	bool single;//�ӵ��Ƿ񵥷�(*��ͨ�㶹����)
	bool repeater;//�ӵ��Ƿ�������(*˫������)
	bool triple;//�ӵ��Ƿ�������(*��������)

	float t;//���������ߵ�ʱ���0...1(*��������)
	vector2 p1, p4;//б��ʱ����ʼλ��

	vector2 pCur;//��ǰʱ���ӵ���λ��

	bool oblique;//�ӵ�б��״̬(*��������)
	bool straight;//�ӵ�ֱ��״̬(*��������)

	float speedoblique;//б��״̬���ٶ�(*��������)
	float speedstraight;//ֱ��״̬���ٶ�(*��������)
};

//�����㶹�ӵ�����������(�������ֵ��ӵ���)
struct bulletsnow
{
	vector2 pCur;//��ǰʱ���ӵ���λ��
	int row;
	bool used;
	int speed;
	bool contant;//�ӵ��Ƿ��뽩ʬ�Ӵ�
	int frameIndex;
};

struct zhiwu
{
	int type;		//0:û��ֲ�� 1��ѡ���˵�һ��ֲ��
	int frameIndex;	//ֲ�ﶶ��״̬������֡���
	bool catched;//�Ƿ񱻽�ʬ����
	int deadTime;//����������

	int timer;
	int x, y;

	bool JalapenoExplode;//�����Ƿ�ȼ��
	int JalapenoframeIndex;//����ȼ��״̬������֡���
};

//���������������
struct sunshineBalls
{
	int x, y;
	int frameIndex;//��ǰ��ʾ��ͼƬ֡�����
	int destY;//���ⷿƮ���Ŀ��λ�õ�y����
	bool used;//�Ƿ���ʹ��
	int timer;//��ʱ��


	float t;//���������ߵ�ʱ���0...1
	vector2 p1, p2, p3, p4;

	vector2 pCur;//��ǰʱ���������λ��
	float speed;
	int status;
};

enum { SUNSHINE_DOWN, SUNSHINE_GROUND, SUNSHINE_COLLECT, SUNSHINE_PRODUCT };
enum { WAN_DOU_1, XIANG_RI_KUI, WAN_DOU_2, WAN_DOU_3, JALAPENO, WAN_DOU_4,ZHI_WU_COUNT };

#endif

