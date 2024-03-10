#include <iostream>
#include <string.h>
#include "functii.h"

using namespace std;

int main(void)
{
    bool exit = 0, ok;
    unsigned int param1 = 0, param2 = 0;
    char s[20];
    PLAYER jucator;

    //initializam jucatorul
    INIT_PLAYER(jucator);

    MENU();
    cout << ">>Enter de command name: ";
    cin >> s;
    while (s && exit == 0)
    {
        ok = 0;

        if (strcmp("ADD_DECK", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1;
            ADD_DECK(param1, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("DEL_DECK", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1;
            DEL_DECK(param1, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("DEL_CARD", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1 >> param2;
            DEL_CARD(param1, param2, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("ADD_CARDS", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1 >> param2;
            ADD_CARDS(param1, param2, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("DECK_NUMBER", s) == 0)
        {
            DECK_NUMBER(jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("DECK_LEN", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1;
            DECK_LEN(param1, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("SHUFFLE_DECK", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1;
            SHUFFLE_DECK(param1, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("MERGE_DECKS", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1 >> param2;
            MERGE_DECKS(param1, param2, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("SPLIT_DECK", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1 >> param2;
            SPLIT_DECK(param1, param2, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("REVERSE_DECK", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1;
            REVERSE_DECK(param1, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("SHOW_DECK", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1;
            SHOW_DECK(param1, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("SHOW_ALL", s) == 0)
        {
            SHOW_ALL(jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("SORT_DECK", s) == 0)
        {
            cout << ">>Enter the parameters: ";
            cin >> param1;
            SORT_DECK(param1, jucator.cap, jucator.coada);
            cout << endl;
            ok = 1;
        }

        if (strcmp("EXIT", s) == 0)
        {
            exit = 1;
            ok = 1;
        }

        if (ok == 0 && exit == 0)
        {
            cout << "Invalid command. Please try again.\n\n";
        }

        if (exit == 0)
        {
            cout << "\n>>Enter de command name: ";
            cin >> s;
        }
    }

    cout << "Thanks for playing my game!\n\n";

    return 0;
}
