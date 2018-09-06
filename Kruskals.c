#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int heapSize;

struct node{
    int rank;
    int parent;
};

struct edge{
    int pointFrom,pointTo,weight;
};

int PARENT(int i){
    return ((i-1)/2);
}
int LEFT(int i){
    return (2*i+1);
}
int RIGHT(int i){
    return (2*i+2);
}

// compares the  current value with its children and puts the smallest value among them
// at the place of the  current value and then recursion goes to the child from which it is
// swapped
void MinHeapify(struct edge* A,int i){
    int l,r,smallest;
    //smallest=i;
    struct edge temp;
    l=LEFT(i);// left child
    r=RIGHT(i);// right child
    if (l<heapSize&&A[l].weight<A[i].weight){
        smallest = l;
    }
    else smallest= i;
    if (r<heapSize&&A[r].weight<A[smallest].weight){
        smallest=r;
    }
    if (smallest!=i){
        temp= A[i];
        A[i]=A[smallest];
        A[smallest]=temp;
        MinHeapify(A,smallest);

    }
}

void BuildMinHeap(struct edge* A,int edges){// builds the minheap initially of the given elements
    int i;
    heapSize = edges;
    for (i=(heapSize/2)-1;i>=0;i--){
        MinHeapify(A,i);
    }
}

// sorts the given array and gives them in decreasing ordeer
void HeapSort(struct edge* A,int edges){
    BuildMinHeap(A,edges);
    int length=edges;
    int i;
    struct edge temp;
    for (i=length-1;i>0;i--){
        temp=A[0];
        A[0]=A[i];
        A[i]=temp;
        heapSize--;
        MinHeapify(A,0);
    }

}
void makeSet(struct node* temp,int i){
    temp[i].parent=i;
    temp[i].rank=0;
}

int findSet(struct node* x,int i){// gives the representative of the set
    if (x[i].parent!=i)
        x[i].parent=findSet(x,x[i].parent);
    return x[i].parent;
}


void Union(struct node* A,int x,int y){ // gives the union of 2 sets
    int xp,yp;
    xp=findSet(A,x);
    yp=findSet(A,y);
    //link(A,xp,yp);
    if (A[xp].rank>A[yp].rank){
        A[yp].parent=xp;
    }
    else{ 
        A[xp].parent=yp;
        if (A[xp].rank==A[yp].rank)
            A[yp].rank++;
    }
}

void Kruskal(int vert,int ed,struct edge* A){
    struct edge MST[vert];
    int i,j=0;
    struct edge temp;
    //struct node* ArrVertices = (struct node*)malloc(sizeof(struct node)*vert);

    HeapSort(A,ed);// array gets sorted in descending with respect to weight
    for(i=0;i<ed;i++){
        printf(" %d ",A[i].weight);
    }
    printf("\n");
    for (i=0;i<ed/2;i++){// converting descending order into ascending order
        temp=A[i];
        A[i]=A[ed-i-1];
        A[ed-i-1]=temp;
    }
    for(i=0;i<ed;i++){
        printf(" %d ",A[i].weight);
    }
    struct node* sets = (struct node*)malloc(sizeof(struct node)*vert);
    for (i=0;i<vert;i++){
        makeSet(sets,i);
    }
    i=0;
    while (j<vert-1){// going through the sorted array
        int x= findSet(sets,A[i].pointFrom);
        int y= findSet(sets,A[i].pointTo);
        
        if (x!=y){// if a cycle is not being formed
            MST[j]=A[i];
            Union(sets,x,y);
            j++;
        }
        i++;

    }
    printf("MST has these edges: [");
    for(i=0;i<j;i++){// printing the MST
        printf("(%d-->%d,weight= %d)",MST[i].pointFrom,MST[i].pointTo,MST[i].weight);
    }


}


void main(){
    int vert,ed,i;
    printf("enter the number of vertices\n");
    scanf("%d",&vert);
    //int ArrVertices[vert];
    printf("enter the number of edges\n");
    scanf("%d",&ed);
    //struct graph* Graph= createGraph(vert,ed);
    struct edge* EDGE =(struct edge*)malloc(sizeof(struct edge)*ed);
    for (i=0;i<ed;i++){
        printf("EDGE[%d].pointFrom : ",i);
        scanf("%d",&EDGE[i].pointFrom);
        printf("\nEDGE[%d].pointTo : ",i);
        scanf("%d",&EDGE[i].pointTo);
        printf("\nEDGE[%d].weight : ",i);
        scanf("%d",&EDGE[i].weight);
        printf("\n(%d,%d,'%d')\n",EDGE[i].pointFrom,EDGE[i].pointTo,EDGE[i].weight);
        
    }

    Kruskal(vert,ed,EDGE);


}