#include<stdio.h>
#define MAXSIZE 20
typedef int KeyType;

typedef struct {
KeyType key;
char   name[10];
char   sex;
char   majory[10];
int    grade;
}RedType;
typedef struct {
RedType r[MAXSIZE+1];
int  length;
}SqList;
void Creat(SqList&L)
{int n,i;
printf("please input the length of the list:\n");
scanf("%d",&n);
L.length=n;
for(i=1;i<=n;i++)
{
printf("please input the information of the %dth student:Number,Name, Sex, Majory, Grade\n",i);
scanf("%d",&L.r[i].key );
scanf("%s%s%s",&L.r[i].name,&L.r[i].sex,&L.r[i].majory);
scanf("%d",&L.r[i].grade);
}
}
void InsertSort(SqList&L)
{int i,j;
for(i=2;i<=L.length;i++)
    if(L.r[i].key<L.r[i-1].key){
		L.r[0]=L.r[i];
		//L.r[i]=L.r[i-1];
		for(j=i-1;L.r[0].key<L.r[j].key;--j)
			L.r[j+1]=L.r[j];
		L.r[j+1]=L.r[0];
	}
}
void ShellInsert(SqList&L,int dk){
int i,j;
for(i=dk+1;i<=L.length ;++i)
    if(L.r[i].key<L.r[i-dk].key){
	L.r[0]=L.r[i];
	for(j=i-dk;j>0&&(L.r[0].key<L.r[j].key);j-=dk)
		L.r[j+dk]=L.r[j];
	L.r[j+dk]=L.r[0];
	}
}
void ShellSort(SqList&L,int dlta[],int t)
{int k;
for(k=0;k<t;++k)
   ShellInsert(L,dlta[k]); 
}
void Print(SqList L)
{
int i;
for(i=1;i<=L.length;i++)
{
printf("the infomation of the %dth student is %d:\n ",i,L.r[i].key );
//printf("Number:%d,Name:%s, Sex:%s, Majory:%s, Grade:%d",L.r[i].key,L.r[i].name,L.r[i].sex ,L.r[i].majory ,L.r[i].grade );
}

}
int Partition(SqList &L,int low,int high)
{int pivotkey;
L.r[0]=L.r[low];
pivotkey=L.r[low].key;
while(low<high){
     while(low<high&&L.r[high].key >=pivotkey) --high;
	 L.r[low]=L.r[high];
	 while(low<high&&L.r[low].key <=pivotkey)  ++low;
	 L.r[high]=L.r[low];
}
L.r[low]=L.r[0];
return low;
}
void QSort(SqList &L,int low,int high){
	int pivotkey;
	if(low<high){
	pivotkey=Partition(L,low,high);
	QSort(L,low,pivotkey-1);
	QSort(L,pivotkey+1,high);	
	}
}
void QuickSort(SqList&L){
QSort(L,1,L.length );

}
typedef SqList HeapType;

void HeapAdjust(HeapType&H,int s,int m)
{RedType rc;int j;
rc=H.r[s];
for(j=2*s;j<=m;j*=2){
if(j<m&&(H.r[j].key <H.r[j+1].key ))  ++j;
if(rc.key >=H.r[j].key ) break;
H.r[s]=H.r[j];s=j;
}
H.r[s]=rc;
}
void HeapSort(HeapType&H)
{int i;RedType rc;
for(i=H.length/2;i>0;--i)
    HeapAdjust(H,i,H.length);printf("the infomation of the student is %d:\n ",H.r[1].key );
for(i=H.length;i>1;--i){
rc=H.r[1];
H.r[1]=H.r[i];
H.r[i]=rc;
HeapAdjust(H,1,i-1);
printf("the infomation of the student is %d:\n ",H.r[1].key );
}

}
typedef RedType  RcdType[MAXSIZE+1];
void Merge(RcdType SR,RcdType &TR,int i,int m,int n)
{int j,k,a,b;
	for(j=m+1,k=i;i<=m&&j<=n;++k){
	if(SR[i].key<SR[j].key) TR[k]=SR[i++];
	else TR[k]=SR[j++];
	}
if(i<=m)
{   for(a=k,b=i;a<=n&&b<=m;a++,b++)
         TR[a]=SR[b];
}       
if(j<=n){
for(a=k,b=j;a<=n&&b<=n;a++,b++)
      TR[a]=SR[b];
}
}
void MSort(RcdType SR,RcdType&TR1,int s,int t)
{RcdType TR2;int m;
if(s==t) TR1[s]=SR[s];
else{
m=(s+t)/2;
MSort(SR,TR2,s,m);
MSort(SR,TR2,m+1,t);
Merge(TR2,TR1,s,m,t);
}
}
void MergeSort(SqList&L)
{
MSort(L.r ,L.r ,1,L.length );
}
void main()
{SqList L;int dlta[3],t=3;
dlta[0]=5;dlta[1]=3;dlta[2]=1;
Creat(L);
InsertSort(L);printf("InsertSort:\n");
Print(L);
ShellSort(L,dlta,t);printf("ShellSort:\n");
Print(L);
QuickSort(L);printf("QuickSort:\n");
Print(L);

printf("HeapSort:\n");
HeapSort(L);

MergeSort(L);printf("MergeSort:\n");
Print(L);
}