#include "Sub.h"
Sub::Sub(long des,long op1,long op2)
{
    this->des = des;
    this->op1 = op1;
    this->op2 = op2;
    Execute();
}
void Sub::Execute()
{
    res = op1 - op2;
    cout<<"EXECUTE: SUB "<<op2<<" from "<<op1<<endl;
    Memory();
} 
void Sub::Write-back()
{
    R[des] = res;
    cout<<"WRITEBACK: Write "<<res<<" to R"<<des<<endl;
}
void Sub::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
    Write-back();
}
