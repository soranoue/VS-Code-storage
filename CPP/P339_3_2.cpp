#include "iostream"
#include "iomanip"
using namespace std;

struct AddressBook{
    string name;
    string sex;
    string address;
    string number;
};

typedef AddressBook ElemType;

struct LLNodeType{
    ElemType data;
    LLNodeType *next;
};

class LinkList{
    private:
        LLNodeType *Head;
    public:
        LinkList();
        ~LinkList(){}
        void Create(int n);
        void Display();
        void Insert(int i,ElemType e);
        void Delete(int i);
        void NameSearch(string name);
        void NumSearch(string number);
};

LinkList::LinkList(){
    Head=new LLNodeType;
    Head->next=NULL;
}

void LinkList::Create(int n){
    int i,length;
    LLNodeType *p,*q;
    length=n;
    if(length>0){
        cout<<"������ͨѶ¼��Ϣ(�Կո����): "<<endl;
        cout<<"���� �Ա� סַ �绰����"<<endl;
        for(i=1;i<=length;i++){
            p=new LLNodeType;
            cin>>p->data.name;
            cin>>p->data.sex;
            cin>>p->data.address;
            cin>>p->data.number;
            p->next=NULL;
            if(i==1)
                Head->next=p;
            else    
                q->next=p;
            q=p;
        }
    }
    else
        cout<<"������������! "<<endl;
}

void LinkList::Display(){
    LLNodeType *p;
    p=Head->next;
    if(p==NULL)
        cout<<"�����ǿյ�! "<<endl;
    else{
        cout<<"ͨѶ¼: "<<endl;
        cout<<"���� �Ա� סַ �绰����"<<endl;
        while(p!=NULL){
            cout<<p->data.name<<" ";
            cout<<p->data.sex<<" ";
            cout<<p->data.address<<" ";
            cout<<p->data.number<<" ";
            cout<<endl;
            p=p->next;
        }
    }
    cout<<endl;
}

void LinkList::Insert(int i,ElemType e){
    LLNodeType *p,*q,*s;
    int k=1;
    q=Head;
    p=Head->next;
    while(k<i && p!=NULL){
        q=p;
        p=p->next;
        k++;
    }
    if(k==i){
        s=new LLNodeType;
        s->data=e;
        s->next=p;
        q->next=s;
        cout<<"���ݲ���ɹ�! "<<endl;
    }
    else
        cout<<"������������! "<<endl;
}

void LinkList::Delete(int i){
    LLNodeType *p,*q;
    int k=1;
    q=Head;
    p=Head->next;
    while(k<i && p!=NULL){
        q=p;
        p=p->next;
        k++;
    }
    if(k==i){
        q->next=p->next;
        delete p;
        cout<<"����ɾ���ɹ�! "<<endl;
    }
    else{
        cout<<"������������! "<<endl;
    }
}

void LinkList::NameSearch(string name){
    LLNodeType *p;
    int find=0;
    p=Head->next;
    if(p==NULL)
        cout<<"�����ǿյ�! "<<endl;
    else{
        while(!find && p!=NULL){
            if(p->data.name==name) find=1;
            else p->next;
        }
        if(find){
            cout<<"���� �Ա� סַ �绰����"<<endl;
            cout<<p->data.name<<" ";
            cout<<p->data.sex<<" ";
            cout<<p->data.address<<" ";
            cout<<p->data.number<<" ";
            cout<<endl;
        }
        else cout<<"���޴���! "<<endl;
    }
}

void LinkList::NumSearch(string number){
    LLNodeType *p;
    int find=0;
    p=Head->next;
    if(p==NULL)
        cout<<"�����ǿյ�! "<<endl;
    else{
        while(!find && p!=NULL){
            if(p->data.number==number) find=1;
            else p->next;
        }
        if(find){
            cout<<"���� �Ա� סַ �绰����"<<endl;
            cout<<p->data.name<<" ";
            cout<<p->data.sex<<" ";
            cout<<p->data.address<<" ";
            cout<<p->data.number<<" ";
            cout<<endl;
        }
        else cout<<"���޴���! "<<endl;
    }
}

int main(){
    LinkList list;
    ElemType e;
    string name,number;
    int n,i,choice=0;
    do{
        cout<<"****************************************"<<endl;
        cout<<"***************ͨѶ¼����***************"<<endl;
        cout<<"*****************1.����*****************"<<endl;
        cout<<"*****************2.��ѯ*****************"<<endl;
        cout<<"*****************3.����*****************"<<endl;
        cout<<"*****************4.ɾ��*****************"<<endl;
        cout<<"**************5.����������**************"<<endl;
        cout<<"**************6.���������**************"<<endl;
        cout<<"*****************0.�˳�*****************"<<endl;
        cout<<"****************************************"<<endl;
        cout<<"��ѡ����������[0-6] "<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:{
            cout<<"��������ϵ������: ";
            cin>>n;
            list.Create(n);
            break;
        }
        case 2:{
            list.Display();
            break;
        }
        case 3:{
            cout<<"��������Ҫ�����λ��: ";
            cin>>i;
            cout<<"������ͨѶ¼��Ϣ(�Կո����): "<<endl;
            cout<<"���� �Ա� סַ �绰����"<<endl;
            cin>>e.name;
            cin>>e.sex;
            cin>>e.address;
            cin>>e.number;
            list.Insert(i,e);
            break;
        }
        case 4:{
            cout<<"��������Ҫɾ����λ��: ";
            cin>>i;
            list.Delete(i);
            break;
        }
        case 5:{
            cout<<"������Ҫ�����˵�����: ";
            cin>>name;
            list.NameSearch(name);
            break;
        }
        case 6:{
            cout<<"������Ҫ�����˵ĺ���: ";
            cin>>number;
            list.NumSearch(number);
            break;
        }
        case 0:
            break;
        
        default:
            cout<<"����ȷ��������[0-6]! "<<endl;
        }
    }while(choice);
    return 0;
}
