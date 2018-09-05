#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <iostream> 
#include <windows.h> 
#include<conio.h>
#include <conio.h>

// '-'

int mapWidth = 52;
int mapHeight = 22;
char map[52][22] = {" "};
int gameScore = 0;
int gameTime = 0;
bool eadFood = true;
int foodX = 0;
int foodY = 0;
bool gameOver = true;
int snakeLength = 1;
// 移动方向
int moveDirec;	

typedef struct snake
{
	int x;
	int y;
	struct snake *next;
} snakeList,*SnakeList;

SnakeList snakehead;

void snakeCreate() {
	snakehead = (SnakeList)malloc(sizeof(snakeList));
	SnakeList node = (SnakeList)malloc(sizeof(snakeList));
	snakehead->next = node;
	node->x = 25;
	node->y = 10;
	node->next = NULL;

	SnakeList node2 = (SnakeList)malloc(sizeof(snakeList));
	node->next = node2;
	node2->x = 26;
	node2->y = 10;
	node2->next = NULL;
}

/**
游戏欢迎界面
*/
void welcomeAnimation()
{
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t\t");
	printf("贪吃蛇游戏");
	printf("\n\t\t\t\t");
	printf("\tloading...");
	Sleep(4000);
}

/**
随机生成食物函数
*/
void generateFood()
{
	if (eadFood == true)
	{
		srand(time(0));
		foodX = rand() % 50 + 1;
		foodY = rand() % 20 + 1;
		//printf("%d %d -", foodX, foodY);
		map[foodX][foodY] = '*';
	}
}

/**
游戏地图边界绘图

*/
void mapBorderDraw()
{
	system("cls");
	printf("\n\n\n\n");

	SnakeList snakenode = snakehead->next;

	while (snakenode != NULL)
	{
		int w = 0, h = 0;
		w = snakenode->x;
		h = snakenode->y;
		map[w][h] = '*';
		snakenode = snakenode->next;
	}

	for (int h = 0; h < mapHeight; h++)
	{
		printf("\n\t\t\t");
		for (int w = 0; w < mapWidth; w++)
		{

			
			

			if (h == 0 || h == mapHeight - 1) 
			{
				map[w][h] = '*';
			}
			if (w == 0 && h > 0 && h < mapHeight - 1)
			{
				map[w][h] = '*';
			}
			if (w == mapWidth - 1 && h > 0 && h < mapHeight - 1)
			{
				map[w][h] = '*';
			}




			//打印地图
			printf("%c", map[w][h]);
			map[w][h] = ' ';
		}
		if (h == 5)
		{
			printf("\t  分数:%d", gameScore);
		}
		if (h == 8)
		{
			printf("\t  时间:%d", gameTime);
		}
	}

}

/**
snake 移动
   0
 1   2
   3
*/
void snakeMove(int direction) {


	SnakeList snakenode = snakehead->next;

	SnakeList lastnode = snakenode;
	int x = snakenode->x;
	int y = snakenode->y;
	int minx;
	int miny;
	//printf("--- %d %d\n", lastnode->x, lastnode->y);
//	SnakeList minnode;
	switch (direction)
	{
	case 0:
		snakenode->y = snakenode->y - 1;
		snakenode = snakenode->next;
		//printf("136 %d %d\n", snakenode->x, snakenode->y);
		while (snakenode != NULL)
		{
			minx = snakenode->x;
			miny = snakenode->y;
			snakenode->x = x;
			snakenode->y = y;
			x = minx;
			y = miny;
			snakenode = snakenode->next;
		/*	snakenode->y = lastnode->y;   lastnode 这个节点会根据snakenode最新
		的数据跟着变。。。xxx
			minnode = snakenode;
			snakenode->x = lastnode->x;
			printf("141 %d %d\n", snakenode->x, lastnode->x);
			snakenode->y = lastnode->y;
			printf("143 %d %d\n", snakenode->y, lastnode->y);
			lastnode = minnode;
			snakenode = snakenode->next;
			*/
		}
		break;
	case 1: 
		snakenode->x = snakenode->x - 1;
		snakenode = snakenode->next;
		while (snakenode != NULL)
		{
			minx = snakenode->x;
			miny = snakenode->y;
			snakenode->x = x;
			snakenode->y = y;
			x = minx;
			y = miny;
			snakenode = snakenode->next;
		}
		break;
	case 2:
		snakenode->y = snakenode->y + 1;
		snakenode = snakenode->next;
		while (snakenode != NULL)
		{
			minx = snakenode->x;
			miny = snakenode->y;
			snakenode->x = x;
			snakenode->y = y;
			x = minx;
			y = miny;
			snakenode = snakenode->next;
		}
		break;
	case 3:
		snakenode->x = snakenode->x + 1;
		snakenode = snakenode->next;
		while (snakenode != NULL)
		{
			minx = snakenode->x;
			miny = snakenode->y;
			snakenode->x = x;
			snakenode->y = y;
			x = minx;
			y = miny;
			snakenode = snakenode->next;
		}
		break;
	default: 
		break;
	}
}

void test1()
{
	SnakeList snakenode1 = snakehead->next;
	while (snakenode1 != NULL)
	{
		printf(" %d %d", snakenode1->x, snakenode1->y);
		snakenode1 = snakenode1->next;
	}
	printf("\n ---\n");
}

/**
游戏引擎和控制
*/
void gameEngineAndControl()
{
	int ch1 = 0;
	int ch2 = 0;
	while (gameOver)
	{
		printf("direction :%d \n", moveDirec);
		snakeMove(moveDirec);
		mapBorderDraw();
		//test1();
		if (_kbhit()) {
			ch1 = _getch();
			if (ch1 == 27) {
				break;
			}
			ch2 = _getch();
			switch (ch2)
			{
			// case 27: printf("gameover"); gameOver = true; break;
			case 72: printf("The key you Pressed is : ↑ \n");
				if (moveDirec == 1 || moveDirec == 3) {
					moveDirec = 0;
				}
				break;
			case 80: printf("The key you Pressed is : ↓ \n");
				if (moveDirec == 1 || moveDirec == 3) {
					moveDirec = 2;
				}
				break;
			case 75: printf("The key you Pressed is : ← \n");
				if (moveDirec == 0 || moveDirec == 2) {
					moveDirec = 1;
				}
				break;
			case 77: printf("The key you Pressed is : → \n");
				if (moveDirec == 0 || moveDirec == 2) {
					moveDirec = 3;
				}
				break;
			default: printf("No direction keys detected \n"); 
				break;
			}
		}
		Sleep(1000); //暂停1秒
	}
}
/**
游戏参数初始化
*/
void gameInit() 
{
	snakeCreate();
	//welcomeAnimation();
	generateFood();
	//mapBorderDraw();
	gameEngineAndControl();
	
}

/**
move test point test 
*/
void test()
{
	snakeCreate();

	SnakeList snakenode1 = snakehead->next;
	while (snakenode1 != NULL)
	{
		printf(" %d %d", snakenode1->x, snakenode1->y);
		snakenode1 = snakenode1->next;
	}
	printf("\n ---\n");

	snakeMove(3);
	SnakeList snakenode = snakehead->next;
	while (snakenode != NULL)
	{
		printf(" %d %d", snakenode->x, snakenode->y);
		snakenode = snakenode->next;
	}
	printf("\n");
}


int main()
{
	gameInit();
	//test();
	system("pause");
	return 0;
}