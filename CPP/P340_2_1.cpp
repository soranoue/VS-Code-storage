#include "iostream"
#include "iomanip"
using namespace std;

const int MAXSIZE=100;
typedef int ElemType;

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
        cout<<"Stack is Empty!"<<endl;
    else{
        cout<<"Data Elem: ";
        for(k=top;k>1;k--)
            cout<<setw(6)<<elem[k];
        cout<<endl;
    }
}

void SqStack::Push(ElemType e){
    if(top==MAXSIZE-1)
        cout<<"Stack Overflow, Cannot Push!"<<endl;
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
    ElemType e;
    int length;
    cout<<"Input length(0~99): "; cin>>length;
    if(length>0){
        for(int j=1;j<=length;j++){
            cout<<"Input Elem: "; cin>>e;
            stack.Push(e);
        }
    }
    else{
        cout<<"Length Error!"<<endl;
        return 0;
    } stack.Display();
    cout<<"Top: "<<stack.GetTop()<<endl;
    if(!stack.IsEmpty()){
        cout<<"Pop the Stack: "<<stack.Pop()<<endl;
        stack.Display();
    }
    cout<<"Top: "<<stack.GetTop()<<endl;
    stack.SetEmpty();
    return 0;
}
