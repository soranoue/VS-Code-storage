#include "iostream"
using namespace std;

typedef struct BiNode{
    int key;
    struct BiNode *lchild,*rchild;
} *BiSortTree;

void Insert(BiSortTree &T,int k){
    if(T==NULL){
        T=new BiNode;
        T->key=k;
        T->lchild=T->rchild=NULL;
    }
    else if(k<T->key)
            Insert(T->lchild,k);
        else
            Insert(T->rchild,k);
}

void CreateBiSortTree(BiSortTree &T,int a[],int n){
    int i;
    for(i=0;i<n;i++)
        Insert(T,a[i]);
}

void Delete(BiSortTree &p,int k){
    BiSortTree s,fs;
    if(p!=NULL){
        if(k<p->key) Delete(p->lchild,k);
        else if(k>p->key) Delete(p->rchild,k);
        else{
            if(p->lchild!=NULL && p->rchild!=NULL){
                fs=p;
                s=p->rchild;
                while(s->lchild!=NULL){
                    fs=s;
                    s=s->lchild;
                }
                p->key=s->key;
                if(p==fs) fs->rchild=s->rchild;
                else fs->lchild=s->rchild;
                delete s;
            }
            else{
                s=p;
                if(p->lchild==NULL)
                    p=p->rchild;
                else if(p->rchild==NULL)
                    p=p->lchild;
                delete s;
            }
        }
    }
}

int main(){
    int n,key;
    BiSortTree tree=NULL;
    int a[]={9,5,12,4,7,10,16,6,8};
    n=9;
    CreateBiSortTree(tree,a,n);
    cout<<"\n请输入需要删除的结点: ";
    cin>>key;
    Delete(tree,key);
    return 0;
}
