#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int toimintoValikkoPuu()
{
    int valinta = 0;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Luo puu tiedostosta\n");
    printf("2) \n");
    printf("3) \n");
    printf("4) Tyhjennä puu\n");
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

    if ((pMuistilohko = (char *)malloc((strlen(tiedostoNimi) + 1) * sizeof(char))) == NULL)
    {
        perror("Muistinvaraus epäonnistui, lopetetaan ");
        exit(0);
    }
    strcpy(pMuistilohko, tiedostoNimi);
    return pMuistilohko;
}
