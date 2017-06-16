#include<stdio.h>
#include<stdlib.h>
#define OK 0
#define ERROR 1
#define STACK_INIT_SIZE  100
#define STACKINCREMENT  10
#define OVERFLOW  -2
typedef int SElemType;
 typedef      int Status;   
typedef struct{
 SElemType  *base;
 SElemType  *top;
 int stacksize;
}SqStack;
Status InitStack(SqStack&S)
{
 S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
 if(!S.base)exit(OVERFLOW);
 S.top=S.base;
 S.stacksize=STACK_INIT_SIZE;
 return OK;
}
Status GetTop(SqStack S,SElemType&e)
{
 if(S.top==S.base)  return ERROR;
  e=*(S.top-1);
  return OK;
}
Status Push(SqStack&S,SElemType e){
	if(S.top-S.base>=S.stacksize){
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
    if(!S.base)exit(OVERFLOW);
	S.top=S.base+S.stacksize;
	S.stacksize+=STACKINCREMENT;}
	*S.top++=e;
	return OK;}
Status Pop(SqStack&S,SElemType&e){
	if(S.top==S.base)return ERROR;
	e=*--S.top;
	return OK;}
void Show(SqStack&S){
int *w;
w=S.base;
while(w!=S.top)
{printf("%3.0d",*w);
       w++;}
}

void main()
{ SqStack S;
int i,j,e,p,q,g;
InitStack(S);
if(InitStack(S)==OK)
{printf("successfully intialize the sqstack!\n");}
else{printf("fail to intialize the sqstack\n");}
printf("plesae input the length of the SqStack\n");
scanf("%d",&i);
S.stacksize=i;
printf("plesae input the SqStack\n");
for(j=0;j<i;j++)
{
scanf("%d",&e);
Push(S,e);
}printf("the current stack is \n");
Show(S);printf("\n");
printf("plesae input the  number you want to push\n");
scanf("%d",&p);
Push(S,p);printf("the current stack is \n");
Show(S);
printf("\n");
printf("delete the top number\n");
Pop(S,q);printf("the current stack is \n");
Show(S);
printf("\n");
GetTop(S,g);
printf("the top is %d\n",g);
if(S.top==S.base)
{printf("the sqstack is empty\n");}
else 
{printf("the sqstack is not empty\n");}


}


