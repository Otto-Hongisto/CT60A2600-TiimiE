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

typedef struct nimipuu
{
    char *nimi;
    int nimiLkm;
    struct nimipuu *pVasen;
    struct nimipuu *pOikea;
} NIMIPUU;

int toimintoValikko();
int struktuuriValikko();
char *tiedostoNimi();
NIMILISTA *varaaMuisti();
NIMILISTA *lueTiedotLista();
void kirjoitaTiedosto();
void kirjoitaTiedostoTakaperin();
NIMILISTA *tyhjennaMuisti();

NIMIPUU *lueTiedotPuu();
NIMIPUU *varaaMuistiPuu();
NIMIPUU *lisaaNodePuuhun(NIMIPUU *pJuuri, NIMIPUU *uusi);

#endif // KIRJASTO_H
