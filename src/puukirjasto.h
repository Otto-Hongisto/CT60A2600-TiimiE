#ifndef PUUKIRJASTO_H
#define PUUKIRJASTO_H

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
void tulostaPuu(NIMIPUU *puu);
void syvyysHakuPuu(int numero, NIMIPUU *puu);
void leveysHaku(NIMIPUU *puu, char *tiedostonNimi);
#endif // PUUKIRJASTO_H
