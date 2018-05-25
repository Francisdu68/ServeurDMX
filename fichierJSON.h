#include <iostream>
#include <sys/stat.h>
#include <string>
#include <cstring>
#include <fstream>

#include "json.h"

using namespace std;

class fichierJSON
{

public:
	static string getName(json_value*, string);
	static int getNameInt(json_value*, string);
	static bool getNameBool(json_value*, string);
	static void setConfig(json_value*, int &, int &, int &, int &, int &);
	static json_value* ouvrirJSON(string);
	static void fermerJSON(json_value*);
};
