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
        int loytyi = 0;
        if (syoteOnNumero == 1 && ptr->nimiLkm == iLuku) {
            loytyi = 1;
        }
        else if (syoteOnNumero == 0 && strcmp(ptr->nimi, syote) == 0) {
            loytyi = 1;
        }
    

    if (loytyi == 1) {
        ptr->pPrev->pNext = ptr->pNext;
        if (ptr->pNext != NULL) {
            ptr->pNext->pPrev = ptr->pPrev;
            }

        free(ptr->nimi);
        free(ptr);
        printf("Poistettu listasta.\n");
        }

        ptr = ptr->pNext;
    }
    return pAlku;
    
}
