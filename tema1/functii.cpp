#include <iostream>
#include <string.h>
#include "functii.h"

using namespace std;

void MENU()
{
	cout << "\n\n\t\t\tCOMMAND LIST:\n";
	cout << "\t\t\t-------------\n";
	cout << "\tADD_DECK <numar_carti>\n";
	cout << "\tDEL_DECK <index_pachet>\n";
	cout << "\tDEL_CARD <index_pachet> <index_carte>\n";
	cout << "\tADD_CARDS <index_pachet> <numar_carti>\n";
	cout << "\tDECK_NUMBER\n";
	cout << "\tDECK_LEN <index_pachet>\n";
	cout << "\tSHUFFLE_DECK <index_pachet>\n";
	cout << "\tMERGE_DECKS <index_pachet1> <index_pachet2>\n";
	cout << "\tSPLIT_DECK <index_pachet> <index_split>\n";
	cout << "\tREVERSE_DECK <index_pachet>\n";
	cout << "\tSHOW_DECK <index_pachet>\n";
	cout << "\tSHOW_ALL\n";
	cout << "\tSORT_DECK <index_pachet>\n";
	cout << "\n\tEXIT\n";
	cout << "\t--------------------------------------------\n\n";

}

void INIT_PLAYER(PLAYER& j)
{
	j.cap = 0;
	j.coada = 0;
}

void INIT_DECK(DECK& d)
{
	d.cap = 0;
	d.coada = 0;
}

void ADD_DECK(unsigned int n, DECK*& cap, DECK*& coada)
{
	DECK* p = 0;
	CARD* p2 = 0;
	unsigned int i;

	//alocam memorie pentru pachet
	p = new DECK;
	if (p == 0)
	{
		cout << "Eroare la alocare pachet (ADD_DECK)\n";
	}
	
	//umplem pachetul
	INIT_DECK(*p);
	cout << ">>Enter deck cards (value symbol):\n";
	for (i = 0; i < n; ++i)
	{
		cout << "\tCard " << i + 1 << ": ";
		p2 = p->coada;
		ADD_CARD(p->cap, p->coada);
		if (p2 == p->coada) //verificam daca s-a pus cartea
		{
			i--;
		}
	}

	if (p->cap == 0) //numar de carti invalid
	{
		cout << "The deck couldn't be created.\n";
		delete p;
		return;
	}

	//adaugam pachetul in lista
	p->next = 0;
	p->prev = coada;
	if (cap) //mai exista deck-uri
	{
		coada->next = p;
	}
	else
	{
		cap = p; //primul deck
	}
	coada = p;

	cout << "The deck was successfully created with " << n << " cards.\n";
}

void ADD_CARD(CARD*& cap, CARD*& coada)
{
	CARD* c = 0;
	unsigned int val;
	char* s = 0;

	//alocam memorie pentru carte
	c = new CARD;
	if (c == 0)
	{
		cout << "Eroare la alocare carte (ADD_CARD)\n";
	}

	//citim perechea {valoare, simbol}
	cin >> val;

	//alocam memorie pentru simbol
	s = new char[7];
	if (s == 0)
	{
		cout << "Eroare la alocare simbol (ADD_CARD)\n";
	}
	cin.get();
	cin >> s;

	//verificam datele introduse
	if (val > 14 || val < 1 || (strcmp("PICA", s) != 0 && strcmp("CUPA", s) != 0 && strcmp("CARO", s) != 0 && strcmp("TREFLA", s) != 0))
	{
		cout << "The provided card is not a valid one.\n";
		delete[] s;
		delete c;
		return;
	}

	c->value = val;
	c->simbol = s;
	c->next = 0;
	c->prev = coada;

	if (cap) //verificam daca mai exista carti
	{
		coada->next = c;
	}
	else
	{
		cap = c;
	}
	coada = c;
}

void DEL_DECK(unsigned int poz, DECK*& cap, DECK*& coada)
{
	unsigned int i;
	DECK* d = cap;
	CARD* c = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz && d->next; ++i) //parcurgem lista de deck-uri pana la deck-ul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz) //nu exista pachetul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	if (d != cap && d != coada) //nu e primul sau ultimul deck
	{
		d->next->prev = d->prev;
		d->prev->next = d->next;
	}

	if (d == cap && d == coada) //este singurul deck
	{
		cap = 0; coada = 0;
	}
	else
		if (d == cap) //este primul deck
		{
			d->next->prev = d->prev;
			cap = d->next;
		}
		else //este ultimul deck
			{
				d->prev->next = d->next;
				coada = d->prev;
			}
	
	//dealocam memoria
	c = d->cap;
	while(c->next)
	{
		delete[] c->simbol;
		c = c->next;
		delete c->prev;
	}
	cout << "The deck " << poz << " was successfully deleted.\n";
	delete c;
	delete d;
}

