class Swi
{
    private:
        long instruction, number;
        void Execute();
        void Memory();
        void Write-Back();
    public:
        Swi(long instruction);
};
