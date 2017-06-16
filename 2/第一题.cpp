#include<stdio.h>
 #include<stdlib.h>
 #define OK   1
 #define ERROR  0
 typedef int ElemType;
 typedef struct LNode{
 ElemType   data;
 struct LNode  *next;
 }LNode, *LinkList;
 LinkList p,q,s;int i,j;

 int ListInsert_L(LinkList&L,int i,ElemType e){
 p=L;j=0;
 while(p&&j<i-1){p=p->next;++j;}
   if(!p||j>i-1)return ERROR;
   s=(LinkList)malloc( sizeof(LNode));
   s->data=e;s->next=p->next;
   p->next=s;
   return OK;
 }
 int ListDelete_L(LinkList&L,int i,ElemType&e){
 p=L;j=0;
 while(p->next&&j<i-1){
 p=p->next;++j;
 } if(!(p->next)||j>i-1)return ERROR;
 q=p->next;p->next=q->next;
 e=q->data;free(q);
 return OK;
 } 
void CreateList_L(LinkList&L,int n){

	
L=(LinkList)malloc(sizeof(LNode));
 L->next=NULL; 
 printf("please input %d number\n",n);
   p=L;
for(i=n;i>0;--i){ 
q=(LinkList)malloc(sizeof(LNode)); 
scanf("%d",&q->data);
 q->next=NULL;
 p->next=q;
 p=q;
 
} } 
void Show_L(LinkList&L)
{  
	LinkList p=L->next;  
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}

void main(){ 
int g,a,b,e; 
  LinkList L; 
printf("pelese input the length of the linklist\n"); 
    scanf("%d",&g); 
 CreateList_L(L,g); printf("successfully creat linklist:");
Show_L(L);printf("\n");
printf("please input the location and the number you want to insert\n"); 
scanf("%d",&a);scanf("%d",&b); 
ListInsert_L(L,a,b); 

Show_L(L);printf("\n");
printf("please input the location of you want to delete\n"); 
scanf("%d",&i); 
ListDelete_L(L,i,e); 

Show_L(L);printf("\n");
}
