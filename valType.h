#ifndef VALTYPE_H_
#define VALTYPE_H_

#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
class ValType {
public :
	virtual void afficher() {}
	virtual ~ValType() {} ;
	
};

class ValTypeEntier : public ValType {
private :
	int entier;
public :	
	~ValTypeEntier() { } ;
	ValTypeEntier(int ent);
	ValTypeEntier(){}
	int getValeur();
	void setValeur(int entier);
	void afficher() ;
};
 
class ValTypeReel : public ValType {
private :
	float reel;
public :
	ValTypeReel(float reel);
	ValTypeReel() {}
	~ValTypeReel() {} 
	float getValeur();
	void setValeur(float reel);
	void afficher() ;
};



 class ValTypeChaine : public ValType {
  private :
	string ch;
  public :
  	ValTypeChaine(string ch);
	ValTypeChaine() {}
  	~ValTypeChaine() {} 
 	string getValeur();
 	void setValeur(string ch);
 	void afficher() ;
};


 class ValTypeCaractere : public ValType {
  private :
	char ch;
  public :
  	ValTypeCaractere(char ch);
	ValTypeCaractere() {}
  	~ValTypeCaractere() {} 
 	char getValeur();
 	void setValeur(char ch);
 	void afficher() ;
};
#endif
