#include "iostream"
using namespace std;

const int MAXSIZE=100;
typedef int ElemType;
struct Data{
    ElemType key;
    //other
    //......
};

template <class T>
void StrInsertSort(T r[],int n){
    int i,j;
    for(i=2;i<=n;i++){
        r[0]=r[i];
        j=i-1;
        while(r[j].key>r[0].key){
            r[j+1]=r[j];
            j--;
        }
        r[j+1]=r[0];
    }
}

template <class T>
void BinaryInsertSort(T r[],int n){
    int i,j,low,high,mid;
    for(i=2;i<=n;i++){
        r[0]=r[i];
        low=1;high=i-1;
        while(low<=high){
            mid=(low+high)/2;
            if(r[0].key<r[mid].key)
                high=mid-1;
            else    
                low=mid+1;
        }
        for(j=i-1;j>=low;j--)
            r[j+1]=r[j];
        r[low]=r[0];
    }
}

template <class T>
void ShellSort(T r[],int n){
    int i,j,k;
    k=n/2;
    while(k>=1){
        for(i=k+1;i<=n;i++){
            r[0].key=r[k].key;
            j=i-k;
            while((r[j].key>r[0].key) && (j>=0)){
                r[j+k].key=r[j].key;
                j=j-k;
            }
            r[j+k]=r[0];
        }
        k=k/2;
    }
}

template <class T>
void BubbleSort(T r[],int n){
    int i,j;
    T x;
    for(i=1;i<=n-1;i++){
        for(j=1;j<=n-i;j++)
            if(r[j+1].key<r[j].key){
                x=r[j+1];
                r[j+1]=r[j];
                r[j]=x;
            }
    }
}

template <class T>
int SubArea(T r[],int first,int last){
    int i,j;
    T x;
    i=first;
    j=last;
    x.key=r[i].key;
    do{
        while((i<j) && (r[j].key>=x.key))
            j--;
        if(i<j){
            r[i].key=r[j].key;
            i++;
        }
        while((i<j) && (r[i].key<=x.key))
            i++;
        if(i<j){
            r[j].key=r[i].key;
            j--;
        }
    }while(i<j);
    r[i].key=x.key;
    return 1;
}

template <class T>
void QuickSort(T r[],int first,int last){
    int i;
    if(first<last){
        i=SubArea(r,first,last);
        QuickSort(r,first,i-1);
        QuickSort(r,i+1,last);
    }
}

template <class T>
void SimSelSort(T r[],int n){
    int i,j,min;
    T x;
    for(i=1;i<=n;i++){
        min=i;
        for(j=i+1;j<n;j++)
            if(r[j].key<r[min].key)
                min=j;
        if(min>i){
            x=r[i];
            r[i]=r[min];
            r[min]=x;
        }
    }
}

template <class T>
void HeapPass(T r[],int i,int m){
    int j,flag=0;
    T x;
    j=2*i;
    x=r[i];
    while(j<=m && flag==0){
        if((j<m) && r[j].key>r[j+1].key)
            j=j+1;
        if(r[j].key>x.key)
            flag=1;
        else{
            r[i]=r[j];
            i=j;
            j=2*i;
        }
    }
    r[i]=x;
}

template <class T>
void HeapSort(T r[],int n){
    int i,m;
    T x;
    for(i=n/2;i>=1;i--)
        HeapPass(r,i,n);
    for(m=n-1;m>=1;m--){
        cout<<setw(4)<<r[1].key;
        x=r[1];r[1]=r[m+1];r[m+1]=x;
        HeapPass(r,1,m);
    }
    cout<<setw(4)<<r[1].key<<endl;
}

template <class T>
void Merge(T r[],T r2[],int s,int mid,int t){
    int i,j,k;
    i=s;j=mid+1;k=s-1;
    while((i<=mid) && (j<=t)){
        k=k+1;
        if(r[i].key<=r[j].key){
            r2[k]=r[i];
            i++;
        }
        else{
            r2[k]=r[j];
            j++;
        }
    }
    while(i<=mid){
        k++;
        r2[k]=r[i];
        i++;
    }
    while(j<=t){
        k++;
        r2[k]=r[j];
        j++;
    }
}

template <class T>
void MergePass(T r[],T r2[],int length,int n){
    int mid,t,j,i=1;
    while((n-i+1)>=2*length){
        mid=i+length-1; t=i+2*length-1;
        Merge(r,r2,i,mid,t);
        i=i+2*length;
    }
    if((n-i+1)<=length)
        for(j=i;j<=n;j++) r2[j]=r[j];
    else{
        mid=i+length-1;
        Merge(r,r2,i,mid,n);
    }
}

template <class T>
void MergeSort(T r[],T r2[],int n){
    int length=1;
    while(length<n){
        MergePass(r,r2,length,n); length=length*2;
        MergePass(r2,r,length,n); length=length*2;
    }
}

int main(){
    Data in[8]={12,45,21,12,30,2,68,33};
    Data assist[MAXSIZE];
    StrInsertSort(in,8);
    BinaryInsertSort(in,8);
    ShellSort(in,8);
    BubbleSort(in,8);
    QuickSort(in,0,7);
    SimSelSort(in,8);
    HeapSort(in-1,8);
    MergeSort(in,assist,8);
    return 0;
}
