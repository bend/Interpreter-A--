// Contient toutes les spécifications de classes nécessaires
// pour représenter l'arbre abstrait
#ifndef ARBRE_H_
#define ARBRE_H_

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Symbole.h"
#include "valType.h"

////////////////////////////////////////////////////////////////////////////////
class Noeud {
// classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
// Remarque : la classe ne contient aucun constructeur
  public:
    virtual ValType *  getValeur() =0 ; // méthode pure (non implémentée) qui rend la classe abstraite
    virtual void afficher(unsigned short indentation=0) { cout << setw(4*indentation) << " "; }
      // pour afficher un noeud avec un décalage (indentation) proportionnel à son niveau dans l'arbre
    virtual void affichageC() {} ;

    virtual ~Noeud() {} // présence d'un destructeur virtuel conseillée dans les classes abstraites
};

////////////////////////////////////////////////////////////////////////////////
class NoeudSeqInst : public Noeud {
// classe pour représenter un noeud "sequence d'instruction"
// qui a autant de fils que d'instructions dans la séquence
  public:
    NoeudSeqInst();   // construit une séquence d'instruction vide
    ~NoeudSeqInst() {} // à cause du destructeur virtuel de la classe Noeud
    ValType * getValeur(); // évalue chaque instruction de la séquence
    void afficher(unsigned short indentation=0); // affiche la séquence d'instructions
    void ajouteInstruction(Noeud* instruction);  // ajoute une instruction à la séquence
    void affichageC(); // Affiche en langage C++

  private:
    vector<Noeud *> tabInst; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstSi : public Noeud {
// classe pour représenter un noeud "instruction si" 
// 
public:
	NoeudInstSi(Noeud* cond, Noeud* alors, Noeud* sinon);
	~NoeudInstSi() {}
	ValType * getValeur();
	void afficher(unsigned short indentation=0);
	void setSuite(Noeud* suite);
   	void affichageC(); // Affiche en langage C++
	
private:
	Noeud* cond; 
	Noeud* alors;
	Noeud* sinon;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudAffectation : public Noeud {
// classe pour représenter un noeud "affectation"
// composé de 2 fils : la variable et l'expression qu'on lui affecte
  public:
     NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation
    ~NoeudAffectation() {} // à cause du destructeur virtuel de la classe Noeud
    ValType * getValeur(); // évalue l'expression et affecte sa valeur à la variable
    void afficher(unsigned short indentation=0); // affiche l'affectation
    void affichageC(); // Affiche en langage C++

  private:
    Noeud* variable;
    Noeud* expression;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudIteration : public Noeud {
// classe pour representer un noeud iteratif
// composé de 2 fils, la condition et la sequence d'instruction
public:
	NoeudIteration(Noeud* cond, Noeud* seqInst); // construit une iteration
	~NoeudIteration() {} // a cause du destructeur virtuel de la classe Noeud
	ValType * getValeur(); 
	void afficher(unsigned short indentation=0);
    	void affichageC(); // Affiche en langage C++
protected:
	Noeud* condition;
	Noeud* seqInst;	
};

////////////////////////////////////////////////////////////////////////////////
class NoeudPour : public NoeudIteration {
public:
	NoeudPour(Noeud* cond, Noeud* seqInst,Noeud* var, Noeud* incre);
	~NoeudPour() {}
	ValType * getValeur();
	void afficher(unsigned short indentation=0);
    	void affichageC(); // Affiche en langage C++
private:
	Noeud* varBoucle;
	Noeud* incrementation;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudRep : public NoeudIteration {
public:
	NoeudRep(Noeud* cond, Noeud* seqInst);
	~NoeudRep() {}
	ValType * getValeur();
	void afficher(unsigned short indentation=0);
    	void affichageC(); // Affiche en langage C++
};

////////////////////////////////////////////////////////////////////////////////
class NoeudSauterLigne : public Noeud {
public:
	NoeudSauterLigne();
	~NoeudSauterLigne() {}
	ValType * getValeur();
	void afficher(unsigned short indentation=0);
	void affichageC(); // Affiche en langage C++
};



////////////////////////////////////////////////////////////////////////////////
class NoeudLire : public Noeud {
public:
	NoeudLire(Noeud* val);
	~NoeudLire() {}
	ValType * getValeur();
	void afficher(unsigned short indentation=0);
    	void affichageC(); // Affiche en langage C++
private:
	Noeud* variable;
	bool isChaine(string s); // renvoie vraie si s n'est ni un entier ni un r�el
	template <class T_class> ValType* ValeurLire(string valeurLue);
};

////////////////////////////////////////////////////////////////////////////////
class NoeudEcrire : public Noeud {
public:
	NoeudEcrire(Noeud* val);
	~NoeudEcrire() {}
	ValType * getValeur();
	void afficher(unsigned short indentation=0);
    	void affichageC(); // Affiche en langage C++
private:
	Noeud* valeur;
	string chaineSansQuotes(string brut);
};

////////////////////////////////////////////////////////////////////////////////
class NoeudOperateurBinaire : public Noeud {
  public:
    NoeudOperateurBinaire(Symbole op, Noeud* operandeG, Noeud* operandeD);
     // construit une opération binaire : operandeGauche operateur OperandeDroit
    virtual ~NoeudOperateurBinaire() {} // à cause du destructeur virtuel de la classe Noeud
    virtual ValType* getValeur() =0; // évalue l'operande gauche, l'operande droit et applique l'opérateur
    void afficher(unsigned short indentation=0); // affiche l'opération
    void affichageC(); // Affiche en langage C++
  protected:
    Symbole operateur;
    Noeud*  operandeGauche;
    Noeud*  operandeDroit;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudOperateurBinaireDeComparaison : public NoeudOperateurBinaire {

  public:
   	NoeudOperateurBinaireDeComparaison(Symbole op, Noeud* operandeG, Noeud* operandeD);
  	~NoeudOperateurBinaireDeComparaison() {}
	ValType* getValeur();
  private :
  	template <class T_class> ValType* ResultatOpBinaireDeComparaison(string op,ValType* og, ValType* od) ;
  	ValType* ResultatOpBinaireDeComparaisonEntier(string op,ValType* og, ValType* od) ;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudOperateurBinaireArithmetique : public NoeudOperateurBinaire {

  public:
    NoeudOperateurBinaireArithmetique(Symbole operateur, Noeud* operandeG, Noeud* operandeD);
    ~NoeudOperateurBinaireArithmetique() {} 
    ValType* getValeur();
  template <class T_class> ValType* ResultatOpBinaireArithmetique(string op,ValType* og, ValType* od) ;
  ValType* ResultatOpBinaireArithmetiqueChaine(string op,ValType* og, ValType* od) ;
};



////////////////////////////////////////////////////////////////////////////////
class NoeudOperateurUnaire : public Noeud {
// classe pour représenter un noeud "opération arithmétique" composé d'un opérateur (- non)
// et de 1 fils : l'opérande de droite
  public:
    NoeudOperateurUnaire(Symbole op, Noeud* operandeD);
     // construit une opération Unaire : operateur OperandeDroit
   ~NoeudOperateurUnaire() {    } // à cause du destructeur virtuel de la classe Noeud
    ValType* getValeur(); // évalue l'operande droit et applique l'opérateur
    void afficher(unsigned short indentation=0); // affiche l'opération
    void affichageC(); // Affiche en langage C++
  private:
    Symbole operateur;
    Noeud*  operandeDroite;
};

#endif /* ARBRE_H_ */