void DEL_CARD(unsigned int poz_p, unsigned int poz_c, DECK*& cap, DECK*& coada)
{
	unsigned int i;
	DECK* d = cap;
	CARD* c = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz_p && d->next; ++i) //parcurgem lista de deck-uri pana la deck-ul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz_p) //nu exista deck-ul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	c = d->cap;
	for (i = 1; i < poz_c && c->next; ++i) //parcurgem lista de carti pana la cartea de pe pozitia dorita
	{
		c = c->next;
	}

	if (i < poz_c) //nu exista cartea
	{
		cout << "The provided index is out of bounds for deck "<<poz_p<<" .\n";
		return;
	}
	
	if (c != d->cap && c != d->coada) //nu e prima sau ultima carte
	{
		c->next->prev = c->prev;
		c->prev->next = c->next;
	}

	if (c == d->cap && c == d->coada) //este singura carte
	{
		DEL_DECK(poz_p, cap, coada);
		cout << "The card was successfully deleted from deck " << poz_p << " .\n";
		return;
	}
	else
		if (c == d->cap) //e prima carte
		{
			c->next->prev = c->prev;
			d->cap = c->next;
		}
		else //e ultima carte
		{
			c->prev->next = c->next;
			d->coada = c->prev;
		}

	//dealocam memoria
	delete[] c->simbol;
	delete c;
	cout << "The card was successfully deleted from deck "<<poz_p<<" .\n";
}

void ADD_CARDS(unsigned int poz_p, unsigned int nr_c, DECK*& cap, DECK*& coada)
{
	unsigned int i;
	DECK* d = cap;
	CARD* c = 0, *ci;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz_p && d->next; ++i) //parcurgem lista de pachete pana la pachetul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz_p) //nu exista deck-ul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	ci = d->coada;
	cout << ">>Enter deck cards (value symbol):\n";
	for (i = 0; i < nr_c; ++i)
	{
		cout << "\tCard " << i + 1 << ": ";
		c = d->coada;
		ADD_CARD(d->cap, d->coada);
		if (c == d->coada) //verificam daca s-a pus cartea
		{
			i--;
		}
	}

	if (d->coada == ci) //numar de carti invalid
	{
		cout << "Invalid command. Please try again.\n";
		return;
	}

	cout << "The cards were successfully added to deck " << poz_p << ".\n";
}

void DECK_NUMBER(DECK*& cap, DECK*& coada)
{
	DECK* d1 = cap, * d2 = coada;
	unsigned int i = 1;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The number of decks is "<<0<<".\n";
		return;
	}

	while (d1 != d2) //nu am ajuns la mijloc
	{
		if (d1->next == d2)
			break;
		d1 = d1->next;
		d2 = d2->prev;
		i += 2;
	}

	if (d1 != d2) //nu exista mijloc (nr par de pachete)
		i += 1;

	cout << "The number of decks is " <<i<< ".\n";
}

void DECK_LEN(unsigned int poz, DECK*& cap, DECK*& coada)
{
	unsigned int i = 1;
	DECK* d = cap;
	CARD* c1 = 0, * c2 = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz && d->next; ++i) //parcurgem lista de pachete pana la pachetul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz) //nu exista pachetul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	c1 = d->cap; c2 = d->coada;
	while (c1 != c2) //nu am ajuns la mijloc
	{
		if (c1->next == c2)
			break;
		c1 = c1->next;
		c2 = c2->prev;
		i += 2;
	}

	if (c1 != c2) //nu exista mijloc (nr par de carti)
		i += 1;

	cout << "The length of deck " << poz << " is "<<i<<".\n";
}

void SHUFFLE_DECK(unsigned int poz, DECK*& cap, DECK*& coada)
{
	unsigned int i;
	DECK* d = cap;
	CARD* c1 = 0, * c2 = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz && d->next; ++i) //parcurgem lista de pachete pana la pachetul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz) //nu exista pachetul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	if (d->cap == d->coada) //exista o singura carte in pachet
	{
		cout << "The deck " << poz << " was successfully shuffled.\n";
		return;
	}

	c1 = d->cap; c2 = d->coada;
	while (c1 != c2) //nu am ajuns la mijloc
	{
		if (c1->next == c2)
			break;
		c1 = c1->next;
		c2 = c2->prev;
	}

	if (c1 == c2) //exista mijloc (nr impar de carti)
	{
		c1 = c2->prev;
	}

	//mutam a doua jumatate la inceput
	c2->prev->next = 0;
	c2->prev = 0;
	d->coada->next = d->cap;
	d->cap = c2;
	d->coada = c1;
}

