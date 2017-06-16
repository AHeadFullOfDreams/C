#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define INFINITY    INT_MAX
#define MAX_VERTEX_NUM   20
#define OK  1
#define ERROR 0
#define FALSE 0
#define TRUE  1

typedef int Status;
typedef int Boolean;
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
//GraphKind   kind;
}MGraph;
Boolean visited[MAX_VERTEX_NUM];
Status (*VisitFunc)(VertexType  v);

void InitGraph(MGraph&G)
{
for(int i=0;i<G.vexnum ;i++)
   for(int j=0;j<G.vexnum ;j++)
   {G.arcs[i][j].adj=0;
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
Status CreatUDG(MGraph&G)
{VertexType Vstart,Vend;int f,i,j;
printf("please input the vertexnum and arcnum:\n");
scanf("%d",&G.vexnum );
scanf("%d",&G.arcnum );
InitGraph(G);
printf("please intput the information of vertex:\n");
getchar();
for(f=0;f<G.vexnum ;f++)
   scanf("%s",&G.vexs[f]);

for(f=0;f<G.vexnum ;f++)
    printf("%s",G.vexs[f]);

printf("please input the connective vertexes:\n ");

for(f=0;f<G.arcnum;f++)
{printf("vertex 1--->vertex 2\n");
scanf("%s%s",&Vstart,&Vend);
i=LocateVex(G,Vstart);
j=LocateVex(G,Vend);
G.arcs[i][j].adj =1;
//G.arcs[j][i].adj =1;
}
return OK;
}

Status Visit(VertexType p)
{
	printf(" %s ",p);
return OK;
}

int FirstAdjVex(MGraph G,VertexType v)
{int i,j=0,k;
k=LocateVex(G,v);
for(i=0;i<G.vexnum ;i++)
   if(G.arcs[k][i].adj !=j)
       return i;
   return -1;
}
int NextAdjVex(MGraph G,VertexType v,VertexType w)
{
int i,j=0,k1,k2;
k1=LocateVex(G,v);
k2=LocateVex(G,w);
for(i=k2+1;i<G.vexnum ;i++)
   if(G.arcs[k1][i].adj !=j)
	   return i;
   return -1;
}
void DFS(MGraph G,VertexType V)
{int v,w;
v=LocateVex(G,V);
visited[v]=TRUE;
VisitFunc(V);
for(w=FirstAdjVex(G,G.vexs[v]);w>=0;w=NextAdjVex(G,G.vexs[v],G.vexs[w]))
   if(!visited[w])  DFS(G,G.vexs[w]);
}
void DFSTraverse(MGraph G,Status (*Visit)(VertexType V))
{
VisitFunc=Visit;int v;
for(v=0;v<G.vexnum ;++v) visited[v]=FALSE;
for(v=0;v<G.vexnum ;++v)
   if(!visited[v]) DFS(G,G.vexs[v]);
}
void main(){
MGraph  G;
CreatUDG(G);
printf("the Matrix is:");
for(int i=0;i<G.vexnum ;i++)
{ printf("\n");
     for(int j=0;j<G.vexnum ;j++)
	 { printf(" %d ",G.arcs[i][j].adj);}}

printf("\n");
printf("the result of DFS:\n");
DFSTraverse(G,Visit);


printf("\n");

}