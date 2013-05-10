/*
 * Name: Harry Beau
 * Mat#: 0815
 */

#include <iostream>
using namespace std;

class Person
{
		string name; //char
		int id;
	public:
		Person(string name, int id): name(name), id(id) {};//char
		void setName(string n) { name = n; };
		void setId(int i) { id = i; };
		string getName(void) { return name; };
		int getId(void) { return id; };
		virtual float bezahlung(void) const = 0;
};
class Angestellter : public Person
{
		float gehalt;
	public:
		Angestellter(float gehalt, string name, int id): Person(name, id), gehalt(gehalt) {};
		void setGehalt(float g) { gehalt = g; };
		float getGehalt(void) const { return gehalt; };
		float bezahlung(void) const { return gehalt; };
};
class Arbeiter : public Person
{
		float stundenlohn;
		int anzahlstunden;
	public:
		Arbeiter(float stundenlohn, int anzahlstunden, string name, int id): Person(name, id), stundenlohn(stundenlohn), anzahlstunden(anzahlstunden) {};
		void setStundenlohn(float sl) { stundenlohn = sl; };
		void setAnzahlstunden(int as) { anzahlstunden = as; };
		float getStundenlohn(void) { return stundenlohn; };
		int getAnzahlstunden(void) { return anzahlstunden; };
		float bezahlung(void) const { return stundenlohn * anzahlstunden; }
};
class Verkaeufer : public Angestellter
{
		float provision;
	public:
		Verkaeufer(float gehalt, float provision, string name, int id): Angestellter(gehalt, name, id), provision(provision) {};
		void setProvision(float p) { provision = p; };
		float getProvision(void) { return provision; };
		float bezahlung(void) const { return getGehalt() + provision; }
};

class Behaelter
{
	public:
		virtual bool insert(Person*) = 0;
		virtual bool remove(void) = 0;
		virtual bool isFull(void) = 0;
		virtual bool isEmpty(void) = 0;
		virtual const Person* getFirst(void) = 0;
		virtual bool hasNext(void) = 0;
		virtual const Person* getNext(void) = 0; //Unklar: Steht der Zeiger anfänglich VOR dem ersten Element?
};
class Queue : public Behaelter
{
		Person** PersonQueue;
		int Qsize, posinsert, posremove, pos, anz;
	public:
		Queue(): Qsize(10), posinsert(0), posremove(0), pos(0), anz(0) { PersonQueue = new Person *[Qsize]; for (int i = 0; i < Qsize; i++) PersonQueue[i] = NULL; }
		Queue(int dim): Qsize(dim), posinsert(0), posremove(0), pos(0), anz(0) { PersonQueue = new Person *[Qsize]; for (int i = 0; i < Qsize; i++) PersonQueue[i] = NULL; }
		~Queue() { for(int i = 0; i < Qsize; i++) if(PersonQueue[i]!=NULL) delete PersonQueue[i]; delete [] PersonQueue; }
		bool insert(Person * inP);
		bool remove(void);
		bool isFull(void) { return anz==Qsize; }
		bool isEmpty(void) { return anz==0; }
		const Person * getFirst(void) { return PersonQueue[pos = posremove]; }
		bool hasNext(void) { return PersonQueue[(pos + 1) % Qsize]!=NULL && (pos + 1) % Qsize != posinsert; }
		const Person * getNext(void) { return PersonQueue[pos = (pos + 1) % Qsize]; }
};
bool Queue::insert(Person* inP)
{
	if(isFull()) return false;
	else
	{
		PersonQueue[posinsert] = inP;
		if(PersonQueue[posinsert]==NULL) return false;
		else
		{
			anz++;
			posinsert = (posinsert + 1) % Qsize;
			return true;
		}
	}
}

