#include "iostream"
#include "iomanip"
using namespace std;

typedef int ElemType;
struct LQNodeType{
    ElemType data;
    LQNodeType *next;
};

class LinkQueue{
    private:
        LQNodeType *front,*rear;
    public:
        LinkQueue();
        ~LinkQueue();
        int IsEmpty();
        void Display();
        ElemType GetFront();
        void AddQ(ElemType e);
        ElemType DelQ();
};

LinkQueue::LinkQueue(){
    front=new LQNodeType;
    rear=front;
}

LinkQueue::~LinkQueue(){
    delete front;
}

int LinkQueue::IsEmpty(){
    if(front==rear)
        return 1;
    else
        return 0;
}

ElemType LinkQueue::GetFront(){
    return front->next->data;
}

void LinkQueue::Display(){
    LQNodeType *s;
    if(IsEmpty()){cout<<"Queue is Empty! "<<endl;return;}
    cout<<"Data elem: "<<endl;
    s=front->next;
    while(s!=NULL){
        cout<<setw(3)<<s->data;
        s=s->next;
    }
    cout<<endl;
}

void LinkQueue::AddQ(ElemType e){
    LQNodeType *s=new LQNodeType;
    s->data=e;
    s->next=NULL;
    rear->next=s;
    rear=s;
}

ElemType LinkQueue::DelQ(){
    LQNodeType *s;
    ElemType e;
    e=front->next->data;
    s=front->next;
    front->next=s->next;
    if(s==rear)
        rear=front;
    delete s;
    return e;
}

int SimFunc(LinkQueue lq){
    cout<<"Param: "<<endl;
    while(!lq.IsEmpty()){
        ElemType param=lq.DelQ();
        cout<<setw(3)<<param;
    }
    return 0;
}

int main(){
    LinkQueue lq;
    //ElemType e;
    lq.AddQ(10);
    lq.AddQ(20);
    lq.AddQ(30);
    lq.Display();
    SimFunc(lq);
    return 0;
}
