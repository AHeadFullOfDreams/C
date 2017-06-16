#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct ElemType{
int key;
char *name;
char sex;
char majory;
int  grade;
}ElemType;
typedef int KeyType;
typedef struct {
ElemType  *elem;
int  length;
}SSTable;
int Creat(SSTable&ST,int n){
int i;
ST.length=n;
ST.elem=(ElemType *)malloc(n+1 *sizeof(ElemType));
printf("please input the conest of the SSTable:\n");
for(i=1;i<=n;i++)
{printf("name , number ,sex ,majory ,grade\n");
scanf("%s",&ST.elem[i].name );
scanf("%d",&ST.elem[i].key );
scanf("%s",&ST.elem[i].sex  );
scanf("%s",&ST.elem[i].majory  );
scanf("%d",&ST.elem[i].grade  );
}

return 0;
}
int Search_Seq(SSTable ST,KeyType key)
{int i;
ST.elem[0].key=key;
 for(i=ST.length;ST.elem[i].key!=key;--i);

return i;
}
void main(){
int n,j,k;SSTable ST;
printf("please input the length of the SSTable:\n");
scanf("%d",&n);
Creat(ST, n);
printf("please input the key :\n");
scanf("%d",&k);
j=Search_Seq(ST, k);
if(j==0) printf("fall to search the key");
else printf("the location of the key is %d \n",j);


}