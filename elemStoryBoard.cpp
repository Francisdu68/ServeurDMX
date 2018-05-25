#include <vector>
#include <string>
#include "elemStoryBoard.h"
#include <iostream>

using namespace std;

string elemStoryBoard::getCible()
{
	return cible;
}
int elemStoryBoard::getAddr()
{
	return addrCible;
}
int elemStoryBoard::getBlue()
{
	return blue;
}
int elemStoryBoard::getRed()
{
	return red;
}
int elemStoryBoard::getGreen()
{
	return green;
}
int elemStoryBoard::getWhite()
{
	return white;
}
int elemStoryBoard::getTime()
{
	return time;
}

void elemStoryBoard::setCible(string a)
{
	cible = a;
}
void elemStoryBoard::setAddr(int a)
{
	addrCible = a;
}
void elemStoryBoard::setBlue(int a)
{
	blue = a;
}
void elemStoryBoard::setRed(int a)
{
	red = a;
}
void elemStoryBoard::setGreen(int a)
{
	green = a;
}
void elemStoryBoard::setWhite(int a)
{
	white = a;
}
void elemStoryBoard::setTime(int a)
{
	time = a;
}

