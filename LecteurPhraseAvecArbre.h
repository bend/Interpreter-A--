#ifndef LECTEURPHRASEAVECARBRE_H_
#define LECTEURPHRASEAVECARBRE_H_

#include "Symbole.h"
#include "LecteurSymbole.h"
#include "TableSymboles.h"
#include "Arbre.h"

class LecteurPhraseAvecArbre
{
public:
	LecteurPhraseAvecArbre(char nomFich[]);	 // Construit un lecteur de phrase pour interpreter
	                                         //  le programme dans le fichier nomFich

	void analyse();  // Si le contenu du fichier est conforme à la grammaire,
	                 //   cette méthode se termine normalement et affiche un message "Syntaxe correcte".
                         //   la table des symboles (ts) et l'arbre abstrait (arbre) auront été construits
	                 // Sinon, le programme sera interrompu (exit).

	inline TableSymboles getTs ()    { return ts;    } // accesseur	
	inline Noeud*        getArbre () { return arbre; } // accesseur
        inline bool 	     getErreurs () { return erreurs; } // accesseur
	

private:
    LecteurSymbole ls;    // le lecteur de symboles utilisé pour analyser le fichier
    TableSymboles  ts;    // la table des symboles valués
    Noeud*         arbre; // l'arbre abstrait
    bool	   erreurs;
    char	   fichier[];

    // implémentation de la grammaire
    Noeud*  programme();   //   <programme> ::= debut <seqInst> fin FIN_FICHIER
    Noeud*  seqInst();	   //     <seqInst> ::= <inst> ; { <inst> ; }
    Noeud*  inst();	       //        <inst> ::= <affectation>
    Noeud*  affectation(); // <affectation> ::= <variable> = <expression>
    Noeud*  expression();  //  <expression> ::= <facteur> { <opBinaire> <facteur> }
    Noeud*  facteur();     //     <facteur> ::= <entier>  | <chaine> | <variable>  |  <opUnaire> <expBool>  |  ( <expBool> ) 
    Noeud*  instSi();	   //      <instSi> ::= si ( <expBool> ) <seqInst> { sinonsi ( <expBool> ) <seqInst> } [sinon <seqInst> ] finsi
    Noeud*  instTq();	   //      <instTq> ::= tantque (<expBool>) <seqInst> fintantque
    Noeud*  instRepeter(); // <instRepeter> ::= repeter <seqInst> jusqua ( <expBool> )
    Noeud*  instPour();    //    <instPour> ::= pour ( <variable> <expBool> <affectation> ) <seqInst> finpour
    Noeud*  instLire();	   //     <instLire> ::= lire(<variable>)
    Noeud*  instEcrire();  //  <instEcrire> ::= ecrire ( <expression> | <chaine> )
    Symbole opAdd();       //       <opAdd> ::= + | -
    Symbole opMult();      //      <opMult> ::= * | /
    Noeud*  terme();       //       <terme> ::= <facteur> { <opMult> <facteur> }
    Noeud*  expBoolInt();  //  <expBoolInt> ::= <relation> { <opOu> <relation> }
    Symbole opOu();        //        <opOu> ::= ou
    Symbole opEt();        //        <opEt> ::= et
    Noeud*  expBool();     //     <expBool> ::= <expBoolInt> { <opEt> <expBoolInt> }	
    Noeud*  relation();    //    <relation> ::= <expression> { <opRel> <expression> }
    Noeud*  instSauterLigne();    //    saute une ligne
    Symbole opRel();       //       <opRel> ::= == | != | < | <= | > | >=
    Symbole opUnaire();    //    <opUnaire> ::= - | non
    
    // outils pour se simplifier l'analyse syntaxique
    bool testerSymCour (char *ch);  // si symbole courant != ch, erreur : on arrete le programme, sinon rien
    bool sauterSymCour (char *ch);  // si symbole courant == ch, on passe au symbole suivant, sinon erreur : on arrete
    void erreur (char mess[]);      // affiche les message d'erreur mess 
};

#endif /* LECTEURPHRASEAVECARBRE_H_ */
