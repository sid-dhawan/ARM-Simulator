#include "Mov.h"
Mov::Mov(long des, long op)
{
	this->op=op;
	this->des=des;
	Execute();
}
void Mov::Execute()
{
	res = op;
    cout<<"EXECUTE: "<<"Mov "<<op<<"\n";
	Memory();
}
void Eor::Memory()
{
	cout<<"MEMORY: No memory operation"<<endl;
    Write-back();
}	
void Mov::Write-back()
{
	R[des]=res;
    cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}

