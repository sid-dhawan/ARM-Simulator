#include "Mvn.h"
Mvn::Mvn(long des, long op)
{
	this->op=op;
	this->des=des;
	Execute();
}
void Mvn::Execute()
{
	res = ~op;
    cout<<"EXECUTE: "<<"MVN "<<op<<"\n";
	Memory();
}
void Eor::Memory()
{
	cout<<"MEMORY: No memory operation"<<endl;
    Write-back();
}	
void Mvn::Write-back()
{
	R[des]=res;
    cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}

