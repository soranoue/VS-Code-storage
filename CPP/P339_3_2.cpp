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
        cout<<"请输入通讯录信息(以空格隔开): "<<endl;
        cout<<"姓名 性别 住址 电话号码"<<endl;
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
        cout<<"数据输入有误! "<<endl;
}

void LinkList::Display(){
    LLNodeType *p;
    p=Head->next;
    if(p==NULL)
        cout<<"链表是空的! "<<endl;
    else{
        cout<<"通讯录: "<<endl;
        cout<<"姓名 性别 住址 电话号码"<<endl;
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
        cout<<"数据插入成功! "<<endl;
    }
    else
        cout<<"数据输入有误! "<<endl;
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
        cout<<"数据删除成功! "<<endl;
    }
    else{
        cout<<"数据输入有误! "<<endl;
    }
}

void LinkList::NameSearch(string name){
    LLNodeType *p;
    int find=0;
    p=Head->next;
    if(p==NULL)
        cout<<"链表是空的! "<<endl;
    else{
        while(!find && p!=NULL){
            if(p->data.name==name) find=1;
            else p->next;
        }
        if(find){
            cout<<"姓名 性别 住址 电话号码"<<endl;
            cout<<p->data.name<<" ";
            cout<<p->data.sex<<" ";
            cout<<p->data.address<<" ";
            cout<<p->data.number<<" ";
            cout<<endl;
        }
        else cout<<"查无此人! "<<endl;
    }
}

void LinkList::NumSearch(string number){
    LLNodeType *p;
    int find=0;
    p=Head->next;
    if(p==NULL)
        cout<<"链表是空的! "<<endl;
    else{
        while(!find && p!=NULL){
            if(p->data.number==number) find=1;
            else p->next;
        }
        if(find){
            cout<<"姓名 性别 住址 电话号码"<<endl;
            cout<<p->data.name<<" ";
            cout<<p->data.sex<<" ";
            cout<<p->data.address<<" ";
            cout<<p->data.number<<" ";
            cout<<endl;
        }
        else cout<<"查无此人! "<<endl;
    }
}

int main(){
    LinkList list;
    ElemType e;
    string name,number;
    int n,i,choice=0;
    do{
        cout<<"****************************************"<<endl;
        cout<<"***************通讯录管理***************"<<endl;
        cout<<"*****************1.建立*****************"<<endl;
        cout<<"*****************2.查询*****************"<<endl;
        cout<<"*****************3.插入*****************"<<endl;
        cout<<"*****************4.删除*****************"<<endl;
        cout<<"**************5.按姓名查找**************"<<endl;
        cout<<"**************6.按号码查找**************"<<endl;
        cout<<"*****************0.退出*****************"<<endl;
        cout<<"****************************************"<<endl;
        cout<<"请选择输入数字[0-6] "<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:{
            cout<<"请输入联系人数量: ";
            cin>>n;
            list.Create(n);
            break;
        }
        case 2:{
            list.Display();
            break;
        }
        case 3:{
            cout<<"请输入需要插入的位置: ";
            cin>>i;
            cout<<"请输入通讯录信息(以空格隔开): "<<endl;
            cout<<"姓名 性别 住址 电话号码"<<endl;
            cin>>e.name;
            cin>>e.sex;
            cin>>e.address;
            cin>>e.number;
            list.Insert(i,e);
            break;
        }
        case 4:{
            cout<<"请输入需要删除的位置: ";
            cin>>i;
            list.Delete(i);
            break;
        }
        case 5:{
            cout<<"请输入要查找人的姓名: ";
            cin>>name;
            list.NameSearch(name);
            break;
        }
        case 6:{
            cout<<"请输入要查找人的号码: ";
            cin>>number;
            list.NumSearch(number);
            break;
        }
        case 0:
            break;
        
        default:
            cout<<"请正确输入数字[0-6]! "<<endl;
        }
    }while(choice);
    return 0;
}
