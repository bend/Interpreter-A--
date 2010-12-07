#include "SymboleValue.h"
#include <stdlib.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
SymboleValue::SymboleValue(Symbole s) :
	Symbole(s.getChaine()) {
	if (s == "<ENTIER>") {
		ValTypeEntier * valEnt = new ValTypeEntier(atoi(s.getChaine().c_str())); // c_str convertit une string en char*
		valeur = dynamic_cast <ValType *> (valEnt);
		defini = true;
	} else if (s == "<CHAINE>") {
		ValTypeChaine * valCh = new ValTypeChaine(s.getChaine().c_str());
		valeur = dynamic_cast <ValType *> (valCh);
		defini = true;
	} else if (s == "<REEL>") {
		ValTypeReel * valReel = new ValTypeReel(atof(s.getChaine().c_str()));
		valeur = dynamic_cast <ValType *> (valReel);
		defini = true;
	} else if (s == "<CARACTERE>") {
		ValTypeCaractere * valChar = new ValTypeCaractere(s.getChaine()[1]);
		valeur = dynamic_cast <ValType *> (valChar);
		defini = true;
	} else {
		valeur = 0;
		defini = false;
	}
}

////////////////////////////////////////////////////////////////////////////////
void SymboleValue::afficher(unsigned short indentation) {
	Noeud::afficher(indentation);
	cout << "Feuille - Symbole value : " << getChaine() << endl; // on affiche la chaine du symbole
}

void SymboleValue::affichageC () {
	cout << getChaine();
}

////////////////////////////////////////////////////////////////////////////////
// Attention : cette fonction (operator) n'est pas membre de la classe SymboleValue
ostream & operator <<(ostream & cout, SymboleValue symb) {
	cout << (Symbole) symb << "\t\t - Valeur=";
	if (symb.defini) {
		symb.valeur->afficher();
		cout << ""; 
	}
	else
		cout << "indefinie ";
	return cout;
}
