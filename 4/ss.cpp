#include<stdio.h>
#include<stdlib.h>
#define OK 0
#define ERROR 1
#define OVERFLOW -2
#define MAXQSIZE  100
typedef  int  QElemType;
typedef  int  Status;
typedef struct{
QElemType  *base;
int  front;
int  rear;
}SqQueue;

Status InitQueue(SqQueue&Q){
Q.base=(QElemType*)malloc(MAXQSIZE *sizeof(QElemType));
if(!Q.base)exit(OVERFLOW);
Q.front=Q.rear=NULL;
return OK;
}
Status EnQueue(SqQueue&Q,QElemType e){
if((Q.rear+1)%MAXQSIZE==Q.front) return ERROR;
Q.base[Q.rear]=e;
Q.rear=(Q.rear+1)%MAXQSIZE;
return OK;
}
Status DeQueue(SqQueue&Q,QElemType &e){
if(Q.front==Q.rear) return ERROR;
e=Q.base[Q.front];
Q.front=(Q.front+1)%MAXQSIZE;
return OK;
}
int QueueLength(SqQueue Q){
return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}
void Show(SqQueue&Q){
int a,i,j=Q.front;
a=QueueLength(Q);
for(i=0;i<a;i++)
{printf("%4.d",Q.base[j]);
   j++;
}
}
void main(){
 SqQueue Q;int a,i,j,e,o,f;
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