#include <string>
#include "Fragment.h"

using namespace std;

Fragment::Fragment(int i, string d)
{
	index = i;
	data = d;
}

int Fragment::getIndex()
{
	return index;
}

string Fragment::getData()
{
	return data;
}

void Fragment::setData(string d)
{
	data = d;
}

void Fragment::setIndex(int i)
{
	index = i;
}
