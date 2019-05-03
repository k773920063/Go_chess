#include<stdio.h>
#include <graphics.h>
#include<windows.h>
#include "func.h"

int main()
{
	void Down_chess(int *turn,int Plat[7][7],int Plat_old[7][7],struct check_table *point,int XY[]);
	void Draw_Plat_line();
	void Display_Chess(int Plat[7][7]);
	void Init_Plat();
	void Draw_Inf_Board(int turn,float Grade[2]); 		//绘制目数 下棋方 时间等信息
	void Copy2old(int Plat[][7],int old[][7]);			// 储存两份数组，实现悔棋功能			
	
	struct check_table table;
	struct check_table *point = &table;
	
	int Play_Mod = 0;		//人人或人机... 
	int Turn = 0;			//Turn=0黑方，=1白方
	int Plat[7][7]={0};		//棋盘格数组 包含落子信息
	int Plat_old[7][7]={0};	//储存上一步棋盘，实现悔棋功能 
	float Grade[2]={0,0};	//Grade[0]为黑棋目数，Grade[1]为白棋目数，开局黑棋让一子 
	
	int XY[2]={-1,-1};		//储存目前下子位置 
	 
	Init_Plat();
	Init_check_table(point);
	
	int time=0;
	while(1)
	{
		Display_Chess(Plat);
		
		Down_chess(&Turn,Plat,Plat_old,point,XY);
		
		Pull_Chess(Plat,point,&time,XY);
		
		Grade_Cal(Grade,Plat);
		
		cleardevice();
		Draw_Plat_line();		//绘制棋盘格
		Draw_Inf_Board(Turn,Grade);	//绘制目数 下棋方 时间等信息
		Display_Chess(Plat);
		
		setfontbkcolor(EGERGB(0xFF, 0xFF, 0xCC));
		xyprintf(10,10,"%d  %d  %d  %d  %d  %d  %d",Plat[0][0],Plat[0][1],Plat[0][2],Plat[0][3],Plat[0][4],Plat[0][5],Plat[0][6]);
		xyprintf(10,25,"%d  %d  %d  %d  %d  %d  %d",Plat[1][0],Plat[1][1],Plat[1][2],Plat[1][3],Plat[1][4],Plat[1][5],Plat[1][6]);
		xyprintf(10,40,"%d  %d  %d  %d  %d  %d  %d",Plat[2][0],Plat[2][1],Plat[2][2],Plat[2][3],Plat[2][4],Plat[2][5],Plat[2][6]);
		xyprintf(10,55,"%d  %d  %d  %d  %d  %d  %d",Plat[3][0],Plat[3][1],Plat[3][2],Plat[3][3],Plat[3][4],Plat[3][5],Plat[3][6]);
		xyprintf(10,70,"%d  %d  %d  %d  %d  %d  %d",Plat[4][0],Plat[4][1],Plat[4][2],Plat[4][3],Plat[4][4],Plat[4][5],Plat[4][6]);
		xyprintf(10,85,"%d  %d  %d  %d  %d  %d  %d",Plat[5][0],Plat[5][1],Plat[5][2],Plat[5][3],Plat[5][4],Plat[5][5],Plat[5][6]);
		xyprintf(10,100,"%d  %d  %d  %d  %d  %d  %d",Plat[6][0],Plat[6][1],Plat[6][2],Plat[6][3],Plat[6][4],Plat[6][5],Plat[6][6]);
		//xyprintf(10,10,"%d",time);
	 } 
}


//图像类函数 
void SetBackGround()		//背景设置 
{
	
}

void Draw_Plat_line()		//绘制棋盘格 
{
	setcolor(BLACK);
	for(int i=0;i<7;i++)
	{
		line(100+i*100,100,100+i*100,700);
		line(100,100+i*100,700,100+i*100);
	} 
	setfillcolor(EGERGB(0x0, 0x0, 0x0));
	fillellipse(400,400,5,5);
	 
}

void Init_Plat()			//初始化棋盘 
{
	setinitmode(0);
	initgraph(1000, 800);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xCC));
	//setcolor(BLACK);
	Draw_Plat_line();
 } 
 


