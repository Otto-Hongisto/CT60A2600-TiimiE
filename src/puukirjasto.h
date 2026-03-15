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
void tulostaPuu(NIMIPUU *puu, char *tiedostoNimi);
void tulostaPuuRekursio(NIMIPUU *puu, FILE *tiedosto);
void syvyysHakuPuu(int numero, NIMIPUU *puu, char *tiedostoNimi);
void syvyysHakuRekursio(int numero, NIMIPUU *puu, FILE *tiedosto);
void leveysHaku(NIMIPUU *puu, char *tiedostonNimi);
void tyhjennaPuu(NIMIPUU *puu);
#endif // PUUKIRJASTO_H
