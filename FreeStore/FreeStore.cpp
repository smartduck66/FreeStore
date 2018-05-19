//
// Book : Version du chapitre 17 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 19/05/2018 
// Commit en cours : Exercice n°3 de la page 624
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "stdafx.h"

// Librairie restreinte fournie par BS
#include "std_lib_facilities.h"

/*
// solution #1, using subscripting:
void to_lower(char* p)
// assume that lower and upper case characters have consecutive integer values
{
for (int i = 0; p[i]; ++i) {
if ('A'<=p[i] && p[i]<='Z') // is upper case (only characters are considered upper case - e.g. not !@#$)
p[i] -= ('A'-'a');		// make lower case
}
}
*/


/*
it has been suggested that to avoid repeating p[i], we should introduce a variable to hold the currect character:

// solution #1.1, using subscripting and a local variable:
void to_lower(char* p)
// assume that lower and upper case characters have consecutive integer values
{
for (int i = 0; char c = p[i]; ++i) {
if ('A'<=c && c<='Z')		// is upper case (only characters are considered upper case - e.g. not !@#$)
p[i] -= ('A'-'a');		// make lower case
}
}

Personally, I don't find this clearer.

It has been suggested that not repeating p[i] is "more efficient" but with modern optimizers
the code generated for solution #1 and solution #1.1 will be identical.

*/



// solution #2, using pointer dereferencing:
void to_lower(char* p)
// assume that lower and upper case characters have consecutive integer values
{
	if (p == 0) return;				// just in case some user tries to_lower(0)
	for (; *p; ++p) {				// p is already initialized, so we don't need and initializer part of the for-statement
		if ('A' <= *p && *p <= 'Z') // is upper case (only characters are considered upper case - e.g. not !@#$)
			*p -= ('A' - 'a');		// make lower case
	}
}


void test(const string& ss)	// rely on visual inspection
{
	string s = ss;			// take a copy to avoid modifying original
	cout << s << '\n';
	char* p = &s[0];		// assume (correctly) that the characters are stored with a terminating 0
	to_lower(p);
	cout << p << '\n';
}

char* strdup_ato(const char* s)
{
	if (s == nullptr)return 0;		// Si la chaîne passée est vide, on renvoie "0"

	cout << "Taille de s = " << strlen(s) << endl;	// Vérification 'visuelle' de la "C-style string" passée en argument
	
	char* sf = new char[strlen(s)+1];	// On crée une chaîne sur la free store de la taille de la chaîne passée (+1 car strlen ne compte pas le \0) = strlen : PPP2, page 1191
	
	int count = 0;
	
	while (*s) {
	
		sf[count] = *s;				// On affecte à la chaîne sur la free store chaque char de la chaîne passée en argument
		++s;						// On avance le pointeur
		++count;					// On incrémente également le compteur de "tableau"
	}
	sf[count] = '\0';				// En sortie de boucle, on "stoppe" la chaîne avec un code ASCII 0 qui représente la fin d'une "C-style string"

	return sf;						// On retourne le pointeur
}

int findx_ato(const char* s, const char* x)
{
	if (s == nullptr)return 0;		// Si la chaîne passée est vide, on renvoie "0"
		
	int count = 0;

	while (*s) {
		if (*s == *x)
			++count;
		++s;
		
	}
	
	return count;						// On retourne le nombre d'occurences
}

int main()
{
	// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
	std::locale::global(std::locale("fr-FR"));

	// Exo 3 *******************************************************************************************************
	test("Hello, World!");

	string s;	// read examples into std::string rather than C-style string to avoid the possibility of overflow

	//while (cin >> s && s != "quit")	// take examples from input, one word at a time, until "quit"
	//	test(s);

	// Exo 4 ********************************************************************************************************
	const char* c = "ABCDEFC";		// const est obligatoire car une chaine (=string literal) en C++ est une constante (PPP2, page 1048)
	char* p = strdup_ato(c);		// On créée la chaîne sur la free store
	cout << "p sur la free store = "<<p<<" et sa taille = "<<strlen(p)<<endl;
	delete p;						// On pense bien à désallouer la mémoire, i.e. la chaîne créée sur la free store

	// Exo 5 *********************************************************************************************************
	int n=findx_ato(c,"C");
	cout << "La sous-chaîne a été trouvée à " << n << " reprise(s)" << endl;

	keep_window_open();
}
