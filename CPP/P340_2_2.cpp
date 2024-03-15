#include "iostream"
#include "iomanip"
using namespace std;

typedef int ElemType;
struct LSNodeType{
    ElemType data;
    LSNodeType *next;
};

class LinkStack{
    private:
            LSNodeType *top;
        public:
            LinkStack(){top=NULL;}
            ~LinkStack(){}
            void Display();
            void Push(ElemType e);
            int IsEmpty(){if(top==NULL) return 1;else return 0;}
            ElemType Pop();
};

void LinkStack::Display(){
    LSNodeType *p;
    p=top;
    if(p==NULL)
        cout<<"Stack is Empty!"<<endl;
    else{
        cout<<"Data Elem: ";
        while(p!=NULL){
            cout<<setw(6)<<p->data;
            p=p->next;
        }
        cout<<endl;
    }
}

void LinkStack::Push(ElemType e){
    LSNodeType *p;
    p=new LSNodeType;
    p->data=e;
    p->next=top;
    top=p;
}

ElemType LinkStack::Pop(){
    LSNodeType *p;
    ElemType x;
    x=top->data;
    p=top;
    top=top->next;
    delete p;
    return x;
}

int main(){
    LinkStack stack;
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
    if(!stack.IsEmpty()){
        cout<<"Pop the Stack: "<<stack.Pop()<<endl;
        stack.Display();
    }
    return 0;
}
