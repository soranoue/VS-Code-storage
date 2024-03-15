#include "iostream"
#include "iomanip"
using namespace std;

const int MAXSIZE=100;
typedef char ElemType;

class SqStack{
    private:
        ElemType elem[MAXSIZE];
        int top;
    public:
        SqStack(){top=1;}
        ~SqStack(){}
        void Push(ElemType e);
        ElemType Pop();
        int IsEmpty();
        ElemType GetTop(){return elem[top];}
        void Display();
        void SetEmpty(){top=1;}
};

int SqStack::IsEmpty(){
    if(top==-1)
        return 1;
    else    
        return 0;
}

void SqStack::Display(){
    int k;
    if(top==1)      //IsEmpty()
        cout<<"ջ����! "<<endl;
    else{
        cout<<"����Ԫ��: ";
        for(k=top;k>1;k--)
            cout<<Pop();
        cout<<endl;
    }
}

void SqStack::Push(ElemType e){
    if(top==MAXSIZE-1)
        cout<<"ջ�����,�޷���ջ! "<<endl;
    else{
        top++;
        elem[top]=e;
    }
}

ElemType SqStack::Pop(){
    top--;
    return elem[top+1];
}

int main(){
    SqStack stack;
    string input;
    int length,i;
    cout<<"�����ַ�: ";
    cin>>input;
    length=input.size();
    if(length>=MAXSIZE){
        cout<<"���볤�ȹ���! "<<endl;
        return 0;
    }
    for(i=0;i<length;i++){
        stack.Push(input[i]);
    }
    stack.Display();
    stack.SetEmpty();
    return 0;
}
