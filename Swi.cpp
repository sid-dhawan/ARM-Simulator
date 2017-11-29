#include "Swi.h"
Swi::Swi(long instruction)
{
    this->instruction = instruction;
}
void Swi::Execute()
{
    if(instruction == (int)(0x11))
    {
        condition = "Exit";
    }
    else if(instruction == (int)(0x6c))
    {
        cout<<"EXECUTE: Read value from console"<<endl;
        condition = "Read";
        cin>>number;
    }
    else
    {
        cout<<"EXECUTE: Print value in R1"<<endl;
        condition = "Print";
    }
}
void Swi::Write-back()
{
    if(condition == "Read")
    {
        R[0] = number;
        cout<<"WRITEBACK: Write "<<number<<" to R0"<<endl;
    }
    else if(condition == "Print")
    {
        cout<<R[1]<<endl;
    }
}
void Swi::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
    if(condition == "Exit")
    {
        cout<<"EXIT:"<<endl;
        exit(0);
    }
}
