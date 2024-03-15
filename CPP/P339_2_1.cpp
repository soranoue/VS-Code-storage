#include "iostream"
#include "iomanip"
using namespace std;

const int MAXSIZE=100;
typedef int ElemType;

class SqList{
    private:
        ElemType elem[MAXSIZE];
        int length;
    public:
        SqList(){length=0;}
        ~SqList(){}
        void Create(int n);
        void Display();
        void Insert(int i,ElemType e);
        void Delete(int i);
};

void SqList::Create(int n){
    int k;
    length=n;
    if(length>0 || length<MAXSIZE){
        cout<<"Input Data Elem: "<<endl;
        for(k=1;k<=length;k++)
            cin>>elem[k];
    }
    else
        cout<<"Length Error!"<<endl;
}

void SqList::Display(){
    int k;
    cout<<"length= "<<length<<endl;
    cout<<"Data Elem: ";
    for(k=1;k<=length;k++)
        cout<<setw(6)<<elem[k];
    cout<<endl;
}

void SqList::Insert(int i,ElemType e){
    int j;
    if(i<1 || i>length)
        cout<<"Insert Location i Error!"<<endl;
    else{
        for(j=length+1;j>i;j--)
            elem[j]=elem[j-1];
        elem[i]=e;
        length++;
        cout<<"Insert Success!"<<endl;
    }
}

void SqList::Delete(int i){
    int j;
    if(i<1 || i>length)
        cout<<"Delete Location i Error!"<<endl;
    else{
        for(j=i;j<length;j++)
            elem[j]=elem[j+1];
        length--;
        cout<<"Delete Success!"<<endl;
    }
}

int main(){
    SqList list;
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
