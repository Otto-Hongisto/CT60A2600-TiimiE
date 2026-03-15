#include "puukirjasto.h"
#include "yleinenkirjasto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


NIMIPUU *lisaaNodePuuhun(NIMIPUU *pJuuri, NIMIPUU *uusi)
{
    if (pJuuri == NULL)
        return uusi;

    if (uusi->nimiLkm < pJuuri->nimiLkm)
        pJuuri->pVasen = lisaaNodePuuhun(pJuuri->pVasen, uusi);
    else
        pJuuri->pOikea = lisaaNodePuuhun(pJuuri->pOikea, uusi);

    return pJuuri;
}

NIMIPUU *varaaMuistiPuu()
{
    NIMIPUU *pUusi = NULL;

    if ((pUusi = (NIMIPUU *)malloc(sizeof(NIMIPUU))) == NULL)
    {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    pUusi->nimi = NULL;
    pUusi->nimiLkm = 0;
    pUusi->pVasen = NULL;
    pUusi->pOikea = NULL;

    return pUusi; 
}

NIMIPUU *lueTiedotPuu()
{
    NIMIPUU *pJuuri = NULL;
    NIMIPUU *pUusi = NULL;
    FILE *tiedosto;
    char aRivi[50];
    char *tiedostonNimi = tiedostoNimi();

    if ((tiedosto = fopen(tiedostonNimi, "r")) == NULL)
    {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, 50, tiedosto); // otsikkorivi pois

    while (fgets(aRivi, 50, tiedosto) != NULL)
    {
        pUusi = varaaMuistiPuu();

        char *tokeni = strtok(aRivi, ";");
        if (tokeni == NULL)
        {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        pUusi->nimi = malloc(strlen(tokeni) + 1);
        strcpy(pUusi->nimi, tokeni);

        tokeni = strtok(NULL, ";");
        if (tokeni == NULL)
        {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        pUusi->nimiLkm = atoi(tokeni);

        // Lisää node puuhun
        pJuuri = lisaaNodePuuhun(pJuuri, pUusi);
    }

    printf("Tiedosto '%s' luettu.\n\n", tiedostonNimi);

    fclose(tiedosto);
    free(tiedostonNimi);

    return pJuuri;
}

void tulostaPuu(NIMIPUU *puu, char *tiedostoNimi) {
    FILE *TIEDOSTO = NULL;

    if ((TIEDOSTO = fopen(tiedostoNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    tulostaPuuRekursio(puu, TIEDOSTO);
    fclose(TIEDOSTO);

    return;
}

void tulostaPuuRekursio(NIMIPUU *puu, FILE *tiedosto) {
    if (puu == NULL) {
        return;
    }
    fprintf(tiedosto, "%s, %d\n", puu->nimi, puu->nimiLkm);

    tulostaPuuRekursio(puu->pVasen, tiedosto);
    tulostaPuuRekursio(puu->pOikea, tiedosto);
}

void syvyysHakuPuu(int numero, NIMIPUU *puu, char *tiedostoNimi) {
    FILE *TIEDOSTO = NULL;

    if ((TIEDOSTO = fopen(tiedostoNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    syvyysHakuRekursio(numero, puu, TIEDOSTO);
    fclose(TIEDOSTO);

    return;
}

void syvyysHakuRekursio(int numero, NIMIPUU *puu, FILE *tiedosto) {
    if (puu == NULL) {
        return;
    }
    fprintf(tiedosto, "%s, %d\n", puu->nimi, puu->nimiLkm);
    
    if (puu->nimiLkm == numero) {
        return;
    }
    syvyysHakuRekursio(numero, puu->pVasen, tiedosto);
    syvyysHakuRekursio(numero, puu->pOikea, tiedosto);
}

    void leveysHaku(NIMIPUU *puu, char *tiedostonNimi, char *haettavaNimi) {
    if (puu == NULL) {
        return;
    }
    FILE *TIEDOSTO = NULL;
    if ((TIEDOSTO = fopen(tiedostonNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    NIMIPUU *iJono[1000]; // Enintään 1000 solmua puussa (oletuksena)
    int alku = 0;
    int loppu = 0;
    iJono[loppu++] = puu; // Lisätään root jonoon

    while (alku < loppu) { // Jatkaa looppia kunnes jono tyhjä
        NIMIPUU *nykyinen = iJono[alku++]; // Otetaan ensimmäinen solmu jonosta

            fprintf(TIEDOSTO, "%s,%d\n", nykyinen->nimi, nykyinen->nimiLkm); // TUlostetaan nykyinen solmu tiedostoon

        if (strcmp(nykyinen->nimi, haettavaNimi) == 0) { // Jos nimi löytyy lopetetaan haku
            printf("Nimi löytyi!\n");
            fclose(TIEDOSTO);
            return;
        }

        if (nykyinen->pVasen != NULL) { // Lisää vasemmanpuoleisen lapsen jonoon
            iJono[loppu++] = nykyinen->pVasen;
        }
        if (nykyinen->pOikea != NULL) { // Lisää oikeanpuoleisen lapsen jonoon
            iJono[loppu++] = nykyinen->pOikea;
        }

    }
    printf("Nimeä ei löytynyt.\n"); //
    fclose(TIEDOSTO);
    return;

}

void tyhjennaPuu(NIMIPUU *puu) {
    if (puu == NULL) {
        return;
    }
    tyhjennaPuu(puu->pVasen);
    tyhjennaPuu(puu->pOikea);
    free(puu->nimi);
    free(puu);
    return;
}