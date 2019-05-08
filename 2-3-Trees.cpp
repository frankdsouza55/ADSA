//Implementation of 2-3 Trees
//for int data

//Reference : https://github.com/StoneBird/2-3-tree

#include<iostream>
#include<malloc.h>
#include<algorithm>
using namespace std;
struct node
{
    int leftData,rightData;         //data item on left & right side of node
    int n;                          //number of data items (1 or 2)
    struct node *left,*middle,*right,*parent;
}*root=NULL;
typedef struct node node;

bool isLeaf(node *temp)
{
    return (temp->left==NULL && temp->right==NULL && temp->middle==NULL);
}
node* instantiate(int data)
{
    ///create a new node, initialize all crucial values
    node *newnode;
    newnode=(node *)malloc(sizeof(node));
    newnode->leftData=data;
    newnode->n=1;
    newnode->left=newnode->middle=newnode->right=newnode->parent=NULL;
    return newnode;
}
void insertSecondItem(node *temp, int x)
{
    ///insert a new item to a 2-node
    if (x < temp->leftData)
    {
        //x should be on left
        temp->rightData=temp->leftData;
        temp->leftData=x;
    }
    else        //x should be on right
        temp->rightData = x;
    temp->n=2;
}
node* splitNode(node *n,node *x,int pos)
{
    //input: a pointer to the node to split, the node that causes the split, and where the split causer comes from (left, middle, right = 0, 1, 2)
    //output: a pointer to the top-most node of manipulated subtree
    node* nodeCache[4];    //cache children of nodes passed in
    //rearrange the position of these children for later hook up
    if (pos == 0)
    {
        //x left, x right, n middle, n right
        nodeCache[0] = x->left;
        nodeCache[1] = x->right;
        nodeCache[2] = n->middle;
        nodeCache[3] = n->right;
    }
    else if (pos == 2)
    {   //n left, n middle, x left, x right
        nodeCache[0] = n->left;
        nodeCache[1] = n->middle;
        nodeCache[2] = x->left;
        nodeCache[3] = x->right;
    }
    else
    {   //n left, x left, x right, n right
        nodeCache[0] = n->left;
        nodeCache[1] = x->left;
        nodeCache[2] = x->right;
        nodeCache[3] = n->right;
    }

    int arr[3]={n->leftData, n->rightData, x->leftData};
    sort(arr,arr+3);

    node *promo = instantiate(arr[1]);   //new promoted node
    node *l = instantiate(arr[0]); //left child
    node *r = instantiate(arr[2]); //right child
    //parental relationship of first relative level
    promo->left = l;
    promo->right = r;
    l->parent = promo;
    r->parent = promo;
    //parental relationship of second relative level; hook up cached nodes
    if (nodeCache[0] != NULL)
    {
        l->left = nodeCache[0];
        l->right = nodeCache[1];
        nodeCache[0]->parent = nodeCache[1]->parent = l;
        r->left = nodeCache[2];
        r->right = nodeCache[3];
        nodeCache[2]->parent = nodeCache[3]->parent = r;
    }
    return promo;
}

