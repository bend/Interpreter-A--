#include "LecteurPhraseSimple.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	char nomFich[255];
	if (argc != 2) {
		cout << "Usage : " << argv[0] << " nom_fichier_source" << endl << endl;
		cout << "Entrez le nom du fichier que vous voulez analyser : ";
		cin.getline(nomFich, sizeof(nomFich));
	} else
		strncpy(nomFich, argv[1], sizeof(nomFich));

	LecteurPhraseSimple lp(nomFich);
	lp.analyse();
}
