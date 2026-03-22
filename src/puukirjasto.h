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

int toimintoValikkoPuu();

NIMIPUU *lueTiedotPuu();
NIMIPUU *varaaMuistiPuu();
int korkeusPuu(NIMIPUU *pNode);
int tasapainoPuu(NIMIPUU *pNode);
NIMIPUU *rotaatioOikeaPuu(NIMIPUU *pVanhaJuuri);
NIMIPUU *rotaatioVasenPuu(NIMIPUU *pVanhaJuuri);
NIMIPUU *lisaaNodePuuhun(NIMIPUU *pJuuri, NIMIPUU *uusi);

void tulostaPuu(NIMIPUU *puu, char *tiedostoNimi);
void tulostaPuuRekursio(NIMIPUU *puu, FILE *tiedosto);
void syvyysHakuPuu(int numero, NIMIPUU *puu, char *tiedostoNimi);
int syvyysHakuRekursio(int numero, NIMIPUU *puu, FILE *tiedosto);
void leveysHaku(NIMIPUU *puu, char *tiedostonNimi, char *haettavaNimi);
void tyhjennaPuu(NIMIPUU *puu);
NIMIPUU *binaariHaku(NIMIPUU *puu, int haettavaNumero, char *tiedostoNimi);
NIMIPUU *binaariHakuRekursio(NIMIPUU *puu, int haettavaNumero, FILE *tiedosto);
#endif // PUUKIRJASTO_H
