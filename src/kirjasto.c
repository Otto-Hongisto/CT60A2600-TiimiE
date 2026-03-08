#include "kirjasto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valikko()
{
    int switchInput = 0;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Luo lista tiedostosta\n");
    printf("2) Kirjoita tiedot tiedostoon\n");
    printf("3) Kirjoita tiedot käänteisessä järjestyksessä\n");
    printf("4) Tyhjennä lista\n");
    printf("0) Lopeta ohjelma\n");
    printf("Anna valintasi: ");
    scanf("%d", &switchInput);
    return switchInput;
}

char *tiedostoNimi()
{
    char fileName[30];
    char *pMuistilohko = NULL;
    printf("Anna tiedoston nimi: ");
    scanf("%s", fileName);

    if ((pMuistilohko = (char *)malloc((strlen(fileName) + 1)* sizeof(char))) == NULL)
    {
        perror("Muistinvaraus epäonnistui, lopetetaan ");
        exit(0);
    }
    strcpy(pMuistilohko, fileName);
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

NIMILISTA *lueTiedot()
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

        // checks if the list is empty. if not empty, adds to that list
        // if not empty, adds to that list to prevent memory leak errors
        // this is a bit incomplete
        pUusi->next = NULL;
        if (pAlku == NULL)
        {
            pAlku = pUusi;
            pLoppu = pUusi;
        }
        else
        {
            pLoppu->next = pUusi;
            pLoppu = pUusi;
        }
    }

    printf("Tiedosto '%s' luettu.\n\n", tiedostonNimi);

    fclose(tiedosto);
    free(tiedostonNimi);
    tiedostonNimi = NULL;

    return pAlku;
}

void tyhjennaMuisti(VERKKOLISTA * lista)
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

void tyhjennaMuisti(NIMILISTA * lista)
{
    NIMILISTA *ptr;
    while (lista != NULL)
    {
        ptr = lista;
        lista = lista->next;
        free(ptr);
    }
    printf("Muisti vapautettu.\n");
}