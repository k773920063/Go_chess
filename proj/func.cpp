#include<stdio.h>

struct check_table
{
	int Checked_Num;
	int Checked_List[7][7];
	int Checked_Chunk[7][7];
	int Stack[200][2];
	int Stack_Num;
	int Live_List[7][7];
};

void Init_check_table(struct check_table *point)		//初始化用以提子判断的结构体 
{
	int i,j;
	point->Checked_Num=0;
	point->Stack_Num=0;
	for(j=0;j<7;j++)
		for(i=0;i<7;i++)
		{
			point->Checked_List[i][j]=-1;
			point->Checked_Chunk[i][j]=0;
		}
	
	point->Live_List[0][0]=2;
	point->Live_List[6][0]=2;
	point->Live_List[6][6]=2;
	point->Live_List[0][6]=2;
	
	for(i=1;i<6;i++)
	{
		point->Live_List[0][i]=3;
		point->Live_List[6][i]=3;
		point->Live_List[i][6]=3;
		point->Live_List[i][0]=3;
	}
	for(j=1;j<6;j++)
		for(i=1;i<6;i++)
		{
			point->Live_List[i][j]=4;
		}
}

void Reset_check_table(struct check_table *point)
{
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
		{
			point->Checked_Chunk[i][j]=0;
			point->Checked_List[i][j]=-1;
		}
	point->Stack_Num=0;
}

int Live_Check(int x,int y,int Plat[7][7])
{
	int n=0,s=0;
	if(x==0&&y==0)				//左上角 
	{
		if(Plat[1][0]>0)
		n++;
		if(Plat[0][1]>0)
		n++;
		if(n<2)
		return 1;				//1为有气，0为无气 
		else
		return 0; 
	}
	else if(x==6&&y==0)			//左下角
	{
		n=0;
		if(Plat[5][0]>0)
		n++;
		if(Plat[6][1]>0)
		n++;
		if(n<2)
		return 1;
		else
		return 0;
	}
	else if(x==0&&y==6)			//右上角 
	{
		n=0;
		if(Plat[0][5]>0)
		n++;
		if(Plat[1][6]>0)
		n++;
		if(n<2)
		return 1;
		else
		return 0;
	 }
	 else if(x==6&&y==6)		//右下角 
	 {
	 	n=0;
	 	if(Plat[5][6]>0)
	 	n++;
	 	if(Plat[6][5]>0)
	 	n++;
	 	if(n<2)
	 	return 1;
	 	else
	 	return 0;
	  }
	  else if(y>0&&y<6&&x==0)	//上边
	  {
	  	n=0;
	  	if(Plat[x][y-1]>0)
	  	n++;
	  	if(Plat[x][y+1]>0)
	  	n++;
	  	if(Plat[x+1][y]>0)
	  	n++;
	  	if(n<3)
	  	return 1;
	  	else
	  	return 0;
	   }
	   else if(y>0&&y<6&&x==6)	//下边
	   {
	   	n=0;
	   	if(Plat[x-1][y]>0)
	   	n++;
	   	if(Plat[x][y-1]>0)
	   	n++;
	   	if(Plat[x][y+1]>0)
	   	n++;
	   	if(n<3)
	   	return 1;
	   	else
	   	return 0;
		}
		else if(y==0&&x>0&&x<6)	//左边
	   {
		 n=0;
		 if(Plat[x][y+1]>0)
		 n++;
		 if(Plat[x-1][y]>0)
		 n++;
		 if(Plat[x+1][y]>0)
		 n++;
		 if(n<3)
		 return 1;
		 else
		 return 0;
	   }
	   else if(y==6&&x>0&&x<6)	//右边 
	   {
	   	n=0;
	   	if(Plat[x][y-1]>0)
	   	n++;
	   	if(Plat[x-1][y]>0)
	   	n++;
	   	if(Plat[x+1][y]>0)
	   	n++;
	   	if(n<3)
	   	return 1;
	   	else
	   	return 0;
		}
		else if(x>0&&x<6&&y>0&&y<6)	//中间块 
		{
			n=0;
			if(Plat[x-1][y]>0)
			n++;
			if(Plat[x+1][y]>0)
			n++;
			if(Plat[x][y-1]>0)
			n++;
			if(Plat[x][y+1]>0)
			n++;
			if(n<4)
			return 1;
			else
			return 0;
		 } 
}

