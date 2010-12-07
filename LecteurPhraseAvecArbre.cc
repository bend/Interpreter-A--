#include "LecteurPhraseAvecArbre.h"

#include <iostream>
// #include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
LecteurPhraseAvecArbre::LecteurPhraseAvecArbre(char nomFich[]) :
	ls(nomFich), ts() {
	erreurs = false;
// 	strcpy(fichier,nomFich);
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecArbre::analyse() {
	arbre=programme();
	if(!erreurs)
		cout << "Syntaxe correcte." << endl;
}

////////////////////////////////////////////////////////////////////////////////
Noeud* LecteurPhraseAvecArbre::programme() {
	// <programme> ::= debut <seq_inst> fin FIN_FICHIER

	sauterSymCour("debut");
	Noeud* si = seqInst();
	sauterSymCour("fin");
	if(testerSymCour("<FINDEFICHIER>"))
		return si;
	else
		return NULL;
}

////////////////////////////////////////////////////////////////////////////////
Noeud* LecteurPhraseAvecArbre::seqInst() {
	// <seqInst> ::= <inst> ; { <inst> ; }

	NoeudSeqInst* si = new NoeudSeqInst();
	do {
		si->ajouteInstruction(inst());
		sauterSymCour(";");
	} while (ls.getSymCour()=="<VARIABLE>" || ls.getSymCour()=="si" || ls.getSymCour()=="tantque" || ls.getSymCour()=="repeter" || ls.getSymCour()=="lire" || ls.getSymCour()=="ecrire" || ls.getSymCour()=="pour" || ls.getSymCour()=="sauter_ligne");
	// tant que le symbole courant est un debut possible d'instruction...
	return si;
}

////////////////////////////////////////////////////////////////////////////////
Noeud* LecteurPhraseAvecArbre::inst() {
// <inst> ::= <affectation> | <instSi> | <instTq> | <instRepeter> | <instEcrire> | <instLire>
	Noeud* inst = NULL;
	if(ls.getSymCour()=="<VARIABLE>")
		inst = affectation();
	else if (ls.getSymCour()=="si")
		inst = instSi();
	else if (ls.getSymCour()=="tantque")
		inst = instTq();
	else if (ls.getSymCour()=="repeter")
		inst = instRepeter();
	else if (ls.getSymCour()=="lire")
		inst = instLire();
	else if (ls.getSymCour()=="ecrire")
		inst = instEcrire();
	else if (ls.getSymCour()=="pour")
		inst = instPour();
	else if(ls.getSymCour()=="sauter_ligne")
		inst = instSauterLigne();
	else 
			erreur("<inst>");
	return inst;

}

////////////////////////////////////////////////////////////////////////////////
Noeud* LecteurPhraseAvecArbre::affectation() {
// <affectation> ::= <variable> = <expression>

	if(testerSymCour("<VARIABLE>")) {
		Noeud* var = ts.chercheAjoute(ls.getSymCour());
		ls.suivant();
		if(sauterSymCour("=")) {
			Noeud* exp = expression();
			return new NoeudAffectation(var,exp);
		}
		else
			return NULL;
	}
	else
		return NULL;
}

////////////////////////////////////////////////////////////////////////////////
Noeud* LecteurPhraseAvecArbre::expression() {
// <expression> ::= <terme> { <opAdd> <terme> }
	Noeud* term = terme();
	while (ls.getSymCour()=="+" || ls.getSymCour()=="-") {
		Symbole operateur = opAdd(); // on stocke le symbole de l'opérateur
		Noeud* termDroit=terme(); // lecture de l'operande droit
		term = new NoeudOperateurBinaireArithmetique(operateur,term,termDroit); // const. du noeud
	}
	return term;
}

////////////////////////////////////////////////////////////////////////////////
Noeud* LecteurPhraseAvecArbre::facteur() {
// <facteur> ::= <entier> | <reel> |  <variable>  | <chaine>  |  - <facteur>  | <chaine> | <caractere> |  ( <expression> )

	Noeud* fact=NULL;

	if (ls.getSymCour()=="<VARIABLE>" || ls.getSymCour()=="<ENTIER>"|| ls.getSymCour()=="<CHAINE>" || ls.getSymCour()=="<REEL>" || ls.getSymCour()=="<CARACTERE>") {
		fact=ts.chercheAjoute(ls.getSymCour());
		ls.suivant();
	} else if (ls.getSymCour()=="-") {
		fact = new NoeudOperateurUnaire(opUnaire(),facteur());
	} else if (ls.getSymCour()=="(") {
		ls.suivant();
		fact=expression();
		sauterSymCour(")");
	} else
		erreur("<facteur>");
	return fact;
}



////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::instSi()	   
//      <instSi> ::= si ( <expBool> ) <seqInst> { sinonsi ( <expBool> ) <seqInst> } [sinon <seqInst> ] finsi
{
	NoeudInstSi* si=NULL;
	Noeud* expbool=NULL;
	Noeud* seqAlors=NULL;
	NoeudInstSi* sinonsi=NULL;
	NoeudInstSi* courant=NULL;
	// si ( <expBool> ) <seqInst>
	sauterSymCour("si");
	sauterSymCour("(");
	expbool=expBool();
	sauterSymCour(")");
	seqAlors = seqInst();
	
	si = new NoeudInstSi(expbool,seqAlors,NULL);
	courant=si;
	// { sinonsi ( <expBool> ) <seqInst> }
	while(ls.getSymCour()=="sinonsi") {
		ls.suivant();
		sauterSymCour("(");
		expbool=expBool();
		sauterSymCour(")");
		seqAlors = seqInst();		
		sinonsi = new NoeudInstSi(expbool,seqAlors,NULL);
		courant->setSuite(sinonsi);
		courant=sinonsi;
	}
	
	// [sinon <seqInst> ]
	if(ls.getSymCour()=="sinon") {
		ls.suivant();
		seqAlors=seqInst();
		courant->setSuite(seqAlors);
		courant=sinonsi;
	}

	sauterSymCour("finsi");
	return si;
}

////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::instTq()	  
//      <instTq> ::= tantque (<expBool>) <seqInst> fintantque
{
	Noeud* expbool=NULL;
	Noeud* seqInstr=NULL;
	sauterSymCour("tantque");
	sauterSymCour("(");
	expbool=expBool();
	sauterSymCour(")");
	seqInstr = seqInst();
	sauterSymCour("fintantque");
	Noeud* tanque=new NoeudIteration(expbool,seqInstr);
	return tanque;
}

////////////////////////////////////////////////////////////////////////////////
Noeud* LecteurPhraseAvecArbre::instSauterLigne()
//
{
	sauterSymCour("sauter_ligne");
	Noeud* saut=new NoeudSauterLigne();
	return saut;
}

////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::instRepeter() 
// <instRepeter> ::= repeter <seqInst> jusqua ( <expBool> )
{
	Noeud* expbool=NULL;
	Noeud* seqInstr=NULL;
	sauterSymCour("repeter");
	seqInstr=seqInst();
	sauterSymCour("jusqua");
	sauterSymCour("(");
	expbool=expBool();
	sauterSymCour(")");
	Noeud* rep = new NoeudRep(expbool,seqInstr);
	return rep;
}

////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::instPour()    
//    <instPour> ::= pour ( <variable> <expBool> <affectation> ) <seqInst> finpour  	
{
	Noeud* var=NULL;
	Noeud* incre=NULL;
	Noeud* expbool=NULL;
	Noeud* seqInstr=NULL;
	sauterSymCour("pour");
	sauterSymCour("(");
	var=affectation();
	sauterSymCour(";");
	expbool=expBool();
	sauterSymCour(";");
	incre=affectation();
	sauterSymCour(")");
	seqInstr=seqInst();
	sauterSymCour("finpour");
	Noeud* pour = new NoeudPour(expbool,seqInstr,var,incre);
	return pour;
}

////////////////////////////////////////////////////////////////////////////////
Noeud* LecteurPhraseAvecArbre::instLire()
// <instLire> ::= lire(<variable>)
{
	Noeud* lire=NULL;
	Noeud* var=NULL;
	sauterSymCour("lire");
	sauterSymCour("(");
	var = ts.chercheAjoute(ls.getSymCour());
	if(ls.getSymCour()=="<VARIABLE>") 
		lire= new NoeudLire(var);
	else
		erreur("<variable>");
	ls.suivant();
	sauterSymCour(")");
	return lire;
}

////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::instEcrire()  
//  <instEcrire> ::= ecrire ( <expression> | <chaine> )
{
	Noeud* ecrire=NULL;
	Noeud* val=NULL;
	sauterSymCour("ecrire");
	sauterSymCour("(");
	val = ts.chercheAjoute(ls.getSymCour());
	if(ls.getSymCour()=="<CHAINE>" || ls.getSymCour()=="<VARIABLE>" || ls.getSymCour()=="<ENTIER>")
		ecrire = new NoeudEcrire(val);
	else
		erreur("<chaine> | <variable> | <entier>");
	ls.suivant();
	sauterSymCour(")");
	return ecrire;
}

////////////////////////////////////////////////////////////////////////////////
Symbole LecteurPhraseAvecArbre::opAdd()       
//       <opAdd> ::= + | -
{
	Symbole operateur;
	if(ls.getSymCour()=="+" || ls.getSymCour()=="-"){
		operateur = ls.getSymCour();
		ls.suivant();
	}
	else
		erreur("<opAd>");
	return operateur;
}


////////////////////////////////////////////////////////////////////////////////
Symbole LecteurPhraseAvecArbre::opMult()      
//      <opMult> ::= * | /
{
	Symbole operateur;
	if(ls.getSymCour()=="*" || ls.getSymCour()=="/") {
		operateur = ls.getSymCour();
		ls.suivant();
	}
	else
		erreur("<opMult>");
	return operateur;
}

////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::terme()      
//       <terme> ::= <facteur> { <opMult> <facteur> }
{
	Noeud* fact = facteur();
	while (ls.getSymCour()=="*" || ls.getSymCour()=="/") {
		Symbole operateur = opMult(); // on stocke le symbole de l'opérateur
		Noeud* factDroit=terme(); // lecture de l'operande droit
		fact = new NoeudOperateurBinaireArithmetique(operateur,fact,factDroit); // const. du noeud
	}
	return fact;
}


////////////////////////////////////////////////////////////////////////////////
Symbole LecteurPhraseAvecArbre::opOu()        
//        <opOu> ::= ou
{
	Symbole operateur;
	if(ls.getSymCour()=="ou") {
		operateur = ls.getSymCour();
		ls.suivant();
	}
	else
		erreur("<opOu>");
	return operateur;
}

////////////////////////////////////////////////////////////////////////////////
Symbole LecteurPhraseAvecArbre::opEt()       
//        <opEt> ::= et
{
	Symbole operateur;
	if(ls.getSymCour()=="et") {
		operateur = ls.getSymCour();
		ls.suivant();
	}
	else
		erreur("<opEt>");
	return operateur;
}

////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::expBoolInt()  
//  <expBoolInt> ::= <relation> { <opOu> <relation> }
{
	Noeud* expBoolInt = NULL;
	Noeud* expBoolIntDroite = NULL;
	Symbole operateur;
	expBoolInt = relation();
	while (ls.getSymCour()=="ou") {
		operateur = opOu();
		expBoolIntDroite = relation();
		expBoolInt = new NoeudOperateurBinaireDeComparaison(operateur,expBoolInt,expBoolIntDroite);
	}
	return expBoolInt;
}

////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::expBool()     
//     <expBool> ::= <expBoolInt> { <opEt> <expBoolInt> }	
{
	Noeud* expBool = NULL;
	Noeud* expBoolDroite = NULL;
	Symbole operateur;
	expBool = expBoolInt();
	while(ls.getSymCour()=="et") {
		operateur = opEt();
		expBoolDroite = expBoolInt();
		expBool = new NoeudOperateurBinaireDeComparaison(operateur,expBool,expBoolDroite);
	}
	return expBool;
}

////////////////////////////////////////////////////////////////////////////////
Noeud*  LecteurPhraseAvecArbre::relation()    
//    <relation> ::= <expression> { <opRel> <expression> }
{
	Noeud* rel = NULL;
	Noeud* reldroite = NULL;
	Symbole operateur;
	rel = expression();
	while(ls.getSymCour()=="==" || ls.getSymCour()=="!=" || ls.getSymCour()=="<" || ls.getSymCour()=="<=" || ls.getSymCour()==">" || ls.getSymCour()==">=") {
		operateur = opRel();
		reldroite = expression();
		rel = new NoeudOperateurBinaireDeComparaison(operateur,rel,reldroite);
	}
	return rel;
}

////////////////////////////////////////////////////////////////////////////////
Symbole LecteurPhraseAvecArbre::opRel()       
//       <opRel> ::= == | != | < | <= | > | >=
{
	Symbole operateur;
	if(ls.getSymCour()=="==" || ls.getSymCour()=="!=" || ls.getSymCour()=="<" || ls.getSymCour()=="<=" || ls.getSymCour()==">" || ls.getSymCour()==">=") {
		operateur = ls.getSymCour();
		ls.suivant();
	}
	else
		erreur("<opRel>");
	return operateur;
}

////////////////////////////////////////////////////////////////////////////////
Symbole LecteurPhraseAvecArbre::opUnaire()
//    <opUnaire> ::= - | non
{
	Symbole operateur;
	if(ls.getSymCour()=="-" || ls.getSymCour()=="non") {
		operateur = ls.getSymCour();
		ls.suivant();
	}
	else
		erreur("<opUnaire>");
	return operateur;
}

////////////////////////////////////////////////////////////////////////////////
bool LecteurPhraseAvecArbre::testerSymCour(char * ch) {
	if (ls.getSymCour() != ch) {
		cout << "-------- " << fichier << ":" << ls.getLigne() << " column "
			<< ls.getColonne() << " : error : expected '" << ch << "'" << " | found : " << ls.getSymCour() << endl;
		erreurs=true;
		return false;
	}
	else
		return true;
}

////////////////////////////////////////////////////////////////////////////////
bool LecteurPhraseAvecArbre::sauterSymCour(char * ch) {
	if(testerSymCour(ch)) {
		ls.suivant();
		return true;
	}
	else
		return false;
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecArbre::erreur(char mess[]) {		
	cout << "-------- " << fichier << ":" << ls.getLigne() << " column "
			<< ls.getColonne() << " : error : expected \"" << mess << "\"" << " | found : " << ls.getSymCour() << endl;
	erreurs = true;
	ls.suivant();
}