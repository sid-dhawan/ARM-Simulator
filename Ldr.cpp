#include "Ldr.h"
Ldr::Ldr(long des,long address,long offset)
{
    this->des = des;
    this->address = address;
    this->offset = offset;
    Execute();
}
void Ldr::Execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
    Memory();
} 
void Ldr::Memory()
{
    fstream data;
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    data.get(numberString,32);
    number = 0;
    for(int i=31;i>=0;i--)
        number += pow(2,31-i)*(int(numberString[i])-int('0'));
    cout<<"MEMORY: "<<number<<" loaded from "<<address*32+offset*32<<" address in memory"<<endl;
    Write-Back();
}
void Write-Back()
{
    R[des] = number;
    cout<<"EXECUTE: write "<<number<<" to R"<<des<<endl;
}
