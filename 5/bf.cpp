#include<stdio.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSTRLEN 255
typedef int Status;
typedef unsigned char SString[MAXSTRLEN+1];
Status StrAssign(SString&T,char *chars)
{

int i,j ;char *c;
for(i=1,c=chars;*c;i++,c++)
  for(j=1;j<=i;j++)
	 { T[j]=chars[j-1];}

return OK;
}

int Index(SString S,SString T,int pos)
{int i=pos,j=1;
while(i<=S[0]&&j<=T[0])
{
	if(S[i]==T[i]){++i;++j;}
	else{i=i-j+2;j=1;}
}
if(j>T[0]) {

	return i-T[0];}
else return 0;
}
void Show(SString S){
int j,i=S[0];
for(j=1;j<=i;j++)
   printf("%c",S[j]);
printf("\n");
}

void main(){
SString S,T;char a[20],b[20];
int pos,p,q,i,j;
printf("please input the  length of the main string:\n");
scanf("%d",&S[0]);
printf("please input the main string:\n");
scanf("%s",a);
StrAssign(S,a);

printf("please input the length of substring:\n");
scanf("%d",&T[0]);
printf("please input the substring:\n");getchar();
scanf("%s",b);
StrAssign(T,b);

printf("please input the postion you want to search:\n");
scanf("%d",&pos);
Index(S,T,pos);
printf(" the location of the substring in main string is %d:\n",Index(S,T,pos));

}