int Same_Color_Check(int x,int y,int Plat[7][7],struct check_table *point)				//判断无气棋子周围是否有同色，有同色且未检查过则进栈 
{
	int c,n=0;
	c=Plat[x][y];
	if((x-1>=0))
	{
		if(point->Checked_Chunk[x-1][y]==0&&Plat[x-1][y]==c)
		{
			n++;
			point->Checked_Chunk[x-1][y]=c;
			point->Stack[point->Stack_Num][0]=x-1;
			point->Stack[point->Stack_Num][1]=y;
			point->Stack_Num++;
		}
	 }
	 if(x+1<=6)
	 {
	 	if(point->Checked_Chunk[x+1][y]==0&&Plat[x+1][y]==c)
		{
			n++;
			point->Checked_Chunk[x+1][y]=c;
			point->Stack[point->Stack_Num][0]=x+1;
			point->Stack[point->Stack_Num][1]=y;
			point->Stack_Num++;
		}
	  }
	  if(y-1>=0)
	  {
	  	if(point->Checked_Chunk[x][y-1]==0&&Plat[x][y-1]==c)
		{
			n++;
			point->Checked_Chunk[x][y-1]=c;
			point->Stack[point->Stack_Num][0]=x;
			point->Stack[point->Stack_Num][1]=y-1;
			point->Stack_Num++;
		}
	   }
	   if(y+1<=6)
	   {
	   	if(point->Checked_Chunk[x][y+1]==0&&Plat[x][y+1]==c)
	   	{
	   		n++;
	   		point->Checked_Chunk[x][y+1]=c;
	   		point->Stack[point->Stack_Num][0]=x;
	   		point->Stack[point->Stack_Num][1]=y+1;
	   		point->Stack_Num++;
		   }
		}
		return n; 
}

void Search_All(int Plat[7][7],struct check_table *point)
{
	int x,y;
	while(point->Stack_Num!=0)
	{
		x=point->Stack[point->Stack_Num-1][0];
		y=point->Stack[point->Stack_Num-1][1];
		point->Stack_Num--;
		Same_Color_Check(x,y,Plat,point);
	}
}

int Recheck(int Plat[7][7],struct check_table *point,int chess)	//从Chunk数组遍历检查每个棋子，若有一个活棋则返回1，不然返回0 
{
	int tar=0;
	int i,j;
	for(j=0;j<7;j++)
		for(i=0;i<7;i++)
		{
			if(point->Checked_Chunk[i][j]==chess)
			{
				tar+=Live_Check(i,j,Plat);
			}
		}
	if(tar>0)
	return 1;
	else
	return 0;
}

void Pull_Chess_part(int Plat[7][7],struct check_table *point,int i,int j)
{
	int chess,live;
	if(Plat[i][j]<=0)						//判断为空子 
			{
				point->Checked_Num++;
				point->Checked_List[i][j]=0;
			}
			else 									//判断为有棋 
			{
				chess=Plat[i][j]; 
				if(point->Checked_List[i][j]==chess)			//若已经过检查，则跳过 
					return;
				else
				{
				 	live=Live_Check(i,j,Plat);
				 	if(live)
				 	{
				 		point->Checked_List[i][j]=chess;	//有气则标记已检查 
				 		point->Checked_Num++;
					}
					
					 else										//无气检查是否有相邻同色棋子 
					{
						if(Same_Color_Check(i,j,Plat,point)==0)	//无同色棋子直接置-1
						{
							point->Checked_List[i][j]=0;
							point->Checked_Num++;
							Plat[i][j]=-1;
							//continue;
						 }
						 else									//有同色棋子 
						 {
						 	int p;
						 	point->Checked_Chunk[i][j]=chess; 
							Search_All(Plat,point);				//搜索所有连接的同色 
						 	p=Recheck(Plat,point,chess);
						 	if(p)
						 	{
						 		int l,m,sum=0;
						 		for(l=0;l<7;l++)
						 			for(m=0;m<7;m++)
						 			{
						 				if(point->Checked_Chunk[l][m]!=0)
						 				{
						 					sum++;
						 					point->Checked_List[l][m]=chess;
										 }
									 }
								point->Checked_Num+=sum;	 
							 }
							 else
							 {
							 	int l,m,sum=0;
							 	for(l=0;l<7;l++)
							 		for(m=0;m<7;m++)
							 		{
							 			if(point->Checked_Chunk[l][m]==chess)
							 			{
							 				sum++;
							 				point->Checked_List[l][m]=chess;
							 				Plat[l][m]=0;
										 }
									 }
								point->Checked_Num+=sum;
							 }
							 Reset_check_table(point);
						  } 
					} 
				} 
				 
			} 
}

