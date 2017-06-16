#include<stdio.h>
#include<stdlib.h>
#define OK  1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;
typedef struct BiTNode{
TElemType  data;
struct BiTNode   *lchild, *rchild;
}BiTNode, *BiTree;
Status CreatBiTree(BiTree&T)
{char ch;
scanf("%c",&ch);
if(ch=='#') T=NULL;
else{
if(!(T=(BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
T->data =ch;
CreatBiTree(T->lchild );
CreatBiTree(T->rchild );
}
return OK;
}

Status PrintElement(TElemType e)
{
printf("%c",e);
return OK;
}

Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e))
{
Visit=PrintElement;
if(T){
  if(Visit(T->data))
	if(PreOrderTraverse(T->lchild ,Visit))
	   if(PreOrderTraverse(T->rchild ,Visit))  return OK;
  return ERROR;
}else return OK;
}
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e))
{
Visit=PrintElement;
if(T){
  if(InOrderTraverse(T->lchild ,Visit))
	if(Visit(T->data ))
	   if(InOrderTraverse(T->rchild ,Visit))  return OK;
  return ERROR;
}else return OK;
}
Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e))
{
Visit=PrintElement;
if(T){
  if(InOrderTraverse(T->lchild ,Visit))
	if(InOrderTraverse(T->rchild ,Visit))  
	   if(Visit(T->data )) return OK;
  return ERROR;
}else return OK;
}
void main(){
BiTree T;
printf("please input the data of BiTree in PreOrder:\n");
CreatBiTree(T);
printf("PreOrderTraverse:\n");
PreOrderTraverse(T,PrintElement);
printf("\n");
printf("InOrderTraverse:\n");
InOrderTraverse(T,PrintElement);
printf("\n");
printf("PostOrderTraverse:\n");
PostOrderTraverse(T,PrintElement);
printf("\n");
}
