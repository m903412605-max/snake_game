/*******系统头文件*******/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <time.h>		//时间控制函数
#include <windows.h>
#include <stdlib.h>
#include <conio.h>		//键盘输入输出

#include "header.h"

//设置光标位置
void gotoxy(int x, int y)
{
	//坐标结构体类型
	COORD c;

	//横坐标
	c.X = x;
	//纵坐标
	c.Y = y;

	//STD_OUTPUT_HANDLE 表示标准输出
	//c 坐标值
	//GetStdHandle(STD_OUTPUT_HANDLE) 获取当前标准输出句柄
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//更改字体颜色
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}

//开始界面
void welcomeToGame()
{
	gotoxy(43, 10);
	color(11);
	printf("贪 吃 蛇 大 作 战");

	color(12);
	gotoxy(25, 22);
	printf("1.开始游戏");
	gotoxy(45, 22);
	printf("2.游戏说明");
	gotoxy(65, 22);
	printf("3.退出游戏");

	gotoxy(60, 1);
	color(15);
	printf("shiroha_pantsu制作");

	gotoxy(40, 28);
	color(12);
	printf("请输入1-3之间的数");

	int n;
	scanf("%d", &n);	//输入选项	
	//待优化1：输入字符会进入死循环
	switch (n)
	{
	case 1:
		system("cls");	//清屏
		startGame();
		break;
	case 2:
		explanation();

		break;
	case 3:
		exit(0);
		break;
	default:
		gotoxy(40, 28);
		color(12);
		printf("请输入有效的选项,按任意键继续");
		_getch();		//输入任意键
		system("cls");	//清屏
		welcomeToGame();
	}

}

//说明界面
void explanation()
{
	getchar();

	int i = 0;
	int j = 0;

	//清屏
	system("cls");

	//输出标题
	color(13);
	gotoxy(44, 3);
	printf("游戏说明");

	//绘制上下左右边框
	//控制行
	for (i = 6; i <= 22; i++)
	{
		//控制列
		for (j = 20; j <= 75; j++)
		{
			//上下边框 =
			if (i == 6 || i == 22)
			{
				gotoxy(j, i);
				printf("=");
			}
			if (j == 20 || j == 75)
			{
				gotoxy(j, i);
				printf("|");
			}
			
		}
	}

	//输出菜单选项
	color(3);
	gotoxy(30, 8);
	printf("★ 1. 按r重新开始游戏");

	color(5);
	gotoxy(30, 11);
	printf("★ 2. F1加速前进，F2减速前进");

	color(11);
	gotoxy(30, 14);
	printf("★ 3. 使用暂停游戏或者继续游戏");

	color(13);
	gotoxy(30, 17);
	printf("★ 4. 使用方向键控制前进的方向");

	color(14);
	gotoxy(30, 20);
	printf("★ 5. 按下ESC键退出游戏");

	//输出提示信息
	color(12);
	gotoxy(20, 24);
	printf("按下回车键返回主界面");
	getchar();
	system("cls");
	welcomeToGame();

}

//绘制地图
void createMap()
{
	int i = 0;
	int j = 0;

	//清屏
	system("cls");

	//控制行
	for (i = 0; i <= 26; i++)
	{
		//控制列
		for (j = 0; j <= 56; j = j + 2)
		{
			//定位光标
			gotoxy(j, i);
			if (0 == i || 26 == i || 0 == j || 56 == j)
			{
				color(5);
				printf("□");
			}
			else
			{
				color(3);
				printf("■");
			}
		}
	}
}

//侧边栏信息
void printscore()
{
	//显示当前得分
	color(14);
	gotoxy(64, 2);
	printf("当前得分: %d", score);
}

void printtips()
{
	//显示历史最高得分
	color(14);
	gotoxy(64, 3);
	FILE* fp;
	int highestscore;
	fp = fopen("save.txt", "r");
	fscanf(fp, "%d", &highestscore);
	printf("历史最高: %d", highestscore);
	fclose(fp);

	//显示温馨提示
	color(12);
	gotoxy(72, 5);
	printf("温 馨 提 示");

	//绘制上下边框
	color(10);
	gotoxy(60, 7);
	printf("==================================");

	gotoxy(60, 19);
	printf("==================================");

	//输出提示信息
	color(13);
	gotoxy(64, 8);
	printf("※ 吃掉每个食物得分: %d", add);

	gotoxy(64, 10);
	printf("※ 按r重新开始游戏");

	gotoxy(64, 12);
	printf("※ F1加速前进，F2减速前进");

	gotoxy(64, 14);
	printf("※ 使用空格暂停游戏或者继续游戏");

	gotoxy(64, 16);
	printf("※ 使用↓↑→←控制前进的方向");

	gotoxy(64, 18);
	printf("※ 按下b返回标题");

}

