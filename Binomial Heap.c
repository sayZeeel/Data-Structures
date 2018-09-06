#include <stdio.h>
#include <stdlib.h>

struct node{
    int value,degree;
    struct node* child;
    struct node* sibling;
    struct node* parent;
};
struct node* head = NULL;





void link(struct node* y,struct node* z){// links 1 heap to  another heap when both the heaps are of same degree
    struct node* temp;
    y->parent= z;
    temp=z->child;
    //y->sibling = z->child;
    y->sibling= temp;
    z->child = y;
    z->degree++;
}
//after linking we arrange the trees in the heaps in the ascending order of their degrees
struct node* merge(struct node* H1,struct node* H2){
    struct node* mergedHeap = NULL;
    struct node* temp;
    struct node* y =H1;
    struct node* z =H2;

    //if one of the heaps is empty the other is returned
    if(y!=NULL){
        if(z!=NULL&& z->degree<y->degree){//the one with lesser degree in start is put as mergedHeap
            mergedHeap=z;
        }
        else
            mergedHeap=y;
    }
    else{
        mergedHeap=z;
    }
    //if degree of the other heap is lesser than the one we are traversing we add that node before the node the traverser is on
    while(y!=NULL&& z!=NULL){
        if(y->degree<z->degree){
            y=y->sibling;
        }
        else if(y->degree==z->degree){
            temp=y->sibling;
            y->sibling=z;
            y=temp;
        }
        else{
            temp=z->sibling;
            z->sibling=y;
            z=temp;
        }
    }
    
    
    

    return mergedHeap;

}
//first merges the two heaps and then makes the trees having same degree as one tree of a degree increased by 1
struct node* Union(struct node* H1,struct node* H2 ){
    struct node* xPrev;
    struct node* x;

    struct node* xNext;
    struct node* newHeap = (struct node*)malloc(sizeof(struct node));
    newHeap = merge(H1,H2);
    if(newHeap==NULL){
        printf("empty heap\n");
        return newHeap;
    }
    x=newHeap;
    xPrev=NULL;
    xNext=x->sibling;
    while(xNext!=NULL){
        //checks if two consecutive degrees are not same and whether 3 consecutive trees have the same degree then the last 2 are erged
        if((x->degree!=xNext->degree)||((xNext->sibling!=NULL)&&(xNext->sibling->degree==x->degree))){
            xPrev=x;
            x=xNext;
        }
        else {
            if (x->value<=xNext->value){
                x->sibling=xNext->sibling;
                link(xNext,x);
            }
            else{
                if(xPrev==NULL){
                    newHeap=xNext;  
                }
                else
                    xPrev->sibling=xNext;
                link(x,xNext);
                x= xNext;
            }
        }
        xNext= x->sibling;

    }
    head = newHeap;
    return newHeap;

}
//finds minimum in the heap
struct node* findMin(struct node* heap){
    struct node* temp = heap;
    struct node* tempPrev = temp;
    if(temp==NULL){
        printf("empty\n");
        return NULL;
    }
    int x= temp->value;//traverse till you reach the mend recording the minimum
    while(temp!=NULL){
        if(temp->value<x){
            x=temp->value;
        }
        tempPrev=temp;
        temp=temp->sibling;
    }
    printf("the min is %d\n",x );
    return tempPrev;
}

struct node* extractMin(struct node* heap){//deletes the minimum
    struct node* temp =heap;
  

    struct node* tempPrev = NULL;
    struct node* tempNext = temp;

    if(temp==NULL){
        printf("empty\n");
        return NULL;

    }
    int x= temp->value;

    while(temp->sibling!=NULL){
        if(temp->sibling->value<x){
            tempPrev=temp;
            x=temp->sibling->value;
            tempNext= temp->sibling;
        }
      
        temp=temp->sibling;
    }
    //node containing min is removed from heap
    if(tempPrev==NULL&&tempNext->sibling==NULL){
        heap=NULL;
    }
    else if(tempPrev==NULL){
        heap=tempNext->sibling;
    }
    else{
        tempPrev->sibling=tempNext->sibling;
    }

    //tempPrev->sibling=tempPrev->sibling->sibling;

    struct node* a =tempNext->child;

    struct node* aPrev=NULL;

    struct node* aNext;

   
    if(a!=NULL){//reverses the entire list by making the rightmost child as  head
        while(a!=NULL){
            aNext=a->sibling;
            a->sibling=aPrev;
            aPrev=a;
            //aPrev->parent=NULL;
            a=aNext;
              
        }
    }
    struct node* temp1 = aPrev;
   
   

    heap = Union(heap,aPrev);
    free(tempNext);

    return heap;
  

}


struct node* insert(struct node* heap){
    int x;
    printf("Enter the element to be inserted\n");
    scanf("%d",&x);
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->value= x;
    newNode->degree= 0;
    newNode->parent= NULL;
    newNode->child= NULL;
    newNode->sibling= NULL;

    heap = Union(heap,newNode);

}

int main(){
    int option = 0;
    while(option!=4){
        printf("start\n");

        printf("Enter your option\n1.insert\n2.find Min\n3.delete min\n4.exit\n");
        scanf("%d",&option);
        if (option==1)
            {
                insert(head);
      
          
            }
        if (option==2){
            findMin(head);
        }
        //printf("22blah\n");
        if(option==3){
          
            extractMin(head);
        }
      
       
      
    }

    return 0;
}