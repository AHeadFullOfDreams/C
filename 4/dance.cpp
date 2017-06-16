#include<stdio.h>
#include<stdlib.h>
#define OK 0
#define ERROR 1
#define OVERFLOW -2
typedef  char  QElemType;
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
int QueueLength(LinkQueue Q){
	int i=1;QueuePtr p=Q.front ;
while(p->next!=Q.rear)
{p=p->next;

i++;
}
return i;
}
Status Show(LinkQueue&Q){
QueuePtr p;
p=Q.front;
while(p!=Q.rear)
{  p=p->next;
  printf("%4.c",p->data);
   }
if(Q.front->next=NULL )return ERROR;
}
Status QueueEmpty(LinkQueue Q){
if (Q.front->next==NULL)
		return ERROR;
	else
		return OK;
}
int main(){
LinkQueue Q,F,M;int a,i,min,l,f,m;char j,b,p,q,h,e;
printf("������һ��������Ҫ����\n");
scanf("%d",&a);
InitQueue(M);InitQueue(F);InitQueue(Q);
for(i=0;i<a;i++)
{printf("�������������:\n");
scanf("%s",&j);
EnQueue(Q,j);
printf("����������Ա�(F/M):\n");
scanf("%s",&b);
if(b=='F'){EnQueue(F,j);}
else{EnQueue(M,j);}
}
f= QueueLength(F);m= QueueLength(M);
min=f>m?m:f;
for(l=1;l<=min;l++)
{DeQueue(F,p); DeQueue(M,q);
printf("��%d����Գɹ���ʼ������ǣ�\n",l);
putchar(p);printf("��");putchar(q);
printf("\n");}

if(QueueEmpty(F)==OK&&QueueEmpty(M)==ERROR)
{printf("ʣ�»�û�ҵ�������Ů��:\n");
Show(F);
DeQueue(F,h);printf("\n");
printf("��һ��������ص���Ů��: %c\n",h);
}
if(QueueEmpty(F)==ERROR&&QueueEmpty(M)==OK)
{printf("ʣ�»�û�ҵ�����������:\n");
Show(M);
DeQueue(M,e);printf("\n");
printf("��һ��������ص�������: %c\n",e);
}
if(QueueEmpty(F)==ERROR&&QueueEmpty(M)==ERROR)
{printf("���˵Ⱥ�ȫ���ҵ����");
}
printf("\n");
return 0;
}
