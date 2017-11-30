#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include "instruction.cpp"
using namespace std;
void fetch()
{
	stringstream stream;
	string s,t;
	long x;
	pc>>s;
	if(!pc)
		return;
	pc.get();
	pc>>t;
	pc.get();
	cout<<"Fetch instruction "<<t<<" from address "<<s<<"\n";
	stream.str("");
	stream.clear();
	stream<<s;
	stream>>hex>>insAddress;
	stream.str("");
	stream.clear();
	stream<<t;
	stream>>hex>>x;
	insCode=x;
	//cout<<insAddress<<" "<<insCode<<"\n";
}
void decode()
{
	int i;
	bool imi;
	cout<<"DECODE: ";
	if(insCode[27]==1&&insCode[26]==1&&insCode[25]==1&&insCode[24]==1)
	{
		//SWI
		bitset<24> Im;
		for(i=0;i<24;i++)
			Im[i]=insCode[i];
		cout<<"Operation is SWI\nSWI Code is "<<Im.to_ulong()<<"\n";
		ins=new Swi(Im.to_ulong());
	}
	else if(insCode[27]==0&&insCode[26]==0&&insCode[25]==0&&insCode[24]==1&&insCode[23]==0&&insCode[22]==0)
	{
		// SWP
		bitset<4> Rn,Rm,Rd;
		long op1,op2;
		for(i=16;i<20;i++)
			Rn[i-16]=insCode[i];
		op2=R[Rn.to_ulong()];
		for(i=12;i<16;i++)
			Rd[i-12]=insCode[i];
		for(i=0;i<4;i++)
			Rm[i]=insCode[i];
		op1=R[Rm.to_ulong()];
		cout<<"Operation is SWP, Source is R"<<Rm.to_ulong();
		cout<<", Address is R"<<Rn.to_ulong()<<"\n";
		cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
		cout<<"Read registers: R"<<Rm.to_ulong()<<" = "<<op1;
		cout<<", R"<<Rn.to_ulong()<<" = "<<op2;
		cout<<endl;		
		ins=new Swp(Rd.to_ulong(),op1,op2);
	}
	else if(insCode[27]==0&&insCode[26]==0&&insCode[25]==0&&insCode[24]==0&&insCode[23]==0&&insCode[22]==0)
	{
		// MUL
		bitset<4> Rn,Rm,Rd;
		long op1,op2;
		for(i=8;i<12;i++)
			Rn[i-8]=insCode[i];
		op2=R[Rn.to_ulong()];
		for(i=0;i<4;i++)
			Rm[i]=insCode[i];
		op1=R[Rm.to_ulong()];
		for(i=16;i<20;i++)
			Rd[i-16]=insCode[i];
		cout<<"Operation is MUL, First operand is R"<<Rm.to_ulong();
		cout<<", Second operand is R"<<Rn.to_ulong()<<"\n";
		cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
		cout<<"Read registers: R"<<Rm.to_ulong()<<" = "<<op1;
		cout<<", R"<<Rn.to_ulong()<<" = "<<op2;
		cout<<endl;
		ins=new Mul(Rd.to_ulong(),op1,op2);
	}
	else if(insCode[27]==0&&insCode[26]==0) 
	{
		bitset<4> opcode,Rn,Rm,Rd;
		bitset<8> Im;
		long op1,op2;
		for(i=21;i<=24;i++)
			opcode[i-21]=insCode[i];
		for(i=16;i<20;i++)
			Rn[i-16]=insCode[i];
		for(i=12;i<16;i++)
			Rd[i-12]=insCode[i];
		op1=R[Rn.to_ulong()];
		if(insCode[25]==1) // Immediate
		{
			imi=true;
			for(i=0;i<8;i++)
				Im[i]=insCode[i];
			op2=Im.to_ulong();
		}
		else if(insCode[25]==0) // Register
		{
			imi=false;
			for(i=0;i<4;i++)
				Rm[i]=insCode[i];
			op2=R[Rm.to_ulong()];
		}
		switch(opcode.to_ulong())
		{
			case 0 : //AND
				cout<<"Operation is AND, First operand is R"<<Rn.to_ulong();
				if(imi)
					cout<<", Immidiate second operand is "<<op2<<"\n";
				else
					cout<<", Second operand is R"<<Rm.to_ulong()<<"\n";
				cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
				cout<<"Read registers: R"<<Rn.to_ulong()<<" = "<<op1;
				if(!imi)
					cout<<", R"<<Rm.to_ulong()<<" = "<<op2;
				cout<<endl;
				ins=new And(Rd.to_ulong(),op1,op2);
				break;

			case 1 : //EOR
				cout<<"Operation is EOR, First operand is R"<<Rn.to_ulong();
				if(imi)
					cout<<", Immidiate second operand is "<<op2<<"\n";
				else
					cout<<", Second operand is R"<<Rm.to_ulong()<<"\n";
				cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
				cout<<"Read registers: R"<<Rn.to_ulong()<<" = "<<op1;
				if(!imi)
					cout<<", R"<<Rm.to_ulong()<<" = "<<op2;
				cout<<endl;
				ins=new Eor(Rd.to_ulong(),op1,op2);
				break;

			case 2 : //SUB
				cout<<"Operation is SUB, First operand is R"<<Rn.to_ulong();
				if(imi)
					cout<<", Immidiate second operand is "<<op2<<"\n";
				else
					cout<<", Second operand is R"<<Rm.to_ulong()<<"\n";
				cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
				cout<<"Read registers: R"<<Rn.to_ulong()<<" = "<<op1;
				if(!imi)
					cout<<", R"<<Rm.to_ulong()<<" = "<<op2;
				cout<<endl;
				ins=new Sub(Rd.to_ulong(),op1,op2);
				break;

			case 4 : //ADD
				cout<<"Operation is ADD, First operand is R"<<Rn.to_ulong();
				if(imi)
					cout<<", Immidiate second operand is "<<op2<<"\n";
				else
					cout<<", Second operand is R"<<Rm.to_ulong()<<"\n";
				cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
				cout<<"Read registers: R"<<Rn.to_ulong()<<" = "<<op1;
				if(!imi)
					cout<<", R"<<Rm.to_ulong()<<" = "<<op2;
				cout<<endl;
				ins=new Add(Rd.to_ulong(),op1,op2);
				break;

			case 10: //CMP
				cout<<"Operation is CMP, First operand is R"<<Rn.to_ulong();
				if(imi)
					cout<<", Immidiate second operand is "<<op2<<"\n";
				else
					cout<<", Second operand is R"<<Rm.to_ulong()<<"\n";
				cout<<"Read registers: R"<<Rn.to_ulong()<<" = "<<op1;
				if(!imi)
					cout<<", R"<<Rm.to_ulong()<<" = "<<op2;
				cout<<endl;
				ins=new Cmp(op1,op2);
				break;

			case 12: //ORR
				cout<<"Operation is ORR, First operand is R"<<Rn.to_ulong();
				if(imi)
					cout<<", Immidiate second operand is "<<op2<<"\n";
				else
					cout<<", Second operand is R"<<Rm.to_ulong()<<"\n";
				cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
				cout<<"Read registers: R"<<Rn.to_ulong()<<" = "<<op1;
				if(!imi)
					cout<<", R"<<Rm.to_ulong()<<" = "<<op2;
				cout<<endl;
				ins=new Orr(Rd.to_ulong(),op1,op2);
				break;

			case 13: //MOV
				cout<<"Operation is MOV";
				if(imi)
					cout<<", Immidiate operand is "<<op2<<"\n";
				else
					cout<<", Operand is R"<<Rm.to_ulong()<<"\n";
				cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
				if(!imi)
					cout<<"Read registers: R"<<Rm.to_ulong()<<" = "<<op2<<"\n";
				ins=new Mov(Rd.to_ulong(),op2);
				break;

			case 15: //MVN
				cout<<"Operation is MVN";
				if(imi)
					cout<<", Immidiate operand is "<<op2<<"\n";
				else
					cout<<", Operand is R"<<Rm.to_ulong()<<"\n";
				cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
				if(!imi)
					cout<<"Read registers: R"<<Rm.to_ulong()<<" = "<<op2<<"\n";
				ins=new Mvn(Rd.to_ulong(),op2);
				break;

			default:
				ins=new Instruction();
		}
	}
	else if(insCode[27]==1&&insCode[26]==0&&insCode[25]==1)
	{
		bitset<4> cond;
		bool flag;
		long offset;
		for(i=28;i<=31;i++)
			cond[i-28]=insCode[i];
		bitset<24> Im;
		for(i=0;i<24;i++)
			Im[i]=insCode[i];
		if(Im[23]==1)
		{
			Im=Im.to_ulong()-1;
			Im=~Im;
			offset=-Im.to_ulong();
		}
		else
			offset=Im.to_ulong();
		cout<<"Operation is B, Offset is "<<offset<<endl;
		switch(cond.to_ulong())
		{
			case 0 : cout<<"Condition is EQ\n";//EQ
				flag=Z;
				break;
			case 1 : cout<<"Condition is NE\n";//NE
				flag=Z;
				break;
			case 10 : cout<<"Condition is GE\n";///GE
				flag=(N==V);
				break;
			case 11: cout<<"Condition is LT\n";///LT
				flag=(N!=V);
				break;
			case 12: cout<<"Condition is GT\n";///GT
				flag=(!Z&&(N==V));
				break;
			case 13: cout<<"Condition is LE\n";///LE
				flag=(Z||(N!=V));
				break;
			default: cout<<"Condition is AL\n";///AL
				flag=true;
		}
		cout<<"Read flags: ";
		cout<<"Z = "<<Z<<", N = "<<N<<", V = "<<V<<endl;
		if(flag)
		{
			cout<<"Condition found True\n";
			ins=new B(offset);	
		}
		else
		{
			cout<<"Condition found False\n";
			ins=new Instruction();
		}
	}
	else if(insCode[27]==0&&insCode[26]==1&&insCode[25]==0) // Immidiate 
	{
		bitset<4> Rn,Rm,Rd;
		bitset<12> Im;
		long op1,op2;
		bool imi;
		for(i=16;i<20;i++)
			Rn[i-16]=insCode[i];
		for(i=12;i<16;i++)
			Rd[i-12]=insCode[i];
		op1=R[Rn.to_ulong()];
		if(insCode[25]==0) // Immediate
		{
			imi=true;
			for(i=0;i<12;i++)
				Im[i]=insCode[i];
			op2=Im.to_ulong();
		}
		else if(insCode[25]==1) // Register
		{
			imi=false;
			for(i=0;i<4;i++)
				Rm[i]=insCode[i];
			op2=R[Rm.to_ulong()];
		}
		if(insCode[23]==0)
			op2=-op2;

		if(insCode[20]==1)//LDR
		{
			cout<<"Operation is LDR, Base address is R"<<Rn.to_ulong();
			if(imi)
				cout<<", Immidiate offset is "<<op2<<"\n";
			else
				cout<<", Offset is R"<<Rm.to_ulong()<<"\n";
			cout<<"Destination register is R"<<Rd.to_ulong()<<"\n";
			cout<<"Read registers: R"<<Rn.to_ulong()<<" = "<<op1;
			if(!imi)
				cout<<", R"<<Rm.to_ulong()<<" = "<<op2;
			cout<<endl;
			ins=new Ldr(Rd.to_ulong(),op1,op2);
		}
		else //STR
		{
			cout<<"Operation is STR, Base address is R"<<Rn.to_ulong();
			if(imi)
				cout<<", Immidiate offset is "<<op2<<"\n";
			else
				cout<<", Offset is R"<<Rm.to_ulong()<<"\n";
			cout<<"Source register is R"<<Rd.to_ulong()<<"\n";
			cout<<"Read registers: R"<<Rd.to_ulong()<<" = "<<R[Rd.to_ulong()];
			cout<<", R"<<Rn.to_ulong()<<" = "<<op1;
			if(!imi)
				cout<<", R"<<Rm.to_ulong()<<" = "<<op2;
			cout<<endl;
			ins=new Str(R[Rd.to_ulong()],op1,op2);
		}
	}
	else
		ins=new Instruction();
}	
int main()
{
	ios_base::sync_with_stdio(false);
	pc.open("INS.MEM");
	while(1)
	{
		fetch();
		if(pc.eof())
			break;
		decode();
		ins->execute();
		ins->memory();
		ins->writeBack();
		cout<<"\n";
	}
	pc.close();
	return 0;
}
