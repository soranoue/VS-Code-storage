#include "iostream"
#include "iomanip"
using namespace std;

typedef int ElemType;
const int MAXSIZE=100;

class SqQueue{
    private:
        ElemType elem[MAXSIZE];
        int front,rear,num;
    public:
        SqQueue(){front=rear=num=0;}
        ~SqQueue(){}
        int IsEmpty();
        void Display();
        void AddQ(ElemType e);
        ElemType DelQ();
        ElemType GetFront();
        int GetNum(){return num;}
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
        cout<<"当前队列为空"<<endl;
    else{
        cout<<"当前排队号码: "<<endl;
        for(i=(front+1)%MAXSIZE;i!=(rear+1)%MAXSIZE;i=(i+1)%MAXSIZE)
            cout<<setw(3)<<elem[i];
        cout<<endl;
    }
}

void SqQueue::AddQ(ElemType e){
    if((rear+1)%MAXSIZE==front)
        cout<<"队列已满,无法取号! "<<endl;
    else{
        rear=(rear+1)%MAXSIZE;
        elem[rear]=e;
        num++;
    }
}

ElemType SqQueue::DelQ(){
    front=(front+1)%MAXSIZE;
    num--;
    return elem[front];
}

int main(){
    SqQueue sq;
    ElemType e;
    int sele,flag;
    flag=1;
    e=0;
    while(flag){
        sq.Display();
        cout<<"叫号: 1 \n取号: 2 \n退出: 3 \n选项: ";
        cin>>sele;
        switch (sele)
        {
        case 1:
            if(sq.IsEmpty()) cout<<"当前队列为空! "<<endl;
            else cout<<"叫号: "<<sq.DelQ()<<" 号 "<<endl;
            system("PAUSE");
            break;

        case 2:
            e++;
            sq.AddQ(e);
            cout<<"取号: "<<e<<" 号,排队人数 "<<sq.GetNum()<<"人 "<<endl;
            system("PAUSE");
            break;

        case 3:
            flag=0;
            break;
        
        default:
            cout<<"输入选项有误! "<<endl;
            break;
        }
    system("CLS");
    }
    return 0;
}
