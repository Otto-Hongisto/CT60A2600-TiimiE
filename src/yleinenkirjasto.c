#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int kysyNumero()
{
    int numero = 0;
    printf("Anna etsittävä numero: ");
    scanf("%d", &numero);
    return numero;
}

/// @brief Tarkistaa onko merkkijono numero
/// @param merkkijono 
/// @return Palauttaa 1 jos merkkijono on numero muuten 0
int onkoNumero(char *merkkijono) {
    if (merkkijono == NULL || merkkijono[0] == '\0') {
        return 0;
    }
    for (int i = 0; i < strlen(merkkijono); i++) {
        if (!isdigit(merkkijono[i])) {
            return 0;
        }
    }
    return 1;
}

/// @brief Kysyy käyttäjältä nimen
/// @param koko 
void kysyNimi(char *koko)
{
    printf("Anna etsittävä nimi: ");
    scanf("%s", koko);
    return;
}