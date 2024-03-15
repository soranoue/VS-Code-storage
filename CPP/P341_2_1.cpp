#include "iostream"
#include "iomanip"
using namespace std;

typedef int ElemType;
const int MAXSIZE=100;

class SqQueue{
    private:
        ElemType elem[MAXSIZE];
        int front,rear;
    public:
        SqQueue(){front=rear=0;}
        ~SqQueue(){}
        int IsEmpty();
        void Display();
        void AddQ(ElemType e);
        ElemType DelQ();
        ElemType GetFront();
};

int SqQueue::IsEmpty(){
    if(rear==front)
        return 1;
    else    
        return 0;
}

ElemType SqQueue::GetFront(){
    return elem[(front+1)%MAXSIZE];
}

void SqQueue::Display(){
    int i;
    if(IsEmpty())
        cout<<"Queue is Empty! "<<endl;
    else{
        cout<<"Data elem: "<<endl;
        for(i=(front+1)%MAXSIZE;i!=(rear+1)%MAXSIZE;i=(i+1)%MAXSIZE)
            cout<<setw(6)<<elem[i];
        cout<<endl;
    }
}

void SqQueue::AddQ(ElemType e){
    if((rear+1)%MAXSIZE==front)
        cout<<"Queue is Full, Cannot AddQ! "<<endl;
    else{
        rear=(rear+1)%MAXSIZE;
        elem[rear]=e;
    }
}

ElemType SqQueue::DelQ(){
    front=(front+1)%MAXSIZE;
    return elem[front];
}

int main(){
    SqQueue sq;
    ElemType e;
    int length,i;
    cout<<"Input length: "; cin>>length;
    if(length<0 || length>MAXSIZE) cout<<"length Error! "<<endl;
    else{
        cout<<"Input elem: "<<endl;
        for(i=0;i<length;i++){
            cin>>e;
            sq.AddQ(e);
        }
        sq.Display();
        cout<<"Front elem: "<<sq.GetFront()<<endl;
    }
    return 0;
}
