#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{ 
     int  weight; 
	 int  lchild,rchild,parent;
}HTNode,*HuffmanTree;


typedef  struct 
{
	char name;
	int cdweight;
}code;
                                     
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

void HuffmanCoding(HuffmanTree &HT,  Huffmancode &HC ,code *w , int n)
{
	int i,m,start,c,f; 
	HuffmanTree p;
	char *cd;
	int s1,s2;
	
	if(n<=1)  return;
	 m=2*n-1  ; 
	 HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); 
    
	
	 
	  for( p=HT+1,i=1;i<=n;++i,++p,++w) 
	  {
		  p->lchild =0;
	      p->rchild =0;
	      p->parent =0;
	      p->weight =w->cdweight;
	  }
		 
		 
        for(;i<=m;++i,++p)
		 {
		  p->lchild =0;
	      p->rchild =0;
	      p->parent =0;
	      p->weight =0;
	  }
	 
 /*	 for(i=1;i<=n;i++)                //数组初始化
	{
		HT[i].weight=w[i-1];
	    HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	for(;i<=m;++i)
	{
		HT[i].weight=0;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}*/

		 
		 for(i=n+1;i<=m;++i)
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
		
		 for(i=1;i<=n;++i)
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


void strcopy(char *p1,char *p2,int m,int n)  //从字符串的m位置开始复制n个长度的字符串
{
  int k=0;
  while(k<m-1)
  {
	  k++;
	  p1++;
  }
  for(int i=0;i<n;i++)
  {
	  *p2=*p1;
	  p1++;
	  p2++;
  }
  *p2='\0';
}

void main()
{
	HuffmanTree ht;
	Huffmancode hc;
	int i,j,len;
	int n=5;


	code a[5];
  
  /*---------构建赫夫曼树---------------*/  
	hc=(Huffmancode)malloc(n*sizeof(Huffmancode));
    
    
	printf("请输入五个编码所需的字符:\n");

	for(i=0;i<5;i++)
	{
				
		scanf("%c",&a[i].name);
	}
	
	printf("请输入五个编码所需的字符的权值:\n");

	for(i=0;i<5;i++)
	{
				
		scanf("%d",&a[i].cdweight);
	}
	code *w=a;

	HuffmanCoding(ht,hc,w,n );

   printf("输出编码为：\n");

	for(i=1;i<=5;i++)
	{
		
	   printf("字符：%c  其权重为:%d    其编码为:%s\n",w[i-1].name,w[i-1].cdweight,hc[i]);
		
	}



/*---------输入明文进行编码---------------*/  
	char mingwen[20];

    printf("请输入长度不超过20的明文:\n");

	scanf("%s",&mingwen);

    printf("明文的编码如下:\n");
	for(i=0;i<strlen(mingwen);i++)
	{
		for( j=0;j<5;j++)
		{
		  if(mingwen[i]==w[j].name)
			  
			 printf("%s",hc[j+1]);
		}	
	}
	 printf("\n");

 /*---------输入电文进行解码---------------*/  
     
	 char dianwen[100];
	 char zichuan[100];
	 printf("请输入需要解码的电文:\n");
	 scanf("%s",dianwen);


	 printf("电文的明文如下:\n");
	 
	 j=1;
	 
	 while(j<strlen(dianwen))
	 {
		 for(i=1;i<=5;i++)
		 {
		  	strcopy(dianwen,zichuan,j,strlen(hc[i]));
		    if(strcmp(zichuan,hc[i])==0)		  
			{
				printf("%c",w[i-1]);	
				j=j+strlen(hc[i]);	
				break;
			}		    	
		 }			 
	 }
	 
	 printf("\n");

}
