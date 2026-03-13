#ifndef KIRJASTO_H
#define KIRJASTO_H

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

int valikko();
char *tiedostoNimi();
NIMILISTA *varaaMuisti();
NIMILISTA *lueTiedot();
void kirjoitaTiedosto();
void kirjoitaTiedostoTakaperin();
NIMILISTA *tyhjennaMuisti();

#endif // KIRJASTO_H
