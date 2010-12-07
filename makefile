# GCC = g++ -Wall -W -O
# all: TestLecteurPhraseAvecArbre
# 
# ######################################################################################################
# # etape 1 - lecteur de symboles 
# ######################################################################################################
# 
# LecteurCaractere.o: LecteurCaractere.cc LecteurCaractere.h
# 	$(GCC) -c LecteurCaractere.cc
# 
# Symbole.o: Symbole.cc Symbole.h
# 	$(GCC) -c Symbole.cc
# 
# LecteurSymbole.o: LecteurSymbole.cc LecteurSymbole.h Symbole.h LecteurCaractere.h
# 	$(GCC) -c LecteurSymbole.cc
# 
# 
# 
# 
# 
# ######################################################################################################
# # etape 2 - lecteur de phrase simple 
# ######################################################################################################
# 
# LecteurPhraseSimple.o: LecteurPhraseSimple.cc LecteurPhraseSimple.h Symbole.h LecteurSymbole.h
# 	$(GCC) -c LecteurPhraseSimple.cc
# 
# 	
# ######################################################################################################
# # etape 3 - lecteur de phrase avec table des symboles 
# ######################################################################################################
# 
# SymboleValue.o: SymboleValue.cc SymboleValue.h Symbole.h valType.h
# 	$(GCC) -c SymboleValue.cc
# 
# TableSymboles.o: TableSymboles.cc TableSymboles.h SymboleValue.h 
# 	$(GCC) -c TableSymboles.cc
# 
# LecteurPhraseAvecTable.o: LecteurPhraseAvecTable.cc LecteurPhraseAvecTable.h LecteurSymbole.h TableSymboles.h
# 	$(GCC) -c LecteurPhraseAvecTable.cc
# 
# 
# 	
# ######################################################################################################
# # etape 4 - lecteur de phrase avec table des symboles et arbre
# ######################################################################################################
# ObjTestLecteurPhraseAvecArbre = LecteurCaractere.o Symbole.o LecteurSymbole.o SymboleValue.o TableSymboles.o Arbre.o LecteurPhraseAvecArbre.o TestLecteurPhraseAvecArbre.o valType.o
# 
# Arbre.o: Arbre.h Arbre.cc Symbole.h SymboleValue.h valType.h
# 	$(GCC) -c Arbre.cc
# 
# LecteurPhraseAvecArbre.o: LecteurPhraseAvecArbre.cc LecteurPhraseAvecArbre.h Symbole.h LecteurSymbole.h TableSymboles.h Arbre.h valType.h
# 	$(GCC) -c LecteurPhraseAvecArbre.cc
# 
# TestLecteurPhraseAvecArbre.o: TestLecteurPhraseAvecArbre.cc LecteurPhraseAvecArbre.h
# 	$(GCC) -c TestLecteurPhraseAvecArbre.cc
# 	
# TestLecteurPhraseAvecArbre: $(ObjTestLecteurPhraseAvecArbre)
# 	$(GCC) -o TestLecteurPhraseAvecArbre $(ObjTestLecteurPhraseAvecArbre)
# 	
# valType.o: valType.cc valType.h	
# 	$(GCC) -c valType.cc
###############################
###############################
GCC = g++ -Wall -W -O
all: TestLecteurSymbole TestLecteurPhraseSimple TestLecteurPhraseAvecTable TestLecteurPhraseAvecArbre

######################################################################################################
# etape 1 - lecteur de symboles 
######################################################################################################
ObjTestLecteurSymbole = LecteurCaractere.o Symbole.o LecteurSymbole.o TestLecteurSymbole.o

LecteurCaractere.o: LecteurCaractere.cc LecteurCaractere.h
	$(GCC) -c LecteurCaractere.cc

Symbole.o: Symbole.cc Symbole.h
	$(GCC) -c Symbole.cc

LecteurSymbole.o: LecteurSymbole.cc LecteurSymbole.h Symbole.h LecteurCaractere.h
	$(GCC) -c LecteurSymbole.cc

TestLecteurSymbole.o: TestLecteurSymbole.cc LecteurSymbole.h
	$(GCC) -c TestLecteurSymbole.cc

TestLecteurSymbole: $(ObjTestLecteurSymbole)
	$(GCC) -o TestLecteurSymbole $(ObjTestLecteurSymbole)

######################################################################################################
# etape 2 - lecteur de phrase simple 
######################################################################################################
ObjTestLecteurPhraseSimple = LecteurCaractere.o Symbole.o LecteurSymbole.o LecteurPhraseSimple.o TestLecteurPhraseSimple.o

LecteurPhraseSimple.o: LecteurPhraseSimple.cc LecteurPhraseSimple.h Symbole.h LecteurSymbole.h
	$(GCC) -c LecteurPhraseSimple.cc
	
TestLecteurPhraseSimple.o: TestLecteurPhraseSimple.cc LecteurPhraseSimple.h
	$(GCC) -c TestLecteurPhraseSimple.cc
	
TestLecteurPhraseSimple: $(ObjTestLecteurPhraseSimple)
	$(GCC) -o TestLecteurPhraseSimple $(ObjTestLecteurPhraseSimple)
	
######################################################################################################
# etape 3 - lecteur de phrase avec table des symboles 
######################################################################################################

ObjTestLecteurPhraseAvecTable = LecteurCaractere.o Symbole.o LecteurSymbole.o SymboleValue.o TableSymboles.o LecteurPhraseAvecTable.o TestLecteurPhraseAvecTable.o valType.o

SymboleValue.o: SymboleValue.cc SymboleValue.h Symbole.h valType.h
	$(GCC) -c SymboleValue.cc

TableSymboles.o: TableSymboles.cc TableSymboles.h SymboleValue.h 
	$(GCC) -c TableSymboles.cc

LecteurPhraseAvecTable.o: LecteurPhraseAvecTable.cc LecteurPhraseAvecTable.h LecteurSymbole.h TableSymboles.h
	$(GCC) -c LecteurPhraseAvecTable.cc

TestLecteurPhraseAvecTable: $(ObjTestLecteurPhraseAvecTable)
	$(GCC) -o TestLecteurPhraseAvecTable $(ObjTestLecteurPhraseAvecTable)
	
######################################################################################################
# etape 4 - lecteur de phrase avec table des symboles et arbre
######################################################################################################
ObjTestLecteurPhraseAvecArbre = LecteurCaractere.o Symbole.o LecteurSymbole.o SymboleValue.o TableSymboles.o Arbre.o LecteurPhraseAvecArbre.o TestLecteurPhraseAvecArbre.o valType.o

Arbre.o: Arbre.h Arbre.cc Symbole.h SymboleValue.h valType.h
	$(GCC) -c Arbre.cc

LecteurPhraseAvecArbre.o: LecteurPhraseAvecArbre.cc LecteurPhraseAvecArbre.h Symbole.h LecteurSymbole.h TableSymboles.h Arbre.h valType.h
	$(GCC) -c LecteurPhraseAvecArbre.cc

TestLecteurPhraseAvecArbre.o: TestLecteurPhraseAvecArbre.cc LecteurPhraseAvecArbre.h
	$(GCC) -c TestLecteurPhraseAvecArbre.cc
	
TestLecteurPhraseAvecArbre: $(ObjTestLecteurPhraseAvecArbre)
	$(GCC) -o TestLecteurPhraseAvecArbre $(ObjTestLecteurPhraseAvecArbre)
	
valType.o: valType.cc valType.h	
	$(GCC) -c valType.cc
