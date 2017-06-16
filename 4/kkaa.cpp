#include<stdio.h>
#include<stdlib.h>
#define OK 0
#define ERROR 1
#define OVERFLOW -2
typedef  int  QElemType;
typedef  int  Status;
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
p->data=e;p->next=NULL;
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
void Show(LinkQueue&Q){
QueuePtr p;
p=Q.front;
while(p!=Q.rear)
{  p=p->next;
  printf("%4.d",p->data);
   }
}
void main(){
LinkQueue Q;int a,i,j,e,o,f;
InitQueue(Q);
if(InitQueue(Q)==OK)
{printf("succesfully initialize the linkqueue!");}
else
{printf("fail to initialize the linkqueue\n");}
printf("\n");
printf("please input the length of the linkqueue\n");
scanf("%d",&a);
printf("please input the number of the linkqueue\n");
for(i=0;i<a;i++)
{scanf("%d",&j);
EnQueue(Q,j);
}
Show(Q);printf("\n");
printf("please input the number you want to insert:\n");
scanf("%d",&o);
EnQueue(Q,o);printf("the current linkqueue is\n");
Show(Q);printf("\n");
printf("after the delete\n");
DeQueue(Q,f);
Show(Q);printf("\n");
printf("the delete number is %d\n",f);
}