#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
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
Status StackEmpty(SqStack&S){

if(S.top==S.base)
{return OK;}
else 
{return ERROR;}
}

void Coversion_8(int N){
SqStack S;
InitStack(S); 
int e;
printf("please input the denary number you want to conversion to octal:\n");
scanf("%d",&N);
while(N){
Push(S,N%8);
N=N/8;
}
printf("after conversion the number is:\n");
while(!StackEmpty(S))
{
Pop(S,e);
printf("%d",e);
}printf("\n");
}
void Coversion_2(int M){
SqStack S;
InitStack(S); 
int e;
printf("please input the denary number you want to conversion to binary:\n");
scanf("%d",&M);
while(M){
Push(S,M%2);
M=M/2;
}
printf("after conversion the number is:\n");
while(!StackEmpty(S))
{
Pop(S,e);
printf("%d",e);
}printf("\n");
}
void main(){
int n;
Coversion_8(n);
Coversion_2(n);
}
