#include <stdio.h>
#include <conio.h>  //conio是Console Input/Output（控制台输入输出）的简写，其中定义了通过控制台进行数据输入和数据输出的函数，主要是一些用户通过按键盘产生的对应操作，比如getch()函数等等。
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define STACK_INIT_SIZE 100  //初始分配量
#define STACKINCREMENT 10    //存储空间的分配增量

typedef char ElemType;     
typedef ElemType OperandType;   //操作数
typedef char OperatorType;

typedef struct
{
 ElemType *base;
 ElemType *top;
 int stacksize;
}SqStack;

 

Status InitStack(SqStack &S)
{
 //构造一个空栈S
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
 //插入元素e为新的栈顶元素
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
 //若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
    if(S.top == S.base) return ERROR;
    e = * --S.top;
    return OK;
}

int In(char c,char OP[])   //判断是运算符还是运算数，是运算符返回1
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

/* 用一个二维数组表示出运算符间的优先关系*/
char OP[8]={'+','-','*','/','(',')','#','\0'};                        //字符串默认结尾有\0 表示字符串结束
// "1"代表">"，"2"代表"<"，"0"代表"="，"-1"代表"不存在"
int m[7][7]={1,1,2,2,2,1,1, 
             1,1,2,2,2,1,1,
             1,1,1,1,2,1,1,
             1,1,1,1,2,1,1,
             2,2,2,2,2,0,-1,
             1,1,1,1,-1,1,1,
             2,2,2,2,2,-1,0};

char Precede(char i,char j)         //判断运算符栈的栈顶元素和输入的运算符之间的优先级，栈顶元素是i
{
  int a,b; 
  char *p;
  for(p=OP,a=0;*p!='\0';p++,a++)   //找到栈顶元素是哪个运算符
    if(*p==i) break;
  for(p=OP,b=0;*p!='\0';p++,b++)   //找到输入元素是哪个运算符
    if(*p==j) break;

  if(m[a][b]==1) return '>';
  else if(m[a][b]==2) return '<';
  else if(m[a][b]==0) return '=';
  else return 'O';
}

char Operate(char a,char theta,char b)   //运算操作
{
 if(a>47 && a<58) a=atoi(&a);   //atoi(将字符串转换成整型数),头文件是stdlib.h

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

OperandType EvaluateExpression() // 算术表达式求值的算符优先算法，
{
  SqStack OPTR,OPND;        //定义了OPTR为运算符栈、OPND为运算数栈
  OperandType a,b,c; 
  OperatorType theta;
  InitStack(OPTR);   //初始化运算符栈
  Push(OPTR,'#');  //将表达式起始符“#”置为运算符栈的栈底元素
  InitStack(OPND); //初始化运算数栈
  c=getchar();   //通过键盘输入获得字符

  while (c!='#' || GetTop(OPTR)!='#')
  {
	  if (!In(c,OP))           //不是运算符则进运算数栈
	  {
		  Push(OPND,c);
		  c=getchar();  //从键盘读入字符直到回车结束
	  }
	  else                     //是运算符的话进运算符的栈或者进行运算操作
		   switch(Precede(GetTop(OPTR),c))  //判断优先级
		   {
		      case '<' :                    //栈顶元素优先权低，输入的运算符优先权高，因此将输入的运算符入栈
			    Push(OPTR,c); 
				c = getchar();
			    break;
		      case '=' :                    //去掉括号，并接受下一个字符
			    Pop(OPTR,c); 
			    c = getchar();
			    break;
		      case '>' :                    //退栈并将运算结果入栈
			    Pop(OPTR,theta);            //将运算符栈顶的运算符出栈，用theta返回其值
			    Pop(OPND,b);                //将运算数栈顶的运算数出栈，用b返回其值
				Pop(OPND,a);                //将运算数栈顶的运算数出栈，用a返回其值
			    Push(OPND,Operate(a,theta,b));   //Operate(a,theta,b)将a和b进行theta运算操作。将运算结果入运算数栈
			  break;
		  }
  }
  return GetTop(OPND);                  //获得栈顶元素，即表达式的最终结果
}

void main()
{
 printf("(以#为结束符)\n");
 printf("请输入：\n");
 int a;
 a=(int)EvaluateExpression();
 printf("%d",a);
 getch();  //所在头文件：conio.h ;函数用途：从控制台读取一个字符，但不显示在屏幕上 
} 