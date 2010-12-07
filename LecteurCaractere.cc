#include <iostream>
using namespace std;

#include "LecteurCaractere.h"

////////////////////////////////////////////////////////////////////////////////
LecteurCaractere::LecteurCaractere(char nomFich[]) : f(nomFich)
{
  ligne=1;
  colonne=0;
  if (f.fail())
  {
    cout << "Fichier \"" << nomFich << "\" non trouve." << endl;
    exit(0); // plus tard on levera une exception
  }
  else
    suivant();
}

////////////////////////////////////////////////////////////////////////////////
void LecteurCaractere::suivant()
{
  if (f.peek()==EOF)
    carCour=EOF;
  else
  {
    if (carCour=='\n')
    {
      colonne=0;
      ligne++;
    }
    f.get(carCour);
    colonne++;
  }
}
