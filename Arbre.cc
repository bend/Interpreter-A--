#include "Arbre.h"
#include "Symbole.h"
#include "SymboleValue.h"

////////////////////////////////////////////////////////////////////////////////
// NoeudSeqInst
////////////////////////////////////////////////////////////////////////////////

NoeudSeqInst::NoeudSeqInst() : tabInst() {
}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudSeqInst::getValeur() {
  ValType * valeur=NULL;
  for (unsigned int i=0; i<tabInst.size(); i++)
    valeur = tabInst[i]->getValeur();  // on evalue chaque instruction de la sC)quence
  return valeur; // par convention, resultat = valeur de la derniere instruction
}


////////////////////////////////////////////////////////////////////////////////
void NoeudSeqInst::afficher(unsigned short indentation) {
  Noeud::afficher(indentation);
  cout << "Noeud - Sequence de " << tabInst.size() << " instruction(s)" << endl;
  for (unsigned int i=0; i<tabInst.size(); i++)
    tabInst[i]->afficher(indentation+1); // on affiche les fils en augmentant l'indentation
}

////////////////////////////////////////////////////////////////////////////////
void NoeudSeqInst::ajouteInstruction(Noeud* instruction) {
  tabInst.push_back(instruction);
}

void NoeudSeqInst::affichageC() {
   for (unsigned int i=0; i<tabInst.size(); i++) {
    tabInst[i]->affichageC();
    cout << endl;
   }
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstSi
////////////////////////////////////////////////////////////////////////////////

NoeudInstSi::NoeudInstSi(Noeud* cond, Noeud* alors, Noeud* sinon)
{
	this->cond = cond;
	this->alors = alors;
	this->sinon = sinon;
}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudInstSi::getValeur() {
	ValType * valeur=NULL;
	ValTypeEntier* condition = dynamic_cast <ValTypeEntier*> (cond->getValeur());
	if(condition->getValeur()) 
		valeur = alors->getValeur();
	else 
	{
		if(sinon!=NULL)
			valeur = sinon->getValeur();
	}
	return valeur;
}

////////////////////////////////////////////////////////////////////////////////
void NoeudInstSi::afficher(unsigned short indentation) {
	Noeud::afficher(indentation);
	cout << "Noeud - Si " << endl;
	cond->afficher(indentation+1);
	Noeud::afficher(indentation);
	cout << "Noeud - Alors " << endl;
	alors->afficher(indentation+1);
	if(sinon != NULL){
		Noeud::afficher(indentation);
		cout << "Noeud - Sinon " << endl;
    		if(typeid(*sinon)==typeid(*alors)) 
			sinon->afficher(indentation+1);
		else	
			sinon->afficher(indentation);
	}

}

void NoeudInstSi::affichageC() {
  cout << "if ( " ; 
  cond->affichageC();
  cout << " ) {" << endl;
  alors->affichageC();
  cout << "} " << endl;

  if(sinon != NULL) {
    cout << "else " ;
    if(typeid(*sinon)==typeid(*alors)) {
	cout << " { " << endl;
    	sinon->affichageC();
	cout << "} " << endl;
    }
    else
	sinon->affichageC();
   }

}

////////////////////////////////////////////////////////////////////////////////
void NoeudInstSi::setSuite(Noeud* suite) {
	this->sinon = suite;
}




////////////////////////////////////////////////////////////////////////////////
// NoeudAffectation
////////////////////////////////////////////////////////////////////////////////

NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression) {
  this->variable=variable;
  this->expression=expression;
}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudAffectation::getValeur() {
  ValType * valeur = expression->getValeur(); // on C)value l'expression
  ((SymboleValue*)variable)->setValeur(valeur); // on affecte la variable
  return valeur; // par convention, une affectation a pour valeur la valeur affectC)e
}