//游戏失败界面
void lostDraw()
{
	int i = 0;
	system("cls");

	//显示游戏失败提示
	color(12);
	gotoxy(44, 3);
	printf("游 戏 失 败!!!");

	//设置边框的颜色
	color(11);
	gotoxy(17, 5);

	//绘制上边框
	printf("+----------------------------------------------------------------+");

	//绘制下边框
	gotoxy(17, 20);
	printf("+----------------------------------------------------------------+");

	//绘制左右边框
	for (i = 6; i < 20; i++)
	{
		gotoxy(17, i);
		printf("|");

		gotoxy(82, i);
		printf("|");
	}
}

//初始化蛇
void initSnake()
{
	SNAKE* body;

	int i;
	for (i = 0;i < 4;i++)
	{
		body = (SNAKE*)malloc(sizeof(SNAKE));
		//检查是否分配内存成功
		if (body == NULL)
		{
			printf("初始化蛇身失败...");
			exit(0);
		}
		memset(body, 0, sizeof(SNAKE));

		//为蛇身赋值
		body->x = 24 + i * 2;
		body->y = 5;

		//将蛇身链接为链表
		body->next = head;
		head = body;	//此处直接赋值head即可，因为head是全局变量

		//遍历链表
		SNAKE* p = head;
		while (p != NULL)
		{
			color(14);
			gotoxy(p->x, p->y);

			if (p == head)printf("●");
			else printf("㈩");

			p = p->next;
		}

	}
	
}

//保存分数
void saveScore()
{
	FILE* fp=NULL;
	fp = fopen("save.txt", "w");
	if (fp == NULL)
	{
		printf("保存失败\n");
		exit(0);
	}

	fprintf(fp, "%d", score);
	fclose(fp);
}

//随机生成食物
void createFood()
{
	SNAKE* food_drop;
	srand((unsigned)time(NULL));
	food_drop = (SNAKE*)malloc(sizeof(SNAKE));
	
	//列为偶数，保证食物在网格线上
	do {
		food_drop->x = rand() % 53 + 2;   
	} while (food_drop->x % 2 != 0);
	food_drop->y = rand() % 25 + 1;

	//判断生成食物是否跟蛇身重合
	SNAKE* p = head;
	while (p->next != NULL)
	{
		if (p->x == food_drop->x && p->y == food_drop->y)
		{
			free(food_drop);
			createFood();
		}
		p = p->next;
	}

	//显示食物
	gotoxy(food_drop->x, food_drop->y);
	color(12);
	printf("$");
	food = food_drop;
	
}

//蛇的移动
void snakeMove()

{
	SNAKE* new = NULL;
	SNAKE* tmp = NULL;
	SNAKE* save = NULL;

	//分配新的节点
	new = malloc(sizeof(SNAKE));
	if (NULL == new)
	{
		printf("malloc failed...\n");
		exit(0);
	}
	memset(new, 0, sizeof(SNAKE));

	//向上
	if (UP == direction)
	{
		new->x = head->x;
		new->y = head->y - 1;
	}

	//向下
	if (DOWN == direction)
	{
		new->x = head->x;
		new->y = head->y + 1;
	}

	//向左
	if (LEFT == direction)
	{
		new->x = head->x - 2;
		new->y = head->y;
	}

	//向右
	if (RIGHT == direction)
	{
		new->x = head->x + 2;
		new->y = head->y;
	}

	new->next = head;
	head = new;

	tmp = head;
	color(14);

	//判断是否为食物
	if ((new->x == food->x) && (food->y == new->y))
	{
		//循环画出蛇
		while (NULL != tmp)
		{
			gotoxy(tmp->x, tmp->y);
			if (head == tmp)
			{
				printf("●");
			}
			else
			{
				printf("㈩");
			}

			tmp = tmp->next;
		}

		score = score + add;
		printscore();
		createFood();
	}
	else
	{
		while (NULL != tmp->next)
		{
			gotoxy(tmp->x, tmp->y);
			if (head == tmp)
			{
				printf("●");
			}
			else
			{
				printf("㈩");
			}

			save = tmp;
			tmp = tmp->next;
		}

		gotoxy(tmp->x, tmp->y);
		color(3);
		printf("■");

		save->next = NULL;
		free(tmp);
	}
}

