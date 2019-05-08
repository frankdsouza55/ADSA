#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
void initArray(int mat[50][50])
{
    ///Function to assign -1 to entire array
    for(int i=0;i<50;i++)
        for(int j=0;j<50;j++)
            mat[i][j]=-1;
}
void display(int mat[50][50], int n)
{
    ///Used to display the upper triangle of the matrix
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
            if(mat[i][j]==-1)
                cout<<"\t";
            else
                cout<<mat[i][j]<<"\t";
        cout<<"\n";
    }
}
int findMin(int arr[50])
{
    int pos=0;
    for(int i=1;i<50;i++)
        if(arr[i] < arr[pos])
            pos=i;
    return pos;
}
void displayTree(string words[50], int r[50][50],int i, int j)
{
    if(i<j)
        cout<<words[r[i][j]-1]<<"\t";
    else return;
    displayTree(words,r,i,r[i][j]-1);
    displayTree(words,r,r[i][j],j);
}
int main()
{
    string data[50]={""};
    int p[50],q[51];
    int c[50][50]={0},w[50][50]={0},r[50][50]={0},n;
    cout<<"\nEnter the total no of elements: ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter element "<<i+1<<": ";
        cin>>data[i];
    }
    cout<<"\nEnter successful probabilities: ";
    for(int i=0;i<n;i++)
        cin>>p[i];
    cout<<"\nEnter unsuccessful probabilities: ";
    for(int i=0;i<=n;i++)
        cin>>q[i];
    initArray(w);
    initArray(c);
    initArray(r);
    for(int i=0;i<=n;i++)   //Compute weight matrix
    {
        for(int j=i;j<=n;j++)
        {
            if(i==j)
            {
                w[i][j]=q[i];
                c[i][j]=r[i][j]=0;
            }
            else
                w[i][j]=w[i][j-1]+p[j-1]+q[j];
        }
    }
    for(int x=1;x<=n;x++)
    {
        for(int i=0,j=x;i<=n && j<=n;i++,j++)
        {
            int sum[50]={0};
            replace(sum,sum+50,0,1000);
            for(int k=i+1;k<=j;k++)
                sum[k]= c[i][k-1] + c[k][j];
            int m=findMin(sum);
            r[i][j]=m;
            c[i][j]=sum[m]+w[i][j];
        }
    }
    cout<<"\nWeight matrix\n";
    display(w,n);
    cout<<"\nCost matrix\n";
    display(c,n);
    cout<<"\nRoot matrix\n";
    display(r,n);

    cout<<"\n\nTotal cost = "<<c[0][n]<<"\nBFS order of OBST is\n";
    displayTree(data,r,0,n);
    return 0;
}
/*input

4
class
private
return
while
2 3 1 2
2 2 1 1 2

*/
