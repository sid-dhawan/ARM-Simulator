class Mov
{
	private:    
		long op, res, des;
		void Execute();
		void Memory();
		void Write-back();
	public:
		Mov(long des, long op);
};

	