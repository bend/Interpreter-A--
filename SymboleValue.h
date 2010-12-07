#ifndef SYMBOLEVALUE_H
#define SYMBOLEVALUE_H

#include <string.h>
#include <iostream>
using namespace std;

#include "valType.h"
#include "Symbole.h"
#include "Arbre.h"

class SymboleValue : public Symbole,  // un symbole valué est un symbole qui a une valeur, définie ou pas
                     public Noeud  {  // et c'est aussi une feuille de l'arbre abstrait


public:
	  SymboleValue(Symbole s); // construit un symbole valué à partir d'un symbole existant s
	  ~SymboleValue( ) {}
	  void        afficher (unsigned short indentation=0);                        // affiche le symbole en tant que noeud de l'arbre
	  inline ValType*  getValeur()              { return valeur;                     } // accesseur
	  inline void setValeur(ValType* valeur)    { this->valeur=valeur; defini=true;  } // accesseur
	  inline bool estDefini()              { return defini;                     } // accesseur
	  void affichageC();

	  friend ostream & operator << (ostream & cout, SymboleValue symb); // affiche un symbole value sur cout

private:
	  bool defini;	// indique si la valeur du symbole est définie
	  ValType *  valeur;	// valeur du symbole si elle est définie, zéro sinon
};

#endif /* SYMBOLEVALUE_H */
