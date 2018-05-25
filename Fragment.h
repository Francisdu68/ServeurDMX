#include <string>

using namespace std;

class Fragment
{
	friend bool operator < (const Fragment & a, const Fragment & b)
    {
       return (a.index < b.index ? true : false);
    }
   
	int index;
	string data;

public:
	Fragment(int, string);
	int getIndex();
	string getData();
	void setIndex(int);
	void setData(string);
};
