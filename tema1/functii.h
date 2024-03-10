#pragma once

struct CARD{
	unsigned int value;		//valoarea cartii [1, 14]
	char* simbol;			//simbolul cartii (PICA, CUPA, CARO, TREFLA)
	CARD* next, * prev;		//pointeri la anterioara si urmatoarea carte din deck
};

struct DECK {
	CARD* cap, * coada;		//pointer la prima carte din deck
	DECK* next, * prev;		//pointeri la anteriorul si urmatorul deck al jucatorului
};

struct PLAYER {
	DECK* cap, * coada;		//pointeri la primul si ultimul deck al jucatorului
};

void MENU();
void INIT_PLAYER(PLAYER&);
void INIT_DECK(DECK&);
void ADD_CARD(CARD*&, CARD*&);

void ADD_DECK(unsigned int, DECK*&, DECK*&);
//adauga packet nou la finalul listei de pachete

void DEL_DECK(unsigned int, DECK*&, DECK*&);
//sterge un pachet din lista

void DEL_CARD(unsigned int, unsigned int, DECK*&, DECK*&);
//sterge o carte dintr-un pachet

void ADD_CARDS(unsigned int, unsigned int, DECK*&, DECK*&);
//adauga intr-un pachet un nr de carti

void DECK_NUMBER(DECK*&, DECK*&);
//afiseaza cate pachete de carti se afla in lista

void DECK_LEN(unsigned int, DECK*&, DECK*&);
//afiseaza lungimea unui pachet

void SHUFFLE_DECK(unsigned int, DECK*&, DECK*&);
//inverseaza prima si a doua jumatate a unui pachet

void MERGE_DECKS(unsigned int, unsigned int, DECK*&, DECK*&);
//combina doua pachete, luand pe rand cate o carte din fiecare

void SPLIT_DECK(unsigned int, unsigned int, DECK*&, DECK*&);
//se imparte un pachet dupa un index

void REVERSE_DECK(unsigned int, DECK*&, DECK*&);
//inverseaza ordinea cartilor dintr-un pachet

void SHOW_DECK(unsigned int, DECK*, DECK*);
//afiseaza cartile dintr-un pachet

void SHOW_ALL(DECK*, DECK*);
//afiseaza toate cartile din toate pachetele

void SORT_DECK(unsigned int, DECK*, DECK*);
//sorteaza un pachet dupa valoarea cartilor de joc