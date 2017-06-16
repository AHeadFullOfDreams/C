#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Code
{char data;
 int  cdweight;
}Code;

typedef struct 
{ 
     int  weight; 
	 int  lchild,rchild,parent;
}HTNode,*HuffmanTree;
                                     
typedef  char ** Huffmancode; 

void SelectMin(HuffmanTree HT,int n, int &s1,int &s2)
{
	//Select()函数，选出赫夫曼树到n为止，权值最小且parent为0的2个节点

	int i,j,temp;
	for(i=1;i<=n;i++)
		if(HT[i].parent==0)
		{
			s1=i;
			break;
		}
		for(j=i+1;j<=n;j++)
			if(HT[j].parent==0)
			{
				s2=j;
				break;
			}
			for(i=1;i<=n;i++)      //挑选权值较小左节点
			{
				if(HT[i].parent==0)       
					if(HT[s1].weight>HT[i].weight)
						if(s2!=i)
							s1=i;
			}
			for(j=1;j<=n;j++)       //挑选权值较小右节点
			{
				if(HT[j].parent==0)
					if(HT[s2].weight>HT[j].weight)
						if(s1!=j)
							s2=j;
			}
			if(s1>s2)
			{
				temp=s1;
				s1=s2;
				s2=temp;
			}

	
}

void HuffmanCoding(HuffmanTree &HT, Huffmancode &HC ,Code *w ,int n )
{
	int i,m,start,c,f; 
	HuffmanTree p;
	char *cd;
	int s1,s2;
	
	if(n<=1)  return;
	 m=2*n-1  ; 
	 HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); 

	  for(p=HT+1,i=1;i<=n;++i,++p,++w) 
	  {
		  p->lchild =0;
	      p->rchild =0;
	      p->parent =0;
	      p->weight =w[i].cdweight;
	  }
		 
		 
        for(;i<=m;++i,++p)
		 {
		  p->lchild =0;
	      p->rchild =0;
	      p->parent =0;
	      p->weight =0;
	  }
		 
		 for(i=n+1;i<=m;i++)
		 {  
             SelectMin(HT,i-1,s1,s2); 
             HT[s1].parent=i;  
			 HT[s2].parent=i;
			 HT[i].lchild=s1; 
			 HT[i].rchild=s2; 
			 HT[i].weight=HT[s1].weight+HT[s2].weight;
          } 

		 HC=(Huffmancode)malloc((n+1)*sizeof(char *));
		 cd=(char *)malloc(n*sizeof(char ));
		 cd[n-1]='\0';  
		
		 for(i=1;i<=n;i++)
		 {
			 start=n-1;         
			 for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
				 if(HT[f].lchild==c )
					 cd[--start]='0';
				 else  cd[--start]='1';

				 HC[i]=(char * )malloc((n-start)*sizeof(char)); 
				 strcpy(HC[i],&cd[start]);
		 }
		 free(cd);

}
void Translate1(Huffmancode hc,char *c,int n,Code *w)
{char *p;int i;
printf("the words you input is:\n");
puts(c);
printf("the result of humancofding is:\n");
for(p=c;*p!='\0';p++)
{
for(i=1;i<=n ;i++)
{
if(*p==w[i].data ) printf("%s",hc[i]);

      
}

}
printf("\n");
}//明文进行编码

void Translate2(Huffmancode hc,char *d,int n,Code *w)
{int i,j,k,l,m,h;
char p[100],q[100];
printf("the coding you input is:\n");
puts(d);
k=strlen(d);

printf("the information is:\n");
strcpy(p,d);

i=0;j=0;
while(i<k)
{
q[j]=p[i];q[j+1]='\0';
i++;j++;
for(m=1;m<=n;m++)
{
if(strcmp(q,hc[m])==0) 
{
printf("%c",w[m].data);
j=0;//q回溯
strcpy(q,"\0");//清空q

break;
}

}

}

}//暗文进行解码



void main()
{int n,i;
char c[100],d[100];
HuffmanTree ht;
Huffmancode hc;
Code *w;
printf("please input the size of the code:\n");
scanf("%d",&n);
w=(Code *)malloc(n* sizeof(Code));
hc=(Huffmancode)malloc(n*sizeof(Huffmancode));
printf("please input the code and its weight:\n");
getchar();//吸收回车符
for(i=1;i<=n;i++)
{
	scanf("%c",&w[i].data );
	scanf("%d",&w[i].cdweight);
}
printf("the content of your input is:\n");
for(i=1;i<=n;i++)
{
	printf("  %c",w[i].data );
	printf("  %d",w[i].cdweight);
}
HuffmanCoding(ht, hc, w,  n);
printf("\nthe result of HuffmanCoding is:\n");
for(i=1;i<=n;i++)
	{
		
		printf(" character is:  %c   weight is:  %d   huffmancode is:  %s\n",w[i].data ,w[i].cdweight ,hc[i]);
	}

printf("plesae input the words you want to Humancoding:\n");
getchar();//吸收回车符
gets(c);
Translate1(hc,c,n,w);

printf("please input the humancoding you want to translate:\n");
gets(d);
Translate2(hc,d,n,w);
printf("\n");

}