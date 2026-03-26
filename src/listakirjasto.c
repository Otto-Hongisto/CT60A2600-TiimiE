#include "listakirjasto.h"
#include "yleinenkirjasto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Listan toimintavalikko
int toimintoValikkoLista()
{
    int valinta = 0;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Luo lista tiedostosta\n");
    printf("2) Kirjoita tiedot tiedostoon\n");
    printf("3) Kirjoita tiedot käänteisessä järjestyksessä\n");
    printf("4) Tyhjennä lista\n");
    printf("7) Lisää alkio listaan\n");
    printf("8) Poista linkitetystä listasta\n");
    printf("0) Valitse datastruktuuri\n");
    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    printf("\n");
    return valinta;
}

// Varaa yhdelle uudelle listanodelle muistin ja palauttaa sen
NIMILISTA *varaaMuistiLista()
{
    NIMILISTA *pUusi = NULL;
    if ((pUusi = (NIMILISTA *)malloc(sizeof(NIMILISTA))) == NULL)
    {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    
    return pUusi;
}

// Lukee tiedot tiedostosta listaan
NIMILISTA *lueTiedotLista(char *tiedostonNimi)
{
    NIMILISTA *pAlku = NULL, *pLoppu = NULL;
    NIMILISTA *pUusi = NULL;
    FILE *tiedosto;
    char aRivi[50];

    if ((tiedosto = fopen(tiedostonNimi, "r")) == NULL)
    {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, 50, tiedosto); // otsikot pois

    while (fgets(aRivi, 50, tiedosto) != NULL)
    {
        // varaa jokaiselle tiedoston riville uudelle nodelle muistia
        pUusi = varaaMuistiLista();
        char *tokeni;
        if ((tokeni = strtok(aRivi, ";")) == NULL)
        {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan .\n", aRivi);
            exit(0);
        }
        pUusi->nimi = malloc(strlen(tokeni) + 1);
        strcpy(pUusi->nimi, tokeni);
        if ((tokeni = strtok(NULL, ";")) == NULL)
        {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan .\n", aRivi);
            exit(0);
        }
        pUusi->nimiLkm = atoi(tokeni);
        
        // checks if the list is empty
        // if not empty, adds to the earlier list to prevent memory leak errors
        // Not properly tested yet
        pUusi->pNext = NULL;
        if (pAlku == NULL)
        {
            pAlku = pUusi;
            pLoppu = pUusi;
            pUusi->pPrev = NULL;
        }
        else
        {
            pUusi->pPrev = pLoppu;
            pLoppu->pNext = pUusi;
            pLoppu = pUusi;
        }
    }

    printf("Tiedosto '%s' luettu.\n\n", tiedostonNimi);
    printf("\n");

    fclose(tiedosto);
    free(tiedostonNimi);
    tiedostonNimi = NULL;

    return pAlku;
}

/// @brief Kirjoittaa listan alkiot tiedostoon
/// @param pAlku osoitin listan alkuun
void kirjoitaTiedosto(NIMILISTA *pAlku) {
    char *tiedostonNimi = tiedostoNimi();
    FILE *TIEDOSTO;

    if ((TIEDOSTO = fopen(tiedostonNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui");
        exit(0);
    }
    NIMILISTA *ptr = pAlku;
    // kirjoitetaan rivit
    while (ptr != NULL) {
        fprintf(TIEDOSTO, "%s,%d\n", ptr->nimi, ptr->nimiLkm);
        ptr = ptr->pNext;
    }
    printf("Tiedosto '%s' kirjoitettu .\n", tiedostonNimi);
    fclose(TIEDOSTO);
    free(tiedostonNimi);

    return;
}


/// @brief kirjoittaa listan takaperin tiedostoon
/// @param pAlku osoitin listan alkuun
void kirjoitaTiedostoTakaperin(NIMILISTA *pAlku) {
    char *tiedostonNimi = tiedostoNimi();
    FILE *TIEDOSTO;
    NIMILISTA *ptr = pAlku;

    if ((TIEDOSTO = fopen(tiedostonNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui");
        exit(0);
    }

    // siirrytän listan loppuun
    if (ptr != NULL) {
        while (ptr->pNext != NULL) {
            ptr = ptr->pNext;
        }
    }
    
    // kirjoitetaan rivit
    while (ptr != NULL) {
        fprintf(TIEDOSTO, "%s,%d\n", ptr->nimi, ptr->nimiLkm);
        ptr = ptr->pPrev;
    }
    printf("Tiedosto '%s' kirjoitettu .\n", tiedostonNimi);
    fclose(TIEDOSTO);
    free(tiedostonNimi);

    return;
}

void lisaaAlkioListaan(NIMILISTA **pAlku, int indexUusi, char *uusiNimi, int nimiLkmUusi) {
    char *nimiMuistilohko = NULL;
    NIMILISTA *uusiAlkio = NULL;
    NIMILISTA *ptr = *pAlku;
    NIMILISTA *ptrSeuraava = NULL;
    int index = 0;

    // tarkistetaan indexin sopivuus
    if (indexUusi < 1) {
        printf("Annettu indexi on liian pieni.\n");
        return;
    }
    // muistin varaaminen nimelle
    nimiMuistilohko = malloc(strlen(uusiNimi) + 1);
    if (nimiMuistilohko == NULL) {
        printf("Muistinvaraus ei onnistunut.\n");
        exit(1);
    }
    strcpy(nimiMuistilohko, uusiNimi);
    // luodaan uusi alkio
    uusiAlkio = varaaMuistiLista();
    uusiAlkio->nimi = nimiMuistilohko;
    uusiAlkio->nimiLkm = nimiLkmUusi;

    // tarkistetaan index = 1 tilanne
    if (indexUusi == 1) {
        uusiAlkio->pPrev = NULL;
        uusiAlkio->pNext = *pAlku;
        if (*pAlku != NULL) {
            (*pAlku)->pPrev = uusiAlkio;
        }
        *pAlku = uusiAlkio;
        return;
    }
    // edetään indexiä edeltävään alkioon
    for (index = 1; index < indexUusi - 1 && ptr != NULL; index++) {
        ptr = ptr->pNext;
    }
    // tarkistetaan, että lista jatkuu
    if (ptr == NULL) {
        free(nimiMuistilohko);
        free(uusiAlkio);
        return;
    }
    // muokataan uuden ja ympäröivien alkioiden tiedot
    ptrSeuraava = ptr->pNext;
    uusiAlkio->pNext = ptrSeuraava;
    uusiAlkio->pPrev = ptr;

    ptr->pNext = uusiAlkio;
    if (ptrSeuraava != NULL) {
        ptrSeuraava->pPrev = uusiAlkio;
    }
    printf("Uusi alkio lisätty listaan kohtaan %d\n", indexUusi);
}

/// @brief  vapauttaa listan varaaman muistin
/// @param pA osoitin listan alkuun
/// @return palauttaa tyhjennetyn osoittimen listan alkuun
NIMILISTA *tyhjennaMuisti(NIMILISTA *pA) {
    // tyhjennetään linkitetyn listan muisti
    NIMILISTA *ptr = pA;
    while (ptr != NULL) {
        pA = ptr->pNext;
        free(ptr->nimi);
        free(ptr);
        ptr = pA;
    }
    printf("Muisti vapautettu.\n");
    return(pA);
}


/// @brief Poistaa käyttäjän valitseman solmun linkitetystä listasta
/// @param pAlku Osoitin listan alkuun
NIMILISTA *poistaLinkitetystaListasta(NIMILISTA *pAlku) {
    char syote[50];
    printf("Anna poistettava nimi tai numero: "); // Kysytään käyttäjältä nimi tai numero
    scanf("%s", syote);

    // Tarkistetaan onko syöte numero vai nimi, onkoNumero() palauttaa 1 jos syote numero, muuten 0
    int syoteOnNumero = onkoNumero(syote);
    int iLuku = 0;

    if (syoteOnNumero == 1) {
        iLuku = atoi(syote);
    }

    NIMILISTA *ptr = pAlku;

    while (ptr != NULL) {
        // Apumuuttujat jotka pitää seuraavan ja edellisen solmun muistissa ennen kuin nykyinen solmu vapautetaan, tekee koodista paljon selkeämmän
        NIMILISTA *edellinen = ptr->pPrev;
        NIMILISTA *seuraava = ptr->pNext;
        int loytyi = 0;

        // Tarkistetaan löytyikö käyttäjän syöttämä nimi tai numero listasta
        if (syoteOnNumero == 1 && ptr->nimiLkm == iLuku) { // Tämän ja else if voisi yhdistää, mutta näin on ehkä selkeämpää lukea
            loytyi = 1;
        }
        else if (syoteOnNumero == 0 && strcmp(ptr->nimi, syote) == 0) {
            loytyi = 1;
        }
    
        // Jos löytyi niin poistetaan se solmu listasta
        if (loytyi == 1) {

            if (edellinen != NULL) { // Jos ei ole edellistä solmua, kyseessä on listan ensimmäinen solmu
                edellinen->pNext = seuraava;
            } else {
                pAlku = seuraava;
            }

            if (seuraava != NULL) {
                seuraava->pPrev = edellinen; // Yhdistää edellisen ja seuraavan solmun toisiinsa
            }

            free(ptr->nimi);
            free(ptr);
            printf("Poistettu '%s' listasta.\n", syote);
            return;
        }
        ptr = seuraava;
    }
    printf("Nimeä tai numeroa ei löytynyt listasta.\n");
    return;
}