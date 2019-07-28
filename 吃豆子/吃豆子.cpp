// 吃豆子.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "graphics.h"
#include "conio.h"
#include "time.h"
//#include "stdlib.h"
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
bool g_win = true ;
IMAGE image[8];
void load_image();
void beinning ();
void initial();
void monster_meet_bean();
void eatbean();
void rand_dir();
void move_yourself();
void monster_moving();
void monster_meet_nullspace();
void losing();
void win();
void play();
bool judge_meet();
int sjs();
//0豆子 1空地   2墙壁  3角色   4怪兽
//豆子数 35
int map[15][20]=
   {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 
	2,1,0,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,2, 
	2,1,2,1,1,1,1,2,2,2,1,0,0,2,1,1,1,1,0,2, 
	2,1,2,1,1,1,1,1,1,2,1,1,2,2,2,2,0,0,0,2, 
	2,4,2,1,1,1,1,1,2,1,1,0,1,1,1,1,0,1,1,2, 
	2,1,2,2,2,1,1,2,2,2,1,1,1,1,1,1,2,2,1,2, 
	2,1,1,1,1,1,1,1,1,1,3,1,1,0,2,2,2,1,1,2, 
	2,1,1,1,0,1,1,0,1,2,1,0,1,2,2,1,1,1,1,2, 
	2,1,2,1,0,1,1,1,1,2,1,0,1,1,1,1,4,1,1,2, 
	2,1,2,2,0,1,2,1,1,1,1,2,1,2,1,1,1,1,1,2, 
	2,1,0,2,1,1,2,2,1,1,2,1,2,1,2,1,0,2,1,2, 
	2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2, 
	2,1,1,1,1,2,1,1,0,0,1,1,1,4,1,2,2,2,1,2, 
	2,1,0,0,0,2,0,1,2,1,1,0,1,1,1,1,0,0,1,2, 
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
int bean_num = 0;
struct character
{
	int x ;    //数组坐标
	int y ;
	int x1 ;   //方向移动
	int y1 ;
	int x2 ;   //加载成图片的坐标
	int y2 ;
};
character you , monster[4];
void beginning ()
{
	IMAGE image;
	loadimage(&image , "背景.jpg");
	putimage(0,0,&image);
	char c1[20] = "游戏说明:" ; 
	settextstyle (25 ,0 ,"宋体");
	setcolor(CYAN);
	outtextxy(100,300,c1);
	char c2[50]="通过字母键（W、A、S、D）控制移动。";
	settextstyle (15 ,0 ,"宋体");
	setcolor(CYAN);
	outtextxy(150,335,c2);
	char c3[20]="点击鼠标开始游戏！";
	settextstyle (30 ,0 ,"宋体");
	setcolor(YELLOW);
	outtextxy(200,400,c3);
	while (1)
	{
		MOUSEMSG msg ;
		msg = GetMouseMsg ();
		if (msg.uMsg == WM_LBUTTONDOWN)
			break ;
	}

}
int sjs(int a , int b)
{
	return a+rand()%(b-a+1);
}
void initial ()
{
	cleardevice();
	for( int i = 0;i < 15;i++)                      
		for(int j = 0;j < 20;j++)
			putimage(j*30,i*30,&image[map[i][j]]);
	you.x=10;            you.y=6;				
	monster[0].x=15; monster[0].y=2; 
	monster[1].x=1;  monster[1].y=4; 
	monster[2].x=16; monster[2].y=8; 
	monster[3].x=13; monster[3].y=12; 
	you.x2 = you.x * 30 ;
	you.y2 = you.y * 30 ;
	for (int i = 0 ; i< 4 ;i++)
	{
		monster[i].x2 = monster[i].x * 30 ;
		monster[i].y2 = monster[i].y * 30 ;
		monster[i].x1 = 0 ;
		monster[i].y1 = 1;
	}
}
void load_image()
{
	loadimage (&image[0],"豆子.jpg");
	loadimage (&image[1],"空地.jpg");
	loadimage (&image[2],"墙壁.jpg");
	loadimage (&image[3],"角色右.jpg");
	loadimage (&image[4],"怪物.jpg");
	loadimage (&image[5],"角色左.jpg");
	loadimage (&image[6],"角色上.jpg");
	loadimage (&image[7],"角色下.jpg");
}
void monster_meet_bean (int i)
{
	int x = monster[i].x2 ;
	int y = monster[i].y2 ;
	for (int j = 0 ; j < 30 ; j++)
	{
		putimage(x,y,&image[0]);
		monster[i].x2 += monster[i].x1 ;
		monster[i].y2 += monster[i].y1 ;
		putimage(monster[i].x2,monster[i].y2 ,&image[4]);
	}
}
void eatbean()
{
	if (map[you.y][you.x] == 0)
	{
		map[you.y][you.x] = 1;
		bean_num ++ ;
	}
}
void monster_meet_nullspace(int i )
{
	int x = monster[i].x2 ;
	int y = monster[i].y2 ;
	for (int j = 0 ; j < 30 ; j++)
	{
		putimage(x,y,&image[1]);
		monster[i].x2 += monster[i].x1 ;
		monster[i].y2 += monster[i].y1 ;
		putimage(monster[i].x2,monster[i].y2 ,&image[4]);
	}
}
void rand_dir(struct character *a)//方向改变
{
	int b = 1 ;
	int x , y ;
	while (b)
	{
		x = sjs(-1 , 1);
		y = sjs(-1 , 1);
		if (map[a ->y + y][a -> x + x] != 2 && abs(y) != abs(x))
		{
			b = 0 ;
			a ->x1 = x ;
			a ->y1 = y ;
		}
		else b = 1 ;
	}
}
void monster_moving()
{
	for (int i = 0 ; i < 4 ; i++)
	{
		if (map[monster[i].y + monster[i].y1][monster[i].x+monster[i].x1] == 2 || abs(monster[i].y1) == abs(monster[i].x1))
			rand_dir(&monster[i]);
	}
	for (int i = 0 ; i< 4 ; i++)
	{
		if (map[monster[i].y][monster[i].x] == 0)
			monster_meet_bean (i);
		else 
			monster_meet_nullspace (i);
		monster[i].x += monster[i].x1;
		monster[i].y += monster[i].y1;
		if (judge_meet())
			break;
	}
	Sleep (300);
}
void move_yourself(int t)
{
	switch (t)
	{
	case LEFT:
		you.x1 = -1;you.y1 = 0;
		if (map[you.y + you.y1 ][you.x + you.x1 ] != 2)
		{
			int x = you.x2;
			int y = you.y2;
			for (int j = 0 ;j <15 ;j++)
			{
				putimage(x,y,&image[1]);
				you.x2 += you.x1 * 2;
				you.y2 += you.y1 * 2;
				putimage(you.x2,you.y2,&image[5]);
			}
			you.x += you.x1;
			you.y += you.y1;
			eatbean();
		}
		break;
	case RIGHT:
		you.x1 = 1;you.y1 = 0;
		if (map[you.y + you.y1 ][you.x + you.x1 ] != 2)
		{
			int x = you.x2;
			int y = you.y2;
			for (int j = 0 ;j <15 ;j++)
			{
				putimage(x,y,&image[1]);
				you.x2 += you.x1 * 2;
				you.y2 += you.y1 * 2;
				putimage(you.x2,you.y2,&image[3]);
			}
			you.x += you.x1;
			you.y += you.y1;
			eatbean();
		}
		break;
	case DOWN:
		you.x1 = 0;you.y1 = 1;
		if (map[you.y + you.y1 ][you.x + you.x1 ] != 2)
		{
			int x = you.x2;
			int y = you.y2;
			for (int j = 0 ;j <15 ;j++)
			{
				putimage(x,y,&image[1]);
				you.x2 += you.x1 * 2;
				you.y2 += you.y1 * 2;
				putimage(you.x2,you.y2,&image[7]);
			}
			you.x += you.x1;
			you.y += you.y1;
			eatbean();
		}
		break;
	case UP:
		you.x1 = 0;you.y1 = -1;
		if (map[you.y + you.y1 ][you.x + you.x1 ] != 2)
		{
			int x = you.x2;
			int y = you.y2;
			for (int j = 0 ;j <15 ;j++)
			{
				putimage(x,y,&image[1]);
				you.x2 += you.x1 * 2;
				you.y2 += you.y1 * 2;
				putimage(you.x2,you.y2,&image[6]);
			}
			you.x += you.x1;
			you.y += you.y1;
			eatbean();
		}
		break;
	}
	if (bean_num == 35 )
			win();
}
bool judge_meet()
{
	for (int i = 0 ; i < 4 ; i++)
	{
		if (monster[i].x == you.x && monster[i].y == you.y )
		{
			g_win = false ;
			losing();
			return true ;
			break;
		}
	}
	return false ;
}
void losing()
{
	cleardevice ();
	IMAGE image_lose;
	loadimage(&image_lose, "LOSE.jpg");
	putimage (0, 0 , &image_lose);
	system ("pause");
}
void win ()
{
	cleardevice ();
	IMAGE image_win ;
	loadimage(&image_win , "WIN.jpg");
	putimage (0 , 0 , &image_win);
	system("pause");
}
void play ()
{
	char key ;
	int t ;
	while (g_win)
	{
		monster_moving();
		while (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 'a':
				t = LEFT;
				move_yourself (t);
				break ;
			case 'd':
				t = RIGHT ;
				move_yourself (t);
				break ;
			case 's':
				t = DOWN ;
				move_yourself (t);
				break ;
			case 'w':
				t = UP ;
				move_yourself (t);
				break ;
			}
		}
		
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	initgraph (600,450);
    beginning();
	load_image ();
    srand((unsigned)time (NULL));
	initial ();
	play();
	system ("pause");
	closegraph ();
	return 0;
}