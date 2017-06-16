#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define MAXQSIZE  100  //�����г���       
typedef int Status;

typedef struct
{
	char name[20];
	char sex;   //�Ա�'F'��ʾŮ�ԣ�'M'��ʾ����
}Person;

typedef Person QElemType;

typedef struct {
     QElemType  *base;  
     int  front;     // ͷָ�룬�����в��գ�ָ�����ͷԪ��
     int  rear;      // βָ�룬�����в��գ�ָ�� ����βԪ�� ����һ��λ��

} SqQueue;


Status InitQueue (SqQueue &Q) 
{
   // ����һ���ն���Q
    Q.base = (QElemType *) malloc (MAXQSIZE *sizeof (QElemType));
    if (!Q.base) exit (OVERFLOW);  // �洢����ʧ��
    Q.front = Q.rear = 0;  //��ʼ�ն���״̬
    return OK;  
}

Status EnQueue (SqQueue &Q, QElemType e) 
{      // ����Ԫ��eΪQ���µĶ�βԪ��
    if ((Q.rear+1) % MAXQSIZE == Q.front) 
        return ERROR; //������
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1) % MAXQSIZE;
    return OK;
}

Status DeQueue (SqQueue &Q, QElemType &e) 
{ // �����в��գ���ɾ��Q�Ķ�ͷԪ�أ�
   // ��e������ֵ��������OK;  ���򷵻�ERROR
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
    if(QueueEmpty(Q)) printf("����Ϊ�գ�\n");
    e= Q.base[Q.front];
	return OK;
}

int QueueLength(SqQueue Q)
{
	return (Q.rear -Q.front +MAXQSIZE) %MAXQSIZE ;
}

void DancePartner(Person dancer[],int num)
{
	//�ṹ����dancer�д���������Ů��num�������������
	Person p;
	SqQueue Mdancers,Fdancers;
    InitQueue(Mdancers);// ��ʿ���г�ʼ��
    InitQueue(Fdancers);// Ůʿ���г�ʼ��
	for(int i=0;i<num;i++)
	{
		p=dancer[i];
        if(p.sex =='F')
          EnQueue(Fdancers,p);//����Ů��
        else
          EnQueue(Mdancers,p);//�����ж�
	}
	printf("����������صĴ��:\n");
	while(!QueueEmpty(Fdancers) && !QueueEmpty(Mdancers))
	{
          DeQueue(Fdancers,p); //Ůʿ����
          printf("%s �� ",p.name);//��ӡ����Ůʿ��
		  DeQueue(Mdancers,p); //��ʿ����
	      printf("%s ",p.name);//��ӡ������ʿ��

	}

	if(!QueueEmpty(Fdancers))
	{
		//���Ůʿʣ����������ͷŮʿ������
		printf("������ %d Ůʿ���ڵȴ���\n",QueueLength(Fdancers));
        QueueFront(Fdancers,p);//ȡ��ͷ
		printf("��һλ����������ص�Ůʿ�������ǣ�%s  \n",p.name);
	}
    else if(!QueueEmpty(Mdancers))
	{
		//���Ůʿʣ����������ͷŮʿ������
		printf("\n ������ %d ��ʿ���ڵȴ���\n",QueueLength(Mdancers));
        QueueFront(Mdancers,p);//ȡ��ͷ
		printf("%s ��һλ����������ص���ʿ�������ǣ� \n",p.name);
	}
}


void main()
{
	int i,j; 
    Person dancer[10];
    printf("���������������:\n");
    scanf("%d",&j);
    while(j<=0)
    {
      printf("�������, ����������:");
      scanf("%d",&j);
    }  
    for(i=1;i<=j;i++)
    {
      printf("�������%d������˵�����:",i);
      scanf("%s",&dancer[i-1].name);
      printf("�������%d������˵��Ա�(F/M):",i);
      scanf("%s",&dancer[i-1].sex);
      while(dancer[i-1].sex!='F'&&dancer[i-1].sex!='M')
      {
          printf("�������, ����������:");
          scanf("%s",&dancer[i-1].sex);
      }
    }
	DancePartner(dancer,j);
   
}




