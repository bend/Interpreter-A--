#include <iostream>
using namespace std;
#include "LecteurPhraseAvecTable.h"

int main(int argc, char* argv[]) {
	char nomFich[255];
	if (argc != 2) {
		cout << "Usage : " << argv[0] << " nom_fichier_source" << endl << endl;
		cout << "Entrez le nom du fichier que vous voulez analyser : ";
		cin.getline(nomFich, sizeof(nomFich));
	} else
		strncpy(nomFich, argv[1], sizeof(nomFich));

	LecteurPhraseAvecTable lp(nomFich);
	lp.analyse();        // on lance l'analyse
	cout << lp.getTs();  // on affiche la table des symboles
}
