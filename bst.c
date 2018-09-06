#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

struct node {
	int info;//information stored in the node
	struct node* left;//pointer to left child
	struct node* right;//pointer to right child
};
struct node* head= NULL;

void insert(){
	printf("Enter a number\n");
	int num;
	scanf("%d",&num);
	struct node* newNode= (struct node*)malloc(sizeof(struct node));
	struct node* temp;//to traverse through the tree
	struct node* tempPrev;//to store the parent of temp
	if (head==NULL){//tree is currently empty
		newNode->info= num;
		//the left and right child are NULL since its the only node in the tree
		newNode->left=NULL;
		newNode->right=NULL;
		head=newNode;//pointing head to the newly inserted node
	}
	else{//tree is not empty
		temp= head;
		tempPrev=NULL;
		while (1){
			tempPrev=temp;//to store the parent of temp before temp changes
				
			if (num<temp->info){//input is less than the current node value
				temp= temp->left;//go left down the tree
				//keep going down the tree until you reach the leaf node
				if (temp==NULL){
					tempPrev->left= newNode;
					newNode->info= num;
					newNode->left=NULL;
					newNode->right=NULL;
					return;//once the node is inserted, you exit the function
				}
			}
			else {//input is greater than the current node value
				temp=temp->right;//go right down the tree
				//keep going down the tree until you reach the leaf node
				if (temp==NULL){
					tempPrev->right= newNode;
					newNode->info= num;
					newNode->left=NULL;
					newNode->right=NULL;
					return;
				}

			}
			}
		}
	

}

struct node* search(){
	printf("Enter a number\n");
	int num,count=0;
	scanf("%d",&num);
	struct node* temp = head;
	
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
	printf("found\n");
	return temp;
}

void delete(){
	printf("Enter a number\n");
	int num,count=0;
	scanf("%d",&num);
	struct node* temp = head,*tempPrev;
	int newHead = 0;
	int ifleft;//to check if the node to be deleted is a left child or a right child
	struct node* successor;
	struct node* childr = head->right;//right child of head
	struct node* childl = head->left;//left child of head
	
	while (temp->info!=num){
		tempPrev = temp;
		count++;
		if (temp!=NULL){
			
			if (temp->info>num){
				temp=temp->left;
				ifleft = 1;
			}
			else{
				temp=temp->right;
				ifleft = 0;
			}

			childl= temp->left;//new children of the traverser
			childr=temp->right;
		}
		if (temp==NULL) {//traverser reached the end of tree
			printf("not found\n");
			return;
		}
	}
	//printf("%d\n",count);

	if (count==0){//the loop never ran so we need to delete the head node
		newHead=1;
		printf("head deletion\n");
	}
	count=0;
	if(childr== NULL && childl==NULL){//leaf node
		free(temp);
		if (newHead==1){
			head=NULL;
			printf("The tree is now empty\n");
			return;
			}
		if (ifleft)//if its left child
		{
			tempPrev->left = NULL;
		}
		else//if its a right child
			tempPrev->right = NULL;

	}
	else if ((childl!=NULL&&childr==NULL) || (childr!=NULL&&childl==NULL)){//it has one child
		if (childl==NULL){//it has a right child
			temp->info= childr->info;//we skip the right child and make its parent point to subsequent nodes
			temp->right=childr->right;
			temp->left= childr->left;
			free(childr);//free memory for childr

		}
		else {//it has a left child
			temp->info= childl->info;//we skip the left child and make its parent point to subsequent nodes
			temp->right=childl->right;
			temp->left= childl->left;
			free(childl);
		}
	}
	else{//it has both right and left child
		ifleft = 0;
		//here childr serves as a traverser 
		while(childr->left!=NULL){//reaching the leftmost node of right child
			tempPrev = childr;//store the parent of childr before it goes down
			ifleft++;
			childr=childr->left;
		}
		if (childr->right==NULL){//leftmost node is a leaf
			temp->info= childr->info;
			
			if(ifleft)
				tempPrev->left = NULL;
			else
				temp->right = NULL;
			free(childr);
			
		}
		else{//leftmost node has a right child 
			temp->info=childr->info;//same rules as skipping a node as stated earlier
			successor=childr;
			childr=successor->right;
			successor->info= childr->info;
			successor->right=childr->right;
			successor->left= childr->left;
			free(childr);

		}
	}
	if (newHead==1){//the head was deleted so updating the new head
		head->info=temp->info;
		head->right=temp->right;
		head->left=temp->left;
	}
	
	printf("Deleted\n");
	
}



void main(){
	int option = 0;
	while(option!=4){
		printf("Enter your option\n1.insert\n2.search\n3.delete\n4.exit\n");
		scanf("%d",&option);
		if (option==1)
			insert();
		if (option==2)
			search();
		if (option==3)
			delete();
		
		
	}
}