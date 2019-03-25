#include<conio.h>
#include<stdio.h>

#define MAX 10
#define inputfile "D:/test3.txt"
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
int KiemTraMaTrankeHopLe(DOTHI g)
{
	int i;
	for(i=1;i<=g.n;i++)
	{
		if(g.a[i][i]!=0)
		return 0;
	}
	return 1;
}
int KTvohuong(DOTHI g)
{
	int i,j;
	for(i=1;i<=g.n;i++)
	{
		for(j=1;j<g.n;j++)
		{
			if(g.a[i][j]!=g.a[j][i])
			return 0;
		}
	}
	return 1;
}
void TimDinhlt(DOTHI g, int nhan[MAX], int i)
{
	for(int j=0;j<g.n;j++)
	{
		if(g.a[i][j]!=0&&nhan[j]!=nhan[i])
		{
			nhan[j]=nhan[i];
			TimDinhlt(g,nhan,j);
		}
	}
}
void Xetlt(DOTHI g)
{
	int nhan[MAX];
	int i;
	for(i=0;i<g.n;i++)
		nhan[i]=0;
	int Sotplt=0;
	for(i=0;i<g.n;i++)
	{
		if(nhan[i]==0)
		{
			Sotplt++;
			nhan[i]=Sotplt;
			TimDinhlt(g,nhan,i);	
		}
	}
	printf("\nSo tp lien thong la %d ",Sotplt );
	for(i=1;i<=Sotplt;i++)
	{
		printf("\n thanh phan lien thong thu %d ",i);
		for(int j=0;j<g.n;j++)
		{
			if(nhan[j]==i)
			printf("%d",j+1);
		}
		printf("\n");
	}	
}
struct STACK
{
	int array[100];
	int size;
};
void KhoiTaoStack(STACK&stack)
{
	stack.size=0;
}
void DayGiaTriVaoStack(STACK&stack, int value)
{
	if(stack.size+1>=100)
	return;
	stack.array[stack.size]=value;
	stack.size++;
}
void TimDuongDi(int i, DOTHI&g,STACK&stack)
{
	for(int j=0;j<g.n;j++)
	{
		if(g.a[i][j]!=0)
		{
			g.a[i][j]=g.a[i][j]=0;
			TimDuongDi(j,g,stack);
		}
	}
	DayGiaTriVaoStack(stack,i);
}
int KTChuTrinhEuler(DOTHI g)
{
	int i,j;
	int x=0;
	int flag=0;
	for(i=0;i<g.n;i++)
	{
		for(j=0;j<g.n;j++)
		{
			if(g.a[i][j]!=0)
			{
				x=i;
				flag=1;
				break;
			}
		}
		if(flag==1)
			break;
	}
	DOTHI temp=g;
	STACK stack;
	KhoiTaoStack(stack);
	TimDuongDi(x,temp,stack);
	for(i=0;i<temp.n;i++)
	{
		for(j=0;j<temp.n;j++)
		{
			if(temp.a[i][j]!=0)
			return 0;
		}
	}
	if(stack.array[stack.size-1]!=stack.array[0])
	return 0;
	printf("chu trinh euler ");
	for(i=stack.size-1;i>=0;i--)
		printf("%d",stack.array[i]+1);
	return 1;	
}
int KTDuongDiEuler(DOTHI g)
{
	int i,j;
	int x=0;
	int flag=0;
	int bac=0;
	for(i=0;i<g.n;i++)
	{
		bac=0;
		for(j=0;j<g.n;j++)
		{
			if(g.a[i][j]!=0)
			{
				bac++;
			}
		}
		if(bac%2!=0)
		{
			x=i;
			flag=1;
			break;
		}
	}
	if(flag==0)
	return 0;
	DOTHI temp=g;
	STACK stack;
	KhoiTaoStack(stack);
	TimDuongDi(x,temp,stack);
	for(i=0;i<temp.n;i++)
	{
		for(j-0;j<temp.n;j++)
		{
			if(temp.a[i][j]!=0)
			return 0;
		}
	}
	if(stack.array[stack.size-1]==stack.array[0])
	return 0;
	printf("duong di euler");
	for(i=stack.size-1;i>=0;i--)
		printf("%d",stack.array[i]+1);
	return 1;	
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
void Dijkstra(int S, int F, DOTHI g)
{
	int i;
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
		printf("duong di ngan nhat tu %d den %d\n",S,F);
		i=F;
		printf("%d",F);
		while(LuuVet[i]!=S)
		{
			printf("<-%d",LuuVet[i]);
			i=LuuVet[i];
		}
		printf("<-%d\n",LuuVet[i]);
		printf("\tvoi do dai la %d\n",DoDaiDuongDiToi[F]);
	}
	else
	{
		printf("ko co duong di tu dinh %d den dinh %d",S,F);
	}
}
int Sau_Nut[MAX][MAX];
int L[MAX][MAX];
void Floyd(DOTHI g)
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
	int S,F;
	printf("\nnhap dinh bat dau");
	scanf("%d",&S);
	printf("\nnhap dinh ket thuc");
	scanf("%d",&F);
	if(Sau_Nut[S][F]==-1)
	{
		printf("ko co duong di");
	}
	else{
		printf("duong di ngan nhat tu dinh %d den dinh %d\n",S,F);
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
	if(KiemTraMaTrankeHopLe(g)==1)
	{
		printf("ma tran hop le ");
		
	}
	else
	printf("ma tran ko hop le");
	if(KTvohuong(g)==0)
	{
		printf("\ndo thi co huong");
		
	}
	else
	printf("\ndo thi vo huong ");
	Xetlt(g);
	if(!KTChuTrinhEuler(g))
	{
		printf("\nko co chu trinh euler trong do thi ");
		if(!KTDuongDiEuler(g))
		{
			printf("\nko co duong di euler trong do thi ");
		}
	}
	int S,F;
	printf("\nnhap dinh bat dau ");
	scanf("%d",&S);
	printf("\nnhap vao dinh ket thuc ");
	scanf("%d",&F);
	printf("thuat toan Dijkstra");
	Dijkstra(S,F,g);
	printf("thuat toan floyd");
	Floyd(g);
	return 0;
}
