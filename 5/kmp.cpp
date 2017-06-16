#include<stdio.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];
void get_next(SString T,int next[])
{int i,j;
i=1;next[1]=0;j=0;
while(i<T[0]){
	if(j==0||T[i]==T[j]){++i;++j;next[i]=j;}
	else j=next[j];
}
}
int Index_KMP(SString S,SString T,int pos)
{int i,j;
i=pos;j=1;
int next[255];
get_next(T ,next );

while(i<=S[0]&&j<=T[0]){
	if (j==0||S[i]==T[j])
	{++i;++j;}
	else j=next[j];
}
if(j>T[0]) 
{return i-T[0];}
else 
{return 0;}
}
int Index(SString S,SString T,int pos)
{int i,j;
i=pos;j=1;
while(i<=S[0]&&j<=T[0]){
	if(S[i]==T[i]){++i;++j;}
	else{i=i-j+2;j=1;}
}
if(j>T[0]) return i-T[0];
else return 0;
}
void main(){
SString S,T;int pos,i,j;char c;
printf("please input the  length of the main string:\n");
scanf("%d",&S[0]);
printf("please input the main string:\n");c=getchar();
for(i=1;i<=S[0]+1;i++)
{
	S[i]=getchar();
}
printf("please input the length of substring:\n");
scanf("%d",&T[0]);
printf("please input the substring:\n");c=getchar();
for(j=1;j<=T[0]+1;j++)
{
	T[j]=getchar();
}
printf("please input the postion you want to search:\n");
scanf("%d",&pos);
Index_KMP(S,T,pos);
printf("KMP:  the location of the substring in main string is %d:\n",Index_KMP(S,T,pos));
Index(S,T,pos);
printf("BF:  the location of the substring in main string is %d:\n",Index_KMP(S,T,pos));

}