////////////////////////////////////////////////////////////////////////////////
void NoeudAffectation::afficher(unsigned short indentation) {
  Noeud::afficher(indentation);
  cout << "Noeud - Affectation" << endl;
  variable->afficher(indentation+1);   // on affiche variable et expression
  expression->afficher(indentation+1); // en augmentant l'indentation
}

void NoeudAffectation::affichageC() {
	variable->affichageC();
	cout << " = " ;
	expression->affichageC();
	cout << " ;" ;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudSauterLigne
////////////////////////////////////////////////////////////////////////////////

NoeudSauterLigne::NoeudSauterLigne() {

}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudSauterLigne::getValeur() {
   cout <<  endl;
   return NULL; // par convention, une affectation a pour valeur la valeur affectC)e
}

////////////////////////////////////////////////////////////////////////////////
void NoeudSauterLigne::afficher(unsigned short indentation) {

}

void NoeudSauterLigne::affichageC() {
	cout << " cout << endl; " ;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudIteration
////////////////////////////////////////////////////////////////////////////////

NoeudIteration::NoeudIteration(Noeud* cond, Noeud* seqInst) {
  condition=cond;
  this->seqInst=seqInst;
}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudIteration::getValeur() {
	ValType * valeur=NULL;
	//while(condition->getValeur()) {
	while( (dynamic_cast <ValTypeEntier*> (condition->getValeur()))->getValeur() ) {
		valeur=seqInst->getValeur();
	}
	return valeur;
}

////////////////////////////////////////////////////////////////////////////////
void NoeudIteration::afficher(unsigned short indentation) {
  Noeud::afficher(indentation);
  cout << "Noeud - Tant que" << endl;
  condition->afficher(indentation+1);   // on affiche la condition
  seqInst->afficher(indentation+1); // on affiche la sequence d'instruction
}

void NoeudIteration::affichageC() {
  cout << "while ( " ;
  condition->affichageC();
  cout << " ) { " << endl;
  seqInst->affichageC();
  cout << " } " << endl;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudRepeter
////////////////////////////////////////////////////////////////////////////////

NoeudRep::NoeudRep(Noeud* cond, Noeud* seqInst) 
:NoeudIteration(cond,seqInst)
{

}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudRep::getValeur() {
	ValType * valeur=NULL;
	do {
		valeur=seqInst->getValeur();
	} while((dynamic_cast <ValTypeEntier*> (condition->getValeur()))->getValeur());
	return valeur;
}

////////////////////////////////////////////////////////////////////////////////
void NoeudRep::afficher(unsigned short indentation) {
  Noeud::afficher(indentation);
  cout << "Noeud - Repeter" << endl;
  seqInst->afficher(indentation+1); // on affiche la sequence d'instruction
  Noeud::afficher(indentation);
  cout << "Noeud - Tantque" << endl;
  condition->afficher(indentation+1);   // on affiche la condition

}

void NoeudRep::affichageC() {
   
  cout << "do { " << endl;
  seqInst->affichageC();
  cout << " } while ( !(";
  condition->affichageC(); 
  cout << ") );"<< endl;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudPour
////////////////////////////////////////////////////////////////////////////////

NoeudPour::NoeudPour(Noeud* cond, Noeud* seqInst, Noeud* var, Noeud* incre) 
:NoeudIteration(cond,seqInst)
{
	varBoucle=var;
	incrementation=incre;
}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudPour::getValeur() {
	ValType * valeur=NULL;
	varBoucle->getValeur();
	while( (dynamic_cast <ValTypeEntier*> (condition->getValeur()))->getValeur() ) {
		valeur = seqInst->getValeur();
		incrementation->getValeur();
	}
	return valeur;
}

////////////////////////////////////////////////////////////////////////////////
void NoeudPour::afficher(unsigned short indentation) {
  Noeud::afficher(indentation);
  cout << "Noeud - Pour" << endl;
  varBoucle->afficher(indentation+1); // on affiche la sequence d'instruction
  condition->afficher(indentation+1);
  incrementation->afficher(indentation+1);
  Noeud::afficher(indentation);
  cout << "Noeud - Faire" << endl;
  seqInst->afficher(indentation+1);   // on affiche la condition

}

void NoeudPour::affichageC() {
  cout << "for ( int " ;
	varBoucle->affichageC();
	condition->affichageC();
  cout <<" ; ";
	incrementation->affichageC();
  cout <<") { " << endl;
 	seqInst->affichageC();
  cout <<" } "<< endl;
   }

////////////////////////////////////////////////////////////////////////////////
// NoeudLire
////////////////////////////////////////////////////////////////////////////////

NoeudLire::NoeudLire(Noeud* var)
{
	variable = var;
}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudLire::getValeur() {
	ValType * valeur = NULL;
	string valeurLue;
	SymboleValue* SymVal;
	cin >> valeurLue;
 	if(isChaine(valeurLue)) { // rajout des guillemette si c'est une chaine (c'est a dire ni un entier ni un r�el)
		valeurLue.insert(0,"\"");
		valeurLue.insert(valeurLue.size(),"\"");
  	}
 
  	SymVal = new SymboleValue(Symbole(valeurLue));

  	if(typeid(*(SymVal->getValeur())) == typeid(ValTypeEntier)) {
		valeur = ValeurLire<ValTypeEntier> (valeurLue);
  	} else if(typeid(*(SymVal->getValeur())) == typeid(ValTypeReel)) {
		valeur = ValeurLire<ValTypeReel> (valeurLue);
  	} else if(typeid(*(SymVal->getValeur())) == typeid(ValTypeChaine)) {
		valeur = ValeurLire<ValTypeChaine> (valeurLue);
  	} 

	((SymboleValue*)variable)->setValeur(valeur);
	return valeur;
}

////////////////////////////////////////////////////////////////
template <class T_class> ValType* NoeudLire::ValeurLire( string valeurLue ) {
	SymboleValue* SymVal = new SymboleValue(Symbole(valeurLue));
        T_class* valSym = dynamic_cast <T_class*> (SymVal->getValeur());
	T_class* valeur = new T_class();
	valeur->setValeur(valSym->getValeur());
	return dynamic_cast <ValType*> (valeur);
}

///////////////////////////////////////////////////////////////////////////////
bool NoeudLire::isChaine(string s){ // méthode de classe : renvoie vrai si s est un Reel ou entier
	bool estUnReel = true;
	bool unPoint = false;

	for(unsigned int i=0;i<s.size();i++) {
		estUnReel = estUnReel && ( isdigit(s[i]) || ((s[i]== '.') && (!unPoint))) ;
		if(s[i] == '.')
			unPoint = true;		
	}
	return !estUnReel;
}

////////////////////////////////////////////////////////////////////////////////
void NoeudLire::afficher(unsigned short indentation) {
// affiche l'opération
  Noeud::afficher(indentation);
  cout << "Noeud - Lire" << endl;
  variable->afficher(indentation+1);   // on affiche : condtion 
}

void NoeudLire::affichageC() {
  cout << "cin >> " ;
  variable->affichageC();
  cout << " ;";
}


////////////////////////////////////////////////////////////////////////////////
// NoeudEcrire
////////////////////////////////////////////////////////////////////////////////

NoeudEcrire::NoeudEcrire(Noeud* val)
{
	valeur = val;
}

////////////////////////////////////////////////////////////////////////////////
ValType * NoeudEcrire::getValeur() {
	
	if(typeid(*(valeur->getValeur())) == typeid(ValTypeEntier)) { // on souhaite ecrire un entier
		   ValTypeEntier* val = dynamic_cast <ValTypeEntier*> (valeur->getValeur());
		   cout << val->getValeur();
	} else if(typeid(*(valeur->getValeur())) == typeid(ValTypeReel)) { // on souhaite ecrire un reel
		   ValTypeReel* val = dynamic_cast <ValTypeReel*> (valeur->getValeur());
		   cout << val->getValeur();
	} else if(typeid(*(valeur->getValeur())) == typeid(ValTypeChaine)) { // on souhaite ecrire une chaine
		   ValTypeChaine* val = dynamic_cast <ValTypeChaine*> (valeur->getValeur());
		   cout << chaineSansQuotes(val->getValeur());
	} 
  	return valeur->getValeur();
}

////////////////////////////////////////////////////////////////////////////////
void NoeudEcrire::afficher(unsigned short indentation) {
	Noeud::afficher(indentation);
	cout << "Noeud - ecrire " << endl;
	//valeur->afficher(indentation+1);
}

void NoeudEcrire::affichageC() {
  cout << "cout << " ;
  valeur->affichageC();
  cout << " ;"  ;
}

////////////////////////////////////////////////////////////////////////////////
string NoeudEcrire::chaineSansQuotes(string brut) {
	string stringFormated = brut;
	stringFormated.erase(stringFormated.size()-1,1);
	stringFormated.erase(0,1);
	return stringFormated;
}


////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaire
////////////////////////////////////////////////////////////////////////////////

NoeudOperateurBinaire::NoeudOperateurBinaire ( Symbole op,
                                               Noeud* operandeG,
                                               Noeud* operandeD) {
  operateur=op;
  operandeGauche=operandeG;
  operandeDroit=operandeD;
}

////////////////////////////////////////////////////////////////////////////////
void NoeudOperateurBinaire::afficher(unsigned short indentation) {
  Noeud::afficher(indentation);
  cout << "Noeud - Operateur Binaire \"" << this->operateur.getChaine() << "\" applique a : " << endl;
  operandeGauche->afficher(indentation+1);  // on affiche fils gauche puis le fils droit
  operandeDroit->afficher(indentation+1);   // en augmentant l'indentation
}

void NoeudOperateurBinaire::affichageC() {
  operandeGauche->affichageC();
  cout << " " << this->operateur.getChaine() << " " ;
  operandeDroit->affichageC();
}


////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaireDeComparaison
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NoeudOperateurBinaireDeComparaison::NoeudOperateurBinaireDeComparaison(Symbole op, Noeud* operandeG, Noeud* operandeD) 		:NoeudOperateurBinaire(op, operandeG, operandeD) 
{
 }

////////////////////////////////////////////////////////////////////////////////
ValType* NoeudOperateurBinaireDeComparaison::getValeur() { 

  ValType* og=operandeGauche->getValeur();
  ValType* od=operandeDroit->getValeur();  	

	if( !(typeid(*og) == typeid(*od)) ) {
		cout << "Erreur : Comparaison entre 2 types differents" << endl;
		exit(0); // plus tard on levera une exception
	}
	if( typeid(*og) == typeid(ValTypeReel) )
		return ResultatOpBinaireDeComparaison <ValTypeReel> (operateur.getChaine(), og,od);
	else if ( typeid(*og) == typeid(ValTypeEntier) )
		return ResultatOpBinaireDeComparaisonEntier (operateur.getChaine(), og,od);
	else
		return ResultatOpBinaireDeComparaison <ValTypeChaine> (operateur.getChaine(), og,od);
}

////////////////////////////////////////////////////////////////////////////////
template <class T_class> ValType* NoeudOperateurBinaireDeComparaison::ResultatOpBinaireDeComparaison(string op,ValType* og, ValType* od) {
	T_class* ogCast = dynamic_cast <T_class*> (og);
  	T_class* odCast = dynamic_cast <T_class*> (od);
  	ValTypeEntier* valeur = new ValTypeEntier();
	
	  if (op=="==") valeur->setValeur(ogCast->getValeur()==odCast->getValeur()) ; 
	  else if (op=="!=") valeur->setValeur(ogCast->getValeur()!=odCast->getValeur()) ; 
	  else if (op=="<=") valeur->setValeur(ogCast->getValeur()<=odCast->getValeur()) ; 
	  else if (op==">=") valeur->setValeur(ogCast->getValeur()>=odCast->getValeur()) ; 
	  else if (op=="<")  valeur->setValeur(ogCast->getValeur()<odCast->getValeur()) ; 
	  else if (op==">")  valeur->setValeur(ogCast->getValeur()>odCast->getValeur()) ; 
	  
  	return dynamic_cast <ValType*> (valeur);
}

////////////////////////////////////////////////////////////////////////////////
ValType* NoeudOperateurBinaireDeComparaison::ResultatOpBinaireDeComparaisonEntier(string op,ValType* og, ValType* od) {	  	
	ValTypeEntier* ogCast = dynamic_cast <ValTypeEntier*> (og);
  	ValTypeEntier* odCast = dynamic_cast <ValTypeEntier*> (od);
  	ValTypeEntier* valeur = new ValTypeEntier();
	
	  if (op=="==") valeur->setValeur(ogCast->getValeur()==odCast->getValeur()) ; 
	  else if (op=="!=") valeur->setValeur(ogCast->getValeur()!=odCast->getValeur()) ; 
	  else if (op=="<=") valeur->setValeur(ogCast->getValeur()<=odCast->getValeur()) ; 
	  else if (op==">=") valeur->setValeur(ogCast->getValeur()>=odCast->getValeur()) ; 
	  else if (op=="<")  valeur->setValeur(ogCast->getValeur()<odCast->getValeur()) ; 
	  else if (op==">")  valeur->setValeur(ogCast->getValeur()>odCast->getValeur()) ; 
	  else if (op=="et" && (typeid(*og) == typeid(ValTypeEntier))) 
				valeur->setValeur(ogCast->getValeur() && odCast->getValeur()) ; 
	  else if (op=="ou" && (typeid(*og) == typeid(ValTypeEntier))) 
	  			valeur->setValeur(ogCast->getValeur() || odCast->getValeur());
	  
  	return dynamic_cast <ValType*> (valeur);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaireArithmetique
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NoeudOperateurBinaireArithmetique::NoeudOperateurBinaireArithmetique(Symbole op, Noeud* operandeG, Noeud* operandeD) 					:NoeudOperateurBinaire(op, operandeG, operandeD) 
{
 }

////////////////////////////////////////////////////////////////////////////////
ValType* NoeudOperateurBinaireArithmetique::getValeur() { 

  ValType* og=operandeGauche->getValeur();
  ValType* od=operandeDroit->getValeur();  	

	if( !( typeid(*og)==typeid(*od) ) ) {
		cout << "Erreur : Operation entre 2 types différents" << endl;
		exit(0); // plus tard on levera une exception
	}	
	if( typeid(*og) == typeid(ValTypeReel))
		return ResultatOpBinaireArithmetique <ValTypeReel> (operateur.getChaine(), og,od);
	else if ( typeid(*og) == typeid(ValTypeEntier))
		return ResultatOpBinaireArithmetique <ValTypeEntier> (operateur.getChaine(), og,od);
	else 
		return ResultatOpBinaireArithmetiqueChaine (operateur.getChaine(), og,od);
}

////////////////////////////////////////////////////////////////
template <class T_class> ValType* NoeudOperateurBinaireArithmetique::ResultatOpBinaireArithmetique(string op,ValType* og, ValType* od) {
	  	
		T_class* ogCast = dynamic_cast <T_class*> (og);
  		T_class* odCast = dynamic_cast <T_class*> (od);
  		T_class* valeur = new T_class();
	
	  if      (op=="+") valeur->setValeur(ogCast->getValeur()+odCast->getValeur());
	  else if (op=="-") valeur->setValeur(ogCast->getValeur()-odCast->getValeur());
	  else if (op=="*") valeur->setValeur(ogCast->getValeur()*odCast->getValeur()); 
	  else  //if (this->operateur=="/") 
	  { if (odCast->getValeur()!=0)
			  valeur->setValeur(ogCast->getValeur()/odCast->getValeur());
		  else {
			  cout << "Erreur : division par zero." << endl;
			  exit(0); // plus tard on levera une exception
		  }
	  } 
  return dynamic_cast <ValType*> (valeur);
}

////////////////////////////////////////////////////////////////
ValType* NoeudOperateurBinaireArithmetique::ResultatOpBinaireArithmetiqueChaine(string op,ValType* og, ValType* od) {
	  	
		ValTypeChaine* ogCast = dynamic_cast <ValTypeChaine*> (og);
  		ValTypeChaine* odCast = dynamic_cast <ValTypeChaine*> (od);
  		ValTypeChaine* valeur = new ValTypeChaine();
	
	  if (op=="+") {
		string ogSsGuil = ogCast->getValeur();
		string odSsGuil = odCast->getValeur();
		// on enleve les guillemets du milieu 
		ogSsGuil.erase(ogSsGuil.size()-1,1);
		odSsGuil.erase(0,1);
		//////////////////////////////////////
		valeur->setValeur( ogSsGuil + odSsGuil); // on concatene
	 } else 	{
		cout << "Erreur opération (\""<< op << "\") interdite sur les chaine : " << op << endl ; 
		exit(0);
	}
  	return dynamic_cast <ValType*> (valeur);
}





////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurUnaire
////////////////////////////////////////////////////////////////////////////////

NoeudOperateurUnaire::NoeudOperateurUnaire(Symbole op, Noeud* operandeD) {
     // construit une opération Unaire : operateur OperandeDroit
  operateur=op;
  operandeDroite=operandeD;
	
}

////////////////////////////////////////////////////////////////////////////////
ValType*  NoeudOperateurUnaire::getValeur() {
 // évalue l'operande droit et applique l'opérateur
	ValType* valeurRetour=NULL;
	ValType* od=operandeDroite->getValeur();
	
	
 if (typeid(*od)==typeid(ValTypeEntier)) {	
  
  ValTypeEntier* odCast = dynamic_cast <ValTypeEntier*> (od);
  ValTypeEntier* valeur = new ValTypeEntier();
  if (this->operateur=="-") 
	
valeur->setValeur(0- odCast->getValeur()); 
  else { // this->operateur=="non"
	if (operandeDroite->getValeur()!=0)
		valeur->setValeur(0);
  	else
		valeur->setValeur(1);
  		}
  valeurRetour = dynamic_cast<ValType*> (valeur);
 }
 else if (typeid(*od)==typeid(ValTypeReel)) {
	 ValTypeReel* odCast = dynamic_cast <ValTypeReel*> (od);
	 ValTypeReel* valeur = new ValTypeReel();
  if (this->operateur=="-") {
	valeur->setValeur(0 - odCast->getValeur());
  } else { // this->operateur=="non"
	if (operandeDroite->getValeur()!=0)
		valeur->setValeur(0);
	else
		valeur->setValeur(1);
		}
  valeurRetour = dynamic_cast<ValType*> (valeur);
}
   
 return valeurRetour;
}

////////////////////////////////////////////////////////////////////////////////
void  NoeudOperateurUnaire::afficher(unsigned short indentation) {
 // affiche l'opération
  Noeud::afficher(indentation);
  cout << "Noeud - Operateur Unaire \"" << this->operateur.getChaine() << "\" applique a : " << endl;
  operandeDroite->afficher(indentation+1);   // en augmentant l'indentation

}

void  NoeudOperateurUnaire::affichageC() {

  cout << " " << this->operateur.getChaine() << " " ;
  operandeDroite->affichageC();   // en augmentant l'indentation

}
