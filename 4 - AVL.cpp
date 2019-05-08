#include<iostream>
#include<malloc.h>
#include<utility>
#include<math.h>
using namespace std;
struct node
{
    int key,nLeft,nRight,bf;
    struct node *left,*right,*parent;
}*root=NULL;
typedef struct node node;
node* create()
{
    node *newnode;
    newnode=(struct node *)malloc(sizeof(struct node));
    cout<<"\nEnter data value: ";
	cin>>newnode->key;
	newnode->nLeft=newnode->nRight=newnode->bf=0;
	newnode->left=newnode->right=newnode->parent=NULL;
    return newnode;
}
void insert(node *root,node *temp)
{
    if(temp->key <= root->key)
    {
        if(root->left !=NULL)
            insert(root->left,temp);
        else
        {
            root->left=temp;
            temp->parent=root;
        }
    }
    if(temp->key > root->key)
    {
        if(root->right !=NULL)
            insert(root->right,temp);
        else
        {
            root->right=temp;
            temp->parent=root;
        }
    }
}
void preorder(node *temp)
{
	if(temp!=NULL)
	{
		cout<<temp->key<<" ";
		preorder(temp->left);
		preorder(temp->right);
	}
}
void dump(node *temp)
{
	if(temp!=NULL)
	{
		cout<<"\n"<<temp->key<<"\t"<<temp->bf<<"\t\t";
		if(temp->left==NULL)
            cout<<"NULL\t";
        else
            cout<<temp->left->key<<"\t";

		if(temp->right==NULL)
            cout<<"NULL\t";
        else
            cout<<temp->right->key<<"\t";
		if(temp==root)
			cout<<"NULL";
		else
			cout<<temp->parent->key;
		dump(temp->left);
		dump(temp->right);
	}
}
node* checkBF(node *temp)
{
    while(temp!=NULL)
    {
        if(temp->bf > 1)
            return temp;
        temp=temp->parent;
    }
    return NULL;
}
void updateBF(node *temp)
{
    if(temp!=NULL)
    {
        updateBF(temp->left);
        updateBF(temp->right);
        if(temp->left==NULL)
            temp->nLeft=0;
        if(temp->right==NULL)
            temp->nRight=0;
        if(temp->left!=NULL)
            temp->nLeft=max(temp->left->nLeft,temp->left->nRight)+1;
        if(temp->right!=NULL)
            temp->nRight=max(temp->right->nLeft,temp->right->nRight)+1;
        temp->bf=abs(temp->nLeft - temp->nRight);
    }
}
void LL(node *x, node *y, node *z)
{
//    cout<<"  LL";
    y->parent = z->parent;
    if(y->parent!=NULL)
        y->parent->left=y;
    z->parent=y;
    z->left=y->right;
    y->right=z;
    if(root==z)
        root=y;
}
void LR(node *x, node *y, node *z)
{
//    cout<<"  LR";
    x->parent = z->parent;
    if(x->parent!=NULL)
        x->parent->left=x;
    y->parent=z->parent=x;
    y->right=x->left;
    z->left=x->right;
    x->left=y;
    x->right=z;
    if(root==z)
        root=x;
}
void RL(node *x, node *y, node *z)
{
//    cout<<"  RL";
    x->parent = z->parent;
    if(x->parent!=NULL)
        x->parent->right=x;
    y->parent=z->parent=x;
    z->right=x->left;
    y->left=x->right;
    x->left=z;
    x->right=y;
    if(root==z)
        root=x;
}
void RR(node *x, node *y, node *z)
{
//    cout<<"  RR";
    y->parent = z->parent;
    if(y->parent!=NULL)
        y->parent->right=y;
    z->parent = y;
    z->right = y->left;
    y->left = z;
    if(root==z)
        root=y;
}
int main()
{
    int ch;
    node *temp,*t;
    do
    {
        cout<<"\n\n1: Insert\n2: Preorder Traversal\n0: Exit\nChoice > ";
        cin>>ch;
        switch(ch)
        {
            case 1: temp=create();
                    if(root==NULL)
                        root=temp;
                    else
                    {
                        insert(root,temp);
                        updateBF(root);
                        t=checkBF(temp);
                        if(t!=NULL)     //finding path to unbalanced node
                        {
                            //cout<<"\nUnbalanced node => "<<t->key;
                            node *x=temp,*y=x->parent,*z=y->parent;
                            while(z!=t)
                            {
                                x=y;
                                y=z;
                                z=z->parent;
                            }
                            if(z->left == y && y->left == x)
                                LL(x,y,z);
                            else if(z->left == y && y->right == x)
                                LR(x,y,z);
                            else if(z->right == y && y->left == x)
                                RL(x,y,z);
                            else if(z->right == y && y->right == x)
                                RR(x,y,z);
                            updateBF(root);
                        }
                    }
                    break;
            case 2: if(root==NULL)
                        cout<<"\nTree is empty";
                    else
                    {
                        cout<<"\nPreorder Traversal: ";
                        preorder(root);
                    }
                    break;
			case 19:cout<<"\nData\tBal fact\tLeft\tRight\tParent";
					dump(root);
					break;
            case 0: return 0;
            default:cout<<"\nInvalid Input";
        }

    }while(ch);
    return 0;
}
/*
INPUTS
1 5 1 6 1 8 1 3 1 2 1 4 1 7
5 3 2 4 7 6 8
*/
