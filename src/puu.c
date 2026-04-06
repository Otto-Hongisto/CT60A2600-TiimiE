#include "puu.h"
#include "yleinen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Binääripuun valikko
/// @return käyttäjän valinta
int toimintoValikkoPuu()
{
    int valinta = 0;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Luo puu tiedostosta\n");
    printf("2) Tulosta puu\n");
    printf("3) Tee syvyyshaku\n");
    printf("4) Tee leveyshaku\n");
    printf("5) Tee binäärihaku\n");
    printf("6) Poista node puusta\n");
    printf("0) Valitse datastruktuuri\n");
    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    printf("\n");
    return valinta;
}

/// @brief Palauttaa puun korkeuden rekursiivisesti
/// @brief Tyhjän puun korkeus on 0
/// @return Plauttaa tämän noden korkeuden (1 + suurenpi alipuu)
int korkeusPuu(NIMIPUU *pNode)
{
    if (pNode == NULL)
        return 0;

    // Lasketaan vasemman ja oikean alipuun korkeudet
    int vasenKorkeus = korkeusPuu(pNode->pVasen);
    int oikeaKorkeus = korkeusPuu(pNode->pOikea);

    // Valitaan suurempi korkeus
    int suurempi;
    if (vasenKorkeus > oikeaKorkeus)
        suurempi = vasenKorkeus;
    else
        suurempi = oikeaKorkeus;

    // Palautetaan tämän noden korkeus (1 + suurenpi alipuu)
    return 1 + suurempi;
}

/// @brief Käytetään AVL-puun tasapainon tarkistamiseen.
/// @return Palauttaa solmun tasapainoarvon (vasen korkeus – oikea korkeus)
int tasapainoPuu(NIMIPUU *pNode)
{
    if (pNode == NULL)
        return 0;
    return korkeusPuu(pNode->pVasen) - korkeusPuu(pNode->pOikea);
}

/// @brief Suorittaa oikean rotaation annetulle juurinodelle
/// @brief ja palauttaa sitten uuden juuren
/// @return osapuun uusi juuri (node)
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

/// @brief Suorittaa vasemman rotaation annetulle juurinodelle
/// @brief ja palauttaa sitten uuden juuren
/// @return osapuun uusi juuri (node)
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

/// @brief Lisää noden puuhun
/// @param pJuuri binääripuun juuri
/// @param pUusi node joka lisätään puuhun
/// @return Binääripuun juuri (voi olla sama)
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

/// @brief varaa muistia uudelle binääripuu nodelle ja palauttaa sen
/// @return palauttaa binääripuun noden
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

/// @brief lukee tiedoston ja tallentaa tiedot binääripuuhun node kerrallaan
/// @return binääripuun juuren (joka on node) pointerin
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
        // varaa uudelle nodelle muistia
        // Yksi rivi vastaa yhtä nodea
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

