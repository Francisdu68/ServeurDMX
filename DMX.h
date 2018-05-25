#include <string>

using namespace std;

class DMX
{
	int addr;
	string type;
	int nbCanaux;
	
public:
	DMX(int, string);
	void remplirTab(int[], int, int, int, int);
	int getCanaux();
	string getType();
};