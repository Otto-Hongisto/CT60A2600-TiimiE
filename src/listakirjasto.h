#ifndef LISTAKIRJASTO_H
#define LISTAKIRJASTO_H

// Nimidatan prosessointiin tiedostoista
typedef struct nimilista
{
    char* nimi;
    int nimiLkm;
    struct nimilista *pNext;
    struct nimilista *pPrev;
} NIMILISTA;

// Verkkodata prosessoimiseen (ei käytössä vielä)
typedef struct verkkolista
{
    char *yliopisto1;
    char *yliopisto2;
    int etaisyys;
    struct verkkolista *next;
    struct verkkolista *prev;
} VERKKOLISTA;

int toimintoValikkoLista();

// Tiedoston lukeminen linkitettyyn listaan
NIMILISTA *varaaMuistiLista();
NIMILISTA *lueTiedotLista(char *tiedostonNimi);
void bubbleSortNouseva(NIMILISTA *pAlku);

void lisaaAlkioListaan(NIMILISTA **pAlku, int indexUusi, char *uusiNimi, int nimiLkmUusi);
void kirjoitaTiedosto();
void kirjoitaTiedostoTakaperin();
NIMILISTA *tyhjennaMuisti();
NIMILISTA *poistaLinkitetystaListasta(NIMILISTA *pAlku, char *syote);

#endif // LISTAKIRJASTO_H
