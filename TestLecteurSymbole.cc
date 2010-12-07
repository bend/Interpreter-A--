#include "LecteurSymbole.h"
#include "Symbole.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	char nomFich[255];
	if (argc != 2) {
		cout << "Usage : " << argv[0] << " nom_fichier_source" << endl << endl ;
		cout << "Entrez le nom du fichier dont voulez-vous lire les symboles : ";
		cin.getline(nomFich,sizeof(nomFich));
	}
	else strncpy(nomFich, argv[1],sizeof(nomFich));

	LecteurSymbole ls(nomFich);
	while (ls.getSymCour()!="<FINDEFICHIER>") {
		cout << "J'ai lu : " << ls.getSymCour() << endl;
		ls.suivant();
	}
	cout << "J'ai lu : " << ls.getSymCour() << endl;

	return EXIT_SUCCESS;
}
