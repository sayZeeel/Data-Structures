#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#define t 3//defining t as 3

struct node {
	int keys[2*t-1];//max number of keys possible is 2*t-1
	struct node* children[2*t];//max number of children possible are 2*t
	int n;//number of keys currently
	bool leaf;//whether its a leaf or not
};
struct node* root=NULL;

void merge(struct node* x, int k);
void prevChildBorrow(struct node* x, int k);
void nextChildBorrow(struct node* x, int k);
void delete(struct node* x,int value);


struct node* search(struct node* x, int k){//we pass the node from where we need to start searching and the value that needs to be searched
	int i;
	struct node* A= NULL;
	for(i=0;i<x->n&&k>x->keys[i];i++){
		//while the value of k is greater than value in keys and we did not reach the end of array, we keep going further in the array
	}
	
	//i records the index
	if(i<x->n&&x->keys[i]==k){//if k matches one of the keys
		printf("Found\n");
		A=x;
	}
	else if (x->leaf){//if the input node is a leaf it cannot have any children to search further in
		printf("Not found\n");
	}
	else search(x->children[i],k);//recursively called in its i'th child 
	return A;
}

void printTree(struct node* x){
	int i;
	for(i=0;i<x->n;i++){
		if(!x->leaf){
			printTree(x->children[i]);
		}
		printf("%d ",x->keys[i] );
	}
	if(!x->leaf){
		printTree(x->children[i]);
	}
}


//called when keys array of the child reaches its max capacity
void splitChild(struct node* x,int i){
	
	struct node* y= x->children[i];
	struct node* z= (struct node*)malloc(sizeof(struct node));//z is the array which we will be putting last t-1 elements of y into

	int j;
	z->leaf=y->leaf;//z has the same properties as y
	z->n=t-1;
	for(j=0;j<t-1;j++){
		z->keys[j]=y->keys[j+t];//putting last t-1 elements of y into z
	}
	if(!y->leaf){//y has children
		for(j=0;j<t;j++){
			z->children[j]=y->children[j+t];//assigning last t children of y to z
		}
	}
	y->n=t-1;//updating size of y
	for(j=x->n;j>i;j--){
		x->children[j+1]=x->children[j];//shifting children of x to the right by 1
	}
	x->children[i+1]=z;//add ing z as child in the correct position
	for(j=x->n-1;j>=i;j--){
		x->keys[j+1]=x->keys[j];//shifting keys of x to the right by 1
	}
	x->keys[i]=y->keys[t-1];//shifting the median to the parent
	x->n++;//updating number of keys in x

}
//when the number of keys have not reached their max capacity
void insertNonFull(struct node* x,int k){
	int i = x->n-1;
	if (x->leaf){//x is a leaf
		for(;i>=0&&k<x->keys[i];i--){
			x->keys[i+1]=x->keys[i];//until we reach the position where k can be placed, we shift the keys to the right
		}

		x->keys[i+1]=k;//inserting k
		x->n=x->n+1;//updating th enumber of keys
	}
	else {//x has children
		for(;i>=0&&k<x->keys[i];i--){//to get the index of the child we are inserting k in

		}
		
		if (x->children[i+1]->n==2*t-1)//if the i+1th child has max capacity we split it 
		{
			splitChild(x,i+1);
			//if the median from the old child is lesser than k we increment i
			if(k>x->keys[i+1]){
				i++;
			}
		}
		//inserting k in correct child
		insertNonFull(x->children[i+1],k);
	}
}
int getIndex(struct node* x,int k){//gets the index of where the value k could be in x's keys or which child of x
	int i=0;
	while(i < x->n && k>x->keys[i]){
		i++;
	}
	return i;
}
void leafDeletion(struct node* x, int k){//if we are deleting from a leaf,here k is the index
	int i;
	for (i=k+1;i<x->n;i++){
		x->keys[i-1]=x->keys[i];//we shift the element to the left by 1 from k onwards
	}
	x->n--;
	return;
}
int findPredecessor(struct node* x, int k){//find predecessor of keys[k]
	struct node* temp = x->children[k];
	int value;
	while(!temp->leaf){
		temp = temp->children[temp->n];
	}
	value= temp->keys[temp->n - 1];//the largest value in that child
	//leafDeletion(temp,temp->n - 1);
	return value;
}

int findSuccessor(struct node* x, int k){//find the successor of keys[k]
	struct node* temp = x->children[k+1];
	int value;
	while(!temp->leaf){
		temp = temp->children[0];
	}
	value= temp->keys[0];//smallest value in that child
	//leafDeletion(temp,0);
	return value;
}

void merge(struct node* x, int k){//meges children[k] with children[k+1] and frees children[k+1]
	struct node* prevChild = x->children[k];
	struct node* nextChild = x->children[k+1];

	int i;

	prevChild->keys[t-1] = x->keys[k]; //inserting the key into t-1th position
	for(i=0;i<nextChild->n;i++){
		prevChild->keys[i+t] = nextChild->keys[i];//adding all values from nextChild to prevChild
	}
	if (!prevChild->leaf){//if it has children
		for(i=0;i<=nextChild->n;i++){
			prevChild->children[i+t] = nextChild->children[i];//assigning children of nextCHild to prevChild
		}
	}
	for (i=k+1;i<x->n;i++){
		x->keys[i-1] = x->keys[i];//shifting keys to the left by 1
	}
	for(i=k+2;i<=x->n;i++){
		x->children[i-1] = x->children[i];//shifting children to the left by 1
	}
	prevChild->n = prevChild->n + nextChild->n +1;//updating the number of keys of mergedchild
	x->n--;//updating number of keys of x
	free(nextChild);
}


