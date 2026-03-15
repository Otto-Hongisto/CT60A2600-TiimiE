#ifndef PUUKIRJASTO_H
#define PUUKIRJASTO_H
#include <stdio.h>

typedef struct nimipuu
{
    char *nimi;
    int nimiLkm;
    struct nimipuu *pVasen;
    struct nimipuu *pOikea;
} NIMIPUU;

NIMIPUU *lueTiedotPuu();
NIMIPUU *varaaMuistiPuu();
NIMIPUU *lisaaNodePuuhun(NIMIPUU *pJuuri, NIMIPUU *uusi);
void tulostaPuu(NIMIPUU *puu, char *tiedostoNimi);
void tulostaPuuRekursio(NIMIPUU *puu, FILE *tiedosto);
void syvyysHakuPuu(int numero, NIMIPUU *puu, char *tiedostoNimi);
int syvyysHakuRekursio(int numero, NIMIPUU *puu, FILE *tiedosto);
void leveysHaku(NIMIPUU *puu, char *tiedostonNimi, char *haettavaNimi);
void tyhjennaPuu(NIMIPUU *puu);
#endif // PUUKIRJASTO_H
