#include "fichierJSON.h"
#include "storyboard.h"
#include "DMX.h"
#include "enttecdmxusb.h"
//#include "Socket.h"
#include "couleur.h"
/*
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/types.h>*/
#include <iostream>

using namespace std;
/*
int couleur::setCouleurProjo(EnttecDMXUSB *interfaceDMX, DMX *projo, json_value *value, int valeurDMX[])
{
	int NBCANAUXPROJO = 12;
	
	//On cherche avant tout la cible du message
	int ADRESSEDEBUTPROJO;	
	ADRESSEDEBUTPROJO = fichierJSON::getNameInt(value->u.object.values[0].value, "targetAddress");
	if(ADRESSEDEBUTPROJO<1 || ADRESSEDEBUTPROJO >(512-NBCANAUXPROJO))
	{
		cout << "Adresse invalide, arret du traitement";
		return 0;
	}
	projo = new DMX(ADRESSEDEBUTPROJO, "PROJO");
	
	int red = fichierJSON::getNameInt(value->u.object.values[0].value, "red");
	if(red<0 || red >255)
	{
		red = 0;
		cout <<" Valeur red invalide, mise par defaut à 0" << endl;
	}
	int green = fichierJSON::getNameInt(value->u.object.values[0].value, "green");
	if(green<0 || green >255)
	{
		green =0;
		cout <<" Valeur green invalide, mise par defaut à 0" << endl;
	}
	int blue = fichierJSON::getNameInt(value->u.object.values[0].value, "blue");
	if(blue<0 || blue >255)
	{
		blue = 0;
		cout <<" Valeur blue invalide, mise par defaut à 0" << endl;
	}
	
	//On rempli le tableau valeurDMX à partir de l'adresse du projo et des valeurs qu'on lui defini
	projo->remplirTab(valeurDMX, red, green, blue, 0);

	for(int i=ADRESSEDEBUTPROJO; i <=ADRESSEDEBUTPROJO+NBCANAUXPROJO - 1; i=i+1)
	{
		//On prepare la trame DMX avec les valeur a envoyer au boitier DMX a partir des valeurs du tableau
		interfaceDMX->SetCanalDMX(i, valeurDMX[i]);
	}
	interfaceDMX->SendDMX();//on envoie la trame DMX au boitier
	return 1;
}

int couleur::setCouleurLyre(EnttecDMXUSB *interfaceDMX, DMX *lyre, json_value *value, int valeurDMX[])
{
	int NBCANAUXLYRE = 7;
	int ADRESSEDEBUTLYRE;
	
	ADRESSEDEBUTLYRE = fichierJSON::getNameInt(value->u.object.values[0].value, "targetAddress");
	if(ADRESSEDEBUTLYRE<1 || ADRESSEDEBUTLYRE >512)
	{
		cout << "Adresse invalide, arret du traitement";
		return 0;
	}
	lyre = new DMX(ADRESSEDEBUTLYRE, "LYRE");
	
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
	
	lyre->remplirTab(valeurDMX, red, green, blue, white);
	
	for(int i=ADRESSEDEBUTLYRE; i<=ADRESSEDEBUTLYRE+NBCANAUXLYRE-1; i=i+1)
	{
		interfaceDMX->SetCanalDMX(i, valeurDMX[i]);
	}
	
	interfaceDMX->SendDMX();
	return 1;
}
*/
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