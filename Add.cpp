#include "Add.h"
Add::Add(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
	Execute();
}
void Add::Execute()
{
	res = op1 + op2;
	cout<<"EXECUTE: "<<"ADD "<<op1<<" and "<<op2<<"\n";			
	Memory();
}
void Add::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
    Write-back();
}
void Add::Write-back()
{
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}

