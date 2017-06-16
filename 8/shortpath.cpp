#include<stdio.h>
#include<string.h>
#include<limits.h>
#define INT_MAX 10000
#define MAX_VERTEX_NUM   20
#define OK  1
#define ERROR 0
#define FALSE 0
#define TRUE  1

typedef int Status;

typedef int VRType;
typedef char InfoType;
typedef char VertexType[10];

typedef struct ArcCell{
VRType  adj;
InfoType  *info;
}ArcCell,AdjMartrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
VertexType  vexs[MAX_VERTEX_NUM];
AdjMartrix  arcs;
int         vexnum,arcnum;
}MGraph;


void InitGraph(MGraph&G)
{
for(int i=0;i<G.vexnum ;i++)
   for(int j=0;j<G.vexnum ;j++)
   {G.arcs[i][j].adj=INT_MAX;
   G.arcs[j][j].adj =0;
   }
}
Status LocateVex(MGraph G,VertexType u)
{
int i;
for(i=0;i<G.vexnum ;++i)
   if(strcmp(u,G.vexs[i])==0)
       return i;
   return ERROR;
}
Status CreatDN(MGraph&G)
{VertexType Vstart,Vend;int f,i,j,w;
printf("please input the vertexnum and arcnum:\n");
scanf("%d",&G.vexnum );
scanf("%d",&G.arcnum );
InitGraph(G);
printf("please intput the information of vertex:\n");
getchar();
for(f=0;f<G.vexnum ;f++)
   scanf("%s",&G.vexs[f]);

printf("please input the connective vertexes and its weight:\n ");

for(f=0;f<G.arcnum;f++)
{printf("vertex 1--->vertex 2 \n");
scanf("%s%s%d",&Vstart,&Vend,&w);
i=LocateVex(G,Vstart);
j=LocateVex(G,Vend);
G.arcs[i][j].adj =w;
}
return OK;
}
typedef struct Node {
int  locate;
Node *pre;
}Node,PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];
void ShortestPath_DIJ(MGraph G,int v0,PathMatrix &P,ShortPathTable &D)
{int v,w,min,i,j,l,final[MAX_VERTEX_NUM];Node *p;
for(v=0;v<G.vexnum ;++v){
   final[v]=FALSE;
   D[v]=G.arcs[v0][v].adj ;
   for(w=0;w<G.vexnum ;++w)  
   {
   P[v][w].pre =NULL;
   P[v][w].locate =w;
   }
   if(D[v]<INT_MAX) {
   P[v][v].pre=&P[v][v0];}
}
D[v0]=0;final[v0]=TRUE;
for(i=1;i<G.vexnum ;++i){
   min=INT_MAX;
   for(w=0;w<G.vexnum ;++w)
	   if(!final[w])
		   if(D[w]<min){v=w; min=D[w];}
   final[v]=TRUE;
   for(w=0;w<G.vexnum ;++w)
	   if(!final[w]&&(min+G.arcs[v][w].adj <D[w]))
	   {D[w] =min + G.arcs[v][w].adj ;
		 for(j=0;j<G.vexnum ;++j)
		 {  P[w][j].pre =P[v][j].pre ;  
		 P[w][w].pre =&P[v][v];
		 }
	   }
}

for(i=0;i<G.vexnum ;i++)
{if(D[i]==INT_MAX||D[i]==0)
{ printf("the path of the start to the %s is nonexistent",G.vexs[i]);}
else{
	printf("the shortest length of the start to the %s is %d  and the shortest path is:\n",G.vexs[i],D[i]);
    p=&P[i][i];
	while((*p).pre)
	{l=(*p).locate;p=(*p).pre;
	printf(" %s<--- ",G.vexs[l]);
	}
	l=(*p).locate ;
    printf(" %s ",G.vexs[l]);
}
printf("\n");
}
}
typedef struct PNode{
int  locate;
PNode  *pre;
}PNode,Pathmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int Distancmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
void ShortestPath_FLOYD(MGraph G,Pathmatrix &P,Distancmatrix &D,int vstart,int vend){
int v,w,u,i;
for(v=0;v<G.vexnum ;++v){ 
   for(w=0;w<G.vexnum ;++w){
	   D[v][w]=G.arcs[v][w].adj ;
	   for(u=0;u<G.vexnum ;++u)  {P[v][w][u].locate =u; P[v][w][u].pre=NULL;}
		if(D[v][w]<INT_MAX){
		P[v][w][v].pre =NULL;P[v][w][w].pre =&P[v][w][v];
		}
	}	
}
for(u=0;u<G.vexnum ;++u){
	for(v=0;v<G.vexnum ;++v){
      for(w=0;w<G.vexnum ;++w)
		   if(D[v][u]+D[u][w]<D[v][w]){
		   D[v][w]=D[v][u]+D[u][w]; 
		   for(i=0;i<G.vexnum ;++i)
		   {P[u][w][u].pre =P[v][u][u].pre ;
		     P[v][w][i].pre =P[u][w][i].pre;
               //P[v][w][i].pre=(P[v][u][i].pre||P[u][w][i].pre);
		   }
		   }
	}
}
}
void main(){
MGraph G;
char p[10],q[10],k[10];
 int v0,vstart,vend,v;
 PNode *e;
 PathMatrix P;Pathmatrix B;
ShortPathTable D;Distancmatrix A;
CreatDN(G);
printf("the Matrix is:");
for(int i=0;i<G.vexnum ;i++)
{ printf("\n");
     for(int j=0;j<G.vexnum ;j++)
	 {if(G.arcs[i][j].adj==10000)  printf("  ¡Þ  ");
	else printf("  %d  ",G.arcs[i][j].adj);}}
printf("\n");
printf("please input the start :\n");
scanf("%s",&p);
v0=LocateVex(G,p);
ShortestPath_DIJ(G, v0,P,D);
printf("please input the start and the end :\n");
scanf("%s%s",&k,&q);
vstart=LocateVex(G,k);
vend=LocateVex(G,q);
ShortestPath_FLOYD(G,B,A,vstart,vend);
printf("the shortest path from %s to %s is %d and the shortest path is :\n",k,q,A[vstart][vend]);
e=&B[vstart][vend][vend];
while((*e).pre )
{
v=(*e).locate ;e=(*e).pre ;
printf("%s<--- ",G.vexs[v]);
}
v=(*e).locate ;printf("%s",G.vexs[v]);
printf("\n");
}
