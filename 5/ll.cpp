#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef struct{
 char  *ch;
 int  length;
}HString;
Status InitHString(HString&S){
S.ch=(S.ch=(char*)malloc(sizeof(char)));
S.ch=NULL;
S.length=0;
return OK;
}
Status StrAssign(HString&T,char *chars){
if(T.ch)  free(T.ch);
int i,j ;char *c;
for(i=1,c=chars;*c;i++,c++)
if(!i)
{T.ch=NULL; T.length=0;}
else{
  if(!(T.ch=(char*)malloc((i)*sizeof(char))))
      exit (OVERFLOW);
  for(j=0;j<i;j++)
	 { T.ch[j]=chars[j];}
  T.length=i;
}
return OK;
}
int StrLength(HString S){
return S.length;
}
int StrCompare(HString S,HString T){
int i;
for(i=0;i<S.length&&i<T.length;++i)
{if(S.ch[i]!=T.ch[i])  return S.ch[i]-T.ch[i];}
return S.length-T.length;
}
Status Concat(HString&T,HString S1,HString S2)
{int j,i,l;
if(T.ch) free(T.ch);
if(!(T.ch=(char*)malloc((S1.length+S2.length)*sizeof(char))))
    exit(OVERFLOW); 
for(j=0;j<S1.length;j++)
   T.ch[j]=S1.ch[j];
T.length=S1.length+S2.length;
for(i=0,l=S1.length ;i<T.length,l<T.length ;i++,l++)
   T.ch[l]=S2.ch[i];
return OK;
}
Status SubString(HString&Sub,HString S, int pos,int len){
int i,j;
if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
   return ERROR;
if(Sub.ch)  free(Sub.ch);
if(!len){Sub.ch=NULL;Sub.length=0;}
else{
  Sub.ch=(char*)malloc(len*sizeof(char));
  for(i=0,j=pos-1;i<len,j<=pos+len-2;i++,j++)
  {Sub.ch[i]=S.ch[j];}
  Sub.length=len;
}
return OK;
}
Status StrCopy(HString&T,HString S){
int i;
if(T.ch) free(T.ch);
if(S.length){ 
	if(!(T.ch=(char*)malloc((S.length)*sizeof(char))))
    exit(OVERFLOW); 
	T.length=S.length;}
for(i=0;i<S.length;i++)
{T.ch[i]=S.ch[i];}
return OK;
}
void Show(HString S){
int j,i=S.length;
for(j=0;j<i;j++)
   printf("%c",S.ch[j]);
printf("\n");
}
void main(){
char str1[20],str2[20];
int pos,len;
HString T,S,C,Sub;
InitHString(T);InitHString(S);InitHString(C);InitHString(Sub);
printf("please input the first hstring:\n");
scanf("%s",str1);
printf("please input the second hstring:\n");
scanf("%s",str2);
StrAssign(T,str1);
StrAssign(S,str2);
printf("the HString1 is :\n");
Show(T);
printf("the HString2 is :\n");
Show(S);
printf("the length of the HString1 is %4.d\n",StrLength(T));
printf("the length of the HString2 is %4.d\n",StrLength(S));
printf("compare the two Hsrings:\n");
if (StrCompare(S,T)>0) printf(" HString2>HString1\n");
if (StrCompare(S,T)<0) printf(" HString2<HString1\n");
if (StrCompare(S,T)==0)printf(" HString2=HString1\n");
Concat(C,S,T);printf("concat  HString2 and HString1 is :\n");
Show(C);
printf("please input the location and the length of substring \n");
scanf("%d",&pos);
scanf("%d",&len);
SubString(Sub, C,  pos, len);
printf(" Sub is :\n");
Show(Sub);
printf("copy HString2 to HString1 is:\n");
StrCopy(T,S);
Show(T);
}