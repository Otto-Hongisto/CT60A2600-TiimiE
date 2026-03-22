#include "puukirjasto.h"
#include "yleinenkirjasto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toimintoValikkoPuu()
{
    int valinta = 0;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Luo puu tiedostosta\n");
    printf("2) Tulosta puu\n");
    printf("3) Tee syvyyshaku\n");
    printf("4) Tee leveyshaku\n");
    printf("5) Tee binäärihaku\n");
    printf("0) Valitse datastruktuuri\n");
    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    printf("\n");
    return valinta;
}

int korkeusPuu(NIMIPUU *pNode)
{
    if (pNode == NULL)
        return 0;

    int vasenKorkeus = korkeusPuu(pNode->pVasen);
    int oikeaKorkeus = korkeusPuu(pNode->pOikea);

    int suurempi;
    if (vasenKorkeus > oikeaKorkeus)
        suurempi = vasenKorkeus;
    else
        suurempi = oikeaKorkeus;

    return 1 + suurempi;
}

int tasapainoPuu(NIMIPUU *pNode)
{
    if (pNode == NULL)
        return 0;
    return korkeusPuu(pNode->pVasen) - korkeusPuu(pNode->pOikea);
}

NIMIPUU *rotaatioOikeaPuu(NIMIPUU *pVanhaJuuri)
{

    // Vasen lapsi nousee uudeksi juureksi
    NIMIPUU *pUusiJuuri = pVanhaJuuri->pVasen;

    // Uuden juuren oikea alilapsi siirtyy vanhan juuren vasemmaksi lapseksi
    NIMIPUU *siirtyvaAlipuu = pUusiJuuri->pOikea;

    // Suoritetaan rotaatio
    pUusiJuuri->pOikea = pVanhaJuuri;
    pVanhaJuuri->pVasen = siirtyvaAlipuu;

    return pUusiJuuri;
}

NIMIPUU *rotaatioVasenPuu(NIMIPUU *pVanhaJuuri)
{
    // Oikea lapsi nousee uuden alipuun juureksi
    NIMIPUU *pUusiJuuri = pVanhaJuuri->pOikea;

    // Uuden juuren vasen alilapsi siirtyy vanhan juuren oikeaksi lapseksi
    NIMIPUU *siirtyvaAlipuu = pUusiJuuri->pVasen;

    // Suoritetaan rotaatio
    pUusiJuuri->pVasen = pVanhaJuuri;
    pVanhaJuuri->pOikea = siirtyvaAlipuu;

    return pUusiJuuri;
}

NIMIPUU *lisaaNodePuuhun(NIMIPUU *pJuuri, NIMIPUU *pUusi)
{
    if (pJuuri == NULL)
        return pUusi;

    // Vertaillaan ensin nimien lukumäärää
    if (pUusi->nimiLkm < pJuuri->nimiLkm)
    {
        pJuuri->pVasen = lisaaNodePuuhun(pJuuri->pVasen, pUusi);
    }
    else if (pUusi->nimiLkm > pJuuri->nimiLkm)
    {
        pJuuri->pOikea = lisaaNodePuuhun(pJuuri->pOikea, pUusi);
    }
    else
    {
        // Jos lukumäärä sama, vertaillaan nimiä aakkosjärjestyksessä
        if (strcmp(pUusi->nimi, pJuuri->nimi) < 0)
            pJuuri->pVasen = lisaaNodePuuhun(pJuuri->pVasen, pUusi);
        else
            pJuuri->pOikea = lisaaNodePuuhun(pJuuri->pOikea, pUusi);
    }

    int puunTasapaino = tasapainoPuu(pJuuri);

    // Vasemman puolen ylikuorma
    if (puunTasapaino > 1)
    {
        if (pUusi->nimiLkm < pJuuri->pVasen->nimiLkm)
            return rotaatioOikeaPuu(pJuuri); // LL-tilanne
        else
        {
            pJuuri->pVasen = rotaatioVasenPuu(pJuuri->pVasen); // LR-tilanne
            return rotaatioOikeaPuu(pJuuri);
        }
    }

    // Oikean puolen ylikuorma
    if (puunTasapaino < -1)
    {
        if (pUusi->nimiLkm > pJuuri->pOikea->nimiLkm)
            return rotaatioVasenPuu(pJuuri); // RR-tilanne
        else
        {
            pJuuri->pOikea = rotaatioOikeaPuu(pJuuri->pOikea); // RL-tilanne
            return rotaatioVasenPuu(pJuuri);
        }
    }

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

    printf("Tiedosto '%s' luettu.\n", tiedostonNimi);
    printf("\n");

    fclose(tiedosto);
    free(tiedostonNimi);

    return pJuuri;
}

