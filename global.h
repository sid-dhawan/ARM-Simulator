#include <fstream>
#include <bitset>
using namespace std;
ifstream pc;
bitset<32> insCode;
long insAddress,R[16];
bool Z,C,V,N;
Instruction* ins;

