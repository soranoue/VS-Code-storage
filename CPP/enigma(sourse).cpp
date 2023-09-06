#include <string>
#include <iostream>
#include <windows.h>
using namespace std;

string Enigma(string input)
{
    int code;
    int n[6] = {24,2,5,4,10,23};
    int nsize=6;
    string output;
    for (int i = 0; i < input.size();i++)
    {
        if(input[i]==' '){output+=' ';continue;}
        code = input[i]-'a';
        for (int j = 0; j < nsize;j++)
        {
            code = (code + n[j]) % 26;
        }

        if(code%2==0) code++;
		else code--;

        for (int j = nsize-1; j >=0;j--)
        {
            code = code - n[j];
            if(code<0) code=26+code;
        }

        n[0]++;
        for (int j = 0; j < nsize-1; j++)
        {
            if (n[j]>=26)
            {
                n[j + 1]++;
                n[j] = 0;
            }
        }
        n[nsize-1] = n[nsize-1] % 26;
        output += code+'a';
    }
    return output;

}


int main()
{
	string text;
	cin>>text;
	string ttext=Enigma(text);
	cout <<"RESULT:"<< ttext<< endl;
	Sleep(5000);
	return 0;
}
