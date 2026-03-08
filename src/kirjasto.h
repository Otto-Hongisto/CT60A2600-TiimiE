#ifndef KIRJASTO_H
#define KIRJASTO_H

typedef struct nimilista
{
    char* nimi;
    int nimiLkm;
    struct nimilista *next;
    struct nimilista *prev;
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

#endif // KIRJASTO_H
