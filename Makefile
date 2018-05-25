all:
	g++ -o json.o -c json.cpp
	g++ -o Fragment.o -c Fragment.cpp
	g++ -o elemStoryBoard.o -c elemStoryBoard.cpp
	g++ -o storyboard.o -c storyboard.cpp
	g++ -o fichierJSON.o -c fichierJSON.cpp
	g++ -o DMX.o -c DMX.cpp
	g++ -o enttecdmxusb.o -c enttecdmxusb.cpp
	g++ -o rs232.o -c rs232.cpp
	g++ -o Socket.o -c Socket.cpp
	g++ -o couleur.o -c couleur.cpp
	g++ -o testEnttecDMXUSBPRO.o -c testEnttecDMXUSBPRO.cpp -std=c++11
	g++ -pthread -o serveur Socket.o Fragment.o enttecdmxusb.o rs232.o testEnttecDMXUSBPRO.o DMX.o elemStoryBoard.o storyboard.o json.o fichierJSON.o couleur.o
	./serveur
