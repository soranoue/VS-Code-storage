#include "iostream"
#include "iomanip"
using namespace std;

const int MAXSIZE=100;
typedef int KeyType;
struct DataNode{
    KeyType key;
    //others
    //......
};

class SqTable{
    private:
        DataNode r[MAXSIZE];
        int n;
    public:
        SqTable(){n=0;}
        void Create();
        void Display();
        void SqSearch(KeyType key);
        void BinarySearch(KeyType key);
};

void SqTable::Create(){
    int k;
    cout<<"Input length: ";
    cin>>n;
    cout<<"Input Data: ";
    for(k=0;k<n;k++)
        cin>>r[k].key;
}

void SqTable::Display(){
    int k;
    cout<<"length= "<<n<<endl;
    cout<<"Record Data: ";
    for(k=0;k<n;k++)
        cout<<setw(6)<<r[k].key;
    cout<<endl;
}

void SqTable::SqSearch(KeyType key){
    int i;
    r[0].key=key;
    for(i=n;r[i].key!=key;i--);
    if(i>0)
        cout<<"SqSearch Success, Record Indexed: "<<i<<endl;
    else    
        cout<<"SqSearch Fail! "<<endl;
}

void SqTable::BinarySearch(KeyType key){
    int mid,low,high,find;
    low=1;high=n;find=0;
    while(find==0 && low<=high){
        mid=(low+high)/2;
        if(key==r[mid].key){
            cout<<"BinarySearch Success, Record Indexed: "<<mid<<endl;
            find=1;
        }
        else if(key<r[mid].key)
                high=mid-1;
            else
                low=mid+1;
    }
    if(find==0)
        cout<<"BinarySearch Fail! "<<endl;
}

int main(){
    SqTable sq;
    KeyType key;
    sq.Create();
    sq.Display();
    cout<<"Input Search Key: ";
    cin>>key;
    sq.SqSearch(key);
    sq.BinarySearch(key);
    return 0;
}
