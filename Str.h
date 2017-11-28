class Str
{
    private:
        long number, address, offset;
        char numberString[32];
        void Execute();
        void Memory();
        void Write-Back();
    public:
        Str(long number, long address, long offset);
};
