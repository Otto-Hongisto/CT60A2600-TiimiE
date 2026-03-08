#include "kirjasto.h"
#include <stdio.h>

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
