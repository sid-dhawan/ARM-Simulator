#include <string>
using namespace std;
class Instruction
{
    public:
        virtual void execute();
        virtual void memory();
        virtual void writeBack();
};
class Add:public Instruction
{
	private:
		long op1, op2, res, des;
	public:
		void execute();
		void memory();
		void writeBack();
		Add(long des, long op1, long op2);
};
class And:public Instruction
{
	private:
		long op1, op2, res, des;
	public:
		void execute();
		void memory();
		void writeBack();
		And(long des, long op1, long op2);
};
class Cmp:public Instruction
{
    private:
        long op1, op2, res;
    public:
        void execute();
        void memory();
        void writeBack();
        Cmp(long op1, long op2);
};
class Eor:public Instruction
{
	private:
		long op1, op2, res, des;
	public:
		void execute();
		void memory();
		void writeBack();
		Eor(long des, long op1, long op2);
};
class Ldr:public Instruction
{
    private:
        long des, number, address, offset;
        char numberString[32];
    public:
        void execute();
        void memory();
        void writeBack();
        Ldr(long des, long address, long offset);
};
class Mov:public Instruction
{
	private:    
		long op, res, des;
	public:
		void execute();
		void memory();
		void writeBack();
		Mov(long des, long op);
};
class Mul:public Instruction
{
    private:
        long op1, op2, res, des;
    public:
        void execute();
        void memory();
        void writeBack();
        Mul(long des, long op1, long op2);
};
class Mvn:public Instruction
{
	private:    
		long op, res, des;
	public:
		void execute();
		void memory();
		void writeBack();
		Mvn(long des, long op);
};
class Orr:public Instruction
{
	private:
		long op1, op2, res, des;
	public:
		void execute();
		void memory();
		void writeBack();
		Orr(long des, long op1, long op2);
};
class Str:public Instruction
{
    private:
        long number, address, offset;
        char numberString[32];
    public:
        void execute();
        void memory();
        void writeBack();
        Str(long number, long address, long offset);
};
class Sub:public Instruction
{
    private:
        long op1, op2, res, des;
    public:
        void execute();
        void memory();
        void writeBack();
        Sub(long des, long op1, long op2);
};
class Swi:public Instruction
{
    private:
        long instruction, number;
        string condition;
    public:
        void execute();
        void memory();
        void writeBack();
        Swi(long instruction);
};
class B:public Instruction
{
	private:
		long offset,address;
	public:
		B(long offset);
		void execute();
		void memory();
		void writeBack();
		
};
class Swp:public Instruction
{
    private:
        long number, address, des;
        char numberString[32];
    public:
        void execute();
        void memory();
        void writeBack();
        Swp(long des, long number, long address);
};
