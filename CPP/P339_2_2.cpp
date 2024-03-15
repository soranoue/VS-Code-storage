#include "iostream"
#include "iomanip"
using namespace std;

typedef int ElemType;
struct LLNodeType{
    ElemType data;
    LLNodeType *next;
};

class LinkList{
    private:
        LLNodeType *Head;
    public:
        LinkList();
        ~LinkList(){}
        void Create(int n);
        void Display();
        void Insert(int i,ElemType e);
        void Delete(int i);
};

LinkList::LinkList(){
    Head=new LLNodeType;
    Head->next=NULL;
}

void LinkList::Create(int n){
    int i,length;
    LLNodeType *p,*q;
    length=n;
    if(length>0){
        cout<<"Input Data Elem: "<<endl;
        for(i=1;i<=length;i++){
            p=new LLNodeType;
            cin>>p->data;
            p->next=NULL;
            if(i==1)
                Head->next=p;
            else    
                q->next=p;
            q=p;
        }
    }
    else
        cout<<"Length Error!"<<endl;
}

void LinkList::Display(){
    LLNodeType *p;
    p=Head->next;
    if(p==NULL)
        cout<<"LinkList is Empty!"<<endl;
    else{
        cout<<"Data Elem: ";
        while(p!=NULL){
            cout<<setw(6)<<p->data;
            p=p->next;
        }
    }
    cout<<endl;
}

void LinkList::Insert(int i,ElemType e){
    LLNodeType *p,*q,*s;
    int k=1;
    q=Head;
    p=Head->next;
    while(k<i && p!=NULL){
        q=p;
        p=p->next;
        k++;
    }
    if(k==i){
        s=new LLNodeType;
        s->data=e;
        s->next=p;
        q->next=s;
        cout<<"Insert Success!"<<endl;
    }
    else
        cout<<"Insert Location i Error!"<<endl;
}

void LinkList::Delete(int i){
    LLNodeType *p,*q;
    int k=1;
    q=Head;
    p=Head->next;
    while(k<i && p!=NULL){
        q=p;
        p=p->next;
        k++;
    }
    if(k==i){
        q->next=p->next;
        delete p;
        cout<<"Delete Success!"<<endl;
    }
    else{
        cout<<"Delete Location Error!"<<endl;
    }
}

int main(){
    LinkList list;
    ElemType e;
    int n,i;
    cout<<"Input length(0~99): "; cin>>n;
    list.Create(n); list.Display();
    cout<<"Input Insert Location: "; cin>>i;
    cout<<"Input Elem: "; cin>>e;
    list.Insert(i,e); list.Display();
    cout<<"Input Delete Location: "; cin>>i;
    list.Delete(i); list.Display();
    return 0;
}
