#include "Instruction.h"
#include "Mvn.h"
#include "Sub.h"
#include "Swi.h"
#include "Swp.h"
#include "Str.h"
#include "Orr.h"
#include "Mul.h"
#include "Mov.h"
#include "Ldr.h"
#include "Eor.h"
#include "And.h"
#include "Add.h"


void Instruction::Execute()
{}
void Instruction::Write-back()
{}
void Instruction::Memory()
{}

Add::Add(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
}
void Add::Execute()
{
	res = op1 + op2;
	cout<<"EXECUTE: "<<"ADD "<<op1<<" and "<<op2<<"\n";			
}
void Add::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}
void Add::Write-back()
{
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


And::And(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
}
void And::Execute()
{
	res=op1 & op2;
	cout<<"EXECUTE: "<<"AND "<<op1<<" and "<<op2<<"\n";
}
void And::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}
void And::Write-back()
{
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Eor::Eor(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
}
void Eor::Execute()
{
	res=op1 ^ op2;
	cout<<"EXECUTE: "<<"EOR "<<op1<<" and "<<op2<<"\n";
}
void Eor::Memory()
{
	cout<<"MEMORY: No memory operation"<<endl;
}
void Eor::Write-back()
{
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Ldr::Ldr(long des,long address,long offset)
{
    this->des = des;
    this->address = address;
    this->offset = offset;
}
void Ldr::Execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
} 
void Ldr::Memory()
{
    ifstream data;
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    data.get(numberString,32);
    number = 0;
    for(int i=31;i>=0;i--)
        number += pow(2,31-i)*(int(numberString[i])-int('0'));
    cout<<"MEMORY: "<<number<<" loaded from "<<address*32+offset*32<<" address in memory"<<endl;
}
void Write-Back()
{
    R[des] = number;
    cout<<"EXECUTE: write "<<number<<" to R"<<des<<endl;
}


Mov::Mov(long des, long op)
{
	this->op=op;
	this->des=des;
}
void Mov::Execute()
{
	res = op;
    cout<<"EXECUTE: "<<"Mov "<<op<<"\n";
}
void Eor::Memory()
{
	cout<<"MEMORY: No memory operation"<<endl;
}	
void Mov::Write-back()
{
	R[des]=res;
    cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Mul::Mul(long des,long op1,long op2)
{
    this->op1 = op1;
    this->op2 = op2;
    this->des = des;
}
void Mul::Execute()
{
    res = op1 * op2;
    cout<"EXECUTE: MUL "<<op1<<" and "<<op2<<endl;
} 
void Mul::Write-back()
{
    R[des] = res;
    cout<<"WRITEBACK: Write "<<res<<" to R"<<des<<endl;
}
void Mul:Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}


Mvn::Mvn(long des, long op)
{
	this->op=op;
	this->des=des;
}
void Mvn::Execute()
{
	res = ~op;
    cout<<"EXECUTE: "<<"MVN "<<op<<"\n";
}
void Eor::Memory()
{
	cout<<"MEMORY: No memory operation"<<endl;
}	
void Mvn::Write-back()
{
	R[des]=res;
    cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Orr::Orr(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
}
void Orr::Execute()	
{
	res=op1 | op2;
	cout<<"EXECUTE: "<<"ORR "<<op1<<" and "<<op2<<"\n";
}
void Orr::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}
void Orr::Write-back()
{		
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Str::Str(long number,long address,long offset)
{
    this->number = number;
    this->address = address;
    this->offset = offset;
}
void Str::Execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
} 
void Str::Memory()
{
    ifstream data();
    cout<<"MEMORY: "<<number<<" stored at "<<address*32+offset*32<<" address in memory"<<endl;
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    for(int i=31;i>=0;i--)
    {
        numberString[i] = (number%2==0?'0':'1');
        number = number/2;
    }
    data.write(numberString,32);
}
void Write-Back()
{
    cout<<"EXECUTE: No write-back operation"<<endl;
}


Sub::Sub(long des,long op1,long op2)
{
    this->des = des;
    this->op1 = op1;
    this->op2 = op2;
}
void Sub::Execute()
{
    res = op1 - op2;
    cout<<"EXECUTE: SUB "<<op2<<" from "<<op1<<endl;
} 
void Sub::Write-back()
{
    R[des] = res;
    cout<<"WRITEBACK: Write "<<res<<" to R"<<des<<endl;
}
void Sub::Memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}


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


Swp::Swp(long des,long number,long address)
{
    this->number = number;
    this->address = address;
    this->des = des;
}
void Swp::Execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
} 
void Swp::Memory()
{
    fstream data();
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    data.get(numberString,32);
    long numberTemp = 0;
    for(int i=31;i>=0;i--)
        numberTemp += pow(2,31-i)*(int(numberString[i])-int('0'));
    cout<<"MEMORY: "<<numberTemp<<" loaded from "<<address*32+offset*32<<" address in memory"<<endl;
    swap(number,numberTemp);
    cout<<numberTemp<<" stored at "<<address*32+offset*32<<" address in memory"<<endl;
	data.seekg(address*32+offset*32,ios::beg);
    for(int i=31;i>=0;i--)
    {
        numberString[i] = (numberTemp%2==0?'0':'1');
        numberTemp = numberTemp/2;
    }
    data.write(numberSwping,32);
}
void Write-Back()
{
    R[des] = number;
    cout<<"WRITEBACK: write "<<number<<" to "<<des<<endl;
}