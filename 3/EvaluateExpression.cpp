#include <stdio.h>
#include <conio.h>  //conio��Console Input/Output������̨����������ļ�д�����ж�����ͨ������̨���������������������ĺ�������Ҫ��һЩ�û�ͨ�������̲����Ķ�Ӧ����������getch()�����ȵȡ�
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define STACK_INIT_SIZE 100  //��ʼ������
#define STACKINCREMENT 10    //�洢�ռ�ķ�������

typedef char ElemType;     
typedef ElemType OperandType;   //������
typedef char OperatorType;

typedef struct
{
 ElemType *base;
 ElemType *top;
 int stacksize;
}SqStack;

 

Status InitStack(SqStack &S)
{
 //����һ����ջS
    S.base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if(!S.base) exit (OVERFLOW);
 S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S){
 ElemType e;
 if (S.top == S.base) return ERROR;
 e = *(S.top-1);
 return e;
}

Status Push (SqStack &S,ElemType e)
{
 //����Ԫ��eΪ�µ�ջ��Ԫ��
 if (S.top - S.base >= S.stacksize){
  S.base = (ElemType *) realloc ( S.base,
   (S.stacksize + STACKINCREMENT) * sizeof(ElemType));
  if(!S.base) exit (OVERFLOW);
  S.top = S.base + S.stacksize;
  S.stacksize += STACKINCREMENT;
 }
 *S.top++ = e;
 return OK;
}

Status Pop (SqStack &S,ElemType &e){
 //��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
    if(S.top == S.base) return ERROR;
    e = * --S.top;
    return OK;
}

int In(char c,char OP[])   //�ж�������������������������������1
{
  if(c>=35 && c<=47)
  return 1;
 else return 0;
/*
	for(int i=0 ; i<7;i++)
	{
		if(c==OP[i])
		{
			return 1;
			break;
		}		
			
	} 
		
   return 0;*/
}

/* ��һ����ά�����ʾ�������������ȹ�ϵ*/
char OP[8]={'+','-','*','/','(',')','#','\0'};                        //�ַ���Ĭ�Ͻ�β��\0 ��ʾ�ַ�������
// "1"����">"��"2"����"<"��"0"����"="��"-1"����"������"
int m[7][7]={1,1,2,2,2,1,1, 
             1,1,2,2,2,1,1,
             1,1,1,1,2,1,1,
             1,1,1,1,2,1,1,
             2,2,2,2,2,0,-1,
             1,1,1,1,-1,1,1,
             2,2,2,2,2,-1,0};

char Precede(char i,char j)         //�ж������ջ��ջ��Ԫ�غ�����������֮������ȼ���ջ��Ԫ����i
{
  int a,b; 
  char *p;
  for(p=OP,a=0;*p!='\0';p++,a++)   //�ҵ�ջ��Ԫ�����ĸ������
    if(*p==i) break;
  for(p=OP,b=0;*p!='\0';p++,b++)   //�ҵ�����Ԫ�����ĸ������
    if(*p==j) break;

  if(m[a][b]==1) return '>';
  else if(m[a][b]==2) return '<';
  else if(m[a][b]==0) return '=';
  else return 'O';
}

char Operate(char a,char theta,char b)   //�������
{
 if(a>47 && a<58) a=atoi(&a);   //atoi(���ַ���ת����������),ͷ�ļ���stdlib.h

 if(b>47 && a<58) b=atoi(&b);
 switch(theta)
 { 
 case '+': return a+b;
    break;
 case '-': return a-b;
   break;
 case '*': return a*b;
   break;
 case '/': return a/b;
   break;
 }
}

OperandType EvaluateExpression() // �������ʽ��ֵ����������㷨��
{
  SqStack OPTR,OPND;        //������OPTRΪ�����ջ��OPNDΪ������ջ
  OperandType a,b,c; 
  OperatorType theta;
  InitStack(OPTR);   //��ʼ�������ջ
  Push(OPTR,'#');  //�����ʽ��ʼ����#����Ϊ�����ջ��ջ��Ԫ��
  InitStack(OPND); //��ʼ��������ջ
  c=getchar();   //ͨ�������������ַ�

  while (c!='#' || GetTop(OPTR)!='#')
  {
	  if (!In(c,OP))           //������������������ջ
	  {
		  Push(OPND,c);
		  c=getchar();  //�Ӽ��̶����ַ�ֱ���س�����
	  }
	  else                     //��������Ļ����������ջ���߽����������
		   switch(Precede(GetTop(OPTR),c))  //�ж����ȼ�
		   {
		      case '<' :                    //ջ��Ԫ������Ȩ�ͣ���������������Ȩ�ߣ���˽�������������ջ
			    Push(OPTR,c); 
				c = getchar();
			    break;
		      case '=' :                    //ȥ�����ţ���������һ���ַ�
			    Pop(OPTR,c); 
			    c = getchar();
			    break;
		      case '>' :                    //��ջ������������ջ
			    Pop(OPTR,theta);            //�������ջ�����������ջ����theta������ֵ
			    Pop(OPND,b);                //��������ջ������������ջ����b������ֵ
				Pop(OPND,a);                //��������ջ������������ջ����a������ֵ
			    Push(OPND,Operate(a,theta,b));   //Operate(a,theta,b)��a��b����theta�������������������������ջ
			  break;
		  }
  }
  return GetTop(OPND);                  //���ջ��Ԫ�أ������ʽ�����ս��
}

void main()
{
 printf("(��#Ϊ������)\n");
 printf("�����룺\n");
 int a;
 a=(int)EvaluateExpression();
 printf("%d",a);
 getch();  //����ͷ�ļ���conio.h ;������;���ӿ���̨��ȡһ���ַ���������ʾ����Ļ�� 
} 