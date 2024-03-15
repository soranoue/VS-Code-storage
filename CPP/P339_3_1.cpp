#include "iostream"
using namespace std;

struct Goods{
    string no;
    string name;
    float unitprice;
    int storage;
};

typedef Goods ElemType;
const int MAXSIZE=100;

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
        void NameSearch(string name);
        void UnitpriceSearch(float unitprice);
        void StorageSearch(int storage);
};

void SqList::Create(int n){
    int k;
    length=n;
    if(length>0){
        cout<<"��������Ʒ��Ϣ(�Կո����): "<<endl;
        cout<<"��� ���� ���� ���"<<endl;
        for(k=1;k<=length;k++){
            cin>>elem[k].no;
            cin>>elem[k].name;
            cin>>elem[k].unitprice;
            cin>>elem[k].storage;
        }
    }
    else
        cout<<"������������! "<<endl;
}

void SqList::Display(){
    int k;
    cout<<"��Ʒ����: "<<length<<endl;
    cout<<"��� ���� ���� ���"<<endl;
    for(k=1;k<=length;k++){
        cout<<elem[k].no<<" ";
        cout<<elem[k].name<<" ";
        cout<<elem[k].unitprice<<" ";
        cout<<elem[k].storage<<" ";
        cout<<endl;
    }
    
}

void SqList::Insert(int i,ElemType e){
    int j;
    if(i<1 || i>length)
        cout<<"������������! "<<endl;
    else{
        for(j=length+1;j>i;j--) elem[j]=elem[j-1];
        elem[i]=e;
        length++;
        cout<<"���ݲ���ɹ�! "<<endl;
    }
}

void SqList::Delete(int i){
    int j;
    ElemType e;
    if(i<1 || i>length)
        cout<<"������������! "<<endl;
    else{
        e=elem[i];
        for(j=i;j<=length;j++) elem[j]=elem[j-1];
        length--;
        cout<<"����ɾ���ɹ�! "<<endl;
        cout<<"��ɾ������Ʒ��Ϣ: "<<endl;
        cout<<"��� ���� ���� ���"<<endl;
        cout<<e.no<<" ";
        cout<<e.name<<" ";
        cout<<e.unitprice<<" ";
        cout<<e.storage<<" ";
        cout<<endl;
    }
}

void SqList::NameSearch(string name){
    int k,l,find=0;
    for(k=1;k<=length;k++){
        if(elem[k].name==name){
            find=1;
            l=k;
            k=length+1;
        }
    }
    if(find){
        cout<<"��� ���� ���� ���"<<endl;
        cout<<elem[l].no<<" ";
        cout<<elem[l].name<<" ";
        cout<<elem[l].unitprice<<" ";
        cout<<elem[l].storage<<" ";
    }
    else cout<<"���޴���! "<<endl;
}

void SqList::UnitpriceSearch(float unitprice){
    int k,l,find=0;
    for(k=1;k<=length;k++){
        if(elem[k].unitprice==unitprice){
            find=1;
            l=k;
            k=length+1;
        }
    }
    if(find){
        cout<<"��� ���� ���� ���"<<endl;
        cout<<elem[l].no<<" ";
        cout<<elem[l].name<<" ";
        cout<<elem[l].unitprice<<" ";
        cout<<elem[l].storage<<" ";
    }
    else cout<<"���޴���! "<<endl;
}

void SqList::StorageSearch(int storage){
    int k,l,find=0;
    for(k=1;k<=length;k++){
        if(elem[k].storage==storage){
            find=1;
            l=k;
            k=length+1;
        }
    }
    if(find){
        cout<<"��� ���� ���� ���"<<endl;
        cout<<elem[l].no<<" ";
        cout<<elem[l].name<<" ";
        cout<<elem[l].unitprice<<" ";
        cout<<elem[l].storage<<" ";
    }
    else cout<<"���޴���! "<<endl;
}

int main(){
    int i,n,choice=0,storage;
    float unitprice;
    string name;
    ElemType e;
    SqList sq;
    do{
        cout<<"****************************************"<<endl;
        cout<<"************��Ʒ��Ϣ����ϵͳ************"<<endl;
        cout<<"*****************1.����*****************"<<endl;
        cout<<"*****************2.��ѯ*****************"<<endl;
        cout<<"*****************3.����*****************"<<endl;
        cout<<"*****************4.ɾ��*****************"<<endl;
        cout<<"**************5.�����Ʋ���**************"<<endl;
        cout<<"**************6.�����۲���**************"<<endl;
        cout<<"**************7.��������**************"<<endl;
        cout<<"*****************0.�˳�*****************"<<endl;
        cout<<"****************************************"<<endl;
        cout<<"��ѡ����������[0-7] "<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:{
            cout<<"��������Ʒ����: ";
            cin>>n;
            sq.Create(n);
            break;
        }
        case 2:{
            sq.Display();
            break;
        }
        case 3:{
            cout<<"��������Ҫ�����λ��: ";
            cin>>i;
            cout<<"��������Ʒ��Ϣ(�Կո����): "<<endl;
            cout<<"��� ���� ���� ���"<<endl;
            cin>>e.no;
            cin>>e.name;
            cin>>e.unitprice;
            cin>>e.storage;
            sq.Insert(i,e);
            break;
        }
        case 4:{
            cout<<"��������Ҫɾ����λ��: ";
            cin>>i;
            sq.Delete(i);
            break;
        }
        case 5:{
            cout<<"������Ҫ������Ʒ������: ";
            cin>>name;
            sq.NameSearch(name);
            break;
        }
        case 6:{
            cout<<"������Ҫ������Ʒ�ĵ���: ";
            cin>>unitprice;
            sq.UnitpriceSearch(unitprice);
            break;
        }
        case 7:{
            cout<<"������Ҫ������Ʒ�Ŀ��: ";
            cin>>storage;
            sq.StorageSearch(storage);
            break;
        }
        case 0:
            break;
        
        default:
            cout<<"����ȷ��������[0-7]! "<<endl;
        }
    }while(choice);
    return 0;
}
