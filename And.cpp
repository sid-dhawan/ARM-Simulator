#include "And.h"
And::And(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
	Execute();
}
void And::Execute()
{
	res=op1 & op2;
	cout<<"EXECUTE: "<<"AND "<<op1<<" and "<<op2<<"\n";
	cout<<"MEMORY: "<<"No memory operation \n"; 
	Memory();
}
void And::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
    Write-back();
}
void And::Write-back()
{
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}

