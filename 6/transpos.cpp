#include<stdio.h>
#define MAXSIZE  12500
#define OK 1
#define ERROR 0
typedef int  ElemType;
typedef int  Status;
typedef struct {
int i,j;
ElemType e;
}Triple;
typedef struct{
Triple  data[MAXSIZE+1];
int  mu,nu,tu;
}TSMatrix;
Status Creat(TSMatrix&T){
int mu,nu,tu,row,col,w,h;
printf("please input the mu ¡¢nu and the number of  NZ :\n");
scanf("%d",&mu);scanf("%d",&nu);scanf("%d",&tu);
T.mu=mu;T.nu=nu;T.tu=tu;

printf("please input the content of the NZ:\n");
for(h=1;h<=tu;h++)
{
scanf("%d",&row);
scanf("%d",&col);
scanf("%d",&w);
if(T.tu>=MAXSIZE){
        printf("\nError:There is no space in the matrix;\n");  
        return ERROR;  
    }  
if(row>T.mu||col>T.nu||row<1||col<1){  
        printf("\nError:the position is beyond the arrange.\n");  
        return ERROR;  
    }
T.data[h].i=row;
T.data[h].j =col;
T.data[h].e=w;
}
}
void Print(TSMatrix M){  
    int i,j,p=1;    
    
    for(i=1;i<=M.mu;i++){  
        for(j=1;j<=M.nu;j++){  
            if(i==M.data[p].i && j==M.data[p].j){  
                printf("%d",M.data[p].e);  
                p++;    }
             else{  
              
				 printf("0");
            }  
        }  
        printf("\n");  
    }  
    printf("\n");  
} 
Status TransposeSMatrix(TSMatrix M,TSMatrix&T)
{int q,p,col;
T.mu=M.nu;T.nu=M.mu; T.tu=M.tu;
if(T.tu){
 q=1;
 for(col=1;col<=M.nu;++col)
 {  for(p=1;p<=M.tu;++p)
	{ if(M.data[p].j==col){
	   T.data[q].i=M.data[p].j;
	   T.data[q].j=M.data[p].i;
	   T.data[q].e=M.data[p].e;
	   ++q;}
	}
 }
}
return OK;
}

void main(){
TSMatrix T,M;
M.mu =0;M.nu =0;M.tu =0;
Creat(M);
printf("the TSMastix is :\n");
Print(M);
TransposeSMatrix(M,T);
printf("TransposeSMatrix M to T:\n");
Print(T);

}