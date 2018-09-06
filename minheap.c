#include <stdio.h>
#include <stdlib.h>

int *A;

int heapSize=0;//initially elements in meanheap are 0

int PARENT(int i){//returns the parent of i 
	return ((i-1)/2);
}
int LEFT(int i){//returns left child of i
	return (2*i+1);
}
int RIGHT(int i){//returns right child of i
	return (2*i+2);
}
void MinHeapify(int i){
	int l,r,smallest;
	//smallest=i;
	int temp;
	l=LEFT(i);
	r=RIGHT(i);
	//here we find the smallest element among the parent and the two children
	if (l<heapSize&&A[l]<A[i]){//if left child is smaller than parent i
		smallest = l;
	}
	else smallest= i;
	if (r<heapSize&&A[r]<A[smallest]){//if right child is smaller than the updated 'smallest'
		smallest=r;
	}
	if (smallest!=i){//if the parent was not the smallest of the three, the properties have been violated
		//we swap the parent with the smallest element of the three
		temp= A[i];
		A[i]=A[smallest];
		A[smallest]=temp;
		MinHeapify(smallest);//recursively called for one level down

	}
}

void insert(){
	int x;
	printf("Enter the element you want to insert\n");
	scanf("%d",&x);
	heapSize++;//we increase the size of meanheap by 1
	A[heapSize-1]=x;//entering the new element at the end
	int i,temp;
	for(i=heapSize-1;i>0;i=PARENT(i)){//if the parent of i'th element is lesser than i'th element we swap the two
		if (A[i]<A[PARENT(i)])
		{
			temp=A[i];
			A[i]=A[PARENT(i)];
			A[PARENT(i)]=temp;
		}
	}

}
void findMin(){
	printf("%d is the min\n",A[0] );//the first element in minheap is the minimum
}
void deleteMin(){
	if (heapSize==0){//empty minheap
		printf("Minheap is empty\n");
		return;
	}
	A[0]=A[heapSize-1];//we put the last element of minheap as first element and decrease the heapsize by 1
	heapSize--;
	MinHeapify(0);//to fix the violated properties of minheap
}
void main(){
	int option = 0,length,i;
	printf("Enter the maximum number of elements you will be inserting\n");
	scanf("%d",&length);
	A=malloc(sizeof(int)*length);
	
	while(option!=4){//until user chooses to exit
		printf("Enter your option\n1.insert\n2.find Min\n3.delete Min\n4.exit\n");
		scanf("%d",&option);
		if (option==1)
			insert();
		if (option==2)
			findMin();
		
		if (option==3)
			deleteMin();
		for(i=0;i<heapSize;i++){
			printf("%d ",A[i] );
		}
		
	}
}