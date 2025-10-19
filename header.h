#ifndef _HEADER_H_
#define _HEADER_H_

/*���峣��*/
//�ߵ�״̬
#define UP 1	//��
#define DOWN 2	//��
#define LEFT 3	//��
#define RIGHT 4	//��

//��Ϸ���������
#define HITWALL 1
#define HITSELF 2
#define ESC 3

/*******����ȫ�ֱ���********/
/*�ṹ�����*/
typedef struct snake
{
	int x;	//����
	int y;
	struct snake* next;	//ָ����һ������
}SNAKE;	//��������
	


/*��ͨ����*/
int score = 0;
int add = 5;
SNAKE* head = NULL;
SNAKE* food = NULL;
int direction = RIGHT;
DWORD sleeptime = 500;
int endgame = 0;

/*******��������*******/
void gotoxy(int x, int y);
int color(int c);
void welcomeToGame();
void createMap();
void printscore();
void printtips();
void initSnake();
void createFood();
int biteSelf();
int crossWall();
void speedUp();
void speedDown();
void snakeMove();
void gameControl();
void lostDraw();
void gameOver();
void explanation();
void saveScore();
void startGame();
void destorySnake();



#endif

