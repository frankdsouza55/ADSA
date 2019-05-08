//Implementation of Patricia Tries

//This code has bugs

#include<iostream>
#include<malloc.h>
#include<string>
using namespace std;
struct node
{
    char key[20];
    int bitNo;
    struct node *left,*right;
}*root=NULL,*A=NULL,*B=NULL;
typedef struct node node;
node* create()
{
    ///Creates a node, assigns memory and returns it
    node *newnode;
    newnode=(struct node *)malloc(sizeof(struct node));
    cout<<"\nEnter data value: ";
	cin>>newnode->key;
    newnode->bitNo=0;
	newnode->left=newnode->right=NULL;
    return newnode;
}
void preorder(node *temp)
{
    if(temp!=NULL)
    {
        cout<<temp->key<<" ";
        if(temp->left!=NULL && temp->left->bitNo > temp->bitNo)
            preorder(temp->left);
        if(temp->right!=NULL && temp->right->bitNo > temp->bitNo)
            preorder(temp->right);
    }
}
node* searchNode(string key)
{
    ///Returns the node where the search terminates
    node *temp=root->left;
    int bit=root->bitNo;
    while(bit < temp->bitNo)
    {
        bit=temp->bitNo;
        if(key.at(bit-1) == '0')
            temp=temp->left;
        else
            temp=temp->right;
    }
    return temp;
}
void insert(node *temp)
{
    ///Inserts node in the Patricia trie
    A=root;
    B=root->left;
    string key=temp->key;
    node *q = searchNode(key);
    int j;
    for(j=1; temp->key[j-1]==q->key[j-1];j++);
    temp->bitNo=j;
    while(A->bitNo < B->bitNo && B->bitNo<j)
    {
        A=B;
        B = (key.at(B->bitNo -1)=='0') ? B->left : B->right;
    }
    if(B == A->left)
        A->left=temp;
    else
        A->right=temp;

    if(key.at(j-1)=='0')
    {
        temp->left=temp;
        temp->right=B;
    }
    else
    {
        temp->right=temp;
        temp->left=B;
    }
}
int main()
{
    int ch;
    node *temp;
    string x;
    do
    {
        cout<<"\n\n1: Insert\n2: Display\n3: Search\n0: Exit\nChoice > ";
        cin>>ch;
        switch (ch)
        {
            case 1: temp=create();
                    if(root == NULL)
                    {
                        root=temp;
                        root->left=root;
                    }
                    else
                        insert(temp);
                    break;
            case 2: if(root == NULL)
                        cout<<"\nPatricia Trie is empty";
                    else
                    {
                        cout<<"\nPreorder traversal: ";
                        preorder(root);
                    }
                    break;
            case 3: cin.ignore();
                    cout<<"\nEnter key to search: ";
                    cin>>x;
                    temp=searchNode(x);
                    if(temp->key == x)
                        cout<<"\nFound";
                    else
                        cout<<"\nNot found";
                    break;
            case 0: return 0;
            default:cout<<"\nInvalid Input";
        }
    }while(ch);
}

/*Inputs
1 1000 1 0010 1 1001 1 1100 1 0000 1 0001

*/