void MERGE_DECKS(unsigned int poz1, unsigned int poz2, DECK*& cap, DECK*& coada)
{
	unsigned int i, pmin, pmax;
	DECK* d1 = cap, * d2 = 0, * nd = 0;
	CARD* c = 0, * p = 0, * q = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	pmin = poz1;
	pmax = poz2;
	if (poz1 > poz2) //poz1 va fi primul deck din lista dintre cele doua deck-uri
		swap(pmin, pmax);

	for (i = 1; i < pmin && d1->next; ++i) //parcurgem lista de pachete pana la primul pachet
	{
		d1 = d1->next;
	}

	d2 = d1;
	for (; i < pmax && d2->next; ++i) //parcurgem lista de pachete pana la al doilea pachet
	{
		d2 = d2->next;
	}

	if (i < pmax) //nu exista pachetul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	if (pmin != poz1) //daca am inversat ordinea la inceput
		swap(d1, d2);

	//alocam memorie pentru pachet
	nd = new DECK;
	if (nd == 0)
	{
		cout << "Eroare la alocare pachet (MERGE_DECKS)\n";
	}

	//initializam pachetul in care se va face merge
	INIT_DECK(*nd);
	//il adaugam la lista de pachete
	coada->next = nd;
	nd->prev = coada;
	nd->next = 0;
	coada = nd;

	//schimbam legaturile deck-urilor
	nd->cap = d1->cap;
	p = d1->cap->next;
	q = d2->cap->next;
	while (d1->cap && d2->cap) //cat timp nu am ajuns la sfarsitul unuia din pachete
	{
		d1->cap->next = d2->cap;
		d2->cap->prev = d1->cap;
		d2->cap->next = p;
		if (p)
			p->prev = d2->cap;
		d1->cap = p;
		d2->cap = q;
		if (p)
			p = p->next;
		if (q)
			q = q->next;
	}

	if (d1->cap) //daca primul deck e mai lung la al doilea, coada sa va fi coada deck-ului final
		nd->coada = d1->coada;
	else
	if (d2->cap) //daca al doilea deck e mai lung ca primul, refacem legatura catre restul listei sale de carti si modificam coada
		{
			d2->cap->prev->next = d2->cap;
			nd->coada = d2->coada;
		}

	//stergem cele 2 deck-uri
	if (d1 == cap) //daca primul deck e primul din lista
	{
		//mai intai ne ocupam de legaturile celuilalt, pentru ca acesta sa nu ajunga primul
		d2->prev->next = d2->next;
		d2->next->prev = d2->prev;

		d1->next->prev = 0;
		cap = d1->next;
	}
	else
		if (d2 == cap) //daca al doilea deck e primul din lista
		{
			//mai intai ne ocupam de legaturile celuilalt, pentru ca acesta sa nu ajunga primul
			d1->prev->next = d1->next;
			d1->next->prev = d1->prev;

			d2->next->prev = 0;
			cap = d2->next;
		}
		else //cazul general
		{
			d1->prev->next = d1->next;
			d1->next->prev = d1->prev;
			d2->prev->next = d2->next;
			d2->next->prev = d2->prev;
		}

	//eliberam memoria
	delete d1;
	delete d2;

	cout << "The deck " << poz1 << " and the deck " << poz2 << " were successfully merged.\n";
}

void SPLIT_DECK(unsigned int poz_p, unsigned int poz_c, DECK*& cap, DECK*& coada)
{
	unsigned int i;
	DECK* d = cap, * nd = 0;
	CARD* c = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz_p && d->next; ++i) //parcurgem lista de pachete pana la pachetul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz_p) //nu exista pachetul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	c = d->cap;
	for (i = 1; i < poz_c && c->next; ++i) //parcurgem lista de carti pana la cartea de pe pozitia dorita
	{
		c = c->next;
	}

	if (i < poz_c || c == d->coada) //nu exista cartea
	{
		cout << "The provided index is out of bounds for deck " << poz_p << " .\n";
		return;
	}

	//alocam memorie pentru pachet
	nd = new DECK;
	if (nd == 0)
	{
		cout << "Eroare la alocare pachet (MERGE_DECKS)\n";
	}

	//initializam pachetul in care se va face split
	INIT_DECK(*nd);
	//adaugam pachetul in lista
	nd->next = d->next;
	if (d->next) //nu e ultimul pachet
	{
		d->next->prev = nd;
	}
	nd->prev = d;
	d->next = nd;
	
	//punem a doua parte de pachet in cel nou
	nd->cap = c->next;
	c->next->prev = 0;
	nd->coada = d->coada;
	
	//rupem legatura catre restul pachetului
	d->coada = c;
	c->next = 0;

	cout << "The deck " << poz_p << " was successfully split by index " << poz_c << " .\n";
}

