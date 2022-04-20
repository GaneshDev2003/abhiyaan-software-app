#include<iostream>
using namespace std;
int main()
{
    int n,m,k;
    cin>>m>>n>>k;
    int a[m][n];
    int f=0;
    int ind_i,ind_j;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>a[i][j];
            if(f==0 && a[i][j]==k)
            {
                f=1;
                ind_i=i;
                ind_j=j;
            }
        }
    }
    if(f==1)
    {
        cout<<"True \n";
        cout<<ind_i<<" "<<ind_j;
    }
    else
    {
        cout<<"False \n";
    }
    
}