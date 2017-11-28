class Orr
{
	private:
		long op1, op2, res, des;
		void Execute();
		void Memory();
		void Write-back();
	public:
		Orr(long des, long op1, long op2);
};