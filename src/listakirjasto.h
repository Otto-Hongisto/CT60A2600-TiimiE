#ifndef LISTAKIRJASTO_H
#define LISTAKIRJASTO_H

typedef struct nimilista
{
    char* nimi;
    int nimiLkm;
    struct nimilista *pNext;
    struct nimilista *pPrev;
} NIMILISTA;

typedef struct verkkolista
{
    char *yliopisto1;
    char *yliopisto2;
    int etaisyys;
    struct verkkolista *next;
    struct verkkolista *prev;
} VERKKOLISTA;

int struktuuriValikko();
NIMILISTA *varaaMuistiLista();
NIMILISTA *lueTiedotLista(char *tiedostonNimi);
void kirjoitaTiedosto();
void kirjoitaTiedostoTakaperin();
NIMILISTA *tyhjennaMuisti();

#endif // LISTAKIRJASTO_H
