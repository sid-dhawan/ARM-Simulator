#include "Orr.h"
Orr::Orr(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
	Execute();
}
void Orr::Execute()	
{
	res=op1 | op2;
	cout<<"EXECUTE: "<<"ORR "<<op1<<" and "<<op2<<"\n";
	Memory();
}
void Orr::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
    Write-back();
}
void Orr::Write-back()
{		
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}

