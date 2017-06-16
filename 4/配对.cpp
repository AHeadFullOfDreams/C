#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define MAXQSIZE  100  //最大队列长度       
typedef int Status;

typedef struct
{
	char name[20];
	char sex;   //性别，'F'表示女性，'M'表示男性
}Person;

typedef Person QElemType;

typedef struct {
     QElemType  *base;  
     int  front;     // 头指针，若队列不空，指向队列头元素
     int  rear;      // 尾指针，若队列不空，指向 队列尾元素 的下一个位置

} SqQueue;


Status InitQueue (SqQueue &Q) 
{
   // 构造一个空队列Q
    Q.base = (QElemType *) malloc (MAXQSIZE *sizeof (QElemType));
    if (!Q.base) exit (OVERFLOW);  // 存储分配失败
    Q.front = Q.rear = 0;  //初始空队列状态
    return OK;  
}

Status EnQueue (SqQueue &Q, QElemType e) 
{      // 插入元素e为Q的新的队尾元素
    if ((Q.rear+1) % MAXQSIZE == Q.front) 
        return ERROR; //队列满
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1) % MAXQSIZE;
    return OK;
}

Status DeQueue (SqQueue &Q, QElemType &e) 
{ // 若队列不空，则删除Q的队头元素，
   // 用e返回其值，并返回OK;  否则返回ERROR
    if (Q.front == Q.rear)  return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front+1) % MAXQSIZE;
    return OK;
}



Status QueueEmpty(SqQueue Q)
{
     if (Q.front == Q.rear)  
		 return TRUE;
	 else
		 return FALSE;
}

Status QueueFront(SqQueue Q, QElemType &e)
{
    if(QueueEmpty(Q)) printf("队伍为空！\n");
    e= Q.base[Q.front];
	return OK;
}

int QueueLength(SqQueue Q)
{
	return (Q.rear -Q.front +MAXQSIZE) %MAXQSIZE ;
}

void DancePartner(Person dancer[],int num)
{
	//结构数组dancer中存放跳舞的男女，num是跳舞的人数。
	Person p;
	SqQueue Mdancers,Fdancers;
    InitQueue(Mdancers);// 男士队列初始化
    InitQueue(Fdancers);// 女士队列初始化
	for(int i=0;i<num;i++)
	{
		p=dancer[i];
        if(p.sex =='F')
          EnQueue(Fdancers,p);//排入女队
        else
          EnQueue(Mdancers,p);//排入男队
	}
	printf("即将进入舞池的搭档是:\n");
	while(!QueueEmpty(Fdancers) && !QueueEmpty(Mdancers))
	{
          DeQueue(Fdancers,p); //女士出队
          printf("%s 和 ",p.name);//打印出队女士名
		  DeQueue(Mdancers,p); //男士出队
	      printf("%s ",p.name);//打印出队男士名

	}

	if(!QueueEmpty(Fdancers))
	{
		//输出女士剩余人数及队头女士的名字
		printf("现在有 %d 女士正在等待。\n",QueueLength(Fdancers));
        QueueFront(Fdancers,p);//取队头
		printf("下一位即将进入舞池的女士的名字是：%s  \n",p.name);
	}
    else if(!QueueEmpty(Mdancers))
	{
		//输出女士剩余人数及队头女士的名字
		printf("\n 现在有 %d 男士正在等待。\n",QueueLength(Mdancers));
        QueueFront(Mdancers,p);//取队头
		printf("%s 下一位即将进入舞池的男士的名字是： \n",p.name);
	}
}


void main()
{
	int i,j; 
    Person dancer[10];
    printf("请输入跳舞的人数:\n");
    scanf("%d",&j);
    while(j<=0)
    {
      printf("输入错误, 请重新输入:");
      scanf("%d",&j);
    }  
    for(i=1;i<=j;i++)
    {
      printf("请输入第%d跳舞的人的姓名:",i);
      scanf("%s",&dancer[i-1].name);
      printf("请输入第%d跳舞的人的性别(F/M):",i);
      scanf("%s",&dancer[i-1].sex);
      while(dancer[i-1].sex!='F'&&dancer[i-1].sex!='M')
      {
          printf("输入错误, 请重新输入:");
          scanf("%s",&dancer[i-1].sex);
      }
    }
	DancePartner(dancer,j);
   
}




