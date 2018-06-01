#include <iostream>
#include <iomanip>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <algorithm>

#include "Fragment.h"
//#include "fichierJSON.h"

#define LG_MESSAGE 1024

class threadServeur
{
public:
	static void start(Socket *mySocket, int *accesFichier)
	{
		while (1)
		{
			char message[LG_MESSAGE];//On initialise le message que le serveur va recevoir
			memset(message, 0x00, LG_MESSAGE*sizeof(char));//On le remet à 0 à chaque fois
			
			//On attend un ordre d'un client
			mySocket->setLus(recvfrom(mySocket->getDescripteur(), message, sizeof(message),0,(struct sockaddr*)mySocket->getPdrDistant(), mySocket->getLgAddr2()));
			cout << "\nmessage recu : " << message << endl << endl;
			string 	str = message;
			
			FILE* fichier = NULL;
			fichier = fopen("temp.json", "w");
			fprintf(fichier, str.c_str());
			fclose(fichier);
			
			json_value* value1 = fichierJSON::ouvrirJSON("temp.json");
			if (value1 != NULL)
			{
				bool isFragmented = fichierJSON::getNameBool(value1, "isFragmented");
				
				fichierJSON::fermerJSON(value1);
				
				if (isFragmented == false)
				{
					while(*accesFichier != 1)
					{
					}
					json_value* value1 = fichierJSON::ouvrirJSON("temp.json");
					if (value1 != NULL)
					{
						string m = fichierJSON::getName(value1, "data");
						
						FILE* fichier = NULL;
						fichier = fopen("temp2.json", "w");
						fprintf(fichier, m.c_str());
						fclose(fichier);
						
						
						json_value* value2 = fichierJSON::ouvrirJSON("temp2.json");
						if (value2 != NULL)
						{
							string n = value2->u.object.values[0].name;
							if(n == "command")
							{
								if (*accesFichier == 1) //Si le fichier est accessible
								{
									json_value* value = fichierJSON::ouvrirJSON("test.json");
									if (value != NULL)
									{
										string nom = value->u.object.values[0].name;
										if (nom == "storyboard")//On regarde si c'est une storyboard ou un changement de couleur qui a été envoyé
										{
											string ack = "{\"nomStory\":\"" + fichierJSON::getName(value->u.object.values[0].value, "name") + "\"}";
											mySocket->sendACK(ack);
										}
										else
										{
											mySocket->sendACK("-4");//Commande non valable
										}
									}
									else
									{
										mySocket->sendACK("-2");
									}
									fichierJSON::fermerJSON(value);
								}
							}
							else
							{
								if (*accesFichier == 1) //Si le fichier est accessible
								{
									string m = fichierJSON::getName(value1, "data");
									FILE* fichier = NULL;
									fichier = fopen("test.json", "w");
									fprintf(fichier, m.c_str());
									fclose(fichier);
									
									json_value* value = fichierJSON::ouvrirJSON("test.json");
									
									if (value != NULL)//Si le fichier n'est pas vide
									{
										string n = value->u.object.values[0].name;
										if (n == "storyboard" || n == "couleur")//On regarde si c'est une storyboard ou un changement de couleur qui a été envoyé
										{
											mySocket->sendACK("0");//Si c'est le cas alors on renvoie au client que le message reçu est correcte
										}
										else//Si ce n'est pas l'un des 2 alors on renvoie un mesasge d'erreur au client
										{
											mySocket->sendACK("-3");
										}
									}
									else
									{
										mySocket->sendACK("-2");
									}
									fichierJSON::fermerJSON(value);
									*accesFichier = 0;//Le fichier sera accessible par le thread DMX
								}
							}
						}
						else
						{
							mySocket->sendACK("-2");
						}
						fichierJSON::fermerJSON(value2);
					}
					else
					{
						mySocket->sendACK("-2");
					}
					fichierJSON::fermerJSON(value1);
				}
				else
				{
					json_value* value1 = fichierJSON::ouvrirJSON("temp.json");
					if (value1 != NULL)
					{
						bool erreurFrag = false;
						vector<Fragment> vectFragments;
						string strData = "";
						string data = fichierJSON::getName(value1, "data");
						int index = fichierJSON::getNameInt(value1, "index");
						Fragment fragment(index, data);
						vectFragments.push_back(fragment);
						
						int nbPacket = fichierJSON::getNameInt(value1, "packetCount");
						fichierJSON::fermerJSON(value1);
						
						for (int i =1; i< nbPacket; i++)
						{
							memset(message, 0x00, LG_MESSAGE*sizeof(char));//On le remet à 0 à chaque fois
							mySocket->setLus(recvfrom(mySocket->getDescripteur(), message, sizeof(message),0,(struct sockaddr*)mySocket->getPdrDistant(), mySocket->getLgAddr2()));
							cout << "message recu : " << message << endl;
							str = message;
							
							FILE* fichier = NULL;
							fichier = fopen("temp.json", "w");
							fprintf(fichier, str.c_str());
							fclose(fichier);
							
							json_value* value1 = fichierJSON::ouvrirJSON("temp.json");
							if (value1 != NULL)
							{
								data = fichierJSON::getName(value1, "data");
								index = fichierJSON::getNameInt(value1, "index");
								fragment.setIndex(index);
								fragment.setData(data);
								vectFragments.push_back(fragment);
							}
							fichierJSON::fermerJSON(value1);
							
						}
						if(vectFragments.size()==nbPacket)
						{
							sort(vectFragments.begin(), vectFragments.end());
							for(int i =0; i< vectFragments.size(); i++)
							{
								strData.append(vectFragments[i].getData());
								cout << "strdata :\" " << strData << " \"" << endl; 
							}
						}
						
						else
						{
							erreurFrag = true;
						}

						if (erreurFrag == false)
						{
							//Stocker le message dans un fichier json
							while(*accesFichier != 1)
							{
							}
							if (*accesFichier == 1) //Si le fichier est accessible
							{
								FILE* fichier = NULL;
								fichier = fopen("test.json", "w");
								fprintf(fichier, strData.c_str());
								fclose(fichier);
								
								json_value* value = fichierJSON::ouvrirJSON("test.json");
								
								if (value != NULL)//Si le fichier n'est pas vide
								{
									string n = value->u.object.values[0].name;
									if (n == "storyboard" || n == "couleur")//On regarde si c'est une storyboard ou un changement de couleur qui a été envoyé
									{
										mySocket->sendACK("0");//Si c'est le cas alors on renvoie au client que le message reçu est correcte
									}
									else//Si ce n'est pas l'un des 2 alors on renvoie un mesasge d'erreur au client
									{
										mySocket->sendACK("-3");
									}
								}
								else
								{
									mySocket->sendACK("-2");
								}
								fichierJSON::fermerJSON(value);
								
								*accesFichier = 0;//Le fichier sera accessible par le thread DMX
							}
						}
						else
						{
							mySocket->sendACK("-1");
						}
					}
					else
					{
						fichierJSON::fermerJSON(value1);
					}
				}
			}
			else 
			{
				fichierJSON::fermerJSON(value1);
				mySocket->sendACK("-2");
			}
		}
	}
};