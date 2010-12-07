#ifndef LECTEURCARACTERE_H_
#define LECTEURCARACTERE_H_

#include <fstream>
using namespace std;

class LecteurCaractere {

  ////////////////////////////////////////////////////////////////////////////////
  public :
    LecteurCaractere(char nomFich[]); // construit le lecteur pour parcourir nomFich
    inline char         getCarCour() { return carCour; } // accesseur
    inline unsigned int getLigne()   { return ligne;   } // accesseur
    inline unsigned int getColonne() { return colonne; } // accesseur
    void suivant(); // passe au caractere suivant, s'il existe

  ////////////////////////////////////////////////////////////////////////////////
  private :
    ifstream f;           // le fichier texte que l'on parcourt
    char carCour;         // le caractere courant
    unsigned int ligne;   // numero de ligne du caractere courant
    unsigned int colonne; // numero de colonne du caractere courant
};

#endif /* LECTEURCARACTERE_H_ */
