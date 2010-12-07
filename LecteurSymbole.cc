#include "LecteurSymbole.h"
#include <ctype.h>
#include <string.h>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
LecteurSymbole::LecteurSymbole(char nom_fich[]) :
	lc(nom_fich), symCour("") {
	suivant(); // pour lire le premier symbole
}

////////////////////////////////////////////////////////////////////////////////
void LecteurSymbole::suivant() {
	sauterSeparateurs();
	sauterCommentaires();
	// on est maintenant positionne sur le premier caractère d'un symbole
	ligne=lc.getLigne();
	colonne=lc.getColonne();
	symCour=Symbole(motSuivant()); // on reconstruit symCour avec le nouveau mot lu
}

////////////////////////////////////////////////////////////////////////////////
void LecteurSymbole::sauterSeparateurs() {
	while (lc.getCarCour()==' '  || 
		   lc.getCarCour()=='\t' || 
		   lc.getCarCour()=='\r' || 
		   lc.getCarCour()=='\n')
		lc.suivant();
}

////////////////////////////////////////////////////////////////////////////////
void LecteurSymbole::sauterCommentaires() {
	if (lc.getCarCour()=='#') {
		do {
			lc.suivant();
		} while (lc.getCarCour() != '\n');
		sauterSeparateurs();
		if(lc.getCarCour()=='#')
			sauterCommentaires();
	}
}

////////////////////////////////////////////////////////////////////////////////
string LecteurSymbole::motSuivant() {
	static string  s;
	s="";
	if (isdigit(lc.getCarCour()))
		// c'est le début d'un entier ou d'un reel
		do {
			s=s+lc.getCarCour();
			lc.suivant();
		} while (isdigit(lc.getCarCour()) || lc.getCarCour() == '.');

	else if (isalpha(lc.getCarCour()))
		// c'est le début d'un mot
		do {
			s=s+lc.getCarCour();
			lc.suivant();
		} while (isalpha(lc.getCarCour())  || 
				 isdigit(lc.getCarCour()) || 
				 lc.getCarCour()=='_');
	else if (symCour.isChaine(lc.getCarCour())) {
		// c'est le debut d'une chaine de caractères
		do {
			s=s+lc.getCarCour();
			lc.suivant();
		} while(!symCour.isChaine(lc.getCarCour()) && lc.getCarCour()!=EOF);
			s=s+lc.getCarCour();
			lc.suivant();
	}
	else if(lc.getCarCour()=='\'')  // c'est un caractere
		for(int i=0; i<3 ; i++) {
		s+=lc.getCarCour();
		lc.suivant();
		}
	else if (lc.getCarCour()!=EOF)
	// c'est un caractere special
	{
		s=lc.getCarCour();
		lc.suivant();
		if(lc.getCarCour()=='=') {
			s=s+lc.getCarCour();
			lc.suivant();
		}
	}
	return s;
}

