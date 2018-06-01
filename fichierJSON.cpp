#include "fichierJSON.h"
#include <string>
#include <cstring>
#include <iostream>
#include "json.h"

using namespace std;

//Rechercher la valeur associer à un nom donné.
string fichierJSON::getName(json_value* value, string name)
{
	int length, x;
	
	if (value == NULL) 
	{
		cout << "value = NULL";
		return "";
	}
	length = value->u.object.length;

	for (x = 0; x < length; x++) 
	{
		string n = "";
		string v = "";
		try
		{
			n = value->u.object.values[x].name;
			if(value->u.object.values[x].value->type == json_string)
			{
				v = value->u.object.values[x].value->u.string.ptr;
			}
			
		}
		catch(exception &e)
		{
			cerr << e.what() << endl;
		}
		
		if(n == name)
		{
			return v;
		}
	}
	return "pas  de valeur coresepondante a ce nom";
}


int fichierJSON::getNameInt(json_value* value, string name)
{
	int length, x;
	
	if (value == NULL) 
	{
		cout << "value = NULL\n";
		return 0;
	}
	length = value->u.object.length;

	for (x = 0; x < length; x++) 
	{
		string n = value->u.object.values[x].name;
		int v = value->u.object.values[x].value->u.integer;
		
		if(n == name)
		{
			return v;
		}
	}
	return 0;
}

bool fichierJSON::getNameBool(json_value* value, string name)
{
	int length, x;
	
	if (value == NULL) 
	{
		cout << "value = NULL";
		return false;
	}
	length = value->u.object.length;

	for (x = 0; x < length; x++) 
	{
		string n = value->u.object.values[x].name;
		bool v = value->u.object.values[x].value->u.boolean;
		
		if(n == name)
		{
			return v;
		}
	}
	return false;
}

//Appliquer la configuration du serveur et des équipement
void fichierJSON::setConfig(json_value* value, int &port, int &portDistant, int &nbCanauxProjo, int &nbCanauxLyre, int &tailleBusDMX)
{
	if(getName(value, "PORT")!="")
	{
		port = atoi(getName(value, "PORT").c_str());
	}
	
	if(getName(value, "PORTDISTANT")!="")
	{
		portDistant = atoi(getName(value, "PORTDISTANT").c_str());
	}
}

//Ouvrir le fichier JSOn avant de pouvoir l'utiliser
//On vérifie qu'il est correct et si c'est le cas on affiche son contenu
json_value* fichierJSON::ouvrirJSON(string fileName)
{
        char* filename = new char[fileName .length() + 1];
		strcpy(filename , fileName .c_str());
	
        FILE* fp;
        struct stat filestatus;
        int file_size;
        char* file_contents;
        json_char* json;
        json_value* value;

        if ( stat(filename, &filestatus) != 0) {
			cout << "File "<< filename <<" not found\n";
			return NULL;
        }
        file_size = filestatus.st_size;
        file_contents = (char*)malloc(filestatus.st_size);
        if ( file_contents == NULL) {
			cout << "Memory error: unable to allocate "<<file_size<<" bytes\n";
			return NULL;
        }

        fp = fopen (filename, "r");
        if (fp == NULL) {
			cout << "Unable to open "<<filename<<endl;
			fclose (fp);
			free(file_contents);
			return NULL;
        }
        if ( fread(file_contents, file_size, 1, fp) != 1 ) {
			cout << "Unable t read content of "<<filename<<endl;
			fclose (fp);
			free(file_contents);
			return NULL;
        }
        fclose (fp);

        json = (json_char*)file_contents;

        value = json_parse(json,file_size);

        if (value == NULL) {
                cout << "Unable to parse data\n";
                free(file_contents);
                return NULL;
        }
		free(file_contents);
	return value;
}

//Une fois que le fichier à fini d'être utilisé,
//Il ne faut pas oubleir de le fermer
void fichierJSON::fermerJSON(json_value* value)
{
	json_value_free(value);
}
