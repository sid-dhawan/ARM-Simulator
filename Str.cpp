#include "Str.h"
Str::Str(long number,long address,long offset)
{
    this->number = number;
    this->address = address;
    this->offset = offset;
    Execute();
}
void Str::Execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
    Memory();
} 
void Str::Memory()
{
    ifstream data();
    cout<<"MEMORY: "<<number<<" stored at "<<address*32+offset*32<<" address in memory"<<endl;
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    for(int i=31;i>=0;i--)
    {
        numberString[i] = (number%2==0?'0':'1');
        number = number/2;
    }
    data.write(numberString,32);
    Write-Back();
}
void Write-Back()
{
    cout<<"EXECUTE: No write-back operation"<<endl;
}
