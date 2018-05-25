#include "elemStoryBoard.h"
#include "enttecdmxusb.h"
#include <vector>

class storyboard
{
	vector<elemStoryBoard> scene;
	
public:
	void ajouterElem(elemStoryBoard);
	void visualiserStoryBoard();
	void lireStoryBoard(EnttecDMXUSB*);
};