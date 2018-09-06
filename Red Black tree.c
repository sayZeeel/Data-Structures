#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

struct node{
	int info;
	char color;//if red we give the value 'r' and 'b' otherwise
	//right and left children and parent
	struct node* right;
	struct node* left;
	struct node* parent;
};

struct node* sentinel;//sentinel's right child will serve as head of the tree here

//left rotation about x
void leftRotate(struct node* x){
	struct node* y;
	y= x->right;//right child
	x->right=y->left;
	if(y->left!=sentinel){//y's left child is not sentinel
		y->left->parent=x;//updating child's parent
	}
	y->parent=x->parent;//updating y's parent 
	if (x->parent==sentinel){
		sentinel->right=y;//updating head
	}
	else if (x==x->parent->left){
		x->parent->left=y;
	}
	else{
		x->parent->right=y;
	}
	y->left=x;//x is left child of y after rotation
	x->parent=y;

}
//left rotation about y
void rightRotate(struct node* y){
	struct node* x;
	x= y->left;
	y->left=x->right;
	if(x->right!=sentinel){//x's left child is not sentinel
		x->right->parent=y;
	}
	x->parent=y->parent;//updating x's parent 
	if(y->parent==sentinel){
		sentinel->right=x;//updating head
	}
	else if (y==y->parent->left){
		y->parent->left=x;
	}
	else{
		y->parent->right=x;
	}
	x->right=y;//y is left child of x after rotation
	y->parent=x;

}

//to fix the properties of red black trees that get violated during insertion
void insertFix (struct node* x){
	struct node* y;
	
	
	while(x->parent->color=='r'){//we cannot have two consecutive red nodes
		if (x->parent==x->parent->parent->left){//parent is a left child
			y= x->parent->parent->right;//y is uncle
			if(y->color=='r'){//if uncle is red we violate the property for equal number of black nodes in each path
				x->parent->color='b';//changing parent color to black
				y->color='b';
				x->parent->parent->color='r';//changing grand parent to red
				x=x->parent->parent;//going two levels up
			}
			else{ //since the property for equal number of black nodes in each path is not violated,
				//if parent of x is a right child we make a left rotation 
				if (x==x->parent->right){
					x= x->parent;
					leftRotate(x);
				}
				x->parent->color='b';
				x->parent->parent->color='r';
				rightRotate(x->parent->parent);
			}
		}
		else{//similar rules as parent being a right child are followed to maintain the properties
			y= x->parent->parent->left;
			if(y->color=='r'){
				x->parent->color='b';
				y->color='b';
				x->parent->parent->color='r';
				x=x->parent->parent;
			}
			else{ 
				if (x==x->parent->left){
					x= x->parent;
					rightRotate(x);
				}
				
				x->parent->color='b';
				x->parent->parent->color='r';
				leftRotate(x->parent->parent);
			}
		}
	}
	sentinel->right->color='b';
}

void insert(){
	printf("Enter a number\n");
	int num,i=0;
	scanf("%d",&num);
	struct node* newNode= (struct node*)malloc(sizeof(struct node));
	struct node* temp;//traverser
	struct node* tempPrev;//to save the parent of temp
	if (sentinel->right==NULL){//the tree is empty
		newNode->info= num;
		newNode->left=sentinel;//the children of leaf node point to sentinel
		newNode->right=sentinel;
		newNode->parent=sentinel;
		sentinel->right=newNode;//updating head
		newNode->color='b';//head is always black
		sentinel->color='b';
		return;
	}
	else{//tree is not empty
		temp= sentinel->right;//traverse from head
		tempPrev=sentinel;//parent of traverser
		
		while(temp!=sentinel){//until you reach the end of tree
			tempPrev=temp;
			if(temp->info>num){//if the input is lesser than info in traverser we go left else we go right
				temp=temp->left;
			}
			else{
				temp=temp->right;
			}
		}
		//new node is inserted at the bottom of tree
		newNode->parent=tempPrev;//updating parent of new node
		newNode->info=num;
		newNode->right=sentinel;
		newNode->left=sentinel;
		newNode->color='r';// all new nodes are given color black initially
		{
		//to decide whether new node is a left or a right child
		if (tempPrev->info>num)
			tempPrev->left=newNode;
		else
			tempPrev->right=newNode;
	}
}



insertFix(newNode);//fix the violated properties after insertion


}

struct node* search(){
	printf("Enter a number\n");
	int num,count=0;
	scanf("%d",&num);
	struct node* temp = sentinel->right;//traverser points to head
	
	while (temp->info!=num){//until the traverser node's value equals the input we keep going down the tree
		if (temp!=NULL){//not reached the end of the tree
			//same rules as insert
			if (temp->info>num)
				temp=temp->left;

			else
				temp=temp->right;
			
		}
		if (temp==NULL) {//reached the end of tree
			printf("not found\n");
			return NULL;
		}
	}
	printf("%d %c\n",temp->info,temp->color );
	printf("found\n");
	return temp;
}



void main(){
	sentinel=(struct node*)malloc(sizeof(struct node));
	sentinel->right=NULL;
	sentinel->left=NULL;
	sentinel->parent=NULL;
	
	sentinel->color='b';

	int option = 0;
	//printf("%d %d %d %d\n",sentinel,sentinel->right,sentinel->left,sentinel->parent );
	
	while(option!=3){//until user chooses to exit
		printf("Enter your option\n1.insert\n2.search\n3.exit\n");
		scanf("%d",&option);
		if (option==1)
			insert();
		if (option==2)
			search();
		
		
		//printf("%d %d %d %d\n",sentinel,sentinel->right,sentinel->left,sentinel->parent );

		
		
	}
}
