#include <graphics.h>
#include <ctime>
#include <iostream>
#include <cassert>
#include "classA.h"
#include "public.h"
#include "System.h"
#include <Windows.h>
using namespace std;


//
//class Realize
//{
//
//private:
//
//
//public:
//	
////绘制木板
//void drawBoard(Board* pBoard);
//
////初始化地图
//void initMap(int map[][8], int row, int cols);
//
////控制木板左右移动
//void keyDown(Board* pBoard);
//
////绘制砖块
//void drawMap(int map[][8], int row, int cols);
//
////绘制球
//void drawBall(Ball* pBall);
//
////移动球
//void moveBall(Ball* pBall, Board* pBaord, int map[][8],int row,int cols);
//
////定时器
//int Timer(int duration, int id);
//
//};
// 
//绘制木板



//int main()
//{
//	srand((unsigned int)time(NULL));
//	initgraph(800, 600);
//	int map[5][8];
//	Board* pBoard = createBoard(300, 600 - 25, 200, 25, WHITE);
//	 Ball* pBall = createBall(400, 300, 10, 5, -5, RED);
//	initMap(map, 5, 8);
//	BeginBatchDraw();
//	while (1)
//	{
//
//		cleardevice();	//清屏
//		drawMap(map, 5, 8);
//		drawBoard(pBoard);
//		drawBall(pBall);
//		if (Timer(20, 0))
//			moveBall(pBall, pBoard, map, 5, 8);
//		keyDown(pBoard);
//		//Sleep(10);		//程序停留20毫秒
//		if (gameOver(pBall, pBoard))
//		{
//			outtextxyInfo(300, 350, "你输了!.....");
//			FlushBatchDraw();
//			break;
//		}
//		if (windGame(map, 5, 8))
//		{
//			outtextxyInfo(300, 350, "你赢了!.....");
//			FlushBatchDraw();
//			break;
//		}
//		FlushBatchDraw();   //显示已经画好的
//	}
//	Sleep(5000);
//	EndBatchDraw();         //不调用FlushBatchDraw 只有EndBatchDraw后才能显示
//	//显示
//	closegraph();
//	return 0;
//}


class Board
{
public:
	int x;
	int y;
	int w;
	int h;
	COLORREF color;
};

class Board* createBoard(int x, int y, int w, int h, COLORREF color)
{
	Board* board = new Board;
	assert(board);
	board->x = x;
	board->y = y;
	board->w = w;
	board->h = h;
	board->color = color;
	return board;
}

class Ball
{
public:
	int x;
	int y;
	int r;
	int dx;
	int dy;
	unsigned long color;
};

class Ball* createBall(int x, int y, int r, int dx, int dy, unsigned long color)
{
	Ball* pBall = new Ball;
	assert(pBall);
	pBall->x = x;
	pBall->y = y;
	pBall->r = r;
	pBall->dx = dx;
	pBall->dy = dy;
	pBall->color = color;
	return pBall;
}

class Map
{
public:
	Map() {}
	
	//初始化地图
	void initMap(int map[][8], int row, int cols);
	//绘制地图
	void drawMap(int map[][8], int row, int cols);
	//绘制木板
	void drawBoard(Board* pBoard);
	//绘制球
	void drawBall(Ball* pBall);
};



class Move
{
public:
	
	//移动球
	void moveBall(Ball* pBall, Board* pBaord, int map[][8], int row, int cols);
	//球击中木板后
	int hitBoard(Ball* pBall, Board* pBoard);
	//球击中墙后
	int hitBricks(Ball* pBall, int map[][8], int row, int cols);
};


class System
{
public:
	//按键操作,控制木板左右移
	void keyDown(Board* pBoard);

	//计时器
	int Timer(int duration, int id);

	//游戏结束
	int gameOver(Ball* pBall, Board* pBoard);

	//游戏结束的文字显示
	void outtextxyInfo(int x, int y, const char* info);

	//游戏胜利
	int windGame(int map[][8], int row, int cols);

};

void Map::drawBoard(Board* pBoard)
{
	setfillcolor(pBoard->color);
	//木板的x , y 坐标 , 木板的坐标加上 宽度 和高度 
	solidrectangle(pBoard->x, pBoard->y, pBoard->x + pBoard->w, pBoard->y + pBoard->h);
}

void Map::initMap(int map[][8], int row, int cols)
{
	for (int i = 0; i < row; i++) 

	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = rand() % 3 + 1; //[1,3]
		}
	}
}

void Map::drawMap(int map[][8], int row, int cols)
{
	setlinecolor(BLACK);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int x = 100 * j;
			int y = 25 * i;
			switch (map[i][j])
			{
			case 0:
				break;
			case 1:
				setfillcolor(RGB(255, 255, 85));
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 2:
				setfillcolor(RGB(85, 255, 85));
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 3:
				setfillcolor(RGB(85, 85, 255));
				fillrectangle(x, y, x + 100, y + 25);
				break;
			}
		}
	}
}

