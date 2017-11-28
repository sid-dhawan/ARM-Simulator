#include "Swp.h"
Swp::Swp(long des,long number,long address)
{
    this->number = number;
    this->address = address;
    this->des = des;
    Execute();
}
void Swp::Execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
    Memory();
} 
void Swp::Memory()
{
    fstream data();
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    data.get(numberString,32);
    long numberTemp = 0;
    for(int i=31;i>=0;i--)
        numberTemp += pow(2,31-i)*(int(numberString[i])-int('0'));
    cout<<"MEMORY: "<<numberTemp<<" loaded from "<<address*32+offset*32<<" address in memory"<<endl;
    swap(number,numberTemp);
    Write-Back();
    number = numberTemp;
    data.seekg(address*32+offset*32,ios::beg);
    for(int i=31;i>=0;i--)
    {
        numberString[i] = (number%2==0?'0':'1');
        number = number/2;
    }
    data.write(numberSwping,32);
    cout<<numberTemp<<" stored at "<<address*32+offset*32<<" address in memory"<<endl;
}
void Write-Back()
{
    R[des] = number;
    cout<<"EXECUTE: write "<<number<<" to "<<des<<endl;
}
