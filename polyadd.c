#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct node
{
	int coeff;
	int exp[3];
	struct node *link;
};
struct node *mkheader()
{
	struct node *p=malloc(sizeof(struct node));
	p->coeff=-1;
	p->exp[0]=-1;
	p->exp[1]=-1;
	p->exp[2]=-1;
	p->link=p;
	return p;
}
struct node *addterm(struct node *p, int coeff, int i, int j, int k)
{
	struct node *temp=malloc(sizeof(struct node));
	struct node *temp1=p;
	temp->coeff=coeff;
	temp->exp[0]=i;
	temp->exp[1]=j;
	temp->exp[2]=k;
	while(temp1->link!=p)
		temp1=temp1->link;
	temp1->link=temp;
	temp->link=p;
	return p;
}
double evaluate(struct node *p, int i, int j, int k)
{
	double sum=0;
	struct node *p0=p->link;
	while(p0!=p)
	{
		sum+=p0->coeff*pow(i,p0->exp[0])*pow(j,p0->exp[1])*pow(k,p0->exp[2]);
		p0=p0->link;
	}
	return sum;
}
void printpoly(struct node *p)
{
	struct node *p0=p->link;
	while(p0!=p)
	{
		printf("%dx^%dy^%dz^%d",p0->coeff,p0->exp[0],p0->exp[1],p0->exp[2]);
		if(p0->link!=p)
			printf("+");
		p0=p0->link;
	}
	printf("\n");
}
void read(struct node *t1, int n)
{
	int i;
	struct node *temp=malloc(sizeof(struct node));
	for(i=1;i<=n;i++)
	{
		printf("\nEnter the values of coefficient and powers of x,y and z\n");
		scanf("%d %d %d %d",&temp->coeff,&temp->exp[0],&temp->exp[1],&temp->exp[2]);
		t1=addterm(t1,temp->coeff,temp->exp[0],temp->exp[1],temp->exp[2]);
	}
	printpoly(t1);
}
struct node *add(struct node *p1, struct node *p2)
{
	struct node *temp=mkheader();
	struct node *t1=p1->link,*t3=p1->link;
	struct node *t2=p2->link,*t4=p2->link;
	int i,flag;
	while(t1!=p1)
	{
		t2=p2->link;
		while(t2!=p2)
		{
			flag=0;
			for(i=0;i<3;i++)
			{
				if(t1->exp[i]!=t2->exp[i])
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				temp=addterm(temp,t1->coeff+t2->coeff,t1->exp[0],t1->exp[1],t1->exp[2]);
				break;
			}
			t2=t2->link;
		}
		if(flag==1)
			temp=addterm(temp,t1->coeff,t1->exp[0],t1->exp[1],t1->exp[2]);
		t1=t1->link;
	}
	while(t4!=p2)
	{
		t3=p1->link;
		while(t3!=p1)
		{
			flag=0;
			for(i=0;i<3;i++)
			{
				if(t3->exp[i]!=t4->exp[i])
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
				break;
			t3=t3->link;
		}
		if(flag==1)
			temp=addterm(temp,t4->coeff,t4->exp[0],t4->exp[1],t4->exp[2]);
		t4=t4->link;
	}
	return temp;
}
int main()
{
	int coeff,x,y,z,n,ch;
	struct node *polysum;
	struct node *p=mkheader();
	struct node *poly2=mkheader();
	while(1)
	{
		printf("\nEnter choice\n1.Evaluate polynomial\n2.Add\n3.Exit\n");
		scanf("%d",&ch);
		switch(ch)
		{	
			case 1:		printf("\nEnter no of terms in polynomial\n");
					scanf("%d",&n);
					read(p,n);
					printf("\nEnter values of x, y and z\n");
					scanf("%d %d %d",&x,&y,&z);
					printf("%lf\n",evaluate(p,x,y,z));
					break;
			case 2:		printf("\nEnter no of terms in polynomial\n");
					scanf("%d",&n);
					read(poly2,n);
					polysum=add(p,poly2);
					printpoly(polysum);
					break;
			case 3: 	exit(0);
		}
	}
	return 0;
}

		
