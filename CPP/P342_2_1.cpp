#include "iostream"
using namespace std;

typedef char ElemType;
struct LBtNodeType{
    LBtNodeType *lch;
    ElemType data;
    LBtNodeType *rch;
};

class LinkBiTree{
    protected:
        LBtNodeType *root;
    public:
        LinkBiTree(){root=NULL;}
        ~LinkBiTree(){Destroy(root);root=NULL;}
        void Creat(){root=Creat(root);}
        void PreOrder(){PreOrder(root);}
        void InOrder(){InOrder(root);}
        void PostOrder(){PostOrder(root);}
        void VisitRoot(){VisitRoot(root);}
    private:
        LBtNodeType* Creat(LBtNodeType *p);
        void VisitRoot(LBtNodeType *p);
        void PreOrder(LBtNodeType *p);
        void InOrder(LBtNodeType *p);
        void PostOrder(LBtNodeType *p);
        void Destroy(LBtNodeType *p);
};

LBtNodeType* LinkBiTree::Creat(LBtNodeType *p){
    ElemType ch;
    cin>>ch;
    if(ch=='#')
        p=NULL;
    else{
        p=new LBtNodeType;
        p->data=ch;
        p->lch=Creat(p->lch);
        p->rch=Creat(p->rch);
    }
    return p;
}

void LinkBiTree::VisitRoot(LBtNodeType *p){
    if(p!=NULL)
        cout<<p->data<<" ";
}

void LinkBiTree::Destroy(LBtNodeType *p){
    if(p!=NULL){
        Destroy(p->lch);
        Destroy(p->rch);
        delete p;
    }
}

void LinkBiTree::PreOrder(LBtNodeType *p){
    if(p!=NULL){
        VisitRoot(p);
        PreOrder(p->lch);
        PreOrder(p->rch);
    }
}

void LinkBiTree::InOrder(LBtNodeType *p){
    if(p!=NULL){
        InOrder(p->lch);
        VisitRoot(p);
        InOrder(p->rch);
    }
}

void LinkBiTree::PostOrder(LBtNodeType *p){
    if(p!=NULL){
        PostOrder(p->lch);
        PostOrder(p->rch);
        VisitRoot(p);
    }
}
//ABD###CFJ##K###
//ABD##E##C#G##
int main(){
    LinkBiTree bt;
    bt.Creat();
    cout<<endl<<"PreOrder: ";
    bt.PreOrder();
    cout<<endl<<"InOrder: ";
    bt.InOrder();
    cout<<endl<<"PostOrder: ";
    bt.PostOrder();
    cout<<endl;
    return 0;
}
