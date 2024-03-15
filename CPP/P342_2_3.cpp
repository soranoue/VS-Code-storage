#include "iostream"
using namespace std;

typedef struct HuffmanNode{
    char data;
    double weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

void select(HuffmanTree t,int i,int &s1,int &s2){
    int j;
    for(j=0;j<i;j++)
        if(t[j].parent==-1)
            break;
    for(s1=j,j++;j<i;j++)
        if(t[j].parent==-1 && t[j].weight<t[s1].weight)
            s1=j;
    for(j=0;j<i;j++)
        if(t[j].parent==-1 && j!=s1)
            break;
    for(s2=j,j++;j<i;j++)
        if(t[j].parent==-1 && j!=s1 && t[j].weight<t[s2].weight)
            s2=j;
}

void CreateHuffmanTree(HuffmanTree &HT,int n){
    int i,m,s1,s2;
    char *node;
    double *w;
    node=new char[n];
    w=new double[n];
    cout<<"请依次输入"<<n<<"个叶子结点的值: ";
    for(i=0;i<=n-1;i++)
        cin>>*(node+i);
    cout<<"请依次输入"<<n<<"个权值: ";
    for(i=0;i<n;i++)
        cin>>*(w+i);
    m=2*n-1;
    HT=new HTNode[m];
    for(i=0;i<n;i++){
        HT[i].data=node[i];
        HT[i].weight=w[i];
        HT[i].parent=-1;
        HT[i].lchild=-1;
        HT[i].rchild=-1;
    }
    for(;i<m;i++)
        HT[i].parent=-1;
    for(i=n;i<m;i++){
        select(HT,i,s1,s2);
        HT[s1].parent=HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    delete []node;
    delete []w;
}

void Code(HuffmanTree &HT,int n,int i,char *code){
    int p,parent,start;
    char *cd;
    cd=new char[n];
    cd[n-1]='\0';
    start=n-1;
    p=i;
    parent=HT[i].parent;
    while(parent!=-1){
        if(HT[parent].lchild==p)
            cd[--start]='0';
        else
            cd[--start]='1';
        p=parent;
        parent=HT[parent].parent;
    }
    strcpy(code,&cd[start]);
    delete []cd;
}

void Decode(HuffmanTree &HT,int n,char *source,char *decode){
    int root=2*n-2;
    int p=root;
    int i=0,k=0;
    while(source[i]){
        if(source[i]=='0') p=HT[p].lchild;
        else p=HT[p].rchild;
        if(HT[p].lchild==-1 && HT[p].rchild==-1){
            decode[k++]=HT[p].data;
            p=root;
        }
        i++;
    }
    decode[k]='\0';
}

int main(){
    return 0;
}
