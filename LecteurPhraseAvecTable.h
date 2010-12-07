#ifndef LECTEURPHRASEAVECTABLE_H_
#define LECTEURPHRASEAVECTABLE_H_

#include "LecteurSymbole.h"
#include "TableSymboles.h"

class LecteurPhraseAvecTable {
public:
	LecteurPhraseAvecTable(char nomFich[]);	// Construit un lecteur de phrase pour vérifier
	                                        // la syntaxe du programme dans le fichier nomFich

	void analyse();   // Si le contenu du fichier est conforme à la grammaire,
	                  //   cette méthode se termine normalement et affiche un message "Syntaxe correcte".
                          //   la table des symboles (ts) aura été construite
	                  // Sinon, le programme sera interrompu (exit).
	inline TableSymboles getTs ()   { return ts; } // accesseur

private:
    LecteurSymbole ls;  // le lecteur de symboles utilisé pour analyser le fichier
    TableSymboles  ts;  // la table des symboles valués

    // implémentation de la grammaire
    void programme();   //   <programme> ::= debut <seqInst> fin <EOF>
    void seqInst();	//     <seqIns>  ::= <inst> ; { <inst> ; }
    void inst();	//        <inst> ::= <affectation> | <instSi> | <instTq> | <instRepeter> | <instEcrire> | <instLire>
    void affectation();	// <affectation> ::= <variable> = <expression>
    void expression();	//  <expression> ::= <terme> { <opAdd> <terme> }
    void facteur();     //     <facteur> ::= <entier>  | <chaine> | <variable>  |  <opUnaire> <expBool>  |  ( <expBool> )
    void instSi();	//      <instSi> ::= si ( <expBool> ) <seqInst> { sinonsi ( <expBool> ) <seqInst> } [sinon <seqInst> ] finsi
    void instTq();	//      <instTq> ::= tantque (<expBool>) <seqInst> fintantque
    void instRepeter(); // <instRepeter> ::= repeter <seqInst> jusqua ( <expBool> )
    void instPour();    //    <instPour> ::= pour ( <variable> <expBool> <affectation> ) <seqInst> finpour
    void instLire();	//     <instLire ::= lire(<variable>)
    void instEcrire();  //  <instEcrire> ::= ecrire ( <expression> | <chaine> )
    void opAdd();       //       <opAdd> ::= + | -
    void opMult();      //      <opMult> ::= * | /
    void terme();       //       <terme> ::= <facteur> { <opMult> <facteur> }
    void expBoolInt();  //  <expBoolInt> ::= <relation> { <opOu> <relation> }
    void opOu();        //        <opOu> ::= ou
    void opEt();        //        <opEt> ::= et
    void expBool();     //     <expBool> ::= <expBoolInt> { <opEt> <expBoolInt> }	
    void relation();    //    <relation> ::= <expression> { <opRel> <expression> }
    void opRel();       //       <opRel> ::= == | != | < | <= | > | >=
    void opUnaire();    //    <opUnaire> ::= - | non
    
    // outils pour se simplifier l'analyse syntaxique
    void testerSymCour (char *ch);  // si symbole courant != ch, erreur : on arrete le programme, sinon rien
    void sauterSymCour (char *ch);  // si symbole courant == ch, on passe au symbole suivant, sinon erreur : on arrete
    void erreur (char mess[]);      // affiche les message d'erreur mess et arrete le programme
};

#endif /* LECTEURPHRASEAVECTABLE_H_ */
