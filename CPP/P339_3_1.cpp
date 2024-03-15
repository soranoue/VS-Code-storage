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
        cout<<"请输入商品信息(以空格隔开): "<<endl;
        cout<<"编号 名称 单价 库存"<<endl;
        for(k=1;k<=length;k++){
            cin>>elem[k].no;
            cin>>elem[k].name;
            cin>>elem[k].unitprice;
            cin>>elem[k].storage;
        }
    }
    else
        cout<<"数据输入有误! "<<endl;
}

void SqList::Display(){
    int k;
    cout<<"商品总数: "<<length<<endl;
    cout<<"编号 名称 单价 库存"<<endl;
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
        cout<<"数据输入有误! "<<endl;
    else{
        for(j=length+1;j>i;j--) elem[j]=elem[j-1];
        elem[i]=e;
        length++;
        cout<<"数据插入成功! "<<endl;
    }
}

void SqList::Delete(int i){
    int j;
    ElemType e;
    if(i<1 || i>length)
        cout<<"数据输入有误! "<<endl;
    else{
        e=elem[i];
        for(j=i;j<=length;j++) elem[j]=elem[j-1];
        length--;
        cout<<"数据删除成功! "<<endl;
        cout<<"已删除的商品信息: "<<endl;
        cout<<"编号 名称 单价 库存"<<endl;
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
        cout<<"编号 名称 单价 库存"<<endl;
        cout<<elem[l].no<<" ";
        cout<<elem[l].name<<" ";
        cout<<elem[l].unitprice<<" ";
        cout<<elem[l].storage<<" ";
    }
    else cout<<"查无此物! "<<endl;
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
        cout<<"编号 名称 单价 库存"<<endl;
        cout<<elem[l].no<<" ";
        cout<<elem[l].name<<" ";
        cout<<elem[l].unitprice<<" ";
        cout<<elem[l].storage<<" ";
    }
    else cout<<"查无此物! "<<endl;
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
        cout<<"编号 名称 单价 库存"<<endl;
        cout<<elem[l].no<<" ";
        cout<<elem[l].name<<" ";
        cout<<elem[l].unitprice<<" ";
        cout<<elem[l].storage<<" ";
    }
    else cout<<"查无此物! "<<endl;
}

int main(){
    int i,n,choice=0,storage;
    float unitprice;
    string name;
    ElemType e;
    SqList sq;
    do{
        cout<<"****************************************"<<endl;
        cout<<"************商品信息管理系统************"<<endl;
        cout<<"*****************1.建立*****************"<<endl;
        cout<<"*****************2.查询*****************"<<endl;
        cout<<"*****************3.插入*****************"<<endl;
        cout<<"*****************4.删除*****************"<<endl;
        cout<<"**************5.按名称查找**************"<<endl;
        cout<<"**************6.按单价查找**************"<<endl;
        cout<<"**************7.按库存查找**************"<<endl;
        cout<<"*****************0.退出*****************"<<endl;
        cout<<"****************************************"<<endl;
        cout<<"请选择输入数字[0-7] "<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:{
            cout<<"请输入商品数量: ";
            cin>>n;
            sq.Create(n);
            break;
        }
        case 2:{
            sq.Display();
            break;
        }
        case 3:{
            cout<<"请输入需要插入的位置: ";
            cin>>i;
            cout<<"请输入商品信息(以空格隔开): "<<endl;
            cout<<"编号 名称 单价 库存"<<endl;
            cin>>e.no;
            cin>>e.name;
            cin>>e.unitprice;
            cin>>e.storage;
            sq.Insert(i,e);
            break;
        }
        case 4:{
            cout<<"请输入需要删除的位置: ";
            cin>>i;
            sq.Delete(i);
            break;
        }
        case 5:{
            cout<<"请输入要查找商品的名称: ";
            cin>>name;
            sq.NameSearch(name);
            break;
        }
        case 6:{
            cout<<"请输入要查找商品的单价: ";
            cin>>unitprice;
            sq.UnitpriceSearch(unitprice);
            break;
        }
        case 7:{
            cout<<"请输入要查找商品的库存: ";
            cin>>storage;
            sq.StorageSearch(storage);
            break;
        }
        case 0:
            break;
        
        default:
            cout<<"请正确输入数字[0-7]! "<<endl;
        }
    }while(choice);
    return 0;
}
