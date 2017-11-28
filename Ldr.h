class Ldr
{
    private:
        long des, number, address, offset;
        char numberString[32];
        void Execute();
        void Memory();
        void Write-Back();
    public:
        Ldr(long des, long address, long offset);
};
