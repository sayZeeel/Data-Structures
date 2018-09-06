#include <stdio.h>
#include <stdlib.h>

struct adjacnListNode {//nodes in the adjacency list
	int point;
	int weight;
	struct adjacnListNode* next;
};

struct adjacnList//the adjacency list
{
	struct adjacnListNode* head;
};

struct adjacnList* Array ;//array of adjacency lists
struct Tree//the tree we use meanheapify on
{
	int vertex;
	int key;
};
int heapSize;//size of minheap
int* position;

int PARENT(int i){//returns the parent of i 
	return ((i-1)/2);
}
int LEFT(int i){//returns the left child of i 
	return (2*i+1);
}
int RIGHT(int i){//returns the rightt child of i 
	return (2*i+2);
}
void MinHeapify(struct Tree* A,int i){
	int l,r,smallest;
	//smallest=i;
	struct Tree temp;
	l=LEFT(i);
	r=RIGHT(i);
	//here we find the smallest element among the parent and the two children
	if (l<heapSize&&A[l].key<A[i].key){//if left child is smaller than parent i
		smallest = l;
	}
	else smallest= i;
	if (r<heapSize&&A[r].key<A[smallest].key){//if right child is smaller than the updated 'smallest'
		smallest=r;
	}
	if (smallest!=i){
		//if the parent was not the smallest of the three, the properties have been violated
		//we swap the parent with the smallest element of the three
		temp= A[i];
		//updating the new positions of vertices in position array
		position[A[i].vertex]=smallest;
		position[A[smallest].vertex]=i;

		A[i]=A[smallest];
		A[smallest]=temp;

		MinHeapify(A,smallest);

	}
}

int extractMin(struct Tree*A){
	int x;
	struct Tree temp;
	if (heapSize==0){
		printf("Minheap is empty\n");
		return -1;
	}
	x = A[0].vertex;

	temp=A[0];
	//updating the new positions of vertices in position array
	position[A[0].vertex]=heapSize-1;
	position[A[heapSize-1].vertex] = 0;
	A[0]=A[heapSize-1];//we put the last element of minheap as first element and decrease the heapsize by 1
	A[heapSize-1]=temp;
	heapSize--;
	MinHeapify(A,0);//to fix the violated properties of minheap
	return x;
}

void prims(int vert){
	struct Tree heap[vert];//our minheap array


	
	int i,j,parent[vert];//to store the parent of vertex still in minheap

	for(i=0;i<vert;i++){
		heap[i].vertex=i;
		heap[i].key = 2147483600;//assigning infinity
		parent[i]= -1;
		position[i]=i;
	}

	heap[0].key= 0;//initial value 0
	i=0;
	struct adjacnListNode* temp;
	struct Tree swap;
	int lmn;
	while(heapSize>0){
		j = extractMin(heap);//the minimum vertex
		
		temp= Array[j].head;//head of the adjacency list
		while(temp!=NULL){//traverse through the list
			i=temp->point;
			lmn=position[i];//find position of the vertex in minheap

			//if i is part of minheap and weight of i-j is less than key, we update key
			if(lmn<heapSize&& temp->weight<heap[lmn].key){
				heap[lmn].key=temp->weight;
				
				//traverse up the heap until the properties of minheap are satisfied
				while(lmn&&heap[lmn].key < heap[PARENT(lmn)].vertex){
					//update positions of vertices
					position[heap[lmn].vertex]=PARENT(lmn);
					position[heap[PARENT(lmn)].vertex]=lmn;
					//swap the elemnts of heap
					swap=heap[lmn];
					heap[lmn]=heap[PARENT(lmn)];
					heap[PARENT(lmn)]=swap;
					lmn=PARENT(lmn);
				
				}
				
				parent[i]=j;//updating the parent of i as j. j is now in MST and out of minheap
			}
			temp=temp->next;
		}
	}
	//printing the MST
	for(i=1;i<vert;i++){
		printf("%d ------ %d \n",i, parent[i]);
	}
}

void main(){
	int vertices,edges,start,end,weight,i=0;
	printf("Enter the number of vertices\n");
	scanf("%d",&vertices);
	printf("Enter the number of edges\n");
	scanf("%d",&edges);
	heapSize = vertices;

	Array = (struct adjacnList*)malloc(sizeof(struct adjacnList)*vertices);
	position = (int*)malloc(sizeof(int)*vertices);
	
	
	while(i<edges){
		printf("Edge %d\n",i);
		printf("Enter the source :");
		scanf("%d",&start);
		printf("Enter the destination :");
		scanf("%d",&end);
		printf("Enter the weight :");
		scanf("%d",&weight);

		//to add the new nodes in the adjacency lists of both the vertices

		struct adjacnListNode* sourceToDest = (struct adjacnListNode*)malloc(sizeof(struct adjacnListNode));
		sourceToDest->point=end;
		sourceToDest->weight=weight;
		sourceToDest->next=Array[start].head;
		
		Array[start].head=sourceToDest;
		

		struct adjacnListNode* destToSource = (struct adjacnListNode*)malloc(sizeof(struct adjacnListNode));
		destToSource->point=start;
		destToSource->weight=weight;
		destToSource->next=Array[end].head;
		
		Array[end].head=destToSource;
		i++;
		

	}
	prims(vertices);

}