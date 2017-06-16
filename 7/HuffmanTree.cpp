#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void HuffmanCoding(HuffmanTree &HT, int n,  Huffmancode &HC ,int *w )
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
	      p->weight =*w;
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

void main()
{
	HuffmanTree ht;
	Huffmancode hc;
	int n=5;
	int *w;
	hc=(Huffmancode)malloc(n*sizeof(Huffmancode));
	w=(int *)malloc(n * sizeof(int));
	printf("请输入五个权值:\n");
	for(int i=0;i<5;i++)
	{
	 scanf("%d",&w[i]);
	 
	}
	HuffmanCoding(ht,n,hc,w );
    printf("输出编码为：\n");

	for(i=1;i<=n;i++)
	{
		
		printf("  权重为:%d    编码为:%s\n",w[i-1],hc[i]);
	}


}
