#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define UNDERFLOW 2
#define MAX_ARRAY_DIM 8
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType  *base;
		int  dim;
		int  *bounds;
		int  *constants;
}Array;
Status InitArray(Array&A,int dim,...)
{int elemtotal,i;
va_list ap;
if(dim<1||dim>MAX_ARRAY_DIM) return ERROR;
A.dim=dim;
A.bounds=(int *)malloc(dim *sizeof(int));
if(!A.bounds) exit(OVERFLOW);
elemtotal=1;
va_start(ap,dim);
for(i=0;i<dim;++i)
{  A.bounds[i]=va_arg(ap,int);
   if(A.bounds[i]<0) return UNDERFLOW;
   elemtotal=elemtotal*A.bounds[i];
}
va_end(ap);
A.base=(ElemType *)malloc(elemtotal *sizeof(ElemType));
if(!A.base) exit(OVERFLOW);
A.constants=(int *)malloc(dim *sizeof(int));
if(!A.constants) exit(OVERFLOW);
A.constants[dim-1]=1;
for(i=dim-2;i>=0;--i)
{A.constants[i]=A.bounds[i+1]*A.constants[i+1];}
return OK;
}
Status DestoryArray(Array&A)
{if(!A.base) return ERROR;
free(A.base); A.base=NULL;
if(!A.bounds) return ERROR;
free(A.bounds); A.bounds=NULL;
if(!A.constants) return ERROR;
free(A.constants); A.constants=NULL;
return OK;
}
Status Locate(Array A,va_list ap, int&off)
{int ind,i;
off=0;
for(i=0;i<A.dim;++i)
{ind=va_arg(ap,int);
if(ind<0||ind>=A.bounds[i]) return OVERFLOW;
off=off+A.constants[i]*ind;
}
return OK;
}
Status Value(ElemType&e,Array A,...)
{int result,off;
va_list ap;
va_start(ap,A);
if((result=Locate(A,ap,off))<=0) return result;
e=*(A.base+off);
return OK;
}
Status Assign(Array &A,ElemType e,...)
{va_list ap;
int result,off;
va_start(ap,e);
if((result=Locate(A,ap,off))<=0) return result;
*(A.base+off)=e;
return OK;
}
void main(){
int a,b,i,j,w,e;
Array A;
printf("please input the bounds of the two-dim array:\n");
scanf("%d",&a);scanf("%d",&b);
InitArray(A,2,a,b);
printf("please input the contents of the array:\n");
for(i=0;i<a;i++)
   for(j=0;j<b;j++)
   {   scanf("%d",&w);
       printf("%d",w);
       Assign(A,w,i,j); }
for(i=0;i<a;i++){
printf("\n");
for(j=0;j<b;j++){
Value(e,A,i,j);
printf("%3d",e);
}
}
printf("\n");
printf("after destory the array:\n");
DestoryArray(A);
if(!A.base) printf("the array is empty\n");
printf("\n");

}