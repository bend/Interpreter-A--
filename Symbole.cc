#include <ctype.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "Symbole.h"

////////////////////////////////////////////////////////////////////////////////
Symbole::Symbole(string s) {
	this->chaine=s;
	// attention : l'ordre des tests ci-dessous n'est pas innocent !
	if      (s=="")         	this->categorie=FINDEFICHIER;
	else if (isEntier(s))		this->categorie=ENTIER;
	else if (isReel(s)) 		this->categorie=REEL;
	else if (isChaine(s))		this->categorie=CHAINE;
	else if (isMotCle(s))   	this->categorie=MOTCLE;
	else if (isCaractere(s))	this->categorie=CARACTERE;
	else if (isalpha(s[0])) 	this->categorie=VARIABLE;
	else                    	this->categorie=INDEFINI;
}


////////////////////////////////////////////////////////////////////////////////
Symbole::Symbole(char * ch) {
	Symbole(string(ch));
}

////////////////////////////////////////////////////////////////////////////////
bool Symbole::operator == (char *ch) {
	string s(ch);
	return  this->chaine==s                              		||
	       (this->categorie==MOTCLE	      && s=="<MOTCLE>") 	||
	       (this->categorie==VARIABLE     && s=="<VARIABLE>") 	||
	       (this->categorie==INDEFINI     && s=="<INDEFINI>") 	||
	       (this->categorie==ENTIER       && s=="<ENTIER>")   	||
	       (this->categorie==CHAINE	      && s=="<CHAINE>") 	||
	       (this->categorie==REEL         && s=="<REEL>")   	||
	       (this->categorie==CARACTERE    && s=="<CARACTERE>") 	||
	       (this->categorie==FINDEFICHIER && s=="<FINDEFICHIER>");
}



////////////////////////////////////////////////////////////////////////////////
bool Symbole::isMotCle(string s) {
	static vector <string> motsCles; // vecteur pour stocker les mots clés du langage
	// si on n'a pas encore chargé les mots clés dans le vecteur, on le fait !
	if (!motsCles.size()) {
		ifstream fichier(FICHIER_MOTS_CLE, ifstream::in);
		while (!fichier.eof()) {
			string mot;
			getline(fichier, mot);
			if (mot!="") { // insertion triée de s dans le vecteur des mots clés
  				vector<string>::iterator it = motsCles.begin();
  				while (it<motsCles.end() && *it < mot) it++;
  				if (it==motsCles.end() || *it != mot) // si pas trouvé...
    					motsCles.insert(it, mot);
			}
		}
		fichier.close();
	}
 	// on recherche  s dans le vecteur des mots clés triés
	unsigned int i;
	for (i=0; i<motsCles.size() && motsCles[i]<s; i++) ;
	return (i<motsCles.size() && motsCles[i]==s);
}

////////////////////////////////////////////////////////////////////////////////
bool Symbole::isCaractere(string s) {
	return (s[0]=='\'' && s.size()==3);
}

////////////////////////////////////////////////////////////////////////////////
bool Symbole::isChaine(string s) {
	return s[0]== '"';
}

////////////////////////////////////////////////////////////////////////////////
bool Symbole::isEntier(string s) {  // méthode de classe : renvoie vrai si s est un Entier
	bool estUnEntier = true;
	for(unsigned int i=0;i<s.size();i++)
		estUnEntier = estUnEntier && isdigit(s[i]);
	
	return estUnEntier;	

}

////////////////////////////////////////////////////////////////////////////////
bool Symbole::isReel(string s){ // méthode de classe : renvoie vrai si s est un Reel
	bool estUnReel = true;
	bool unPoint = false;

	for(unsigned int i=0;i<s.size();i++) {
		estUnReel = estUnReel && ( isdigit(s[i]) || ((s[i]== '.') && (!unPoint))) ;
		if(s[i] == '.')
			unPoint = true;	
	}
	return estUnReel;
}

////////////////////////////////////////////////////////////////////////////////
// Attention : cette fonction (operator << ) n'est pas membre de la classe Symbole
ostream & operator <<(ostream & cout, Symbole symb) {
	cout << "Symbole de type ";
	if      (symb.categorie==Symbole::MOTCLE)       cout << "<MOTCLE>      ";
	else if (symb.categorie==Symbole::VARIABLE)     cout << "<VARIABLE>    ";
	else if (symb.categorie==Symbole::REEL)         cout << "<REEL>        ";
	else if (symb.categorie==Symbole::INDEFINI)     cout << "<INDEFINI>    ";
	else if (symb.categorie==Symbole::CARACTERE)    cout << "<CARACTERE>   ";
	else if (symb.categorie==Symbole::CHAINE)       cout << "<CHAINE>      ";
	else if (symb.categorie==Symbole::ENTIER)       cout << "<ENTIER>      ";
	else if (symb.categorie==Symbole::FINDEFICHIER) cout << "<FINDEFICHIER>";
	cout << " : \"" << symb.chaine << "\"" ;
	return cout;
}
