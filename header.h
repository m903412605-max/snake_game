#ifndef _HEADER_H_
#define _HEADER_H_

/*定义常量*/
//蛇的状态
#define UP 1	//上
#define DOWN 2	//下
#define LEFT 3	//左
#define RIGHT 4	//右

//游戏结束的情况
#define HITWALL 1
#define HITSELF 2
#define ESC 3

/*******定义全局变量********/
/*结构体变量*/
typedef struct snake
{
	int x;	//坐标
	int y;
	struct snake* next;	//指向下一节蛇身
}SNAKE;	//定义蛇身
	


/*普通变量*/
int score = 0;
int add = 5;
SNAKE* head = NULL;
SNAKE* food = NULL;
int direction = RIGHT;
DWORD sleeptime = 500;
int endgame = 0;

/*******函数声明*******/
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

