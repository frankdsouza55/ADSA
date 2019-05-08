#include<iostream>
#include<malloc.h>
#include<utility>
#include<math.h>
using namespace std;
struct node
{
    int key;
    struct node *left,*right,*parent;
}*root=NULL;
typedef struct node node;
node* create()
{
    node *newnode;
    newnode=(struct node *)malloc(sizeof(struct node));
    cout<<"\nEnter data value: ";
	cin>>newnode->key;
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
		cout<<"\n"<<temp->key<<"\t";
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

void LL(node *x, node *y, node *z)
{
    ///Performs single right rotation
//    cout<<"  LL";
    if(z==NULL)
    {
        x->parent=y->parent;
        y->left=x->right;
        x->right=y;
        y->parent=x;
        root=x;
    }
    else
    {
        x->parent = z->parent;
        if(x->parent!=NULL)
            x->parent->left=x;
        y->parent=x;
        z->parent=y;
        z->left=y->right;
        y->right=z;
        y->left=x->right;
        x->right=y;
        if(root==z)
            root=x;
    }
}
void LR(node *x, node *y, node *z)
{
    ///Performs left followed by right rotation
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
    ///Performs right followed by left rotation
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
    ///Performs single left rotation
//    cout<<"  RR";
    if(z==NULL)
    {
        x->parent=y->parent;
        y->right=x->left;
        x->left=y;
        y->parent=x;
        root=x;
    }
    else
    {
        x->parent = z->parent;
        if(x->parent!=NULL)
            x->parent->right=x;
        y->parent = x;
        z->parent = y;
        z->right = y->left;
        y->left = z;
        y->right=x->left;
        x->left=y;
        if(root==z)
            root=x;
    }
}
void splay(node *temp)
{
    ///Performs splay operation on temp
    if(temp==root)
        return;
    node *x=temp,*y=x->parent,*z=y->parent;
    if(z==NULL) //One level splay
    {
        if(y->left == x)
            LL(x,y,NULL);
        else if(y->right == x)
            RR(x,y,NULL);
    }
    else        //Two level splay
    {
        if(z->left == y && y->left == x)
            LL(x,y,z);
        else if(z->left == y && y->right == x)
            LR(x,y,z);
        else if(z->right == y && y->left == x)
            RL(x,y,z);
        else if(z->right == y && y->right == x)
            RR(x,y,z);
        splay(x);
    }
}
node* findNode(node *temp, int k)
{
    ///Returns node if found else returns last node reached
    cout<<temp->key<<" ";
    if(temp->key == k)
    {
        cout<<"\n"<<k<<" Found";
        return temp;
    }
    if(k < temp->key)
    {
        if(temp->left!=NULL)
            return findNode(temp->left,k);
        else
        {
            cout<<"\n"<<k<<" Not found";
            return temp;
        }
    }
    else
    {
        if(temp->right!=NULL)
            return findNode(temp->right,k);
        else
        {
            cout<<"\n"<<k<<" Not found";
            return temp;
        }
    }
}
int main()
{
    int ch,t;
    node *temp;
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
                        splay(temp);
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
            case 3: cout<<"\nEnter element to be searched: ";
                    cin>>t;
                    temp=findNode(root,t);
                    cout<<temp->key;
                    splay(temp);
                    break;
			case 19:cout<<"\nData\tLeft\tRight\tParent";
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
1 6 1 5 1 1 1 4 1 3 1 2 1 9
5 3 2 4 7 6 8
*/
