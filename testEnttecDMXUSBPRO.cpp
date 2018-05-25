//Programme serveur commande projo et lyre

#include <iostream>
#include <iomanip>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#include <thread>

#include <cstdio>
#include <cstdlib>

#include "DMX.h"
#include "storyboard.h"
#include "Socket.h"
#include "json.h"
#include "enttecdmxusb.h"
#include "fichierJSON.h"
#include "threadServeur.h"
#include "couleur.h"
#include "threadDMX.h"

using namespace std;

#define DMXDEVICE "/dev/ttyUSB0"

int main()
{
	//On crée l'objet interface DMX
    cout << "Peripherique : " << DMXDEVICE << endl;
    EnttecDMXUSB *interfaceDMX;
    interfaceDMX = new EnttecDMXUSB(DMX_USB_PRO, "/dev/ttyUSB0");
    bool test = interfaceDMX->IsAvailable();
	
    if(test)//On verifie si l'interface DMX est OK
    {
		//On prépare valeures présentes dans le fichier de config
		json_value* value = fichierJSON::ouvrirJSON("config.json");
	
		int PORTDISTANT = atoi(fichierJSON::getName(value, "PORTDISTANT").c_str());
		int PORT = atoi(fichierJSON::getName(value, "PORT").c_str());
		
		//On verifie que les ports sont bien renseigne sinon on arrete le programme
		if (PORTDISTANT < 0 || PORTDISTANT> 65536)
		{
			cout << "PORT DISTANT MAL RENSEIGNER, VERIFIER LE FICHIER \"config.json\"" << endl;
			return 1;
		}
		
		if (PORT < 0 || PORT> 65536)
		{
			cout << "PORT MAL RENSEIGNER, VERIFIER LE FICHIER \"config.json\"" << endl;
			return 1;
		}
		
		cout << "Port serveur : " << PORT << endl;
		cout << "Port client : " << PORTDISTANT << endl;
		
		fichierJSON::fermerJSON(value);
		
		//On crée le socket qui permettra de communiquer en reseau avec les application
		Socket *mySocket = new Socket();
		//On lui applique les valeurs qu'on a extraite du fichier de config
		mySocket->setDescripteur(PF_INET,SOCK_DGRAM,0);
		mySocket->setPdrLocal(PF_INET, htons(PORT), htonl(INADDR_ANY));
		mySocket->setPdrDistant(0, htons(PORTDISTANT), 0);
		mySocket->bindSocket();
		
		cout << endl << "serveur lance" << endl << endl;
		
		//On scinde le programme en 2 fonction qui s'executent de façon simultannées
		int accesFichier = 0;
		
		thread first(threadServeur::start, mySocket, &accesFichier); //Le serveur qui attend des message et les copie dans un fichier .json
		thread second(threadDMX::start, mySocket, interfaceDMX, &accesFichier);//Une fonction qui permet de lire en permanence ce fichier et qui va gerer les spots
		
		//On attend que les 2 fonctions soient termiénes avant de finir le programme
		first.join();
		second.join();
		cout << "Execution des threads terminée " << endl;
		
	}
    delete interfaceDMX;
	
	return 0;
}
