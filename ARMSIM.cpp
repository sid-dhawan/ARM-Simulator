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
	cout<<insAddress<<" "<<insCode<<"\n";
}
void decode()
{
	int i;
	bool imi;
	cout<<"DECODE: ";
	if(insCode[27]==0&&insCode[26]==0) 
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
			if(Im[7]==1)
			{
				Im=Im.to_ulong()-1;
				Im=~Im;
				op2=-Im.to_ulong();
			}
			else
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
                //ins=new Cmp(Rd.to_ulong(),op1,op2);
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
		for(i=28;i<=31;i++)
			cond[i-28]=insCode[i];
		bitset<24> offset;
		for(i=0;i<24;i++)
			offset[i]=insCode[i];
		switch(cond.to_ulong())
		{
			case 0 : //EQ
					 flag=Z;
					 break;
			case 1 : //NE
					 flag=Z;
					 break;
			case 10 : //GE
					 flag=(N==V);
					 break;
			case 11: //LT
					 flag=(N!=V);
					 break;
			case 12: //GT
					 flag=(!Z&&(N==V));
					 break;
			case 13: //LE
					 flag=(Z||(N!=V));
					 break;
			default: //AL
					 flag=true;
		}
		if(flag)
		{
			//
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
			ins=new Ldr(Rd.to_ulong(),op1,op2);
		}
		else //STR
		{
			ins=new Str(Rd.to_ulong(),op1,op2);
		}
	}
	else
		ins=new Instruction();
}	
int main()
{
	ios_base::sync_with_stdio(false);
	pc.open("input");
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
