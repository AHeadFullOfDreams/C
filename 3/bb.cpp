#include<stdio.h>
#include<stdlib.h>
#define OK 0
#define ERROR 1
#define STACK_INIT_SIZE  100
#define STACKINCREMENT  10
#define OVERFLOW  -2
 typedef      int Status; 
 typedef int OperandType;
typedef char SElemType;
typedef struct{
 SElemType  *base;
 SElemType  *top;
 int stacksize;
}SqStack;

char OP[8]={'+','-','*','/','(',')','#','\0'};
int m[7][7]={1,1,2,2,2,1,1,
             1,1,2,2,2,1,1,
             1,1,1,1,2,1,1,
             1,1,1,1,2,1,1,
             2,2,2,2,2,0,-1,
             1,1,1,1,-1,1,1,
             2,2,2,2,2,-1,0,//方便比较优先级而建立的二维数组
};
Status InitStack(SqStack*S)//初始化函数
{
 (*S).base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
 if(!(*S).base)exit(OVERFLOW);
 (*S).top=(*S).base;
 (*S).stacksize=STACK_INIT_SIZE;
 return OK;
}
Status Push(SqStack&S,SElemType e)//入栈
{
	if(S.top-S.base>=S.stacksize){
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
    if(!S.base)exit(OVERFLOW);
	S.top=S.base+S.stacksize;
	S.stacksize+=STACKINCREMENT;}
	*S.top++=e;
	return OK;}
Status Pop(SqStack&S,SElemType *e)//删除
{
	if((S).top==(S).base)return ERROR;
	*e=*--(S).top;
	return OK;}
Status GetTop(SqStack *S)
{ int *e;
  if((*S).top==(*S).base)  return ERROR;
  *e=*((*S).top-1);
   return *e;
}

char Precede(char i,char j)//判断运算符优先级函数
{
 int a,b;
 char *p;
 for(p=OP,a=0;*p!='\0';p++,a++)
     if(*p==i) break;
 for(p=OP,b=0;*p!='\0';p++,b++)
	 if(*p==j) break;
if(m[a][b]==1) return '>';
else if(m[a][b]==2) return '<';
else if(m[a][b]==0) return '=';
else return '0';
}
char Operate( char a,char theta,char b)//运算函数
{if(a>47&&a<58) a=atoi(&a);
 if(b>47&&a<58) b=atoi(&b);
 switch(theta)
 {case '+': return a+b;
 break;
 case'-': return a-b;
 break;
 case'*': return a*b;
 break; 
 case'/': return a/b;
 break;
 }
}
int In(char c,char OP[])//判断是否为运算符
{
 if(c>=35&&c<=47)
    return 1;
 else return 0;

}
OperandType EvaluateExpression()//表达式求值函数
{
SqStack OPTR,OPND;char c,theta,x,a,b;
InitStack(&OPTR);  Push(OPTR,'#');
InitStack(&OPND);  printf("please input the expression and add '#' at the end of the expression:\n");
c=getchar();
while(c!='#'||GetTop(*OPTR)!='#'){
	if(!In(c,OP)){Push(OPND,c);c=getchar();}
	else
	{	switch(Precede(GetTop(*OPTR),c)){
		  case'<':
			  {Push(OPTR,c); c=getchar();
			  break;}
		  case'=':
			  { Pop(OPTR,&x); c=getchar();
			  break;}
		  case'>':
			  { Pop(OPTR,&theta);
			  Pop(OPND,&b);Pop(OPND,&a);
			  Push(OPND,Operate(a,theta,b));
			  break;}
	}}
}

return GetTop(*OPND);
}
void main(){
int a;

a=EvaluateExpression();

printf("the result is %d\n",a);

}