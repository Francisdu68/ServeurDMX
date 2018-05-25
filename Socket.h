#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class Socket
{
	int descripteurSocket;
	struct sockaddr_in pointDeRencontreLocal;
	struct sockaddr_in pointDeRencontreDistant;
	socklen_t longueurAdresse;
	char* messageRecu;
	int lus;
	int retour;

public:
	Socket();

	void setDescripteur(int, int, int);

	void setPdrLocal(short , unsigned short , unsigned long );
	void setPdrDistant(short , unsigned short , unsigned long );
	void affichePdrDistant();
	void setMessage(char *);
	void setRetour(int );
	void setLus (int);
	int getDescripteur();
	
	void sendACK(string);
	
	
	struct sockaddr_in *getPdrLocal();
	struct sockaddr_in *getPdrDistant();
	socklen_t getLgAddr();
	socklen_t* getLgAddr2();
	char* getMessage();
	int getLus();
	int getRetour();
	void bindSocket();
	void closeDescripteur();
	~Socket();
};

