#include "DMX.h"
#include <string>
#include <cstdlib>

using namespace std;

//Pour etre construit, l'objet DMX doit OBLIGATOIREMENT posseder une adresse de type DMX et un type
DMX::DMX(int address, string equipement)
{
	addr = address;
	type = equipement;
	
	if (type == "SPOTLED")
	{
		nbCanaux = 7;
	}
	
	else if (type == "BARRELED")
	{
		nbCanaux = 12;
	}
}

//On rempli le tableau qui contient les 512 valeur DMX selon l'adresse et le type de l'objet
//Le tableau sera rempli à des adresse différente, sur un nombre de canal différent et sur un
//protocol propre à chaque équipement
void DMX::remplirTab(int valeurDMX[], int red, int green, int blue, int white)
{
	if (type == "SPOTLED")
	{
		valeurDMX[addr]=255; //Fixe pour garder le mode DMX
		valeurDMX[addr+1]=red;
		valeurDMX[addr+2]=green;
		valeurDMX[addr+3]=blue;
		valeurDMX[addr+4]=white;
	}
	
	else if (type == "BARRELED")
	{
		for(int i=0; i<=3;i=i+1)
		{
			valeurDMX[addr + (i*3)] = red;
			valeurDMX[addr + 1 +(i*3)] = green;
			valeurDMX[addr + 2 +(i*3)] = blue;
		}
	}
}

int DMX::getCanaux()
{
	return nbCanaux;
}

string DMX::getType()
{
	return type;
}

