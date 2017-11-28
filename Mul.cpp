#include "Mul.h"
Mul::Mul(long des,long op1,long op2)
{
    this->op1 = op1;
    this->op2 = op2;
    this->des = des;
    Execute();
}
void Mul::Execute()
{
    res = op1 * op2;
    cout<"EXECUTE: MUL "<<op1<<" and "<<op2<<endl;
    Memory();
} 
void Mul::Write-back()
{
    R[des] = res;
    cout<<"WRITEBACK: Write "<<res<<" to R"<<des<<endl;
}
void Mul:Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
    Write-back();
}