/// @brief kutsuu puun rekursiivista tulostusta
/// @param puu osoitin puun juureen
/// @param tiedostoNimi tiedosto johon polku kirjoitetaan
void tulostaPuu(NIMIPUU *puu, char *tiedostoNimi) {
    FILE *TIEDOSTO = NULL;

    if (puu == NULL) {
        printf("Puu on tyhjä.\n");
        return;
    }
    
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


/// @brief suorittaa puun tulostuksen
/// @param puu osoitin puun juureen
/// @param tiedosto tiedosto johon polku kirjoitetaan
void tulostaPuuRekursio(NIMIPUU *puu, FILE *tiedosto) {
    if (puu == NULL) {
        printf("Puu on tyhjä.\n");
        return;
    }
    //puun tulostaminen rekursiivisesti
    fprintf(tiedosto, "%s,%d\n", puu->nimi, puu->nimiLkm);
    //tietoalkioiden läpikäynti
    tulostaPuuRekursio(puu->pVasen, tiedosto);
    tulostaPuuRekursio(puu->pOikea, tiedosto);
}

/// @brief Kutsuu rekursiivista syvyyshakua
/// @param numero numero jota etsitään syvyyshaulla
/// @param puu osoitin puun juureen
/// @param tiedostoNimi tiedosto johon polku kirjoitetaan
void syvyysHakuPuu(int numero, NIMIPUU *puu, char *tiedostoNimi) {
    FILE *TIEDOSTO = NULL;

    if (puu == NULL) {
        printf("Puu on tyhjä.\n");
        return 0;
    }

    if ((TIEDOSTO = fopen(tiedostoNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    //rekursion kutsu
    syvyysHakuRekursio(numero, puu, TIEDOSTO);
    fclose(TIEDOSTO);

    return;
}

/// @brief suorittaa syvyyshaun puuhun
/// @param numero numero jota etsitään syvyyshaulla
/// @param puu osoitin puun juureen
/// @param tiedosto tiedosto johon polku kirjoitetaan
/// @return Osoitin löydettyyn alkioon
int syvyysHakuRekursio(int numero, NIMIPUU *puu, FILE *tiedosto)
{
    if (puu == NULL) {
        printf("Puu on tyhjä.\n");
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

/// @brief Suorittaa Leveyshaun (BFS) ja kirjoittaa tulokset tiedostoon
/// @param puu Osoitin puun juureen
/// @param tiedostonNimi Tiedosto, johon tulokset kirjoitetaan
/// @param haettavaNimi Merkkijono jota etsitään
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

/// @brief Vapauttaa puun varaaman muistin
/// @param puu Osoitin puun juureen
void tyhjennaPuu(NIMIPUU *puu) {
    if (puu == NULL) {
        printf("Puu on tyhjä.\n");
        return;
    }
    //puun tyhjentäminen rekursiivisesti
    tyhjennaPuu(puu->pVasen);
    tyhjennaPuu(puu->pOikea);
    if (puu->nimi != NULL) {
        free(puu->nimi); //nimen varaaman muistin vapautus
    }
    free(puu);
    printf("Puu tyhjennetty.\n")
    return;
}

/// @brief Kutsuu binäärihaun rekursiota
/// @param puu Osoitin puun juureen
/// @param haettavaNumero Numero jota etsitään binäärihaulla
/// @param tiedostonNimi Tiedosto, johon tulokset kirjoitetaan
/// @return Osoitin löydettyyn nodeen
NIMIPUU *binaariHaku(NIMIPUU *puu, int haettavaNumero, char *tiedostoNimi) {
    NIMIPUU *alkio = NULL;
    if (puu == NULL) {
        printf("Puu on tyhjä.\n");
        return NULL;
    }

    FILE *TIEDOSTO = NULL;
    //tiedoston avaus
    if ((TIEDOSTO = fopen(tiedostoNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    //rekursiivisen binaarihaun kutsuminen
    alkio = binaariHakuRekursio(puu, haettavaNumero, TIEDOSTO);
    fclose(TIEDOSTO);

    return alkio;

}

/// @brief Suorittaa binäärihaun puuhun rekursiivisesti
/// @param puu Osoitin puun juureen
/// @param haettavaNumero Numero jota etsitään binäärihaulla
/// @param tiedosto Tiedosto, johon kuljettu tie kirjoitetaan
/// @return Osoitin löydettyyn nodeen
NIMIPUU *binaariHakuRekursio(NIMIPUU *puu, int haettavaNumero, FILE *tiedosto) {
    if (puu == NULL) {
        printf("Puu on tyhjä.\n");
        return NULL;
    }

    fprintf(tiedosto, "%s,%d\n", puu->nimi, puu->nimiLkm);
    //numeron tarkistus
    if (puu->nimiLkm == haettavaNumero) {
        return puu;
    }
    //käydään läpi vasen puoli
    else if (haettavaNumero < puu->nimiLkm) {
        return binaariHakuRekursio(puu->pVasen, haettavaNumero, tiedosto);
    }
    //käydään läpi oikea puoli
    else {
        return binaariHakuRekursio(puu->pOikea, haettavaNumero, tiedosto);
    }
}

/// @brief Poistaa annetun nimen perusteella Noden puusta
/// @param puu Osoitin puun juureen
/// @param nimi Merkkijono jota etsitään
/// @return Osoitin poistettuun nodeen tai NULL jos nodea ei löydy
NIMIPUU *poistaNodePuustaNimella(NIMIPUU *puu, char *nimi) {
    if (puu == NULL) {
        return NULL;
    }

    // Jos node on leaf node ja nimi täsmää käyttäjän antamaan niin poistetaans se
    if (puu->pVasen == NULL && puu->pOikea == NULL && strcmp(puu->nimi, nimi) == 0) {
        free(puu->nimi); // Vapautetaan muistit eli positaan node ja sen nimi
        free(puu);
        printf("Node '%s' on poistettu.\n", nimi);
        return NULL; // tämä paluttaa nullin vanhemmalla nodelle
    }

    // Käydään läpi vasen puoli
    puu->pVasen = poistaNodePuustaNimella(puu->pVasen, nimi);

    // Käydään läpi oikea puoli
    puu->pOikea = poistaNodePuustaNimella(puu->pOikea, nimi);
    // Puuta ei tarvitse tasapainottaa leaf noden poistossa uudestaan
    

    return puu;
}

/// @brief Poistaa annetun numeron perusteella Noden puusta
/// @param puu Osoitin puun juureen
/// @param numero Numero jota etsitään
/// @return Osoitin poistettuun nodeen tai NULL jos nodea ei löydy
NIMIPUU *poistaNodePuustaNumerolla(NIMIPUU *puu, int numero) {
    if (puu == NULL) {
        return NULL;
    }

    // Jos haettava numero pienempi siirrytään vasemmalle
    if (numero < puu->nimiLkm) {
        puu->pVasen = poistaNodePuustaNumerolla(puu->pVasen, numero);
    }
    // Jos haettava numero suurempi siirrytään oikealle
    else if (numero > puu->nimiLkm) {
        puu->pOikea = poistaNodePuustaNumerolla(puu->pOikea, numero);
    }

    else {
        // Node löytyi, poistetaan se, 4 eri tapausta
        if (puu->pVasen == NULL && puu->pOikea == NULL) { // Jos leaf node eli ei lapsia
            free(puu->nimi); // Vapautetaan nimen varaama muisti ja sitten itse node.
            free(puu);
            return NULL; // tämä paluttaa nullin vanhemmalla nodelle
        }
        else if (puu->pVasen == NULL) { // Jos nodella on vain oikea lapsi
            NIMIPUU *temp = puu->pOikea;
            free(puu->nimi);
            free(puu);
            return temp; // Palautetaan oikea lapsi vanhemmalle nodelle
        }
        else if (puu->pOikea == NULL) { // Jos nodella on vain vasen lapsi
            NIMIPUU *temp = puu->pVasen;
            free(puu->nimi);
            free(puu);
            return temp; // Palautetaan vasen lapsi vanhemmalle nodelle
        }
        else { // Jos nodella on kaksi lasta etsitään perivä node oikealta
            NIMIPUU *temp = puu->pOikea;
            while (temp->pVasen != NULL) {
                temp = temp->pVasen;
            }
            // Kopioidaan perijän data nykyiseen nodeen
            char *tempNimi = malloc(strlen(temp->nimi) + 1);
            strcpy(tempNimi, temp->nimi);
            int tempLkm = temp->nimiLkm;

            free(puu->nimi);
            puu->nimi = tempNimi;
            puu->nimiLkm = tempLkm;
            // Poistetaan perivä node rekusiolla
            puu->pOikea = poistaNodePuustaNumerolla(puu->pOikea, tempLkm);
        }
        // Uutta tasapainaitusta ei tarvita.
    }
    return puu;
}

