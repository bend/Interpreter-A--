#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "valType.h"

////////////////////////////////////////////////////////////////////////////////
//  ValTypeEntier
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
ValTypeEntier::ValTypeEntier(int ent) {
	this->entier = ent;
}

////////////////////////////////////////////////////////////////////////////////
int ValTypeEntier::getValeur(){
	return entier;
}

////////////////////////////////////////////////////////////////////////////////
void ValTypeEntier:: setValeur(int entier){
	this->entier = entier;
}

////////////////////////////////////////////////////////////////////////////////
void ValTypeEntier::afficher() { 
	cout << entier ;
}


////////////////////////////////////////////////////////////////////////////////
//  ValTypeReel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
ValTypeReel::ValTypeReel(float reel) {
	this->reel = reel;
}

////////////////////////////////////////////////////////////////////////////////
float ValTypeReel::getValeur(){
	return reel;
}

////////////////////////////////////////////////////////////////////////////////
void ValTypeReel::setValeur(float reel) {
	this->reel = reel;
}

////////////////////////////////////////////////////////////////////////////////
void ValTypeReel::afficher() {
	cout << reel;
}


////////////////////////////////////////////////////////////////////////////////
//  ValTypeChaine
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
ValTypeChaine::ValTypeChaine(string ch) {
	this->ch = ch;
}

////////////////////////////////////////////////////////////////////////////////
string ValTypeChaine::getValeur(){
	return ch;
}

////////////////////////////////////////////////////////////////////////////////
void ValTypeChaine::setValeur(string ch) {
	this->ch = ch;
}

////////////////////////////////////////////////////////////////////////////////
void ValTypeChaine::afficher() {
	cout << ch;
}


////////////////////////////////////////////////////////////////////////////////
//  ValTypeCharactere
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
ValTypeCaractere::ValTypeCaractere(char ch) {
	this->ch =ch;
}

////////////////////////////////////////////////////////////////////////////////
char ValTypeCaractere::getValeur() {
	return ch;
}

////////////////////////////////////////////////////////////////////////////////
void ValTypeCaractere::setValeur(char ch) {
	this->ch =ch;
} 	

////////////////////////////////////////////////////////////////////////////////
void ValTypeCaractere::afficher() {
	cout << "'" << ch << "'";
}