void tulostaPuu(NIMIPUU *puu, char *tiedostoNimi) {
    FILE *TIEDOSTO = NULL;
    // tiedoston avaus
    if ((TIEDOSTO = fopen(tiedostoNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    //rekursion kutsu
    tulostaPuuRekursio(puu, TIEDOSTO);
    fclose(TIEDOSTO);

    return;
}

void tulostaPuuRekursio(NIMIPUU *puu, FILE *tiedosto) {
    if (puu == NULL) {
        return;
    }
    //puun tulostaminen rekursiivisesti
    fprintf(tiedosto, "%s,%d\n", puu->nimi, puu->nimiLkm);
    //tietoalkioiden läpikäynti
    tulostaPuuRekursio(puu->pVasen, tiedosto);
    tulostaPuuRekursio(puu->pOikea, tiedosto);
}

void syvyysHakuPuu(int numero, NIMIPUU *puu, char *tiedostoNimi) {
    FILE *TIEDOSTO = NULL;

    if ((TIEDOSTO = fopen(tiedostoNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    //rekursion kutsu
    syvyysHakuRekursio(numero, puu, TIEDOSTO);
    fclose(TIEDOSTO);

    return;
}

int syvyysHakuRekursio(int numero, NIMIPUU *puu, FILE *tiedosto)
{
    if (puu == NULL) {
        return 0;
    }

    fprintf(tiedosto, "%s,%d\n", puu->nimi, puu->nimiLkm);
    //etsittävän numeron tarkistus
    if (puu->nimiLkm == numero) {
        return 1;
    }
    //vasemman haaran haku
    if (syvyysHakuRekursio(numero, puu->pVasen, tiedosto)) {
        return 1;
    }
    //oikean haaran haku
    if (syvyysHakuRekursio(numero, puu->pOikea, tiedosto)) {
        return 1;
    }

    return 0;
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
    //puun tyhjentäminen rekursiivisesti
    tyhjennaPuu(puu->pVasen);
    tyhjennaPuu(puu->pOikea);
    if (puu->nimi != NULL) {
        free(puu->nimi); //nimen varaaman muistin vapautus
    }
    free(puu);
    return;
}

NIMIPUU *binaariHaku(NIMIPUU *puu, int haettavaNumero, char *tiedostoNimi) {
    NIMIPUU *alkio = NULL;
    if (puu == NULL) {
        return NULL;
    }

    FILE *TIEDOSTO = NULL;

    if ((TIEDOSTO = fopen(tiedostoNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    alkio = binaariHakuRekursio(puu, haettavaNumero, TIEDOSTO);
    fclose(TIEDOSTO);

    return alkio;

}

NIMIPUU *binaariHakuRekursio(NIMIPUU *puu, int haettavaNumero, FILE *tiedosto) {
    if (puu == NULL) {
        return NULL;
    }

    fprintf(tiedosto, "%s,%d\n", puu->nimi, puu->nimiLkm);

    if (puu->nimiLkm == haettavaNumero) {
        return puu;
    }
    else if (haettavaNumero < puu->nimiLkm) {
        return binaariHakuRekursio(puu->pVasen, haettavaNumero, tiedosto);
    }
    else {
        return binaariHakuRekursio(puu->pOikea, haettavaNumero, tiedosto);
    }
}