//Inkonsitzenz in den Spezifikation: Laut A3: "Die Funktion remove() entfernt eine Person aus dem Behälter und gibt sie als Rückgabewert zurück."
bool Queue::remove(void)
{
	if(!isEmpty())
	{
		delete PersonQueue[posremove];
		PersonQueue[posremove] = NULL;
		posremove = (posremove + 1) % Qsize;
		anz--;
		return true;
	}
	else return false;
}
class Stack : public Behaelter
{
		Person** PersonStack;
		int Ssize, pos, anz;
	public:
		Stack(): Ssize(10), pos(0), anz(0) { PersonStack = new Person *[Ssize]; for (int i = 0; i < Ssize; i++) PersonStack[i] = NULL; }
		Stack(int dim): Ssize(dim), pos(0), anz(0) { PersonStack = new Person *[Ssize]; for (int i = 0; i < Ssize; i++) PersonStack[i] = NULL; }
		~Stack() { for(int i = 0; i < anz; i++) delete PersonStack[i]; delete [] PersonStack; }
		bool insert(Person * inP);
		bool remove(void);
		bool isFull(void) { return anz==Ssize; }
		bool isEmpty(void) { return anz==0; }
		const Person * getFirst(void) { return PersonStack[pos = 0]; }
		bool hasNext(void) { return pos + 1 < anz; }
		const Person* getNext(void) { return PersonStack[++pos]; } //Segmention Fault bei falscher Nutzung. Überprüfung von hasNext()?
};
bool Stack::insert(Person* inP)
{
	if(isFull()) return false;
	else
	{
		PersonStack[anz++] = inP;
		return true;
	}
}
bool Stack::remove(void)
{
	if(!isEmpty())
	{
		delete PersonStack[--anz];
		return true;
	}
	else return false;
}

int main(void)
{
	///Eines von denen auskommentieren!
	//Behaelter * pb = new Queue;
	//Behaelter * pb = new Queue(x); // fuer x beliebige Ganzzahl eingeben
	//Behaelter * pb = new Stack;
	//Behaelter * pb = new Stack(x); // fuer x beliebige Ganzzahl eingeben
	Person * p = NULL;
	string instr;
	int ini1, ini2;
	float inf1, inf2, summe;
	char in[2];
	do
	{
		cout << endl << "\t- Menu zur Behaelterklasse-" << endl
			<< "- 0 - eXit" << endl
			<< "- 1 - Angestellten einfuegen" << endl
			<< "- 2 - Arbeiter einfuegen" << endl
			<< "- 3 - Verkaeufer einfuegen" << endl
			<< "- 4 - Person loeschen" << endl
			<< "- 5 - Gehaltsumme berechnen" << endl
			<< "-   -\b\b\b" << flush;
		cin >> in;
		switch((int)(in[0]-'0'))
		{
			case 0: delete pb; break;
			case 1: cout << endl << "\t- Angestellten einfuegen -" << endl
					<< "[Id:Name:Gehalt]" << endl;
				cin >> ini1; cin >> instr; cin >> inf1;
				p = new Angestellter(inf1, instr, ini1);
				if(pb -> insert(p)) cout << "Einfuegen erfolgreich!" << endl;
				else cout << "Einfuegen fehlgeschlagen!" << endl;
				break;
			case 2: cout << endl << "\t- Arbeiter einfuegen -" << endl
					<< "[Id:Name:Stundenlohn:Stundenanzahl]" << endl;
				cin >> ini1; cin >> instr; cin >> inf1; cin >> ini2;
				p = new Arbeiter(inf1, ini2, instr, ini1);
				if(pb -> insert(p)) cout << "Einfuegen erfolgreich!" << endl;
				else cout << "Einfuegen fehlgeschlagen!" << endl;
				break;
			case 3: cout << endl << "\t- Verkaeufer einfuegen -" << endl
					<< "[Id:Name:Gehalt:Provision]" << endl;
				cin >> ini1; cin >> instr; cin >> inf1; cin >> inf2;
				p = new Verkaeufer(inf1, inf2, instr, ini1);
				if(pb -> insert(p)) cout << "Einfuegen erfolgreich!" << endl;
				else cout << "Einfuegen fehlgeschlagen!" << endl;
				break;
			case 4: if(pb -> remove()) cout << "Loeschen erfolgreich!" << endl;
				else cout << "Loeschen fehlgeschlagen!" << endl;
				break;
			case 5: if(pb -> isEmpty()) cout << "Keine Personen vorhanden!" << endl;
				else
				{
					summe = pb -> getFirst() -> bezahlung();
					while(pb -> hasNext()) summe += (pb -> getNext()) -> bezahlung();
					cout << "Gehaltssumme aller Personen: " << summe << endl;
				}
				break;
			default: cout << endl << "Ungueltige Eingabe!" << endl;
		}	
	}while(in[0]-'0');
	return 0;
}

