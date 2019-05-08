#include<iostream>
#include<malloc.h>
#include<utility>
using namespace std;
int c=0;
struct node
{
	int data,index;
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
	newnode->left=newnode->right=newnode->next=newnode->parent=NULL;
	if(root==NULL)
		root=rear=newnode;
	else
	{
		rear->next=newnode;
		rear=rear->next;
	}
}
void preorder(node *temp)
{
	if(temp!=NULL)
	{
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
void check(node *temp)
{
	if(temp->parent != NULL)
	{
		if(temp->data > temp->parent->data)
			swap(temp->data , temp->parent->data);
		check(temp->parent);
	}
}
void checkChild(node *temp)
{
	if(temp != NULL)
	{
		if(temp->left != NULL && temp->right != NULL)
			if(temp->right->data > temp->left->data && temp->right->data > temp->data)
			{
				swap(temp->data , temp->right->data);
				checkChild(temp->right);
			}
		if(temp->left != NULL)
			if(temp->left->data > temp->data)
			{
				swap(temp->data , temp->left->data);
				checkChild(temp->left);
			}
		if(temp->right != NULL)
			if(temp->right->data > temp->data)
			{
				swap(temp->data , temp->right->data);
				checkChild(temp->right);
			}
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
	c=0;
	cout<<"\nHeap cleared!";
}
void delete_one()
{
	if(root!=NULL)
	{
		cout<<"\nDeleted node => "<<root->data;
		c--;
		node *temp=root,*temp2;
		if(root->next != NULL)
		{
			swap(root->data , rear->data);
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
			free(temp->next);		//delete
			temp->next=NULL;
			checkChild(root);
		}
		else
		{
			root=rear=NULL;
			c=0;
			free(temp);
		}
	}
	else
		cout<<"\nHeap is empty";
}
void delete_all()
{
	delete_one();
	while(root!=NULL)
		delete_one();
}
int main()
{
	int ch;
	do
	{
		cout<<"\n\n1: Add node\n2: Preorder Traversal\n3: Inorder Traversal";
		cout<<"\n4: Postorder Traversal\n5: Delete one node\n6: Delete all nodes";
		cout<<"\n7: Empty the heap\n0: Exit\nChoice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:	insert();
					link_child(root);
					check(rear);
					break;
			case 2:	if(root == NULL)
						cout<<"\nHeap is empty";
					else
					{
						cout<<"\nPreorder Traversal : \t";
						preorder(root);
					}
					break;
			case 3:	if(root == NULL)
						cout<<"\nHeap is empty";
					else
					{
						cout<<"\nInorder Traversal : \t";
						inorder(root);
					}
					break;
			case 4:	if(root == NULL)
						cout<<"\nHeap is empty";
					else
					{
						cout<<"\nPostorder Traversal : \t";
						postorder(root);
					}
					break;
			case 5: delete_one();
					break;
			case 6: delete_all();
					break;
			case 7: clear();
					break;
			case 0: clear();
					return 0;
			default:cout<<"\nInvalid Input\n";
		}
	}while(ch);
}
/*
Input
1 8 1 55 1 77 1 4 1 33 1 32 1 45 1 6 1 65

*/