int posChild(node *p, node *n)
{
    ///check if the node is parent's left, middle or right child
    //input: a pointer to the parent, and a pointer to the node itself
    //output: return 0 for left, 1 for middle, 2 for right child
    if (p->left == n)
        return 0;    //if left child
    else if (p->middle == n)
        return 1; //if middle child
    else
        return 2;  //if right child
}
void auxilary(node* n, int x)
{
    ///recursive helper function for insert()
    //input: a pointer to the node to start with, the value to insert
    //output: value is inserted to the tree
    if (isLeaf(n))
    {
        //base case; if n is a leaf
        if (n->n == 1)      //leaf has empty space
            insertSecondItem(n, x);
        else
        {
            //leaf is full; split it; promote the node to parent
            int pos = posChild(n->parent, n);
            node *promo = splitNode(n, instantiate(x), pos);  //split the node
            while (n->parent != root)
            {
                //if parent is not root
                if (n->parent->n == 1)
                {
                    //the parent is not full
                    insertSecondItem(n->parent, promo->leftData);   //insert value to parent
                    //rearrange leftover's linking
                    int pos = posChild(n->parent, n);
                    if (pos == 0)
                    {
                        //if n is left child
                        n->parent->left = promo->left;
                        n->parent->middle = promo->right;
                    }
                    else if (pos == 2)
                    {
                        //if n is right child
                        n->parent->middle = promo->left;
                        n->parent->right = promo->right;
                    }
                    promo->left->parent = promo->right->parent = n->parent;
                    break;  //insertion complete
                }
                else
                {
                    //continue to split parent's parent and so on
                    pos = posChild(n->parent, n);   //direction the split request comes from
                    n = n->parent;  //go one level up
                    promo = splitNode(n, promo, pos);   //split parent's parent
                }
            }
            if (n->parent == root)
            {
                //when trace to root
                pos = posChild(n->parent, n);   //direction the split request comes from
                if (n->parent->n == 1)
                {
                    //the root is not full
                    insertSecondItem(n->parent, promo->leftData);
                    if (pos == 0)
                    {
                        //if n is left child
                        n->parent->left = promo->left;
                        n->parent->middle = promo->right;
                    }
                    else if (pos == 2)
                    {
                        //if n is right child
                        n->parent->middle = promo->left;
                        n->parent->right = promo->right;
                    }
                    promo->left->parent = promo->right->parent = n->parent;
                }
                else
                {
                    //split the root
                    pos = posChild(n->parent, n);
                    n = n->parent;
                    root = splitNode(n, promo, pos);    //root will be updated
                }
            }
        }
    }
    else
    {
        //non-base case
        if (n->n == 1)
        {   //2-node
            if (x < n->leftData)
                auxilary(n->left, x);  //go left subtree
            else
                auxilary(n->right, x);   //go right subtree
        }
        else
        {
            //3-node
            if (x < n->leftData)
                auxilary(n->left, x);  //go left subtree
            else if (x > n->rightData)
                auxilary(n->right, x);  //go left subtree
            else
                auxilary(n->middle, x);    //go middle subtree
        }
    }
}

void insert(int data)
{
    ///insert an item to the tree
    if(root==NULL)
        root=instantiate(data);
    else if(isLeaf(root))
    {
        if (root->n == 1)       //if it's a 2-node
            insertSecondItem(root, data);
        else      //it's a 3-node
            root = splitNode(root, instantiate(data), 0);
    }
    else
        auxilary(root, data);

}
void displayInorder(node *temp)
{
    ///output the inorder traversal of the tree
    if(root==NULL)
        cout<<"\nTree is empty";
    else if(isLeaf(temp))           //the base case; if n is leaf
    {
        if(temp!=NULL)
        {
            if (temp->n==1)
                cout<<temp->leftData<<" ";
            else
                cout<<temp->leftData<<" "<<temp->rightData<<" ";
        }
    }
    else
    {
        displayInorder(temp->left);
        cout<<temp->leftData<<" ";
        if(temp->middle!=NULL)
        {
            displayInorder(temp->middle);
            cout<<temp->rightData<<" ";
        }
        displayInorder(temp->right);
    }

}

int main()
{
    int ch,x;
    do
    {
        cout<<"\n\n1: Insert\n2: Display\n0: Exit\nChoice > ";
        cin>>ch;
        switch(ch)
        {
            case 1:
                cout<<"\nEnter the data value: ";
                cin>>x;
                insert(x);
                break;
            case 2:
                cout<<"\n";
                displayInorder(root);
                break;
            case 0:
                return 0;
            default:
                cout<<"\nInvalid Input";
                break;
        }
    }while(ch);
}

/*Sample Inputs
1 10 1 70 1 60 1 20 1 110 1 40 1 80 1 130 1 100 1 50 1 190 1 90 1 180 1 240 1 30 1 120 1 140 1 160

*/
