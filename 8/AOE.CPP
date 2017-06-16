#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#define INFINITY    INT_MAX
#define MAX_VERTEX_NUM   20
#define OK  1
#define ERROR 0
#define FALSE 0
#define TRUE  1
#define OVERFLOW -2
typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef char VertexType[10];
typedef struct ArcNode{
int  adjvex;
struct ArcNode   *nextarc;
InfoType         *info;
}ArcNode;
typedef struct VNode{
VertexType  data;
ArcNode     *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
AdjList  vertices;
int      vexnum,arcnum;
int      kind;
}ALGraph;

typedef struct ArcCell{
VRType  adj;
InfoType  *info;
}ArcCell,AdjMartrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
VertexType  vexs[MAX_VERTEX_NUM];
AdjMartrix  arcs;
int         vexnum,arcnum;
}MGraph;


//构造有向无环网AOE

Status LocateVex(ALGraph G,VertexType u)
{
int i;
for(i=0;i<G.vexnum ;++i)
   if(strcmp(u,G.vertices[i].data )==0)
       return i;
   return ERROR;
}

void InitGraph(MGraph&G)
{
for(int i=0;i<G.vexnum ;i++)
   for(int j=0;j<G.vexnum ;j++)
   {G.arcs[i][j].adj=0;
   }
}

Status CreatDG(ALGraph&G,MGraph&H)//输入的同时用两种方式存储网
{int f,i,j;VertexType Vstart,Vend;
ArcNode *p,*q;
printf("please input the vexnum and arcnum:\n");
scanf("%d%d",&G.vexnum ,&G.arcnum );
H.vexnum=G.vexnum ;H.arcnum=G.arcnum ;
InitGraph(H);//初始化临接矩阵
for(i=0;i<G.vexnum ;i++)
{
G.vertices[i].firstarc =NULL;
}
printf("please input the information of vertex:\n");
for(i=0;i<G.vexnum ;i++)
{
scanf("%s",&G.vertices[i].data);
strcpy(H.vexs[i],G.vertices[i].data );
}
printf("please input the connective vertexes:\n ");
for(f=0;f<G.arcnum;f++)
{printf("vertex 1--->vertex 2\n");
scanf("%s%s",&Vstart,&Vend);
i=LocateVex(G,Vstart);
j=LocateVex(G,Vend);

H.arcs[i][j].adj =1;//临接矩阵赋值

 p=(ArcNode *)malloc(sizeof(ArcNode));
(*p).adjvex=j;(*p).nextarc=NULL;
if(!G.vertices[i].firstarc)
{    G.vertices[i].firstarc =p;}
else  {
q=G.vertices[i].firstarc;
while((*q).nextarc)
{     q=(*q).nextarc;}
(*q).nextarc=p;
}
}
return OK;
}

//以下为栈的基本操作
#define STACK_INIT_SIZE  100
#define STACKINCREMENT  10
#define OVERFLOW  -2
typedef int SElemType;  
typedef struct{
 SElemType  *base;
 SElemType  *top;
 int stacksize;
}Stack;
Status InitStack(Stack&S)
{
 S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
 if(!S.base)exit(OVERFLOW);
 S.top=S.base;
 S.stacksize=STACK_INIT_SIZE;
 return OK;
}
Status Push(Stack&S,SElemType e){
	if(S.top-S.base>=S.stacksize){
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
    if(!S.base)exit(OVERFLOW);
	S.top=S.base+S.stacksize;
	S.stacksize+=STACKINCREMENT;}
	*S.top++=e;
	return OK;}
Status Pop(Stack&S,SElemType&e){
	if(S.top==S.base)return ERROR;
	e=*--S.top;
	return OK;}
Status StackEmpty(Stack&S){

if(S.top==S.base)
{return OK;}
else 
{return ERROR;}
}

//以下为求关键路径算法
int ve[MAX_VERTEX_NUM];//全局变量ve
int vl[MAX_VERTEX_NUM];//全局变量vl
int indegree[MAX_VERTEX_NUM];
Status FindIndegree(ALGraph G,int indegree[MAX_VERTEX_NUM])
{int i,j;ArcNode *p;
for(i=0;i<G.vexnum ;i++)
{     indegree[i]=0;}
for(i=0;i<G.vexnum ;i++)
{p=G.vertices[i].firstarc ;
   j=1;
   while(p->nextarc)
	  { p=(*p).nextarc ;
      j++;
   }
   indegree[i]=j;
}
return OK;
}
Status TopologicalOrder(ALGraph G,Stack &T)
{ Stack S;int indegree[MAX_VERTEX_NUM];
int count,i,j,k;ArcNode *p;
FindIndegree(G,indegree);
InitStack(T);count=0;
for(i=0;i<G.vexnum ;i++)
      ve[i]=0;
while(!StackEmpty(S)){
  Pop(S,j);Push(T,j); ++count;
  for(p=G.vertices[j].firstarc ;p;p=p->nextarc ){
	  k=p->adjvex;
      if(--indegree[k]==0) Push(S,k);
	  if(ve[j]+*(p->info )>ve[k])   ve[k]=ve[j]+*(p->info );
}
}
if(count<G.vexnum ) return ERROR;
else return OK;
}
Status CriticalPath(ALGraph G)
{Stack  T;int i,j,k,ee,el,dut;
char tag;
ArcNode *p;
if(!TopologicalOrder(G,T))  return ERROR;
for(i=0;i<G.vexnum ;i++)
{vl[i]=ve[G.vexnum-1];}
while(!StackEmpty(T))
     for(Pop(T,j),p=G.vertices[j].firstarc;p;p=p->nextarc )
	 {
	 k=p->adjvex ; dut=*(p->info );
	 if(vl[k]-dut<vl[j])  vl[j]=vl[k]-dut;
	 }
for(j=0;j<G.vexnum ;++j)
{ 
	for(p=G.vertices[j].firstarc;p;p=p->nextarc ){
		k=p->adjvex ;dut=*(p->info );
		ee=ve[j];el=vl[k]-dut;
		tag=(ee==el)?'*':' ';
		printf("%d %d %d %d %d %s",j,k,dut,ee,el,tag);
	}
}
}





void main()
{
ALGraph  G;MGraph H;

CreatDG(G,H);

printf("The Critical Path is:\n");

CriticalPath(G);


}