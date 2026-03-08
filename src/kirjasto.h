#ifndef KIRJASTO_H
#define KIRJASTO_H

typedef struct nimilista
{
    char* nimi;
    int nimiLkm;
    struct nimilista *next;
    struct nimilista *prev;
} Nimilista;

typedef struct verkkolista
{
    char *yliopisto1;
    char *yliopisto2;
    int etaisyys;
    struct verkkolista *next;
    struct verkkolista *prev;
} Verkkolista;

int valikko();

#endif // KIRJASTO_H