//撞墙
int crossWall()
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		return 1;
	}
	else return 0;
}

//咬到自己
int biteSelf()
{
	SNAKE* p = head->next;
	while (p != NULL)
	{
		if ((head->x == p->x) && (head->y == p->y))
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//加速和减速
void speedUp()
{
	if (sleeptime >= 100)
	{
		sleeptime -= 100;
		add += 1;
	}
}

void speedDown()
{
	if (sleeptime <= 1000)
	{
		sleeptime += 100;
		add -= 1;
	}
}

//游戏控制
void gameControl()
{
	while (1)	//使用一个死循环持续接受输入
	{
		//方向键控制蛇移动
		if (GetAsyncKeyState(VK_UP) && direction != DOWN)
		{
			direction = UP;
		}
		if (GetAsyncKeyState(VK_DOWN) && direction != UP)
		{
			direction = DOWN;
		}
		if (GetAsyncKeyState(VK_LEFT) && direction != RIGHT)
		{
			direction = LEFT;
		}
		if (GetAsyncKeyState(VK_RIGHT) && direction != LEFT)
		{
			direction = RIGHT;
		}

		//空格暂停继续游戏
		if (GetAsyncKeyState(VK_SPACE))
		{
			while (1)
			{
				Sleep(100);
				if (GetAsyncKeyState(VK_SPACE))
				{
					break;
				}
			}
		}

		//使用r键重新开始游戏
		if (GetAsyncKeyState('R'))
		{	
			system("cls");
			destorySnake();
			startGame();
			
			break;
		}

		//按b返回标题
		if (GetAsyncKeyState('B'))
		{
			system("cls");
			destorySnake();
			welcomeToGame();
			
			break;
		}
		//这里有bug，不管是回到标题还是结束游戏r和b都会被输入到控制台中

		//加速和减速
		if (GetAsyncKeyState(VK_F1))
		{
			speedUp();
			printtips();
		}
		if (GetAsyncKeyState(VK_F2))
		{
			speedDown();
			printtips();
		}

		//esc退出游戏
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			endgame = ESC;
			gameOver();
			break;
		}

		//蛇的自动前进
		Sleep(sleeptime);
		snakeMove();

		//判断游戏失败
		if (crossWall() == 1)
		{
			endgame = HITWALL;
			gameOver();
			break;
		}
		if (biteSelf() == 1)
		{
			endgame = HITSELF;
			gameOver();
			break;
		}
	}
}

//游戏开始
void startGame()
{
	createMap();
	printscore();
	printtips();
	initSnake();
	createFood();

	gameControl();
}

//游戏结束
void gameOver()
{
	FILE* fp;
	int highestscore;
	fp = fopen("save.txt", "r");
	fscanf(fp, "%d", &highestscore);
	fclose(fp);

	int n;
	lostDraw();

	color(12);
	gotoxy(38, 9);

	//不同的状态 显示不同失败提示 endStatus
	switch (endgame)
	{
	case HITWALL:
		printf("您撞到墙了，游戏结束!!!");
		break;
	case HITSELF:
		printf("您咬到蛇身了，游戏结束!!!");
		break;
	case ESC:
		printf("您已经结束了游戏，游戏结束!!!");
		break;
	}

	//显示得分
	color(13);
	gotoxy(43, 12);
	printf("您的得分: %d", score);

	//显示最高分
	if (score > highestscore)
	{
		color(10);
		gotoxy(38, 16);
		printf("恭喜你，您已经破纪录了。");

		//将最高分写入文件
		saveScore();
	}
	else
	{
		color(10);
		gotoxy(38, 16);
		printf("加油哦， 离最高分还差%d分", highestscore - score);
	}

	//结束后的选择
	gotoxy(25, 23);
	color(12);
	printf("再玩一局请输入：1");

	gotoxy(52, 23);
	printf("直接退出请输入：2");

	gotoxy(46, 25);
	color(11);
	printf("请选择: ");

	while (1)
	{
		scanf("%d", &n);
		getchar();

		if (n == 1)
		{
			score = 0;
			add = 5;
			sleeptime = 500;
			destorySnake();
			startGame();
		}
		else if (n == 2)
		{
			exit(0);
		}
		else
		{
			gotoxy(30, 27);
			color(12);
			printf("您的输入有误，请重新输入，按下回车键继续");
			getchar();
		}
	}
}

//销毁蛇
void destorySnake()
{
	SNAKE* tmp = head;
	SNAKE* tmp2;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}

	head = NULL;
}



int main(int argc, char* argv[])
{
	welcomeToGame();
	return 0;
}
