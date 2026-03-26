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


void lisaaAlkioListaan(NIMILISTA **pAlku) {

    int nimiLkmUusi = 0;
    int indexUusi = 0;
    int index = 0;
    char uusiNimi[30];
    char *nimiMuistilohko = NULL;
    NIMILISTA *uusiAlkio = NULL;
    NIMILISTA *ptr= *pAlku;
    NIMILISTA *ptrSeuraava = NULL;

    printf("Mihin kohtaan listaa haluat lisätä alkion: ");
    scanf("%d", &indexUusi);

    printf("Anna lisättävä lukumäärä: ");
    scanf("%d", &nimiLkmUusi);

    printf("Anna lisättävä nimi: ");
    scanf("%s", uusiNimi);

    nimiMuistilohko = malloc(strlen(uusiNimi) + 1);
    if (nimiMuistilohko == NULL) {
        printf("Muistinvaraus ei onnistunut.");
        exit(1);    
    }
    strcpy(nimiMuistilohko, uusiNimi);

    if (indexUusi < 1) {
        free(nimiMuistilohko);
        printf("Annettu indexi on liian pieni.\n");
        return;
    }

    uusiAlkio = varaaMuistiLista();
    uusiAlkio->nimi = nimiMuistilohko;
    uusiAlkio->nimiLkm = nimiLkmUusi;

    if (indexUusi == 1) {
        uusiAlkio->pPrev = NULL;
        uusiAlkio->pNext = *pAlku;
        (*pAlku)->pPrev = uusiAlkio;
        *pAlku = uusiAlkio;
        return;
    }
    
    for (index = 1; index < indexUusi - 1 && ptr != NULL; index++) {
        ptr = ptr->pNext;
    }

    if (ptr == NULL) {
        free(nimiMuistilohko);
        free(uusiAlkio);
        return;
    }

    ptrSeuraava = ptr->pNext;

    uusiAlkio->pNext = ptrSeuraava;
    uusiAlkio->pPrev = ptr;

    ptr->pNext = uusiAlkio;
    if (ptrSeuraava != NULL) {
        ptrSeuraava->pPrev = uusiAlkio;
    }

    printf("Uusi alkio lisätty listaan kohtaan %d/n)", indexUusi);

    return;
}

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
