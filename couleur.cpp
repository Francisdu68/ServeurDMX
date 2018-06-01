#include "fichierJSON.h"
#include "storyboard.h"
#include "DMX.h"
#include "enttecdmxusb.h"
#include "couleur.h"

#include <iostream>

using namespace std;

int couleur::setCouleur(EnttecDMXUSB *interfaceDMX, string cible, json_value *value)
{
	int ADRESSEDEBUT;
	
	int TAILLEBUSDMX = 512;
	
	int valeurDMX[TAILLEBUSDMX];//tableau contenant les Valeur des 512 canaux du bus DMX
	memset(valeurDMX,0x00, TAILLEBUSDMX);
	
	ADRESSEDEBUT = fichierJSON::getNameInt(value->u.object.values[0].value, "targetAddress");
	if(ADRESSEDEBUT<1 || ADRESSEDEBUT >512)
	{
		cout << "Adresse invalide, arret du traitement";
		return 0;
	}
	DMX equipement(ADRESSEDEBUT, cible);
	int NBCANAUX = equipement.getCanaux();
	
	int red = fichierJSON::getNameInt(value->u.object.values[0].value, "red");
	if(red<0 || red >255)
	{
		red = 0;
		cout <<" Valeur red invalide, mise par defaut à 0" << endl;
	}
	
	int green = fichierJSON::getNameInt(value->u.object.values[0].value, "green");
	if(green<0 || green >255)
	{
		green = 0;
		cout <<" Valeur green invalide, mise par defaut à 0" << endl;
	}
	
	int blue = fichierJSON::getNameInt(value->u.object.values[0].value, "blue");
	if(blue<0 || blue >255)
	{
		blue = 0;
		cout <<" Valeur blue invalide, mise par defaut à 0" << endl;
	}
	
	int white = fichierJSON::getNameInt(value->u.object.values[0].value, "white");
	if(white<0 || white >255)
	{
		white = 0;
		cout <<" Valeur white invalide, mise par defaut à 0" << endl;
	}
	
	equipement.remplirTab(valeurDMX, red, green, blue, white);
	
	for(int i=ADRESSEDEBUT; i<=ADRESSEDEBUT+NBCANAUX-1; i=i+1)
	{
		interfaceDMX->SetCanalDMX(i, valeurDMX[i]);
	}
	
	interfaceDMX->SendDMX();
	return 1;
}