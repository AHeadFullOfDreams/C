
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct LNode
{
 ElemType data;
 struct LNode *next;
}LNode,*LinkList;
void CreateList_L(LinkList&L,int n){
	int i;LinkList p,q;
L=(LinkList)malloc(sizeof(LNode));
 L->next=NULL; 
 p=L;
 printf("please input %d number\n",n);

for(i=n;i>0;--i){ 
 q=(LinkList)malloc(sizeof(LNode)); 
 scanf("%d",&q->data);
 q->next=NULL;
 p->next=q;
 p=q;
 
}
} 
void Reverse_L(LinkList&L)
{
LNode *p,*q;

p=L->next;
L->next=NULL;
while(p!=NULL)
{q=p->next;
p->next=L->next;
L->next=p;
p=q;
}

}

void Show_L(LinkList&L)
{ 
	LinkList p=L->next;  
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}

void main() 
{ int n; 
  LinkList L; 
printf("pelese input the length of the linklist\n"); 
    scanf("%d",&n); 
 CreateList_L(L,n); printf("the list is:\n");
 Show_L(L);
 printf("\n");
Reverse_L(L);printf("the reverse list is:\n");
Show_L(L);
 printf("\n");
 }


