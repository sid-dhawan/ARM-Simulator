#include <iostream>
using namespace std;
int main()
{
	string s;
	long i=0;
	while(cin>>s)
	{
		cout<<"0x"<<hex<<i<<" 0x"<<s<<"\n";
		i+=4;
	}
	return 0;
}

