class Instruction
{
    public:
        void Execute();
        void Memory();
        void Write-back();
};
class Add:Instruction
{
	private:
		long op1, op2, res, des;
	public:
		void Execute();
		void Memory();
		void Write-back();
		Add(long des, long op1, long op2);
};
class And:Instruction
{
	private:
		long op1, op2, res, des;
	public:
		void Execute();
		void Memory();
		void Write-back();
		And(long des, long op1, long op2);
};
class Eor:Instruction
{
	private:
		long op1, op2, res, des;
	public:
		void Execute();
		void Memory();
		void Write-back();
		Eor(long des, long op1, long op2);
};
class Ldr:Instruction
{
    private:
        long des, number, address, offset;
        char numberString[32];
    public:
        void Execute();
        void Memory();
        void Write-Back();
        Ldr(long des, long address, long offset);
};
class Mov:Instruction
{
	private:    
		long op, res, des;
	public:
		void Execute();
		void Memory();
		void Write-back();
		Mov(long des, long op);
};
class Mul:Instruction
{
    private:
        long op1, op2, res, des;
    public:
        void Execute();
        void Memory();
        void Write-back();
        Mul(long des, long op1, long op2);
};
class Mvn:Instruction
{
	private:    
		long op, res, des;
	public:
		void Execute();
		void Memory();
		void Write-back();
		Mvn(long des, long op);
};
class Orr:Instruction
{
	private:
		long op1, op2, res, des;
	public:
		void Execute();
		void Memory();
		void Write-back();
		Orr(long des, long op1, long op2);
};
class Str:Instruction
{
    private:
        long number, address, offset;
        char numberString[32];
    public:
        void Execute();
        void Memory();
        void Write-Back();
        Str(long number, long address, long offset);
};
class Sub:Instruction
{
    private:
        long op1, op2, res, des;
    public:
        void Execute();
        void Memory();
        void Write-back();
        Sub(long des, long op1, long op2);
};
class Swi:Instruction
{
    private:
        long instruction, number;
        string condition;
    public:
        void Execute();
        void Memory();
        void Write-Back();
        Swi(long instruction);
};
class Str:Instruction
{
    private:
        long number, address, des;
        char numberString[32];
    public:
        void Execute();
        void Memory();
        void Write-Back();
        Str(long des long number, long address);
};