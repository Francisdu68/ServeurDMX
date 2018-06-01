#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include "enttecdmxusb.h"
using namespace std;

Socket::Socket()
{
	longueurAdresse = sizeof(struct sockaddr_in);
	messageRecu = new char[256];
}

//On crée le canal de communication en definissant le protocal de communication
void Socket::setDescripteur(int a, int b, int c)
{
	descripteurSocket = socket(a, b, c);
	if(descripteurSocket < 0)
	{
		cerr << "socket";
		exit(-1);
	}
	else
	{
		cout <<"Socket cree avec succes" << endl;
	}
}

//On défini l'adresse IP et le port sur laquelle le serveur va recevoir les données
void Socket::setPdrLocal(short sinFamily, unsigned short sinPort, unsigned long sAddr)
{
	pointDeRencontreLocal.sin_family = sinFamily;
	pointDeRencontreLocal.sin_port = sinPort;
	pointDeRencontreLocal.sin_addr.s_addr = sAddr;
}

//On définit le port sur lequel le client attend la réponse
//L'adresse IP du client est, quant à elle, directement récupérée
//Lorsque celui ci envoie un message au serveur
void Socket::setPdrDistant(short sinFamily, unsigned short sinPort, unsigned long sAddr)
{
//	pointDeRencontreDistant.sin_family = sinFamily;
	pointDeRencontreDistant.sin_port = sinPort;
//	pointDeRencontreDistant.sin_addr.s_addr = sAddr;
}

void Socket::affichePdrDistant()
{
	cout << "sin_family = " << pointDeRencontreDistant.sin_family << endl;
	cout << "sin_port = " << pointDeRencontreDistant.sin_port << endl;
	cout << "sin_addr.s_addr = " << pointDeRencontreDistant.sin_addr.s_addr << endl;
}

void Socket::setMessage(char *a)
{
	messageRecu = a;
}

void Socket::setLus(int a)
{
	lus = a;
}

void Socket::setRetour(int a)
{
	retour = a;
}

int Socket::getDescripteur()
{
	return descripteurSocket;
}

struct sockaddr_in* Socket::getPdrLocal()
{
	return &pointDeRencontreLocal;
}

struct sockaddr_in* Socket::getPdrDistant()
{
	return &pointDeRencontreDistant;
}

socklen_t* Socket::getLgAddr2()
{
	return &longueurAdresse;
}

socklen_t Socket::getLgAddr()
{
	return longueurAdresse;
}

char* Socket::getMessage()
{
	return messageRecu;
}

int Socket::getLus()
{
	return lus;
}

int Socket::getRetour()
{
	return retour;
}

//Une fois le socket crée et les point de rencontre configurée (adresse ip et port )
//On attache le socket afin qu'il soit opérationnel et que les client puissent
//dialoguer avec lui
void Socket::bindSocket()
{
	int a;
	a = bind(descripteurSocket, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse);
	if(a < 0)
	{
		cerr <<"bind";
		exit(-2);
	}
	else
	{
		cout << "Socket attache avec succes"<< endl;
	}
}

void Socket::closeDescripteur()
{
	close(descripteurSocket);
}

Socket::~Socket()
{
	
	delete messageRecu;
}

void Socket::sendACK(string a)
{
	char reponse[100];
	memset(reponse, 0x00, 100*sizeof(char));
	strcpy(reponse, a.c_str());
	sendto(descripteurSocket, reponse,sizeof(reponse), 0, (struct sockaddr *)&pointDeRencontreDistant, longueurAdresse);
}








