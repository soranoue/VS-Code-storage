#include "iostream"
#include "iomanip"
using namespace std;

typedef char ElemType;
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
            ElemType GetTop();
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

ElemType LinkStack::GetTop(){
    return top->data;
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
    string input;
    int length,i;
    cout<<"输入表达式(UTF-8): ";
    cin>>input;
    length=input.size();
    if(length>0){
        for(i=0;i<length;i++){
            if(input[i]=='(') stack.Push(input[i]);
            else if(input[i]==')' && !stack.IsEmpty()){
                stack.Pop();
            } 
            else{
                cout<<"括号不配对! "<<endl;
                return 0;
            }
        }
    }
    else{
        cout<<"输入长度有误! "<<endl;
        return 0;
    }
    if(!stack.IsEmpty()) cout<<"括号不配对! "<<endl;
    else cout<<"括号配对! "<<endl;
    return 0;
}
