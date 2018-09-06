#include <stdio.h>
#include <stdlib.h>

int* parent;
int* rank;

int FIND(int x){//retuens the representative of x
	if(parent[x]!=x){
		parent[x]= FIND(parent[x]);
	}
	return parent[x];
}

void UNION(int x,int y){//creates a union of the sets containing x and y
	int xRep = FIND(x);
	int yRep = FIND(y);
	//printf("%d %d\n",xRep,yRep );
	int Rep=yRep;

	if(xRep!=yRep){//if the representatives are not equal
		if(rank[xRep]<rank[yRep]){//if rank of y is greater than rank of x
			parent[xRep]=yRep;
			Rep=yRep;
		}
		else if (rank[xRep]>rank[yRep]){
			parent[yRep]=xRep;
			Rep=xRep;
		}
		else{
			parent[xRep]=yRep;
			Rep=yRep;
			rank[yRep]++;//if the ranks are equal we increment the rank of any one
		}
		printf("representative for both is %d now\n",Rep );
	}
	else{
		printf("They already have the same representative %d\n", Rep);
	}
}

void main(){
	int N,option=0,x,y;
	printf("Enter N the number of disjoint elements. N elements will be created with the values 0,1,2...N-1 with initial ranks 0 \n");
	scanf("%d",&N);

	parent = (int*)malloc(sizeof(int)*N);
	rank = (int*)malloc(sizeof(int)*N);

	for(x=0;x<N;x++){
		parent[x]=x;
		rank[x]=0;
	}
	while(option!=3){
		printf("1.Find an element's representative\n2.Make a union out of the sets containing two elements\n3.exit\n\n");
		scanf("%d",&option);
		if(option==1){
			printf("Enter the element :");
			scanf("%d",&x);
			if(x<0 || x>=N){
				printf("element not present\n");
			}
			else{
				y=FIND(x);
				printf("The representative is %d\n",y);
			}
		}
		if(option==2){
			printf("Enter the first element :");
			scanf("%d",&x);
			printf("Enter the second element :");
			scanf("%d",&y);
			if(x<0 || x>=N){
				printf("%d not present\n",x);
				break;
			}
			if(y<0 || y>=N){
				printf("%d not present\n",y);
				break;
			}
			UNION(x,y);
		}
	}
}