void nonLeafDeletion(struct node* x, int k){//if the leaf we are deleting from has children
	int value = x->keys[k];
	int predecessor;
	if(x->children[k]->n >= t){//if kth child has more than minimum keys
		predecessor =  findPredecessor(x,k);//get the predecessor
		x->keys[k] = predecessor;//update the key
		delete(x->children[k],predecessor);
	
	}

	else if(x->children[k+1]->n >= t){//if k+1th child has more than minimum keys
		int successor = findSuccessor(x,k);//get the successor
		x->keys[k]= successor;//update the key
		delete(x->children[k+1],successor);
		}

	else{//if both the children have exactly minimum keys
		merge(x,k);//merge the two children
		delete(x->children[k],value);
	}
}

void fill (struct node* x, int k){//to fill the child with less than minimum keys
	if(k!=0&& x->children[k-1]->n>=t){//k-1th child has more than minimum keys,borrow a key from it
		prevChildBorrow(x,k);
	}
	else if(k!=x->n&& x->children[k+1]->n>=t){//k+1th child has more than minimum keys
		nextChildBorrow(x,k);
	}
	else{//if both have exactly minimum keys
		if(k!=x->n){//if its not the last key
			merge(x,k);
		}
		else{
			merge(x,k-1);
		}
	}
	return;
}

void prevChildBorrow(struct node* x, int k){//borrow key from children[k-1]
	struct node* prevChild = x->children[k-1];
	struct node* Child = x->children[k];
	int i;
	//last key from prevChild goes to parent at kth position and the key over there is put in the 1st position of Child
	for(i=Child->n-1;i>=0;i--){//shifting keys to the right by 1
		Child->keys[i+1]=Child->keys[i];
	}
	Child->keys[0]= x->keys[k-1];
	if(!Child->leaf){//not a leaf
		for(i=Child->n;i>=0;i--){//shifting children to the right by 1
			Child->children[i+1] = Child->children[i];
		}
	}
	if(!x->leaf){//last child of prevChild as first child of Child
		Child->children[0]=prevChild->children[prevChild->n];
	}
	x->keys[k-1] =prevChild->keys[prevChild->n-1];

	//updating the number of keys
	Child->n++;
	prevChild->n--;

	return;

}

//borrow a key fro children[k+1]
//similar rules as prevChildBorrow are followed but here 1st key from nextChild goes to parent at kth position and key over ther is put in last position of Child
void nextChildBorrow(struct node* x, int k){
	struct node* nextChild = x->children[k+1];
	struct node* Child = x->children[k];
	int i;

	Child->keys[Child->n]= x->keys[k];
	x->keys[k]=nextChild->keys[0];

	for (i=1;i<nextChild->n;i++){
		nextChild->keys[i-1]=nextChild->keys[i];
	}
	if(!nextChild->leaf){
		for (i=1;i<=nextChild->n;i++){
			nextChild->children[i-1]=nextChild->children[i];
		}
	}

	if(!(Child->leaf)){
		Child->children[Child->n+1]=nextChild->children[0];
	}

	Child->n++;
	nextChild->n--;

}

void delete(struct node* x,int value){//delete value from tree x
	int k,y=0;
	
	struct node* temp = x;
	
	k= getIndex(temp,value);

	if(k<temp->n && value==temp->keys[k]){
		if(temp->leaf)//no children
			leafDeletion(temp,k);
		else//has children
			nonLeafDeletion(temp,k);
	}

	else {
		if(temp->leaf){//if we are at a leaf, the value is not present
			printf("Value not found\n");
			return;
		}
		if(k==temp->n){//if we going into the last child of the node
			y=1;
		}
		//the child has less than minimum keys after deletion
		if(x->children[k]->n < t){
			fill(x,k);
		}
		//if merged with the last child or not
		if(y && k>x->n){
			delete(x->children[k-1],value);
		}
		else
			delete(x->children[k],value);

	}
	

	if (root->n==0){//if root has 0 keys,if it has children, its first child is made the new root
		struct node* discard = root;
		if(root->leaf){
			root=NULL;
		}
		else{
			root = root->children[0];

		}
		free(discard);
	}

	return;
	
		
}




void insert(){
	//printTree(root);
	printf("inserting\n");
	int value;
	printf("Enter the value :");
	scanf("%d",&value);
	struct node* temp=root;
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	if (temp==NULL){//tree is empty
		newNode->keys[0]=value;
		newNode->leaf=TRUE;
		newNode->n=1;
		root=newNode;//updating root
		return;
	}
	if (temp->n==2*t-1){//if the keys are all full
		printf("full\n");
		//update the root and makeold root as child of new root
		root= newNode;
		newNode->leaf= FALSE;
		newNode->n=0;
		newNode->children[0]=temp;
		//split the full child 
		splitChild(newNode,0);
		insertNonFull(newNode,value);

	}
	else
		insertNonFull(temp,value);

}

void main(){
	int option = 0;
	while(option!=4){
		printf("start\n");
		//printTree(root);
		printf("Enter your option\n1.insert\n2.search\n3.delete\n4.exit\n");
		scanf("%d",&option);
		if (option==1)
			{
				insert();
			//printf("blah\n");
			
			}
		if (option==2){
			int value;
			printf("Enter the value to be searched :");
			scanf("%d",&value);
			search(root,value);
		}
		//printf("22blah\n");
		if(option==3){
			int value;
			printf("Enter the value to be deleted :");
			scanf("%d",&value);
			delete(root,value);
		}
		printTree(root);
		
		
	}
}