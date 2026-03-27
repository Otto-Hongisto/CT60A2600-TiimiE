#include "listakirjasto.h"
#include "yleinenkirjasto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Listan toimintavalikko
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

/// Varaa yhdelle uudelle listanodelle muistin ja palauttaa sen
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

/// Lukee tiedot tiedostosta listaan
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

    fgets(aRivi, 50, tiedosto); /// otsikot pois

    while (fgets(aRivi, 50, tiedosto) != NULL)
    {
        /// varaa jokaiselle tiedoston riville uudelle nodelle muistia
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

/// @brief  Nouseva bubblesort
/// @param pAlku 
void bubbleSortNouseva(NIMILISTA *pAlku)
{
    if (!pAlku)
        return;

    int nodetVaihdettu;
    NIMILISTA *ptr;
    NIMILISTA *pLoppu = NULL;

    do
    {
        nodetVaihdettu = 0; // false
        ptr = pAlku;

        while (ptr->pNext != pLoppu)
        {

            // Apumuuttuja testaamaan pitääkö peräkkäisten nodejen paikkoja pakko vaihtaa
            int nodeVaihdettava = 0;

            // testaa pitääkö nimiLkm:n perusteella vaihtaa nodejen paikkoja
            if (ptr->nimiLkm > ptr->pNext->nimiLkm)
            {
                nodeVaihdettava = 1;
            }
            // testaa pitääkö nimi:n perusteella vaihtaa nodejen paikkoja
            else if (ptr->nimiLkm == ptr->pNext->nimiLkm && strcmp(ptr->nimi, ptr->pNext->nimi) > 0)
            {
                nodeVaihdettava = 1;
            }

            if (nodeVaihdettava)
            {
                // vaihda nimiLkm nodejen välillä
                int tmpLkm = ptr->nimiLkm;
                ptr->nimiLkm = ptr->pNext->nimiLkm;
                ptr->pNext->nimiLkm = tmpLkm;

                // vaihda nimi nodejen välillä
                char *temp = ptr->nimi;
                ptr->nimi = ptr->pNext->nimi;
                ptr->pNext->nimi = temp;

                nodetVaihdettu = 1;
            }
            ptr = ptr->pNext;
        }
        pLoppu = ptr;
    } while (nodetVaihdettu);
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

    //siirrytän listan loppuun
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