void Draw_Inf_Board(int turn,float Grade[2]) 		//绘制分数 功能按钮 等信息
{
	setfontbkcolor(EGERGB(0xFF, 0xFF, 0xCC));
	if(turn==0)
	xyprintf(350,10,"黑方");
	else
	xyprintf(350,10,"白方");
	
	xyprintf(800,300,"黑方分数:%.1f",Grade[0]);
	xyprintf(800,450,"白方分数:%.1f",Grade[1]); 
	
	setfillcolor(EGERGB(0xFF,0x0,0x80));
	bar(820,600,880,630);
	setfontbkcolor(EGERGB(0xFF,0x0,0x80));
	xyprintf(835,605,"悔棋"); 
}

void DrawChess(int x,int y,int color)		//绘制棋子
{
	if(color==1)
	{
		setfillcolor(EGERGB(0x0, 0x0, 0x0));
		fillellipse(100+x*100, 100+y*100, 45, 45);
	}
	
	else if(color==2)
	{
		setfillcolor(EGERGB(0xff, 0xff, 0xff));
		fillellipse(100+x*100, 100+y*100, 45, 45);
	}
} 
 

void Display_Chess(int Plat[7][7])		//根据实际棋局绘制棋子 
{
	for(int j=0;j<7;j++)
	{
		for(int i=0;i<7;i++)
		{
			if(Plat[i][j]!=0&&Plat[i][j]!=-1)
			DrawChess(j,i,Plat[i][j]);
		}
	}

}




//后台处理类函数
void Copy2old(int Plat[][7],int old[][7])
{
	int i,j;
	for(i=0;i<7;i++)
		for(j=0;j<7;j++)
		{
			old[i][j]=Plat[i][j];
		}
 } 

int  Pull_Chess(int Plat[7][7])		//提子函数 
{
	
}

void Repair_Plat(int Plat[7][7])	//打劫恢复
{
	for(int j=0;j<7;j++)
		for(int i=0;i<7;i++)
		{
			if(Plat[i][j]==-1)
			Plat[i][j]=0;
		}
} 

void Cal_Grade(int Plat[7][7],float Grade[])		//点目函数 
{
	
}

void Rand_AI(int Plat[7][7])		//随机假智能落子 
{
	
}

 

//后台操作类函数
int Down_chess(int *turn,int Plat[7][7],int Plat_old[7][7],struct check_table *point,int XY[])		//落子函数
{
	int x=0,y=0,i=0,j=0;
	mouse_msg msg = {0};
	for ( ; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			msg = getmouse();
		}

		 
		if((int)msg.is_down()==1)
		{
			x=msg.x;
			y=msg.y;
			//xyprintf(0,20,"x=%10d  y=%10d",x,y);
			break;
		}
	}
	if(x<=750)
	{
		Copy2old(Plat,Plat_old);
		for(i=100;i<=700;i+=100)
		{
			if((x-i)>-50&&(x-i)<50)
			{
				x=i;
				break;
			}
		}
		for(i=100;i<=700;i+=100)
		{
			if((y-i)>-50&&(y-i)<50)
			{
				y=i;
				break;
			}
		}
	
		x=x/100-1;
		y=y/100-1;
	
		//下子是否合规检测
	 
		if(Plat[y][x]==0)
		{	 
			//修改turn 实现切换下棋方的目的 
			if(*turn==0)
			{
				Plat[y][x]=1;
				*turn = 1;
			
				XY[0]=y;
				XY[1]=x;
			 
				Reset_Forbiden_location(Plat);
				//Pull_Chess(Plat,point);
				//cleardevice();
			}
			else if(*turn==1)
			{
				Plat[y][x]=2;
				*turn = 0;
			
				XY[0]=y;
				XY[1]=x;
			
				Reset_Forbiden_location(Plat);
				//Pull_Chess(Plat,point);
				//cleardevice();
			}
		}
		else if(Plat[y][x]==-1)
		{
			//打劫违规
			MessageBox(NULL,"可能存在打劫","提示",MB_SYSTEMMODAL);
		}
		else
		{
			//已有落子
			MessageBox(NULL,"此处已有落子","提示",MB_SYSTEMMODAL); 
	 	}
	}
	else if(x>=820&&x<=880&&y>=600&&y<=630)
	{
		Copy2old(Plat_old,Plat);
	}
	
} 


 
