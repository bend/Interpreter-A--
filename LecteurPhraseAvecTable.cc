#include "LecteurPhraseAvecTable.h"

#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
LecteurPhraseAvecTable::LecteurPhraseAvecTable(char nomFich[]) :
	ls(nomFich), ts() {
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::analyse() {
	programme();
	cout << "Syntaxe correcte." << endl;
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::programme() {
// <programme> ::= debut <seqInst> fin <EOF>

	sauterSymCour("debut");
	seqInst();
	sauterSymCour("fin");
	testerSymCour("<FINDEFICHIER>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::seqInst() {
// <seqIns> ::= <inst> ; { <inst> ; }

	do {
		inst();
		sauterSymCour(";");
	} while (ls.getSymCour()=="<VARIABLE>" || ls.getSymCour()=="si" || ls.getSymCour()=="tantque" || ls.getSymCour()=="repeter" || ls.getSymCour()=="lire" || ls.getSymCour()=="ecrire" || ls.getSymCour()=="pour");
	// tant que le symbole courant est un debut possible d'instruction...
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::inst() {
// <inst> ::= <affectation> | <instSi> | <instTq> | <instRepeter> | <instEcrire> | <instLire>
	if(ls.getSymCour()=="<VARIABLE>")
			affectation();
		else if (ls.getSymCour()=="si")
			instSi();
		else if (ls.getSymCour()=="tantque")
			instTq();
		else if (ls.getSymCour()=="repeter")
			instRepeter();
		else if (ls.getSymCour()=="lire")
			instLire();
		else if (ls.getSymCour()=="ecrire")
			instEcrire();
		else if (ls.getSymCour()=="pour")
			instPour();
		else
			erreur("<inst>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::instSi()		
// <instSi> ::= si ( <expBool> ) <seqInst> { sinonsi ( <expBool> ) <seqInst> } [sinon <seqInst> ] finsi
{
	// si ( <expBool> ) <seqInst>
	sauterSymCour("si");
	
	if(ls.getSymCour()=="(") {
		ls.suivant();
		expBool();
		sauterSymCour(")");
	}
	else
		erreur("<expBool>");
	
	seqInst();
	
	// { sinonsi ( <expBool> ) <seqInst> }
	while(ls.getSymCour()=="sinonsi") {
		sauterSymCour("sinonsi");
		if(ls.getSymCour()=="(") {
			ls.suivant();
			expBool();
			sauterSymCour(")");
		}
		else
			erreur("<expBool>");
		seqInst();
	}
	ls.suivant();
	// [sinon <seqInst> ]
	if(ls.getSymCour()=="sinon") 
		sauterSymCour("sinon");
		seqInst();
	
	// finsi
	if(ls.getSymCour()=="finsi")
		sauterSymCour("finsi");
	else
		erreur("<instSi>");
		
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::instTq()		
// <instTq> ::= tantque (<expBool>) <seqInst> fintantque
{
	sauterSymCour("tantque");
	if(ls.getSymCour()=="(") {
		ls.suivant();
		expBool();
		sauterSymCour(")");
	}
	else
		erreur("<expBool>");
	seqInst();
	if(ls.getSymCour()=="fintantque")
		sauterSymCour("fintantque");
	else
		erreur("<instTq>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::instRepeter() 
// <instRepeter> ::= repeter <seqInst> jusqua ( <expBool> )
{
	sauterSymCour("repeter");
	seqInst();
	if(ls.getSymCour()=="jusqua")
		sauterSymCour("jusqua");
	else
		erreur("<instRepeter>");
	if(ls.getSymCour()=="(") {
		ls.suivant();
		expBool();
		sauterSymCour(")");
	}
	else
		erreur("<expBool>");
	
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::instPour()   
// <instPour> ::= pour ( <variable> <expBool> <affectation> ) <seqInst> finpour
{
	sauterSymCour("pour");
	if(ls.getSymCour()=="(") {
		ls.suivant();
		affectation();
		if(ls.getSymCour()==";")
			ls.suivant();
		else
			erreur("<instPour>");
		expBool();
		if(ls.getSymCour()==";")
			ls.suivant();
		else
			erreur("<instPour>");
		affectation();
		sauterSymCour(")");
	}
	else
		erreur("<instPour>");
	seqInst();
	if(ls.getSymCour()=="finpour")
		sauterSymCour("finpour");
	else
		erreur("<instPour>");
	
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::instLire()
// <instLire ::= lire(<variable>)
{
	sauterSymCour("lire");
	if(ls.getSymCour()=="(") {
		ls.suivant();
		if(ls.getSymCour()=="<VARIABLE>")
			ls.suivant();
		else
			erreur("<instLire>");
		sauterSymCour(")");
	}
	else
		erreur("<instLire>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::instEcrire()
// <instEcrire> ::= ecrire ( <expression> | <chaine> )
{
	sauterSymCour("ecrire");
	if(ls.getSymCour()=="(") {
		ls.suivant();
		if(ls.getSymCour()=="<CHAINE>")
			ls.suivant();
		else
			expression();
		sauterSymCour(")");
	}
}


////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::affectation() {
// <affectation> ::= <variable> = <expression>

	//sauterSymCour("<VARIABLE>");
	testerSymCour("<VARIABLE>");
	ts.chercheAjoute(ls.getSymCour());
	ls.suivant();
	sauterSymCour("=");
	expression();
}



////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::expression() {
// <expression> ::= <terme> { <opAdd> <terme> }

	terme();
	while (ls.getSymCour()=="+" || ls.getSymCour()=="-") {
		opAdd();
		terme();
	}
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::facteur() {
// <facteur> ::= <entier>  | <chaine> | <variable>  |  <opUnaire> <expBool>  |  ( <expBool> )

	if (ls.getSymCour()=="<VARIABLE>" || ls.getSymCour()=="<ENTIER>" || ls.getSymCour()=="<CHAINE>") {
		ts.chercheAjoute(ls.getSymCour());
		ls.suivant();
	} else if ((ls.getSymCour()=="-" || ls.getSymCour()=="non")) {
		ls.suivant();
		expBool();
	} else if (ls.getSymCour()=="(") {
		ls.suivant();
		expBool();
		sauterSymCour(")");
	} else
		erreur("<facteur>");
}


/////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::opAdd()
// <opAdd> ::= + | -
{
	if(ls.getSymCour()=="+" || ls.getSymCour()=="-")
		ls.suivant();
	else
		erreur("<opAd>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::opMult()
// <opMult> ::= * | /
{
	if(ls.getSymCour()=="*" || ls.getSymCour()=="/")
		ls.suivant();
	else
		erreur("<opMult>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::terme()
// <terme> ::= <facteur> { <opMult> <facteur> }
{
	facteur();
	while (ls.getSymCour()=="*" || ls.getSymCour()=="/") {
		opMult();
		facteur();
	}
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::expBoolInt()
// <expBoolInt> ::= <relation> { <opOu> <relation> }
{
	relation();
	while (ls.getSymCour()=="ou") {
		opOu();
		relation();
	}
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::opOu()
// <opOu> ::= ou
{
	if(ls.getSymCour()=="ou")
		ls.suivant();
	else
		erreur("<opOu>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::opEt()
// <opEt> ::= et
{
	if(ls.getSymCour()=="et")
		ls.suivant();
	else
		erreur("<opEt>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::expBool()
// <expBool> ::= <expBoolInt> { <opEt> <expBoolInt> }	
{
	expBoolInt();
	while(ls.getSymCour()=="et") {
		opEt();
		expBoolInt();
	}
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::relation()
// <relation> ::= <expression> { <opRel> <expression> }
{
	expression();
	while(ls.getSymCour()=="==" || ls.getSymCour()=="!=" || ls.getSymCour()=="<" || ls.getSymCour()=="<=" || ls.getSymCour()==">" || ls.getSymCour()==">=") {
		opRel();
		expression();
	}
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::opRel()
// <opRel> ::= == | != | < | <= | > | >=
{
	if(ls.getSymCour()=="==" || ls.getSymCour()=="!=" || ls.getSymCour()=="<" || ls.getSymCour()=="<=" || ls.getSymCour()==">" || ls.getSymCour()==">=")
		ls.suivant();
	else
		erreur("<opRel>");
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::opUnaire()
// <opUnaire> ::= - | non
{
	if(ls.getSymCour()=="-" || ls.getSymCour()=="non")
		ls.suivant();
	else
		erreur("<opUnaire>");
}


////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::testerSymCour(char * ch) {
	if (ls.getSymCour() != ch) {
		cout << endl << "-------- Erreur ligne " << ls.getLigne()
				<< " - Colonne " << ls.getColonne() << endl << "   Attendu : "
				<< ch << endl << "   Trouve  : " << ls.getSymCour() << endl
				<< endl;
		exit(0); // plus tard, on levera une exception
	}
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::sauterSymCour(char * ch) {
	testerSymCour(ch);
	ls.suivant();
}

////////////////////////////////////////////////////////////////////////////////
void LecteurPhraseAvecTable::erreur(char mess[]) {
	cout << endl << "-------- Erreur ligne " << ls.getLigne() << " - Colonne "
			<< ls.getColonne() << endl << "   Attendu : " << mess << endl
			<< "   Trouve  : " << ls.getSymCour() << endl << endl;
	exit(0); // plus tard, on levera une exception
}
