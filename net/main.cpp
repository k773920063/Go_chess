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
	void Draw_Inf_Board(int turn,float Grade[2]); 		//����Ŀ�� ���巽 ʱ�����Ϣ
	void Copy2old(int Plat[][7],int old[][7]);			// �����������飬ʵ�ֻ��幦��			
	
	struct check_table table;
	struct check_table *point = &table;
	
	int Play_Mod = 0;		//���˻��˻�... 
	int Turn = 0;			//Turn=0�ڷ���=1�׷�
	int Plat[7][7]={0};		//���̸����� ����������Ϣ
	int Plat_old[7][7]={0};	//������һ�����̣�ʵ�ֻ��幦�� 
	float Grade[2]={0,0};	//Grade[0]Ϊ����Ŀ����Grade[1]Ϊ����Ŀ�������ֺ�����һ�� 
	
	int XY[2]={-1,-1};		//����Ŀǰ����λ�� 
	 
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
		Draw_Plat_line();		//�������̸�
		Draw_Inf_Board(Turn,Grade);	//����Ŀ�� ���巽 ʱ�����Ϣ
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


//ͼ���ຯ�� 
void SetBackGround()		//�������� 
{
	
}

void Draw_Plat_line()		//�������̸� 
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

void Init_Plat()			//��ʼ������ 
{
	setinitmode(0);
	initgraph(1000, 800);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xCC));
	//setcolor(BLACK);
	Draw_Plat_line();
 } 
 


void Draw_Inf_Board(int turn,float Grade[2]) 		//���Ʒ��� ���ܰ�ť ����Ϣ
{
	setfontbkcolor(EGERGB(0xFF, 0xFF, 0xCC));
	if(turn==0)
	xyprintf(350,10,"�ڷ�");
	else
	xyprintf(350,10,"�׷�");
	
	xyprintf(800,300,"�ڷ�����:%.1f",Grade[0]);
	xyprintf(800,450,"�׷�����:%.1f",Grade[1]); 
	
	setfillcolor(EGERGB(0xFF,0x0,0x80));
	bar(820,600,880,630);
	setfontbkcolor(EGERGB(0xFF,0x0,0x80));
	xyprintf(835,605,"����"); 
}

void DrawChess(int x,int y,int color)		//��������
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
 

void Display_Chess(int Plat[7][7])		//����ʵ����ֻ������� 
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




//��̨�����ຯ��
void Copy2old(int Plat[][7],int old[][7])
{
	int i,j;
	for(i=0;i<7;i++)
		for(j=0;j<7;j++)
		{
			old[i][j]=Plat[i][j];
		}
 } 

int  Pull_Chess(int Plat[7][7])		//���Ӻ��� 
{
	
}

void Repair_Plat(int Plat[7][7])	//��ٻָ�
{
	for(int j=0;j<7;j++)
		for(int i=0;i<7;i++)
		{
			if(Plat[i][j]==-1)
			Plat[i][j]=0;
		}
} 

void Cal_Grade(int Plat[7][7],float Grade[])		//��Ŀ���� 
{
	
}

void Rand_AI(int Plat[7][7])		//������������� 
{
	
}

 

//��̨�����ຯ��
int Down_chess(int *turn,int Plat[7][7],int Plat_old[7][7],struct check_table *point,int XY[])		//���Ӻ���
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
	
		//�����Ƿ�Ϲ���
	 
		if(Plat[y][x]==0)
		{	 
			//�޸�turn ʵ���л����巽��Ŀ�� 
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
			//���Υ��
			MessageBox(NULL,"���ܴ��ڴ��","��ʾ",MB_SYSTEMMODAL);
		}
		else
		{
			//��������
			MessageBox(NULL,"�˴���������","��ʾ",MB_SYSTEMMODAL); 
	 	}
	}
	else if(x>=820&&x<=880&&y>=600&&y<=630)
	{
		Copy2old(Plat_old,Plat);
	}
	
} 


 
