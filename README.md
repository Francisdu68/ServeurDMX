# DMX Server

## Installation sur un autre raspberry pi
Télécharger l’éxecutable « serveur » et le fichier « config.json »

Les copier sur une autre raspberry pi grâce à une clé usb ou au logiciel winSCP.

Faire la commande « chmod a+x serveur » pour donner les droits d’exécution.

L’application est installée est prête à être lancée.

## Lancement du serveur

Au démarrage du raspberry, taper la commande « vncserver :1 », puis lancez vnc sur votre ordinateur

Une fois vnc lancé, ouvrir une invite de commande.

Aller dans le dossier de l’exécutable grâce à la commande « cd » (dans notre cas l’exécutable est dans le dossier « exeServeur ») et faire la commande « ./serveur »

Le serveur est lancé et attend de recevoir un message pour commencer à contrôler les éléments scéniques
