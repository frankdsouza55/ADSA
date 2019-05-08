#include<iostream>
#include<malloc.h>
#include<utility>
#include<math.h>
using namespace std;
int c=1,minC=0,maxC=0;
struct node
{
	int data,index,minI,maxI;
	struct node *left,*right,*next,*parent;
}*root=NULL,*rear=NULL;
typedef struct node node;
void insert()
{
	node *newnode;
	newnode=(node *)malloc(sizeof(node));
	cout<<"\nEnter data value: ";
	cin>>newnode->data;
	newnode->index=++c;
	newnode->minI=newnode->maxI=0;
	newnode->left=newnode->right=newnode->next=newnode->parent=NULL;
	if(root==NULL)
	{
		node *temp=(node *)malloc(sizeof(node));
		temp->data=-1;
		temp->index=1;
		temp->minI=temp->maxI=0;
		temp->left=temp->right=temp->next=temp->parent=NULL;
		root=rear=temp;
	}
	int level=log2(newnode->index);
	//Find which side of the tree node is inserted
	if(newnode->index < (pow(2,level)+pow(2,level-1)))
		newnode->minI=++minC;
	else
		newnode->maxI=++maxC;
	rear->next=newnode;
	rear=rear->next;
}
void preorder(node *temp)
{
	if(temp!=NULL)
	{
		if(temp->data==-1)
			cout<<"ROOT ";
		else
			cout<<temp->data<<" ";
		preorder(temp->left);
		preorder(temp->right);
	}
}
void inorder(node *temp)
{
	if(temp!=NULL)
	{
		preorder(temp->left);
		if(temp->data==-1)
			cout<<"ROOT ";
		else
			cout<<temp->data<<" ";
		preorder(temp->right);
	}
}
void postorder(node *temp)
{
	if(temp!=NULL)
	{
		preorder(temp->left);
		preorder(temp->right);
		if(temp->data==-1)
			cout<<"ROOT ";
		else
			cout<<temp->data<<" ";
	}
}
node* search_index(int pos)
{
	node *temp=root;
	while(temp != NULL)
	{
		if(temp->index==pos)
			return temp;
		temp=temp->next;
	}
}
node* search_maxPartner(int a)
{
	node *temp=root->right;
	while(temp != NULL)
	{
		if(temp->maxI==a)
			return temp;
		temp=temp->next;
	}
	return NULL;
}
void link_child(node *temp)
{
	node *temp2=NULL;
	if(temp != NULL)
	{
		int leftChildPos,rightChildPos;
		leftChildPos = 2*temp->index;
		rightChildPos = 2*temp->index + 1;
		if(leftChildPos<=c && temp->left==NULL)
		{
			temp2=search_index(leftChildPos);
			temp->left=temp2;
			temp2->parent=temp;
		}
		if(rightChildPos<=c && temp->right==NULL)
		{
			temp2=search_index(rightChildPos);
			temp->right=temp2;
			temp2->parent=temp;
		}
		link_child(temp->next);
	}
}
void clear()
{
	node *temp=root;
	while(root!=NULL)
	{
		root=root->next;
		free(temp);
		temp=root;
	}
	root=rear=NULL;
	c=1;
	maxC=minC=0;
	cout<<"\nDeap cleared!";
}
void check_partner(node *temp)
{
	if(temp!=NULL)
	{
		if(temp->maxI == 0)
		{
			node *j=search_maxPartner(temp->minI);
			if(j==NULL)
				j=search_maxPartner(temp->parent->minI);
			if(j==NULL)
				return;
			if(temp->data > j->data)
				swap(temp->data,j->data);
		}
		check_partner(temp->next);
	}
}
void checkMin(node *temp)
{
	if(temp->parent != root)
	{
		if(temp->data < temp->parent->data)
			swap(temp->data , temp->parent->data);
		checkMin(temp->parent);
	}
}
void checkMax(node *temp)
{
	if(temp->parent != root)
	{
		if(temp->data > temp->parent->data)
			swap(temp->data , temp->parent->data);
		checkMax(temp->parent);
	}
}
void checkMin2(node *temp)
{
	if(temp != NULL)
	{
		if(temp->left != NULL && temp->right != NULL)
			if(temp->right->data < temp->left->data && temp->right->data < temp->data)
			{
				swap(temp->data , temp->right->data);
				checkMin2(temp->right);
			}
		if(temp->left != NULL)
			if(temp->left->data < temp->data)
			{
				swap(temp->data , temp->left->data);
				checkMin2(temp->left);
			}
		if(temp->right != NULL)
			if(temp->right->data < temp->data)
			{
				swap(temp->data , temp->right->data);
				checkMin2(temp->right);
			}
	}
}
void checkMax2(node *temp)
{
	if(temp != NULL)
	{
		if(temp->left != NULL && temp->right != NULL)
			if(temp->right->data > temp->left->data && temp->right->data > temp->data)
			{
				swap(temp->data , temp->right->data);
				checkMax2(temp->right);
			}
		if(temp->left != NULL)
			if(temp->left->data > temp->data)
			{
				swap(temp->data , temp->left->data);
				checkMax2(temp->left);
			}
		if(temp->right != NULL)
			if(temp->right->data > temp->data)
			{
				swap(temp->data , temp->right->data);
				checkMax2(temp->right);
			}
	}
}
void delete_min()
{
	if(root->left!=NULL)
	{
		cout<<"\nDeleted node => "<<root->left->data;
		c--;
		node *temp=root->left,*temp2;
		if(temp->next != NULL)
		{
			swap(temp->data , rear->data);
			while(temp->next != rear)
				temp=temp->next;
			rear=temp;
			//make left or right child pointer of parent NULL
			temp2=temp->next->parent;
			//temp2 points to the parent of the node to be deleted
			//temp->next is the node to be deleted
			if(temp2->left == temp->next)
				temp2->left=NULL;
			if(temp2->right == temp->next)
				temp2->right=NULL;
			if(temp->next->maxI == 0)
				minC--;
			else
				maxC--;
			free(temp->next);		//delete
			temp->next=NULL;
			check_partner(root->left);
			checkMin2(root->left);
		}
		else
		{
			root=rear=NULL;
			c=maxC=minC=0;
			free(temp);
		}
	}
	else
		cout<<"\nDeletion not possible";
}
void delete_max()
{
	if(root->right!=NULL)
	{
		cout<<"\nDeleted node => "<<root->right->data;
		c--;
		node *temp=root->right,*temp2;
		if(temp->next != NULL)
		{
			swap(temp->data , rear->data);
			while(temp->next != rear)
				temp=temp->next;
			rear=temp;
			//make left or right child pointer of parent NULL
			temp2=temp->next->parent;
			//temp2 points to the parent of the node to be deleted
			//temp->next is the node to be deleted
			if(temp2->left == temp->next)
				temp2->left=NULL;
			if(temp2->right == temp->next)
				temp2->right=NULL;
			if(temp->next->maxI == 0)
				minC--;
			else
				maxC--;
			free(temp->next);		//delete
			temp->next=NULL;
			check_partner(root->left);
			checkMax2(root->right);
		}
		else
		{
			root->right=NULL;
			rear=root->left;
			c--;
			maxC=0;
			free(temp);
		}
	}
	else
		cout<<"\nDeletion not possible";
}
void dump(node *temp)
{
	if(temp!=NULL)
	{
		cout<<"\n"<<temp->data<<"\t"<<temp->index<<"\t";
		cout<<temp->minI<<"\t"<<temp->maxI<<"\t";
		if(temp==root)
			cout<<"NULL";
		else
			cout<<temp->parent->data;
		dump(temp->next);
	}
}
int main()
{
	int ch;
	do
	{
		cout<<"\n\n1: Add node\n2: Preorder Traversal\n3: Inorder Traversal";
		cout<<"\n4: Postorder Traversal\n5: Delete min\n6: Delete max";
		cout<<"\n7: Empty the deap\n0: Exit\nChoice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:	insert();
					link_child(root);
					if(rear->maxI == 0)
						checkMin(rear);
					else
						checkMax(rear);
					check_partner(root->left);
					break;
			case 2:	if(root == NULL)
						cout<<"\nDeap is empty";
					else
					{
						cout<<"\nPreorder Traversal : \t";
						preorder(root);
					}
					break;
			case 3:	if(root == NULL)
						cout<<"\nDeap is empty";
					else
					{
						cout<<"\nInorder Traversal : \t";
						inorder(root);
					}
					break;
			case 4:	if(root == NULL)
						cout<<"\nDeap is empty";
					else
					{
						cout<<"\nPostorder Traversal : \t";
						postorder(root);
					}
					break;
			case 5: delete_min();
					check_partner(root->left);
					break;
			case 6: delete_max();
					check_partner(root->left);
					break;
			case 7: clear();
					break;
			case 19:cout<<"\nData\tIndex\tMinI\tMaxI\tParent";
					dump(root);
					break;
			case 0: clear();
					return 0;
			default:cout<<"\nInvalid Input\n";
		}
	}while(ch);
}
/* INPUT
1 8 1 55 1 77 1 4 1 33 1 32 1 45 1 6 1 65 1 70
*/