int Pull_Chess(int Plat[7][7],struct check_table *point,int *time,int XY[])
{
	int i,j,chess;
	
	
	chess = Plat[XY[0]][XY[1]];
	if(XY[0]-1>=0&&Plat[XY[0]-1][XY[1]]!=chess)
	{
		Pull_Chess_part(Plat,point,XY[0]-1,XY[1]);
	 } 
	if(XY[0]+1<=6&&Plat[XY[0]+1][XY[1]]!=chess)
	 {
	 	Pull_Chess_part(Plat,point,XY[0]+1,XY[1]);
	 }
	 if(XY[1]-1>=0&&Plat[XY[0]][XY[1]-1]!=chess)
	 {
	 	Pull_Chess_part(Plat,point,XY[0],XY[1]-1);
	 }
	 if(XY[1]+1<=6&&Plat[XY[0]][XY[1]+1]!=chess)
	 {
	 	Pull_Chess_part(Plat,point,XY[0],XY[1]+1);
	 }
	
	
	
	for(i=0;i<7;i++)
		for(j=0;j<7;j++)
		{
			if(XY[0]==i&&XY[1]==j)
			continue;
			Pull_Chess_part(Plat,point,i,j);
		}
		Pull_Chess_part(Plat,point,XY[0],XY[1]);
	Init_check_table(point);
	(*time)++;
}

void Reset_Forbiden_location(int Plat[7][7])	//打劫-1重新置0
{
	for(int j=0;j<7;j++)
		for(int i=0;i<7;i++)
		{
			if(Plat[i][j]==-1)
			Plat[i][j]=0;
		}
} 

void Input_Word_Chess(int *turn,int Plat[7][7])
{
	int x=0,y=0;
	scanf("%d %d",&x,&y);
	Plat[x][y]=*turn;
	if(*turn==1)
	*turn=2;
	else
	*turn=1;
 } 
 
void Grade_Cal(float Grade[2],int Plat[7][7])		//计分函数 
{
	int chess=0,black=0,white=0,i,j;
	Grade[0]=0;
	Grade[1]=0;
	for(j=0;j<7;j++)
	{
		for(i=0;i<7;i++)
		{
			black=0;
			white=0;
			if(Plat[i][j]==0||Plat[i][j]==-1)
			{
				if(i-1>=0)
				{
					if(Plat[i-1][j]==1)
					black++;
					else if(Plat[i-1][j]==2)
					white++;
				 }
				 if(i+1<=6)
				 {
				 	if(Plat[i+1][j]==1)
				 	black++;
				 	else if(Plat[i+1][j]==2)
				 	white++;
				  }
				  if(j-1>=0)
				  {
				  	if(Plat[i][j-1]==1)
				  	black++;
				  	else if(Plat[i][j-1]==2)
				  	white++;
				   }
				   if(j+1<=6)
				   {
				   	if(Plat[i][j+1]==1)
				   	black++;
				   	else if(Plat[i][j+1]==2)
				   	white++;
					}
					if(black>0&&white==0)
					{
						Grade[0]+=0.5;
					 }
					 else if(black==0&&white>0)
					 {
					 	Grade[1]+=0.5;
					  }
					  else if(black>0&&white>0)
					  {
					  	Grade[0]+=0.5;
					  	Grade[1]+=0.5;
					   } 
				}
				else if(Plat[i][j]==1)
				{
					Grade[0]+=1;
				}
				else if(Plat[i][j]==2)
				{
					Grade[1]+=1;
				}
		}
	}
	Grade[1]+=1;								//黑棋让一子(白棋加1) 
 } 

/* 
int main()
{
	struct check_table table;
	struct check_table *point = &table;
	Init_check_table(point);
	int turn=1;
	int h=0;
	int *time=&h;
	int Plat[7][7]={0};
	while(1)
	{
		Input_Word_Chess(&turn,Plat);
		Pull_Chess(Plat,point,time);
		for(int i=0;i<7;i++)
		{
			printf("\n");
			for(int j=0;j<7;j++)
			printf("%d ",Plat[i][j]);
		}
		printf("\n\n");
	}
}
*/ 

