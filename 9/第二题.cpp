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
int Search_Bin(SSTable ST,KeyType key)
{int low,high,mid;
low=1;high=ST.length ;
while(low<=high){
mid=(low+high)/2;
if(key==ST.elem[mid].key ) return mid;
else if(key<ST.elem[mid].key )  high=mid-1;
else low=mid+1;
}
return 0;
}
void main(){
	int n, k,j;SSTable ST;
printf("please input the length of the SSTable:\n");

scanf("%d",&n);
Creat(ST, n);
printf("please input the key :\n");
scanf("%d",&k);
j=Search_Bin(ST, k);
if(j==0) printf("fall to search\n");
else printf("the location of the key is %d\n",j);

}