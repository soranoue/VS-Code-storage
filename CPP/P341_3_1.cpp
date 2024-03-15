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
        cout<<"��ǰ����Ϊ��"<<endl;
    else{
        cout<<"��ǰ�ŶӺ���: "<<endl;
        for(i=(front+1)%MAXSIZE;i!=(rear+1)%MAXSIZE;i=(i+1)%MAXSIZE)
            cout<<setw(3)<<elem[i];
        cout<<endl;
    }
}

void SqQueue::AddQ(ElemType e){
    if((rear+1)%MAXSIZE==front)
        cout<<"��������,�޷�ȡ��! "<<endl;
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
        cout<<"�к�: 1 \nȡ��: 2 \n�˳�: 3 \nѡ��: ";
        cin>>sele;
        switch (sele)
        {
        case 1:
            if(sq.IsEmpty()) cout<<"��ǰ����Ϊ��! "<<endl;
            else cout<<"�к�: "<<sq.DelQ()<<" �� "<<endl;
            system("PAUSE");
            break;

        case 2:
            e++;
            sq.AddQ(e);
            cout<<"ȡ��: "<<e<<" ��,�Ŷ����� "<<sq.GetNum()<<"�� "<<endl;
            system("PAUSE");
            break;

        case 3:
            flag=0;
            break;
        
        default:
            cout<<"����ѡ������! "<<endl;
            break;
        }
    system("CLS");
    }
    return 0;
}
