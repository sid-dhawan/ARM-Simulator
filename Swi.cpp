#include "Swi.h"
Swi::Swi(long instruction)
{
    this->instruction = instruction;
    Execute();
}
void Swi::Execute()
{
    if(instruction == (int)(0x11))
    {
        Memory();
    }
    else if(instruction == (int)(0x6c))
    {
        cin>>number;
        Write-back();
    }
    else
    {
        cout<<"EXECUTE: print value in R1"<<endl;
        cout<<R[1]<<endl;
    }
}
void Swi::Write-back()
{
    R[0] = number;
    cout<<"WRITEBACK: Write "<<number<<" to R0"<<endl;
}
void Swi::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
    cout<<"EXIT:"<<endl;
    return;
}
