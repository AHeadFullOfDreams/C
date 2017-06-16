#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM   20
#define OK  1
#define ERROR 0
#define FALSE 0
#define TRUE  1
#define OVERFLOW -2
typedef int Status;
typedef int Boolean;
Boolean visited[MAX_VERTEX_NUM];
typedef int InfoType;
typedef char VertexType[10];
typedef struct ArcNode{
int  adjvex;
struct ArcNode   *nextarc;
InfoType         *info;
}ArcNode;
typedef struct VNode{
VertexType  data;
ArcNode     *firsttarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
AdjList  vertices;
int      vexnum,arcnum;
int      kind;
}ALGraph;

Status LocateVex(ALGraph G,VertexType u)
{
int i;
for(i=0;i<G.vexnum ;++i)
   if(strcmp(u,G.vertices[i].data )==0)
       return i;
   return ERROR;
}

Status CreatDG(ALGraph&G)
{int f,i,j;VertexType Vstart,Vend;
ArcNode *p,*q;
printf("please input the vexnum and arcnum:\n");
scanf("%d%d",&G.vexnum ,&G.arcnum );

for(i=0;i<G.vexnum ;i++)
{
G.vertices[i].firsttarc =NULL;

}//初始化
printf("please input the information of vertex:\n");
for(i=0;i<G.vexnum ;i++)
{
scanf("%s",&G.vertices[i].data);
}
printf("please input the connective vertexes:\n ");
for(f=0;f<G.arcnum;f++)
{printf("vertex 1--->vertex 2\n");
scanf("%s%s",&Vstart,&Vend);
i=LocateVex(G,Vstart);//弧尾
j=LocateVex(G,Vend);//弧头
 p=(ArcNode *)malloc(sizeof(ArcNode));
(*p).adjvex=j;(*p).nextarc=NULL;
if(!G.vertices[i].firsttarc)
{    G.vertices[i].firsttarc =p;}
else  {
q=G.vertices[i].firsttarc;
while((*q).nextarc)
{     q=(*q).nextarc;}//找到最后一个结点
(*q).nextarc=p;
}
}

return OK;
}


typedef int QElemType;

typedef struct QNode{
 QElemType  data;
 struct QNode  *next;
}QNode,*QueuePtr;
typedef struct{
QueuePtr front;
QueuePtr rear;
}LinkQueue;
Status InitQueue(LinkQueue&Q){
Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
if(!Q.front)exit(OVERFLOW);
Q.front->next=NULL;
return OK;
}
Status EnQueue(LinkQueue&Q,QElemType e){
QueuePtr p;
p=(QueuePtr)malloc(sizeof(QNode));
if(!p) exit(OVERFLOW);
p->data=e;
p->next=NULL;
Q.rear->next=p;
Q.rear=p;
return OK;
}
Status DeQueue(LinkQueue&Q,QElemType &e){
QueuePtr p;
if(Q.front==Q.rear)return ERROR;
p=Q.front->next;
e=p->data;
Q.front->next=p->next;
if(Q.rear==p) Q.rear=Q.front;
free(p);
return OK;
}

Status QueueEmpty(LinkQueue Q){
if (Q.front->next==NULL)
		return OK;
	else
		return ERROR;
}
int FirstAdjVex(ALGraph G,int m)
{ArcNode *p;int q;
if(G.vertices[m].firsttarc)
{p=G.vertices[m].firsttarc;
    q=(*p).adjvex;
    return q;}
return -1;
}
int NextAdjVex(ALGraph G,int m,int n)
{ArcNode *p;int i;
p=G.vertices[m].firsttarc;
while((*p).adjvex !=n)  
{   p=(*p).nextarc;}
if((*p).nextarc)
{  p=(*p).nextarc;
   i=(*p).adjvex;
     return i;}
else  return -1;
}
Status Visit(ALGraph&G,int v)
{
char p[10],*q;
strcpy(p,"顶点");
q=strcat(p,G.vertices[v].data);
strcpy(G.vertices[v].data,q);
printf("%s",G.vertices[v].data);
return OK;
}


void BFSTraverse(ALGraph G,Status(*Visit)(ALGraph&G,int V))
{LinkQueue Q;
int v,w,u;
for(v=0;v<G.vexnum ;v++) visited[v]=FALSE;
InitQueue(Q);
for(v=0;v<G.vexnum ;v++)
{
    if(!visited[v]){
       visited[v]=TRUE;   
	   Visit(G,v);
       EnQueue(Q,v);
       while(!QueueEmpty(Q)){
	   DeQueue(Q,u);
	   for(w=FirstAdjVex(G,u);w>=0;w=NextAdjVex(G,u,w))
		   if(!visited[w]) {
		   visited[w]=TRUE;  Visit(G,w);
		   EnQueue(Q,w);
		   }
	   }
	}
}

}


void main()
{
ALGraph  G;
CreatDG(G);
printf("the  result of BFS is:\n");
BFSTraverse(G,Visit);

printf("\n");
}