#include "TableSymboles.h"

////////////////////////////////////////////////////////////////////////////////
TableSymboles::TableSymboles():table()
// Construit une table des symboles valués vide
{
}

////////////////////////////////////////////////////////////////////////////////
SymboleValue * TableSymboles::chercheAjoute (Symbole s)
// si s est identique à un symbole valué déjà présent dans la table,
// on renvoie un pointeur sur ce symbole valué.
// Sinon, on insère un nouveau symbole valué correspondant à s
// et on renvoie un pointeur sur le nouveau symbole valué inséré.
{
  vector<SymboleValue*>::iterator i;

  i=table.begin();
  while (i<table.end() && (**i).getChaine() < s.getChaine()) i++;
  if (i==table.end() || (**i).getChaine() != s.getChaine()) // si pas trouvé...
    i=table.insert(i, new SymboleValue(s));
  return *i;
}

////////////////////////////////////////////////////////////////////////////////
ostream & operator << (ostream & cout, TableSymboles ts)
// affiche ts sur cout
{
  cout << endl << "Contenu de la Table des Symboles Values :" << endl
       <<         "=========================================" << endl << endl;
  for (unsigned int i=0; i<ts.table.size(); i++)
    cout << "  " << *(ts.table[i]) << endl;
  cout << endl;
  return cout;
}
