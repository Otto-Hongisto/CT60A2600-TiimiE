#include "kirjasto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toimintoValikko()
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

int struktuuriValikko()
{
    int valinta = 0;
    printf("Valitse haluamasi datastruktuuri:\n");
    printf("1) Linkitetty lista\n");
    printf("2) Binääripuu\n");
    printf("0) Lopeta ohjelma\n");
    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    printf("\n");
    return valinta;
}

char *tiedostoNimi()
{
    char tiedostoNimi[30];
    char *pMuistilohko = NULL;
    printf("Anna tiedoston nimi: ");
    scanf("%s", tiedostoNimi);

    if ((pMuistilohko = (char *)malloc((strlen(tiedostoNimi) + 1)* sizeof(char))) == NULL)
    {
        perror("Muistinvaraus epäonnistui, lopetetaan ");
        exit(0);
    }
    strcpy(pMuistilohko, tiedostoNimi);
    return pMuistilohko;
}

NIMILISTA *varaaMuisti()
{
    NIMILISTA *pUusi = NULL;
    if ((pUusi = (NIMILISTA *)malloc(sizeof(NIMILISTA))) == NULL)
    {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    return pUusi;
}

NIMILISTA *lueTiedotLista()
{
    NIMILISTA *pAlku = NULL, *pLoppu = NULL;
    NIMILISTA *pUusi = NULL;
    FILE *tiedosto;
    char aRivi[50];
    char *tiedostonNimi = tiedostoNimi();

    if ((tiedosto = fopen(tiedostonNimi, "r")) == NULL)
    {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, 50, tiedosto); // otsikot pois

    while (fgets(aRivi, 50, tiedosto) != NULL)
    {
        pUusi = varaaMuisti();
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

void kirjoitaTiedosto(NIMILISTA *pAlku) {
    char *tiedostonNimi = tiedostoNimi();
    FILE *TIEDOSTO;

    if ((TIEDOSTO = fopen(tiedostonNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui");
        exit(0);
    }
    NIMILISTA *ptr = pAlku;
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

    if (ptr != NULL) {
        while (ptr->pNext != NULL) {
            ptr = ptr->pNext;
        }
    }
    

    while (ptr != NULL) {
        fprintf(TIEDOSTO, "%s,%d\n", ptr->nimi, ptr->nimiLkm);
        ptr = ptr->pPrev;
    }
    printf("Tiedosto '%s' kirjoitettu .\n", tiedostonNimi);
    fclose(TIEDOSTO);
    free(tiedostonNimi);

    return;
}

void tyhjennaMuisti1(VERKKOLISTA * lista)
{
    VERKKOLISTA *ptr;
    while (lista != NULL)
    {
        ptr = lista;
        lista = lista->next;
        free(ptr);
    }
    printf("Muisti vapautettu.\n");
}

NIMILISTA *tyhjennaMuisti(NIMILISTA *pA) {
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