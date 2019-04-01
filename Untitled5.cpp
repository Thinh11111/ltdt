#include<conio.h>
#include<stdio.h>

#define MAX 10
#define inputfile "D:/test.txt"
#define VOCUC 1000
typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;

//==============================================================
int DocMaTranKe(const char* TenFile,DOTHI &g)
{	FILE* f;
	f = fopen(TenFile,"rt");
	if(f==NULL)
	{
		printf("Khong mo duoc file\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	for(int i=1;i<=g.n;i++)
		for(int j=1;j<=g.n;j++)
			fscanf(f,"%d",&g.a[i][j]);
	fclose(f);
	return 1;
}
//==============================================================
void XuatMaTranKe(DOTHI g)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Ma tran ke cua do thi la:\n");
	for(int i=1;i<=g.n;i++)
	{	for(int j=1;j<=g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
int LuuVet[MAX];
int ChuaXet[MAX];
int DoDaiDuongDiToi[MAX];
int TimDuongDiNhoNhat(DOTHI g)
{
	int li=-1;
	float p=VOCUC;
	for(int i=1;i<=g.n;i++)
	{
		if(ChuaXet[i]==0&&DoDaiDuongDiToi[i]<p)
		{
			p=DoDaiDuongDiToi[i];
			li=i;
		}
	}
	return li;
}
void CapNhapDuongDi(int u, DOTHI g)
{
	ChuaXet[u]=1;
	for(int v=0;v<g.n;v++)
	{
		if(ChuaXet[v]==0&&g.a[u][v]>0&&g.a[u][v]<VOCUC)
			if(DoDaiDuongDiToi[v]>DoDaiDuongDiToi[u]+g.a[u][v])
			{
				DoDaiDuongDiToi[v]=DoDaiDuongDiToi[u]+g.a[u][v];
				LuuVet[v]=u;
			}
	}
}
int Chuyen[MAX];
void Dijkstra(int S, int F, DOTHI g)
{
	int i;
	int d=0;
	for(int i=1;i<=g.n;i++)
	{
		ChuaXet[i]=0;
		DoDaiDuongDiToi[i]=VOCUC;
		LuuVet[i]=-1;
	}
	DoDaiDuongDiToi[S]=0;
	while(ChuaXet[F]==0)
	{
		int u=TimDuongDiNhoNhat(g);
		if(u==-1)break;
		CapNhapDuongDi(u,g);
	}
	if(ChuaXet[F]==1)
	{
		printf("\nduong di ngan nhat tu %d den %d\n",S,F);
		i=F;
		//printf("%d",F);
		Chuyen[d]=F;
		while(LuuVet[i]!=S)
		{
			//printf("<-%d",LuuVet[i]);
			Chuyen[++d]=LuuVet[i];
			i=LuuVet[i];
		}
		//printf("<-%d\n",LuuVet[i]);
		Chuyen[++d]=LuuVet[i];
		printf("%d",S);
		for(int i=d-1;i>=0;i--)
			printf("->%d",Chuyen[i]);
		printf("\nvoi do dai la %d\n",DoDaiDuongDiToi[F]);
	}
	else
	{
		printf("\nko co duong di tu dinh %d den dinh %d",S,F);
	}
}
int Sau_Nut[MAX][MAX];
int L[MAX][MAX];
void Floyd(int S, int F, DOTHI g)
{
	int i,j;
	for(i=1;i<=g.n;i++)
	{
		for(j=1;j<=g.n;j++)
		{
			if(g.a[i][j]>0)
			{
				Sau_Nut[i][j]=j;
				L[i][j]=g.a[i][j];
			}
			else
			{
				Sau_Nut[i][j]=-1;
				L[i][j]=VOCUC;
			}
		}
	}
	for(int k=1;k<=g.n;k++)
	{
		for(i=1;i<=g.n;i++)
		{
			for(j=1;j<=g.n;j++)
			{
				if(L[i][j]>L[i][k]+L[k][j])
				{
					L[i][j]=L[i][k]+L[k][j];
					Sau_Nut[i][j]=Sau_Nut[i][k];
				}
			}
		}
	}
	if(Sau_Nut[S][F]==-1)
	{
		printf("ko co duong di");
	}
	else{
		printf("\nduong di ngan nhat tu dinh %d den dinh %d\n",S,F);
		printf("\t%d",S);
		int u=S;
		while(Sau_Nut[u][F]!=F)
		{
			u=Sau_Nut[u][F];
			printf("->%d",u);
		}
	}
	printf("->%d",F);
	printf("\nvoi tong trong so la %d",L[S][F]);
}
//==============================================================
int main()
{
	DOTHI g;

	if(DocMaTranKe(inputfile, g)==1) //doc file duoc
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
	}
	int S,F;
	printf("\nnhap dinh bat dau ");
	scanf("%d",&S);
	printf("\nnhap vao dinh ket thuc ");
	scanf("%d",&F);
	int c;
	do{
	 	printf("\nmoi ban nhap\nNhan phim 1 de tim duong di ngan nhat dung thuat toan Dijkstra \nNhan phim 2 de tim duong di ngan nhat dung thuat toan Floyd \nNhan phim 0 de dong chuong trinh.");
		scanf("%d",&c);
		switch(c) 
		{
			case 1:
			{
				printf("\nthuat toan Dijkstra\n");
				Dijkstra(S,F,g);
				break;
			}
			case 2:
			{
				printf("\nthuat toan floyd");
				Floyd(S,F,g);
				break;
			}
		default:
				return 0;
		}
	}while(c!=0);
}