void System::keyDown(Board* pBoard) 
{
	//修改木板的坐标
	//_getch()
	//使用异步处理函数 , 按键控制
	if((GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) && pBoard->x > 0) 
	{
		pBoard->x -= 1;
	}
	if((GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))&& pBoard->x + pBoard->w < 800) 
	{
		pBoard->x += 1;
	}
}

void Map::drawBall(Ball* pBall) 
{
	//setfillcolor(pBall->color);
	setfillcolor(RGB(rand() % 255, rand() % 255 , rand() % 255)); //随机颜色
	solidcircle(pBall->x, pBall->y, pBall->r);
}

void Move::moveBall(Ball* pBall, Board* pBoard, int map[][8], int row, int cols) 
{
	//碰撞反弹, 
	/*if(pBall->x - pBall->r <= 0 || pBall->x + pBall->r >= 800) 
	{
		pBall->dx = -pBall->dx;
	}

	if(pBall->y - pBall->r <= 0 || pBall->y + pBall->r >=600 ) 
	{
		pBall->dy = -pBall->dy;
	}*/
	
	if (pBall->x - pBall->r <= 0 || pBall->x + pBall->r >= 800)
	{
		pBall->dx = -pBall->dx;
	}

#if 0
	if (pBall->y - pBall->r <= 0 || hitBoard(pBall, pBoard))
	{
		cout << "发生碰撞" << endl;
		cout << "没有发生反射" << endl;
		pBall->dy = -pBall->dy;
	}
#else
	if(pBall->y - pBall->r <= 0 
	|| pBall->y + pBall->r >= 600 
	|| hitBoard(pBall,pBoard)
	|| hitBricks(pBall,map,row,cols))
	{
		cout << "发生碰撞" << endl;
		pBall->dy = -pBall->dy;
	}
#endif
	pBall->x += pBall->dx;
	pBall->y += pBall->dy;
	 
}

int System::Timer (int duration,int id) 
{
	static int startTime[10];	//静态变量自动初始化为零
	//用静态变量是因为要记录上一次的运行结果

	int endTime = clock();
	if(endTime - startTime[id] >= duration) 
	{
		//下一次开始的时间编程变成一次结束的时间
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}

int Move::hitBoard(Ball* pBall, Board* pBoard)
{

#if 0
	if(pBall->y + pBall->r == pBoard->y) 
	{
		if(pBall->x > pBoard->x && pBall->x < pBoard->x + pBoard->w) 
		{
			cout << "发生碰撞" << endl;
			return 1;
		}
		else 
		{
			cout << "碰撞出错" << endl;
		}
	}
#else
	if (pBall->y + pBall->r == pBoard->y)
	{
		if (pBall->x > pBoard->x && pBall->x <= pBoard->x + pBoard->w)
		{
			cout << "发生碰撞" << endl;
			return 1;
		}
		else
		{
			cout << "碰撞出错" << endl;
		}
	}
#endif

	return 0;
}

int Move::hitBricks(Ball* pBall,int map[][8],int row,int cols)
{
	int j = pBall->x / 100;
	int i = (pBall->y - pBall->r) / 25;
	if(i < row && j < cols && map[i][j] != 0) 
	{
		map[i][j] = 0;
		return 1;
	}
	return 0;
}

int System::gameOver(Ball* pBall,Board* pBoard)
{
	if(pBall->y + pBall->r > pBoard->y) 
	{
		return 1;
	}
	return 0;
}

int System::windGame(int map[][8], int row, int cols)
{
	for(int i = 0; i < row; ++i) 
	{
		for(int j = 0; j < cols; ++j) 
		{
			if(map[i][j] !=0) 
			{
				return 0;
			}
		}
	}
	return 1;
}

void System::outtextxyInfo(int x, int y, const char* info)
{
	settextstyle(45, 0, "楷体");
	settextcolor(RED);
	outtextxy(x, y, info);
}

int main() 
{
	Map init;
	Move move;
	System psystem;
	System judge;
	srand((unsigned int)time(NULL));
	initgraph(800, 600);
	int map[5][8];
	Board* pBoard = createBoard(300, 600 - 25, 200, 25, BLUE);
	Ball* pBall = createBall(400, 300, 10, 15, -5, RED);
	init.initMap(map, 5, 8);
	BeginBatchDraw();
	while (true)
	{ 
		cleardevice();	
		init.drawMap(map, 5, 8);
		init.drawBoard(pBoard);
		init.drawBall(pBall);
		if (judge.Timer(20, 0))
			move.moveBall(pBall, pBoard, map, 5, 8);
		judge.keyDown(pBoard);
		//Sleep(10);		
		if (judge.gameOver(pBall, pBoard)) 
		{
			psystem.outtextxyInfo(300, 350, "游戏失败");
			FlushBatchDraw();
			break;
		}
		if (judge.windGame(map, 5, 8)) 
		{
			psystem.outtextxyInfo(300, 350, "游戏胜利");
			FlushBatchDraw();
			break;
		}
		FlushBatchDraw();   
	}
	Sleep(5000);
	EndBatchDraw();         
	
	closegraph();
	return 0;
}