void REVERSE_DECK(unsigned int poz, DECK*& cap, DECK*& coada)
{
	unsigned int i;
	DECK* d = cap;
	CARD* c = 0, * c2 = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz && d->next; ++i) //parcurgem lista de pachete pana la pachetul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz) //nu exista pachetul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	//primul element devine ultimul
	d->coada = d->cap;
	c = d->cap->next;
	c2 = c;
	d->cap->next = 0;

	if (c) //daca nu am ajuns la capatul listei
	{
		while (c->next) //daca mai urmeaza un element, inversam legaturile
		{
			c2 = c->next;
			c->next = d->cap;
			d->cap->prev = c;
			d->cap = c;
			c = c2;
		}

		//inversam legaturile si pentru ultima carte, care va deveni prima
		c->next = d->cap;
		d->cap->prev = c;
		c->prev = 0;
		d->cap = c2;
	}
	cout << "The deck " << poz << " was successfully reversed.\n";
}

void SHOW_DECK(unsigned int poz, DECK* cap, DECK* coada)
{
	unsigned int i;
	DECK* d = cap;
	CARD* c = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz && d->next; ++i) //parcurgem lista de pachete pana la pachetul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz) //nu exista pachetul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	cout << "Deck " << poz << ":\n";
	for (c = d->cap; c; c = c->next)
	{
		cout << "\t" << c->value << "  " << c->simbol << endl;
	}
}

void SHOW_ALL(DECK* cap, DECK* coada)
{
	unsigned int i;
	DECK* d = cap;
	CARD* c = 0;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; d; ++i)
	{
		cout << "Deck " << i << ":\n";
		for (c = d->cap; c; c = c->next) //afisam cartile din pachetul i
		{
			cout << "\t" << c->value << "  " << c->simbol << endl;
		}

		d = d->next;
	}

	if (i == 1) //nu exista pachete
	{
		cout << "The provided index is out of bounds for the deck list.\n";
	}
}

void SORT_DECK(unsigned int poz, DECK* cap, DECK* coada)
{
	unsigned int i, val1, val2;
	DECK* d = cap;
	CARD* c = 0, * c2 = 0;
	bool schimb = 1;

	if (cap == coada && cap == 0) //nu exista deck-uri
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	for (i = 1; i < poz && d->next; ++i) //parcurgem lista de pachete pana la pachetul de pe pozitia dorita
	{
		d = d->next;
	}

	if (i < poz) //nu exista pachetul
	{
		cout << "The provided index is out of bounds for the deck list.\n";
		return;
	}

	while (schimb)
	{
		schimb = 0;
		for (c = d->cap; c->next; c = c->next)
		{
			if (c->value < c->next->value)
			{
				swap(c->value, c->next->value);
				swap(c->simbol, c->next->simbol);
				schimb = 1;
			}
			else
				if (c->value == c->next->value) //daca au aceeasi valoare, verificam simbolul
				{
					if (strcmp("PICA", c->simbol) == 0)
						val1 = 1;
					if (strcmp("CUPA", c->simbol) == 0)
						val1 = 2;
					if (strcmp("CARO", c->simbol) == 0)
						val1 = 3;
					if (strcmp("TREFLA", c->simbol) == 0)
						val1 = 4;
					if (strcmp("PICA", c->next->simbol) == 0)
						val2 = 1;
					if (strcmp("CUPA", c->next->simbol) == 0)
						val2 = 2;
					if (strcmp("CARO", c->next->simbol) == 0)
						val2 = 3;
					if (strcmp("TREFLA", c->next->simbol) == 0)
						val2 = 4;

					if (val1 > val2)
					{
						swap(c->value, c->next->value);
						swap(c->simbol, c->next->simbol);
						schimb = 1;
					}
				}
		}
	}

	cout << "The deck " << poz << " was successfully sorted.\n";
}