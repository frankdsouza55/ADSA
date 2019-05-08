#include<iostream>
#include<malloc.h>
#include<utility>
#include<math.h>
using namespace std;
struct node
{
    int key,degree;
    struct node *right,*left,*parent,*child;
}*minH1=NULL,*minH2=NULL;
typedef struct node node;
void display(node *minH)
{
    if(minH==NULL)
    {
        cout<<"Empty";
        return;
    }
    node *temp=minH;
    do
    {
        cout<<temp->key<<" ";
        temp=temp->right;
    }while(temp!=minH);
}
void insert(int c)
{
    node *newnode;
	newnode=(node *)malloc(sizeof(node));
	cout<<"\nEnter key value: ";
	cin>>newnode->key;
	newnode->degree=0;
    newnode->right=newnode->left=newnode->child=newnode->parent=NULL;
    if(c==1)
        if(minH1==NULL)
        {
            minH1=newnode;
            minH1->right=minH1->left=minH1;
        }
        else
        {
            newnode->right=minH1;
            newnode->left=minH1->left;
            minH1->left->right=newnode;
            minH1->left=newnode;
            if(minH1->left->key < minH1->key)
                minH1=minH1->left;
        }
    else if(c==2)
        if(minH2==NULL)
        {
            minH2=newnode;
            minH2->right=minH2->left=minH2;
        }
        else
        {
            newnode->right=minH2;
            newnode->left=minH2->left;
            minH2->left->right=newnode;
            minH2->left=newnode;
            if(minH2->left->key < minH2->key)
                minH2=minH2->left;
        }
}
void heap_union()
{
    if(minH2==NULL)
        return;
    if(minH1==NULL)
    {
        minH1=minH2;
        minH2=NULL;
        return;
    }
    minH1->left->right = minH2;
    minH2->left->right = minH1;
    node *temp=minH2->left;
    minH2->left=minH1->left;
    minH1->left=temp;
    if(minH2->key < minH1->key)
        minH1=minH2;
    minH2=NULL;
    cout<<"\nHeaps merged";
}
void decreaseKey1()
{
    int k,x;
    cout<<"\nEnter original key and new key: ";
    cin>>k>>x;
    if(x>k)
    {
        cout<<"\nNew key value cannot be greater than old key value";
        return;
    }
    if(minH1==NULL)
        return;
    node *temp=minH1;
    do
    {
        if(temp->key == k)
        {
            temp->key=x;
            return;
        }
        temp=temp->right;
    }while(temp != minH1);
}
void decreaseKey2()
{
    int k,x;
    cout<<"\nEnter original key and new key: ";
    cin>>k>>x;
    if(x>k)
    {
        cout<<"\nNew key value cannot be greater than old key value";
        return;
    }
    if(minH2==NULL)
        return;
    node *temp=minH2;
    do
    {
        if(temp->key == k)
        {
            temp->key=x;
            return;
        }
        temp=temp->right;
    }while(temp != minH2);
}
int main()
{
    int ch;
    do
    {
        cout<<"\n\n1: Insert in Heap 1\n2: Insert in Heap 2\n3: Display\n4: Union\n5: Finding node with minimum element\n6: Decrease key in Heap 1\n7: Decrease key in Heap 2\n0: Exit\nChoice: ";
        cin>>ch;
        switch(ch)
        {
            case 1: insert(1);
                    break;
            case 2: insert(2);
                    break;
            case 3: cout<<"\nHeap 1 => ";
                    display(minH1);
                    cout<<"\nHeap 2 => ";
                    display(minH2);
                    break;
            case 4: heap_union();
                    break;
            case 5: if(minH1==NULL)
                        cout<<"\nFibonacci heap 1 is empty";
                    else
                        cout<<"\nMinimum key in Fibonacci heap 1 => "<<minH1->key;
                    if(minH2==NULL)
                        cout<<"\nFibonacci heap 2 is empty";
                    else
                        cout<<"\nMinimum key in Fibonacci heap 2 => "<<minH2->key;
                    break;
            case 6: decreaseKey1();
                    break;
            case 7: decreaseKey2();
                    break;
            case 0: return 0;
            default:cout<<"\nInvalid Input\n";
        }
    }while(ch);
}
/*
INPUTS
1 5 1 25 1 3 1 75 1 4 1 43 1 6
2 48 2 75 2 11 2 10 2 19 2 4
*/
