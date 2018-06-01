//
// Book : Version des chapitres 17, 18 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 19/05/2018 
// Commit en cours : Drill page 644, 1er juin 2018
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

// Exo 11 **********************************************************************************************************************************************************
class Link {
public:
	string value;
	
	Link(const string& v, Link* p=nullptr, Link* s=nullptr):value{v}, prev{p},succ{s} {}
	Link* insert(Link* n);
	Link* add(Link* n);
	Link* erase();
	Link* find(const string& s);
	//const Link* find(const string& s) const;

	Link* advance(int n);

	Link* next() const { return succ; }
	Link* previous() const { return prev; }

private:
	Link* prev;
	Link* succ;
};

Link* Link::insert(Link* n) 
{  
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = this;
	if (prev) 
		prev->succ = n;
	n->prev = prev;
	prev = n;
	return n;
}

Link* Link::add(Link* n)
{
	// much like insert
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = this;
	if (prev) prev->succ = n;
	n->prev = prev;
	prev = n;
	return n;
}

Link* Link::erase()
{
	if (this == nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}


Link* Link::find(const string& s)	// find s in list;
									// return 0 for "not found"
{	
	Link* p = this;					// Obligatoire de réaffecter l'objet en cours à un pointeur temporaire 'p' car il est impossible de réaffecter "this"...
	while (p) {
		if (p->value == s) return p;
		p = p->succ;				// ... afin de pouvoir "bouger" dans la liste liée !
	}
	return 0;
}

Link* Link::advance(int n)
{
	if (this == nullptr) return nullptr;
	if (0<n) {
	while (n--) {
		if (succ == nullptr) return nullptr;
		this->succ;
		}
	}
	else if (n<0) {
		while (n++) {
			if (prev == nullptr) return nullptr;
			this->prev;
		}
	}
	return this;
}

void print_all(Link* p)
{
	cout << "{";
	while (p) {
		cout << p->value;
		if (p = p->next()) cout << ", ";
		
	}
	cout << "}";

}

// Exo 13 **********************************************************************************************************************************
class God {
public:
	struct {
		string name{ };
		string mithology{};
		string vehicle{};
		string weapon{};
	};

	God(const string& n, const string& m, const string& v, const string& w, God* p = nullptr, God* s = nullptr) :name{ n }, mithology{ m }, vehicle{ v }, weapon{ w }, prev{ p }, succ{ s } {}
	God* insert(God* n);
	God* add_ordered(God* n);
	God* erase();
	God* find(const string& s);
	

	God* advance(int n);

	God* next() const { return succ; }
	God* previous() const { return prev; }

private:
	God* prev;
	God* succ;
};

void print_god(God* p) 
{
	// On se positionne au début de la liste chaînée : tant que previous() non nul, on remonte la liste
	while (p->previous()) p = p->previous();
	
	cout << "Liste ordonnée des dieux {";
	while (p) {
		cout << p->name;
		if (p = p->next()) cout << ", ";

	}
	cout << "}"<<endl<<"*****************************************************************************"<<endl;
}


void list_god(God* p)
{
	// On se positionne au début de la liste chaînée : tant que previous() non nul, on remonte la liste
	while (p->previous()) p = p->previous();

	cout << "Liste des dieux par mythologie"<<endl;
	cout << "Gods :		Greek		Roman		Norse" << endl << endl;
	while (p) {
		if (p->mithology == "Greek")cout << setw(22) << p->name << endl;
		if (p->mithology == "Roman")cout << setw(37) << p->name << endl;
		if (p->mithology == "Norse")cout << setw(52) << p->name << endl;
		p = p->next();

	}
	cout << endl << "*****************************************************************************" << endl;
}

God* God::add_ordered(God* n)					// Argument n = new god to insert
{
	
	if (n == nullptr) return this;				// Si l'argument est vide, on retourne la liste actuelle représentée par l'objet this
	if (this == nullptr) return n;				// Si la liste est vide (normalement impossible), on retourne alors le dieu à insérer

	God* p = this;								// Le pointeur 'p' référence l'objet 'en cours', soit la liste chaînée
	God* k = nullptr;							// Le pointeur 'k' est initialisé et nous servira plus bas
	while (p->previous()) p = p->previous();	// On se positionne au début de la liste chaînée : tant que previous() non nul, on remonte la liste
	
	// Cas de la 1ère insertion quand p->next() pointe sur NULL ; la liste chaînée initialisée par un new dans "main" ne contient qu'un seul élément
	if (!p->next()) {
		if (p->name < n->name) {				// Cas n°1 : insertion du nouveau dieu AVANT celui constituant la liste chaînée
			n->prev = p;
			p->succ = n;
			
		} else {								// Cas n°2 : sinon, insertion APRES
			n->succ = p;
			p->prev = n;
			
		}

		return n;
	}

	// Autres insertions : on avance dans la liste tant que le nom du dieu à insérer (n->name) est alphabétiquement supérieur à celui déjà dans la liste (p->name)
	while (p->name < n->name) {
		k = p;									// On stocke le "pointeur-Dieu" actuel
		
		if (p->next())
			p = p->next();						// On avance si on peut...
		else {
			// ... sinon cela signifie que l'on est arrivé à la fin et que le nouveau dieu devient le dernier de la chaîne
			n->prev = p;
			p->succ = n;
			return n;
			}

		}
	
	// On insère alors le nouveau Dieu en le chaînant ENTRE les deux occurences
	n->prev = k;
	if (k) k->succ = n;							// Si k est null, on ne lui donne pas de successeur car cela signifie que l'on insère en tout début de liste
	n->succ = p;
	p->prev = n;
	return n;
	
}

struct X{
	int val;

	void out(const string& s, int nv)
	{
		cerr << this << "->" << s << ": " << val << " (" << nv << ")\n";
	}

	X() { out("X()", 0); val = 0; }
	X(int v) { val = v; out("X(int)", v); }
	X(const X& x) { val = x.val; out("X(X&) ", x.val); }
	X& operator=(const X& a) { out("X::operator=()", a.val); val = a.val; return *this; }
	~X() { out("~X()", 0); }
	
};

X glob(2);
X copy(X a) { return a; }
X copy2(X a) { X aa = a; return aa; }
X& ref_to(X& a) { return a; }
X* make(int i) { X a(i); return new X(a); }
struct XX { X a; X b; };

int main()
{
	
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));
		
		// Exo 13 *********************************************************************************
		God* gods = new God{ "Athena", "Greek", "Daim", "Elbow" };
		gods = gods->add_ordered(new God{ "Odin", "Norse", "8-legged flying horse called Spleiner", "Spear called Gungnir" });
		gods = gods->add_ordered(new God{ "Mars", "Roman", "Asteroid", "Sword" });
		gods = gods->add_ordered(new God{ "Neptune", "Roman", "Dolphin", "Trident" });
		gods = gods->add_ordered(new God{ "Zeus", "Greek", "", "lightning" });
		gods = gods->add_ordered(new God{ "Freia", "Norse", "Eagle", "Knife" });
		
		print_god(gods);
		cout << endl << endl;
	
		list_god(gods);
		cout << endl << endl;

		// Exo 11 *********************************************************************
		Link* norse_gods = new Link{"Thor"};
		norse_gods = norse_gods->insert(new Link{ "Odin" });
		norse_gods = norse_gods->insert(new Link{ "Zeus" });
		norse_gods = norse_gods->insert(new Link{ "Freia" });

		Link* greek_gods = new Link{ "Hera" };
		greek_gods = greek_gods->insert(new Link{ "Athena" });
		greek_gods = greek_gods->insert(new Link{ "Mars" });
		greek_gods = greek_gods->insert(new Link{ "Poseidon" });

		
		Link* p = greek_gods->find("Mars");
		if (p) p->value = "Ares";
		
		Link* p2 = norse_gods->find("Zeus");
		if (p2) {
			if (p2 == norse_gods)norse_gods = p2->next();
			p2->erase();
			greek_gods = greek_gods->insert(p2);
					
		}
		
		print_all(norse_gods);
		cout << endl;
		print_all(greek_gods);
		cout << endl<<endl;
		
		// Drill page 644-645 : essential operations on class ***********************************************************************************************************************************
		cout << "Construction & Destruction of objects" << endl;
		X loc{ 4};
		X loc2{ loc };
		loc=X{ 5 };
		loc2 = copy(loc);
		loc2 = copy2(loc);
		X loc3{ 6 };
		X& r = ref_to(loc);
		delete make(7);
		delete make(8);
		vector<X> v(4);
		XX loc4;
		X* ppp=new X{ 9 };
		delete ppp;
		X* pppp = new X[5];
		delete[] pppp;
		
		keep_window_open("");

		

		/*
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

		// Exo 6 *********************************************************************************************************
		// On alloue jusqu'à la 'memory exhaustion' - A priori, seules 22 créations sont possibles avant l'exception levée

		double count = 0;

		vector <double*> qcrash{};
		while (true) {	// Boucle sans fin
		++count;
		qcrash.push_back(new double[10000000]);
		cout << "Création d'un tableau de dix millions de double (1 double occupe 8 bytes/octets en RAM) : occurence n° " << count <<" à l'adresse "<< &qcrash[count-1] <<endl;
		}


		// Exo 7 *********************************************************************************************************
		char cx=0;
		int occ = 0;
		char* cc=new char[10000];	// C-style string de 10 000 caractères

		cout << "Chaque caractère saisi est stocké dans un array créé sur la free store (! pour sortir)" << endl;
		while (cin >> cx && cx != '!') {	//Tant que le caractère saisi n'est pas le point d'exclamation, on continue à stocker dans la free store
		cc[occ]=cx;
		++occ;
		}

		// On "termine" la chaine
		cc[occ] = '\0';

		// On vérifie le stockage
		cout << "La chaîne saisie est : " << cc << endl;

		// On désalloue la mémoire;
		delete cc;

		*/
	}
	
	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}

	catch (...) {	// this code is to produce error messages
		cout << "Erreur indéfinie" << endl;
		keep_window_open("q");	// For some Windows(tm) setups
	}

	keep_window_open();
}
